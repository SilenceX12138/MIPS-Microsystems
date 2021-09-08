#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../include/GlobalConst.h"
#include "../include/IntermediateCode.h"
#include "../include/StreamManager.h"
#include "../include/SyntaxAnalysis.h"
#include "../include/Token.h"
#include "../include/utils.h"

using namespace std;

bool hasRet = false;
int whileCnt = 0;
int forCnt = 0;
int ifCnt = 0;
int switchCnt = 0;

Token SyntaxAnalysis::currentToken = Token();

void SyntaxAnalysis::startSyntaxAnalyze()
{
    getToken();
    parseProgram(0);
    if (Token::currentTokenPos != (int)Token::tokenList.size())
    {
        logfileStringstream << "The syntax analysis terminated unexpectedly." << endl;
    }
    return;
}

void SyntaxAnalysis::getToken()
{
    if (Token::currentTokenPos >= (int)Token::tokenList.size())
    {
        return;
    }
    if (Token::currentTokenPos > -1)
    {
        syntaxfileStringstream << Token::tokenList[Token::currentTokenPos] << endl;
    }
    Token::currentTokenPos += 1;
    if (Token::currentTokenPos == (int)Token::tokenList.size())
    {
        currentToken = Token();
        return;
    }
    currentToken = Token::tokenList[Token::currentTokenPos];
}

void SyntaxAnalysis::ungetToken()
{
    if (Token::currentTokenPos <= -1)
    {
        return;
    }
    Token::currentTokenPos -= 1;
    if (Token::currentTokenPos == -1)
    {
        currentToken = Token();
        return;
    }
    currentToken = Token::tokenList[Token::currentTokenPos];
}

Token SyntaxAnalysis::getRelativeToken(int relativePosition)
{
    int tempPos = Token::currentTokenPos + relativePosition;
    assert(tempPos >= 0 && tempPos < (int)Token::tokenList.size());
    return Token::tokenList[tempPos];
}

bool SyntaxAnalysis::previewToken(int expectedCategory)
{
    for (int i = Token::currentTokenPos + 1; i < int(Token::tokenList.size()); i++)
    {
        if (Token::tokenList[i].isTypeof(expectedCategory))
        {
            return true;
        }
        else if (Token::tokenList[i].isTypeof(SEMICN))
        {
            return false;
        }
    }
    return false;
}

void SyntaxAnalysis::skipTo(int endCategory)
{
    while (!currentToken.isTypeof(endCategory))
    {
        getToken();
    }
}

// <加法运算符> ::= +|-
void SyntaxAnalysis::parseAddOp()
{
    assert(currentToken.isTypeof(PLUS) || currentToken.isTypeof(MINU));
    getToken();
}

// <参数表> ::= <类型标识符><标识符>{,<类型标识符><标识符>}|<空>
void SyntaxAnalysis::parseArgTable(int currentRegionId, vector<SymbolType> &argType)
{
    SymbolType tempArgType = UndefSymType;
    Token tempArgToken;
    while (currentToken.isTypeof(INTTK) || currentToken.isTypeof(CHARTK))
    {
        tempArgType = tokenType2SymbolType(currentToken);
        parseTypeIdentifier();
        argType.push_back(tempArgType);
        tempArgToken = currentToken;
        parseIdentifier(currentRegionId, true);
        SymbolTable::insertSym(currentRegionId, tempArgToken, VarSym, tempArgType);
        if (!currentToken.isTypeof(COMMA))
        {
            break;
        }
        getToken();
    }
    syntaxfileStringstream << "<参数表>" << endl;
}

// <赋值语句> ::= <标识符>＝<表达式>|<标识符>'['<表达式>']'=<表达式>|<标识符>'['<表达式>']''['<表达式>']'=<表达式>
void SyntaxAnalysis::parseAssignStatement(int currentRegionId)
{
    Token tempToken = currentToken;
    Symbol targetSymbol;
    SymbolType tempExprType = UndefSymType;
    IntermediateCodeItem leftItem, rightItem, arrItem, idx1 = nullItem, idx2 = nullItem;
    targetSymbol = parseIdentifier(currentRegionId, false);
    if (targetSymbol.getKind() == ConstSym)
    {
        Error::outputError(getRelativeToken(-1).getLineNumber(), ConstModification);
    }
    if (currentToken.isTypeof(LBRACK))
    {
        getToken();
        tempToken = currentToken;
        tempExprType = UndefSymType;
        parseExpression(currentRegionId, tempExprType, idx1);
        if (tempExprType != IntSym)
        {
            Error::outputError(tempToken.getLineNumber(), IllegalArrayIndex);
        }
        if (!currentToken.isTypeof(RBRACK))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), RbrackMissing);
            ungetToken();
        }
        getToken();
        if (currentToken.isTypeof(LBRACK))
        {
            getToken();
            tempToken = currentToken;
            tempExprType = UndefSymType;
            parseExpression(currentRegionId, tempExprType, idx2);
            if (tempExprType != IntSym)
            {
                Error::outputError(tempToken.getLineNumber(), IllegalArrayIndex);
            }
            if (!currentToken.isTypeof(RBRACK))
            {
                Error::outputError(getRelativeToken(-1).getLineNumber(), RbrackMissing);
                ungetToken();
            }
            getToken();
        }
    }
    assert(currentToken.isTypeof(ASSIGN));
    getToken();
    tempExprType = UndefSymType;
    parseExpression(currentRegionId, tempExprType, rightItem);
    if (idx1.isTypeof(UndefItem))
    {
        leftItem = IntermediateCodeItem::create(SymItem, to_string(targetSymbol.getId()));
        IntermediateCode::insert(Assign, {rightItem, leftItem});
    }
    else
    {
        arrItem = IntermediateCodeItem::create(SymItem, to_string(targetSymbol.getId()));
        IntermediateCodeItem idxItem;
        if (!idx2.isTypeof(UndefItem))
        {
            idxItem = IntermediateCodeItem::create(SymItem, to_string(SymbolTable::createTempInt(currentRegionId)));
            IntermediateCode::insert(Mult, {idx1, IntermediateCodeItem::create(ImmIntItem, to_string(targetSymbol.getArrDim(1))), idxItem});
            IntermediateCode::insert(Add, {idxItem, idx2, idxItem});
        }
        else
        {
            idxItem = idx1;
        }
        IntermediateCode::insert(SaveArr, {arrItem, idxItem, rightItem});
    }
    syntaxfileStringstream << "<赋值语句>" << endl;
}

// <字符串> ::= "{十进制编码为32,33,35-126的ASCII字符}"
void SyntaxAnalysis::parseCharString()
{
    assert(currentToken.isTypeof(STRCON));
    getToken();
    syntaxfileStringstream << "<字符串>" << endl;
}

// <字符> ::= '<加法运算符>'|'<乘法运算符>'|'<字母>'|'<数字>'
void SyntaxAnalysis::parseCharacter()
{
    assert(currentToken.isTypeof(CHARCON));
    getToken();
}

// <复合语句> ::= [<常量说明>][<变量说明>]<语句列>
void SyntaxAnalysis::parseCompoundStatement(int currentRegionId)
{
    if (currentToken.isTypeof(RBRACE))
    {
        parseStatementList(currentRegionId);
        SymbolTable::setFuncMemImg(currentRegionId);
        syntaxfileStringstream << "<复合语句>" << endl;
        return;
    }
    if (currentToken.isTypeof(CONSTTK))
    {
        parseConstDescription(currentRegionId);
    }
    while (currentToken.isTypeof(INTTK) || currentToken.isTypeof(CHARTK))
    {
        parseVarDescription(currentRegionId);
    }
    parseStatementList(currentRegionId);
    SymbolTable::setFuncMemImg(currentRegionId);
    syntaxfileStringstream << "<复合语句>" << endl;
}

// <条件> ::= <表达式><关系运算符><表达式>
void SyntaxAnalysis::parseCondition(int currentRegionId, IntermediateCodeItem &leftItem, IntermediateCodeItem &rightItem, IntermediateCodeType &relaCode, int &lstart, int &lend, int &rstart, int &rend)
{
    Token tempToken = currentToken;
    SymbolType targetType = UndefSymType;
    lstart = IntermediateCode::intermediateCodeList.size();
    parseExpression(currentRegionId, targetType, leftItem);
    lend = IntermediateCode::intermediateCodeList.size();
    if (targetType != IntSym)
    {
        Error::outputError(tempToken.getLineNumber(), IllegalConditionType);
    }
    parseRelationOp(relaCode);
    tempToken = currentToken;
    targetType = UndefSymType;
    rstart = IntermediateCode::intermediateCodeList.size();
    parseExpression(currentRegionId, targetType, rightItem);
    rend = IntermediateCode::intermediateCodeList.size();
    if (targetType != IntSym)
    {
        Error::outputError(tempToken.getLineNumber(), IllegalConditionType);
    }
    syntaxfileStringstream << "<条件>" << endl;
}

// <条件语句> ::= if'('<条件>')'<语句>[else<语句>]
void SyntaxAnalysis::parseConditionStatement(int currentRegionId)
{
    int lstart, rstart, lend, rend;
    IntermediateCodeItem leftItem, rightItem;
    IntermediateCodeType relaCode = UndefCode;
    int ifSeq = ifCnt++;
    assert(currentToken.isTypeof(IFTK));
    getToken();
    assert(currentToken.isTypeof(LPARENT));
    getToken();
    parseCondition(currentRegionId, leftItem, rightItem, relaCode, lstart, lend, rstart, rend);
    IntermediateCode::insert(revLogic(relaCode), {leftItem, rightItem, IntermediateCodeItem::create(LabelItem, "else_$" + to_string(ifSeq))});
    if (!currentToken.isTypeof(RPARENT))
    {
        Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
        ungetToken();
    }
    getToken();
    parseStatement(currentRegionId);
    IntermediateCode::insert(GOTO, {IntermediateCodeItem::create(LabelItem, "if_end_$" + to_string(ifSeq))});
    IntermediateCode::insert(Label, {IntermediateCodeItem::create(LabelItem, "else_$" + to_string(ifSeq))});
    if (currentToken.isTypeof(ELSETK))
    {
        getToken();
        parseStatement(currentRegionId);
    }
    IntermediateCode::insert(Label, {IntermediateCodeItem::create(LabelItem, "if_end_$" + to_string(ifSeq))});
    syntaxfileStringstream << "<条件语句>" << endl;
}

// <常量定义> ::= int<标识符>＝<整数>{,<标识符>＝<整数>}|char<标识符>＝<字符>{,<标识符>＝<字符>}
void SyntaxAnalysis::parseConstDefinition(int currentRegionId)
{
    assert(currentToken.isTypeof(INTTK) || currentToken.isTypeof(CHARTK));
    char tempCharacter;
    Token tempConstToken;
    SymbolType tempConstType = tokenType2SymbolType(currentToken);
    getToken();
    while (true)
    {
        tempConstToken = currentToken;
        parseIdentifier(currentRegionId, true);
        assert(currentToken.isTypeof(ASSIGN));
        getToken();
        if (tempConstType == IntSym)
        {
            string tempInteger = parseInteger();
            SymbolTable::insertSym(currentRegionId, tempConstToken, ConstSym, IntSym, stoi(tempInteger));
        }
        else
        {
            tempCharacter = currentToken.getText()[0];
            parseCharacter();
            SymbolTable::insertSym(currentRegionId, tempConstToken, ConstSym, CharSym, tempCharacter);
        }
        if (!currentToken.isTypeof(COMMA))
        {
            break;
        }
        getToken();
    }
    syntaxfileStringstream << "<常量定义>" << endl;
}

// <常量说明> ::= const<常量定义>;{ const<常量定义>;}
void SyntaxAnalysis::parseConstDescription(int currentRegionId)
{
    assert(currentToken.isTypeof(CONSTTK));
    while (currentToken.isTypeof(CONSTTK))
    {
        getToken();
        parseConstDefinition(currentRegionId);
        if (!currentToken.isTypeof(SEMICN))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), SemicnMissing);
            ungetToken();
        }
        getToken();
    }
    syntaxfileStringstream << "<常量说明>" << endl;
}

// <常量> ::= <整数>|<字符>
string SyntaxAnalysis::parseConstValue(SymbolType &targetType)
{
    string tempConstVal = "";
    if (currentToken.isTypeof(CHARCON))
    {
        tempConstVal = currentToken.getText();
        parseCharacter();
        targetType = CharSym;
    }
    if (currentToken.isTypeof(PLUS) || currentToken.isTypeof(MINU) || currentToken.isTypeof(INTCON))
    {
        tempConstVal = parseInteger();
        targetType = IntSym;
    }
    syntaxfileStringstream << "<常量>" << endl;
    return tempConstVal;
}

// <声明头部> ::= int<标识符>|char<标识符>
void SyntaxAnalysis::parseDeclarationHead(int currentRegionId, FunctionRetType &funcRetType, Token &funcToken)
{
    assert(currentToken.isTypeof(INTTK) || currentToken.isTypeof(CHARTK));
    funcRetType = tokenType2RetType(currentToken);
    getToken();
    funcToken = currentToken;
    parseIdentifier(currentRegionId, true);
    syntaxfileStringstream << "<声明头部>" << endl;
}

// <表达式> ::= [＋|－]<项>{<加法运算符><项>}
void SyntaxAnalysis::parseExpression(int currentRegionId, SymbolType &targetType, IntermediateCodeItem &result)
{
    IntermediateCodeItem op1, op2, tempResult;
    Token tempAddOp;
    if (currentToken.isTypeof(PLUS) || currentToken.isTypeof(MINU))
    {
        targetType = IntSym;
        parseAddOp();
        tempAddOp = getRelativeToken(-1);
    }
    parseItem(currentRegionId, targetType, op1);
    if (tempAddOp.isTypeof(PLUS) || tempAddOp.isTypeof(MINU))
    {
        tempResult = IntermediateCodeItem::create(SymItem, to_string(SymbolTable::createTempInt(currentRegionId)));
        IntermediateCode::insert(tempAddOp.isTypeof(PLUS) ? Add : Sub, {IntermediateCodeItem::create(RegItem, "0"), op1, tempResult});
        op1 = tempResult;
    }
    else
    {
        tempResult = op1;
    }
    while (currentToken.isTypeof(PLUS) || currentToken.isTypeof(MINU))
    {
        targetType = IntSym;
        parseAddOp();
        tempAddOp = getRelativeToken(-1);
        parseItem(currentRegionId, targetType, op2);
        tempResult = IntermediateCodeItem::create(SymItem, to_string(SymbolTable::createTempInt(currentRegionId)));
        IntermediateCode::insert(tempAddOp.isTypeof(PLUS) ? Add : Sub, {op1, op2, tempResult});
        op1 = tempResult;
    }
    result = tempResult;
    syntaxfileStringstream << "<表达式>" << endl;
}

// <因子> ::= <标识符>|<标识符>'['<表达式>']'|<标识符>'['<表达式>']''['<表达式>']'|'('<表达式>')'|<整数>|<字符>|<有返回值函数调用语句>
void SyntaxAnalysis::parseFactor(int currentRegionId, SymbolType &targetType, IntermediateCodeItem &result)
{
    if (currentToken.isTypeof(LPARENT))
    {
        targetType = IntSym;
        getToken();
        parseExpression(currentRegionId, targetType, result);
        if (!currentToken.isTypeof(RPARENT))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
            ungetToken();
        }
        getToken();
        syntaxfileStringstream << "<因子>" << endl;
        return;
    }
    if (currentToken.isTypeof(CHARCON))
    {
        if (targetType == UndefSymType)
        {
            targetType = CharSym;
        }
        if (targetType == CharSym)
        {
            result = IntermediateCodeItem::create(ImmCharItem, currentToken.getText());
        }
        else
        {
            result = IntermediateCodeItem::create(ImmIntItem, to_string((int)currentToken.getText()[0]));
        }
        getToken();
        syntaxfileStringstream << "<因子>" << endl;
        return;
    }
    if (SymbolTable::isRetFunc(currentToken.getText()))
    {
        if (targetType == UndefSymType)
        {
            targetType = SymbolTable::getFuncByName(currentToken.getText()).getRetType() == CharRet ? CharSym : IntSym;
        }
        parseRetFuncCallStatement(currentRegionId);
        result = IntermediateCodeItem::create(SymItem, to_string(targetType == CharSym ? SymbolTable::createTempChar(currentRegionId) : SymbolTable::createTempInt(currentRegionId)));
        IntermediateCode::insert(Assign, {IntermediateCodeItem::create(RegItem, "2"), result}); // 将$v0赋值给临时变量作为函数返回值
        syntaxfileStringstream << "<因子>" << endl;
        return;
    }
    if (currentToken.isTypeof(PLUS) || currentToken.isTypeof(MINU) || currentToken.isTypeof(INTCON))
    {
        targetType = IntSym;
        string tempInteger = parseInteger();
        result = IntermediateCodeItem::create(ImmIntItem, tempInteger);
        syntaxfileStringstream << "<因子>" << endl;
        return;
    }
    Symbol varFactor = parseIdentifier(currentRegionId, false);
    targetType = (varFactor.getType() == CharSym && targetType == UndefSymType) ? CharSym : IntSym;
    IntermediateCodeItem idx1 = nullItem, idx2 = nullItem;
    while (currentToken.isTypeof(LBRACK))
    {
        getToken();
        Token tempToken = currentToken;
        SymbolType targetExpType = UndefSymType;
        parseExpression(currentRegionId, targetExpType, idx1.isTypeof(UndefItem) ? idx1 : idx2);
        if (targetExpType != IntSym)
        {
            Error::outputError(tempToken.getLineNumber(), IllegalArrayIndex);
        }
        if (!currentToken.isTypeof(RBRACK))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), RbrackMissing);
            ungetToken();
        }
        getToken();
    }
    if (idx1.isTypeof(UndefItem))
    {
        result = IntermediateCodeItem::create(SymItem, to_string(varFactor.getId()));
    }
    else
    {
        IntermediateCodeItem arrItem = IntermediateCodeItem::create(SymItem, to_string(varFactor.getId()));
        IntermediateCodeItem idxItem, tempResult;
        tempResult = IntermediateCodeItem::create(SymItem, to_string(targetType == CharSym ? SymbolTable::createTempChar(currentRegionId) : SymbolTable::createTempInt(currentRegionId)));
        if (!idx2.isTypeof(UndefItem))
        {
            idxItem = IntermediateCodeItem::create(SymItem, to_string(SymbolTable::createTempInt(currentRegionId)));
            IntermediateCode::insert(Mult, {idx1, IntermediateCodeItem::create(ImmIntItem, to_string(varFactor.getArrDim(1))), idxItem});
            IntermediateCode::insert(Add, {idxItem, idx2, idxItem});
        }
        else
        {
            idxItem = idx1;
        }
        IntermediateCode::insert(LoadArr, {arrItem, idxItem, tempResult});
        result = tempResult;
    }
    syntaxfileStringstream << "<因子>" << endl;
}

// <标识符> ::= <字母>{<字母>|<数字>}
Symbol SyntaxAnalysis::parseIdentifier(int currentRegionId, bool isDefinition)
{
    assert(currentToken.isTypeof(IDENFR));
    Symbol tempSym = Symbol();
    if (!isDefinition)
    {
        if (!SymbolTable::searchInAllRegion(currentRegionId, currentToken.getLowerText(), tempSym))
        {
            Error::outputError(currentToken.getLineNumber(), UndefinedName);
        }
    }
    getToken();
    return tempSym;
}

// <整数> ::= [＋|－]<无符号整数>
string SyntaxAnalysis::parseInteger()
{
    string coef = "";
    if (currentToken.isTypeof(PLUS) || currentToken.isTypeof(MINU))
    {
        coef = currentToken.getText();
        parseAddOp();
    }
    parseUnsignedInteger();
    syntaxfileStringstream << "<整数>" << endl;
    return coef + getRelativeToken(-1).getText();
}

// <项> ::= <因子>{<乘法运算符><因子>}
void SyntaxAnalysis::parseItem(int currentRegionId, SymbolType &targetType, IntermediateCodeItem &result)
{
    IntermediateCodeItem op1, op2, tempResult;
    Token tempMultOp;
    parseFactor(currentRegionId, targetType, op1);
    tempResult = op1;
    while (currentToken.isTypeof(MULT) || currentToken.isTypeof(DIV))
    {
        targetType = IntSym;
        parseMultOp();
        tempMultOp = getRelativeToken(-1);
        parseFactor(currentRegionId, targetType, op2);
        tempResult = IntermediateCodeItem::create(SymItem, to_string(SymbolTable::createTempInt(currentRegionId)));
        IntermediateCode::insert(tempMultOp.isTypeof(MULT) ? Mult : Div, {op1, op2, tempResult});
        op1 = tempResult;
    }
    result = tempResult;
    syntaxfileStringstream << "<项>" << endl;
}

// <循环语句> ::= while'('<条件>')'<语句>|for'('<标识符>＝<表达式>;<条件>;<标识符>＝<标识符>(+|-)<步长>')'<语句>
void SyntaxAnalysis::parseLoopStatement(int currentRegionId)
{
    SymbolType tempExprType = UndefSymType;
    int lstart, rstart, lend, rend;
    IntermediateCodeItem leftItem, rightItem;
    IntermediateCodeType relaCode = UndefCode;
    assert(currentToken.isTypeof(WHILETK) || currentToken.isTypeof(FORTK));
    if (currentToken.isTypeof(WHILETK))
    {
        int whileSeq = whileCnt++;
        getToken();
        assert(currentToken.isTypeof(LPARENT));
        getToken();
        parseCondition(currentRegionId, leftItem, rightItem, relaCode, lstart, lend, rstart, rend);
        IntermediateCode::insert(revLogic(relaCode), {leftItem, rightItem, IntermediateCodeItem::create(LabelItem, "while_end_$" + to_string(whileSeq))});
        IntermediateCode::insert(Label, {IntermediateCodeItem::create(LabelItem, "while_head_$" + to_string(whileSeq))});
        if (!currentToken.isTypeof(RPARENT))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
            ungetToken();
        }
        getToken();
        parseStatement(currentRegionId);
        IntermediateCode::dup(lstart, lend);
        IntermediateCode::dup(rstart, rend);
        IntermediateCode::insert(relaCode, {leftItem, rightItem, IntermediateCodeItem::create(LabelItem, "while_head_$" + to_string(whileSeq))});
        IntermediateCode::insert(Label, {IntermediateCodeItem::create(LabelItem, "while_end_$" + to_string(whileSeq))});
        syntaxfileStringstream << "<循环语句>" << endl;
        return;
    }
    if (currentToken.isTypeof(FORTK))
    {
        Symbol loopVar, tempSym1, tempSym2;
        int step;
        int forSeq = forCnt++;
        getToken();
        assert(currentToken.isTypeof(LPARENT));
        getToken();
        loopVar = parseIdentifier(currentRegionId, false);
        assert(currentToken.isTypeof(ASSIGN));
        getToken();
        tempExprType = UndefSymType;
        IntermediateCodeItem targetItem;
        parseExpression(currentRegionId, tempExprType, targetItem);
        IntermediateCode::insert(Assign, {targetItem, IntermediateCodeItem::create(SymItem, to_string(loopVar.getId()))});
        if (!currentToken.isTypeof(SEMICN))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), SemicnMissing);
            ungetToken();
        }
        getToken();
        parseCondition(currentRegionId, leftItem, rightItem, relaCode, lstart, lend, rstart, rend);
        IntermediateCode::insert(revLogic(relaCode), {leftItem, rightItem, IntermediateCodeItem::create(LabelItem, "for_end_$" + to_string(forSeq))});
        IntermediateCode::insert(Label, {IntermediateCodeItem::create(LabelItem, "for_head_$" + to_string(forSeq))});
        if (!currentToken.isTypeof(SEMICN))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), SemicnMissing);
            ungetToken();
        }
        getToken();
        tempSym1 = parseIdentifier(currentRegionId, false);
        assert(currentToken.isTypeof(ASSIGN));
        getToken();
        tempSym2 = parseIdentifier(currentRegionId, false);
        assert(currentToken.isTypeof(PLUS) || currentToken.isTypeof(MINU));
        step = currentToken.isTypeof(PLUS) ? 1 : -1;
        getToken();
        step *= parseStep();
        if (!currentToken.isTypeof(RPARENT))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
            ungetToken();
        }
        getToken();
        parseStatement(currentRegionId);
        IntermediateCode::insert(Add, {IntermediateCodeItem::create(SymItem, to_string(tempSym1.getId())), IntermediateCodeItem::create(ImmIntItem, to_string(step)), IntermediateCodeItem::create(SymItem, to_string(tempSym2.getId()))});
        IntermediateCode::dup(lstart, lend);
        IntermediateCode::dup(rstart, rend);
        IntermediateCode::insert(relaCode, {leftItem, rightItem, IntermediateCodeItem::create(LabelItem, "for_head_$" + to_string(forSeq))});
        IntermediateCode::insert(Label, {IntermediateCodeItem::create(LabelItem, "for_end_$" + to_string(forSeq))});
        syntaxfileStringstream << "<循环语句>" << endl;
        return;
    }
    logfileStringstream << "Something wrong with SyntaxAnalysis::parseLoopStatement(currentRegionId)" << endl;
}

// <主函数> ::= void main'('')''{'<复合语句>'}'
void SyntaxAnalysis::parseMainFunc(int currentRegionId)
{
    assert(currentToken.isTypeof(VOIDTK));
    getToken();
    Token tempFuncToken = currentToken;
    vector<SymbolType> tempArgType;
    assert(currentToken.isTypeof(MAINTK));
    getToken();
    assert(currentToken.isTypeof(LPARENT));
    getToken();
    if (!currentToken.isTypeof(RPARENT))
    {
        Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
        ungetToken();
    }
    int tempFuncId = SymbolTable::insertSym(currentRegionId, tempFuncToken, FuncSym, VoidRet, tempArgType);
    IntermediateCode::insert(Label, {IntermediateCodeItem::create(LabelItem, tempFuncToken.getText())});
    getToken();
    assert(currentToken.isTypeof(LBRACE));
    getToken();
    parseCompoundStatement(tempFuncId);
    IntermediateCode::insert(Ret, {});
    assert(currentToken.isTypeof(RBRACE));
    getToken();
    syntaxfileStringstream << "<主函数>" << endl;
}

// <乘法运算符> ::= *|/
void SyntaxAnalysis::parseMultOp()
{
    assert(currentToken.isTypeof(MULT) || currentToken.isTypeof(DIV));
    getToken();
}

// <无返回值函数调用语句> ::= <标识符>'('<值参数表>')'
void SyntaxAnalysis::parseNonRetFuncCallStatement(int currentRegionId)
{
    Token tempFuncToken = currentToken;
    assert(SymbolTable::isNonRetFunc(tempFuncToken.getText()));
    getToken();
    assert(currentToken.isTypeof(LPARENT));
    getToken();
    parseValArgTable(currentRegionId, tempFuncToken.getText());
    Symbol func = SymbolTable::getFuncByName(tempFuncToken.getText());
    IntermediateCode::insert(Call, {IntermediateCodeItem::create(LabelItem, func.getName())});
    if (!currentToken.isTypeof(RPARENT))
    {
        Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
        ungetToken();
    }
    getToken();
    syntaxfileStringstream << "<无返回值函数调用语句>" << endl;
}

// <无返回值函数定义> ::= void<标识符>'('<参数表>')''{'<复合语句>'}'
void SyntaxAnalysis::parseNonRetFuncDefinition(int currentRegionId)
{
    assert(currentToken.isTypeof(VOIDTK));
    getToken();
    Token tempFuncToken = currentToken;
    vector<SymbolType> tempArgType;
    parseIdentifier(currentRegionId, true);
    int tempFuncId = SymbolTable::insertSym(currentRegionId, tempFuncToken, FuncSym, VoidRet, tempArgType);
    IntermediateCode::insert(Label, {IntermediateCodeItem::create(LabelItem, tempFuncToken.getText())});
    assert(currentToken.isTypeof(LPARENT));
    getToken();
    parseArgTable(tempFuncId, tempArgType);
    SymbolTable::updateSym(tempFuncId, tempArgType);
    if (!currentToken.isTypeof(RPARENT))
    {
        Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
        ungetToken();
    }
    getToken();
    assert(currentToken.isTypeof(LBRACE));
    getToken();
    parseCompoundStatement(tempFuncId);
    IntermediateCode::insert(Ret, {});
    assert(currentToken.isTypeof(RBRACE));
    getToken();
    syntaxfileStringstream << "<无返回值函数定义>" << endl;
}

// <程序> ::= [<常量说明>][<变量说明>]{<有返回值函数定义>|<无返回值函数定义>}<主函数>
void SyntaxAnalysis::parseProgram(int currentRegionId)
{
    if (currentToken.isTypeof(CONSTTK))
    {
        parseConstDescription(currentRegionId);
    }
    if (!getRelativeToken(2).isTypeof(LPARENT))
    {
        parseVarDescription(currentRegionId);
    }
    SymbolTable::setFuncMemImg(0);
    while (currentToken.isTypeof(VOIDTK) || currentToken.isTypeof(INTTK) || currentToken.isTypeof(CHARTK))
    {
        if (currentToken.isTypeof(VOIDTK))
        {
            if (getRelativeToken(1).isTypeof(MAINTK))
            {
                break;
            }
            parseNonRetFuncDefinition(currentRegionId);
        }
        else
        {
            parseRetFuncDefinition(currentRegionId);
        }
    }
    parseMainFunc(currentRegionId);
    syntaxfileStringstream << "<程序>" << endl;
}

// <读语句> ::= scanf'('<标识符>')'
void SyntaxAnalysis::parseReadStatement(int currentRegionId)
{
    assert(currentToken.isTypeof(SCANFTK));
    getToken();
    assert(currentToken.isTypeof(LPARENT));
    getToken();
    Token tempToken = currentToken;
    Symbol targetSymbol = parseIdentifier(currentRegionId, false);
    if (targetSymbol.getKind() == ConstSym)
    {
        Error::outputError(getRelativeToken(-1).getLineNumber(), ConstModification);
    }
    IntermediateCode::insert(Read, {IntermediateCodeItem::create(SymItem, to_string(targetSymbol.getId()))});
    if (!currentToken.isTypeof(RPARENT))
    {
        Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
        ungetToken();
    }
    getToken();
    syntaxfileStringstream << "<读语句>" << endl;
}

// <关系运算符> ::= <|<=|>|>=|!=|==
void SyntaxAnalysis::parseRelationOp(IntermediateCodeType &relaCode)
{
    if (currentToken.isTypeof(LSS) || currentToken.isTypeof(LEQ) || currentToken.isTypeof(GRE) || currentToken.isTypeof(GEQ) || currentToken.isTypeof(NEQ) || currentToken.isTypeof(EQL))
    {
        relaCode = token2RelaCode(currentToken);
        getToken();
        return;
    }
    logfileStringstream << "There is something wrong with SyntaxAnalysis::parseRelationOp()" << endl;
}

// <有返回值函数调用语句> ::= <标识符>'('<值参数表>')'
void SyntaxAnalysis::parseRetFuncCallStatement(int currentRegionId)
{
    Token tempFuncToken = currentToken;
    assert(SymbolTable::isRetFunc(tempFuncToken.getText()));
    getToken();
    assert(currentToken.isTypeof(LPARENT));
    getToken();
    parseValArgTable(currentRegionId, tempFuncToken.getText());
    Symbol func = SymbolTable::getFuncByName(tempFuncToken.getText());
    IntermediateCode::insert(Call, {IntermediateCodeItem::create(LabelItem, func.getName())});
    if (!currentToken.isTypeof(RPARENT))
    {
        Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
        ungetToken();
    }
    getToken();
    syntaxfileStringstream << "<有返回值函数调用语句>" << endl;
}

// <有返回值函数定义> ::= <声明头部>'('<参数表>')''{'<复合语句>'}'
void SyntaxAnalysis::parseRetFuncDefinition(int currentRegionId)
{
    FunctionRetType tempRetType = UndefRetType;
    Token tempFuncToken = currentToken;
    vector<SymbolType> tempArgType;
    parseDeclarationHead(currentRegionId, tempRetType, tempFuncToken);
    int tempFuncId = SymbolTable::insertSym(currentRegionId, tempFuncToken, FuncSym, tempRetType, tempArgType);
    IntermediateCode::insert(Label, {IntermediateCodeItem::create(LabelItem, tempFuncToken.getText())});
    assert(currentToken.isTypeof(LPARENT));
    getToken();
    parseArgTable(tempFuncId, tempArgType);
    SymbolTable::updateSym(tempFuncId, tempArgType);
    if (!currentToken.isTypeof(RPARENT))
    {
        Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
        ungetToken();
    }
    getToken();
    assert(currentToken.isTypeof(LBRACE));
    getToken();
    hasRet = false;
    parseCompoundStatement(tempFuncId);
    if (!hasRet)
    {
        Error::outputError(currentToken.getLineNumber(), IllegalRetFunc);
    }
    assert(currentToken.isTypeof(RBRACE));
    getToken();
    syntaxfileStringstream << "<有返回值函数定义>" << endl;
}

// <返回语句> ::= return['('<表达式>')']
void SyntaxAnalysis::parseRetStatemant(int currentRegionId)
{
    hasRet = true;
    assert(currentToken.isTypeof(RETURNTK));
    getToken();
    FunctionRetType matchRet = SymbolTable::getRegionById(currentRegionId).getRetType();
    if (matchRet == UndefRetType)
    {
        Error::outputError(currentToken.getLineNumber(), UndefinedName);
    }
    if (matchRet == VoidRet)
    {
        if (!currentToken.isTypeof(SEMICN))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), IllegalNonRetFunc); // probably \n after return
            skipTo(SEMICN);
        }
        IntermediateCode::insert(Ret, {});
    }
    else
    {
        if (!currentToken.isTypeof(LPARENT))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), IllegalRetFunc);
            skipTo(SEMICN);
        }
        else
        {
            getToken();
            if (currentToken.isTypeof(RPARENT))
            {
                Error::outputError(currentToken.getLineNumber(), IllegalRetFunc);
                skipTo(SEMICN);
            }
            else
            {
                Token tempToken = currentToken;
                SymbolType targetType = UndefSymType;
                IntermediateCodeItem targetItem;
                parseExpression(currentRegionId, targetType, targetItem);
                if ((targetType == IntSym && matchRet != IntRet) || (targetType == CharSym && matchRet != CharRet))
                {
                    Error::outputError(tempToken.getLineNumber(), IllegalRetFunc);
                }
                IntermediateCode::insert(Ret, {targetItem});
                if (!currentToken.isTypeof(RPARENT))
                {
                    Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
                    ungetToken();
                }
                getToken();
            }
        }
    }
    syntaxfileStringstream << "<返回语句>" << endl;
}

// <缺省> ::= default:<语句>
void SyntaxAnalysis::parseSituationDefaultStatement(int currentRegionId)
{
    assert(currentToken.isTypeof(DEFAULTTK));
    getToken();
    assert(currentToken.isTypeof(COLON));
    getToken();
    parseStatement(currentRegionId);
    syntaxfileStringstream << "<缺省>" << endl;
}

// <情况语句> ::= switch'('<表达式>')''{'<情况表><缺省>'}'
void SyntaxAnalysis::parseSituationStatement(int currentRegionId)
{
    assert(currentToken.isTypeof(SWITCHTK));
    getToken();
    assert(currentToken.isTypeof(LPARENT));
    getToken();
    SymbolType matchType = UndefSymType;
    IntermediateCodeItem targetItem;
    int switchSeq = switchCnt++;
    int caseCnt = 0;
    parseExpression(currentRegionId, matchType, targetItem);
    if (!currentToken.isTypeof(RPARENT))
    {
        Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
        ungetToken();
    }
    getToken();
    assert(currentToken.isTypeof(LBRACE));
    getToken();
    caseCnt = parseSituationTable(currentRegionId, matchType, targetItem, switchSeq);
    IntermediateCode::insert(Label, {IntermediateCodeItem::create(LabelItem, "switch_$" + to_string(switchSeq) + "_case_$" + to_string(caseCnt))});
    if (!currentToken.isTypeof(DEFAULTTK))
    {
        Error::outputError(currentToken.getLineNumber(), DefaultStatementMissing);
    }
    else
    {
        parseSituationDefaultStatement(currentRegionId);
    }
    IntermediateCode::insert(Label, {IntermediateCodeItem::create(LabelItem, "switch_end_$" + to_string(switchSeq))});
    assert(currentToken.isTypeof(RBRACE));
    getToken();
    syntaxfileStringstream << "<情况语句>" << endl;
}

// <情况子语句> ::= case<常量>:<语句>
void SyntaxAnalysis::parseSituationSubStatement(int currentRegionId, SymbolType matchType, IntermediateCodeItem matchItem, int switchSeq, int caseCnt)
{
    assert(currentToken.isTypeof(CASETK));
    getToken();
    Token tempToken = currentToken;
    SymbolType targetType = UndefSymType;
    string tempConst = parseConstValue(targetType);
    if (matchType != targetType)
    {
        Error::outputError(currentToken.getLineNumber(), ConstTypeMismatch);
    }
    IntermediateCode::insert(Label, {IntermediateCodeItem::create(LabelItem, "switch_$" + to_string(switchSeq) + "_case_$" + to_string(caseCnt))});
    IntermediateCode::insert(BNE, {matchItem, IntermediateCodeItem::create(targetType == CharSym ? ImmCharItem : ImmIntItem, tempConst), IntermediateCodeItem::create(LabelItem, "switch_$" + to_string(switchSeq) + "_case_$" + to_string(caseCnt + 1))});
    assert(currentToken.isTypeof(COLON));
    getToken();
    parseStatement(currentRegionId);
    IntermediateCode::insert(GOTO, {IntermediateCodeItem::create(LabelItem, "switch_end_$" + to_string(switchSeq))});
    syntaxfileStringstream << "<情况子语句>" << endl;
}

// <情况表> ::= <情况子语句>{<情况子语句>}
int SyntaxAnalysis::parseSituationTable(int currentRegionId, SymbolType matchType, IntermediateCodeItem matchItem, int switchSeq)
{
    int caseCnt = 0;
    while (currentToken.isTypeof(CASETK))
    {
        parseSituationSubStatement(currentRegionId, matchType, matchItem, switchSeq, caseCnt);
        caseCnt++;
    }
    syntaxfileStringstream << "<情况表>" << endl;
    return caseCnt;
}

// <语句> ::= <循环语句>|<条件语句>|<有返回值函数调用语句>;|<无返回值函数调用语句>;|<赋值语句>;|<读语句>;|<写语句>;|<情况语句>|<空>;|<返回语句>;|'{'<语句列>'}'
void SyntaxAnalysis::parseStatement(int currentRegionId)
{
    if (currentToken.isTypeof(SEMICN))
    {
        getToken();
        syntaxfileStringstream << "<语句>" << endl;
        return;
    }
    if (currentToken.isTypeof(WHILETK) || currentToken.isTypeof(FORTK))
    {
        parseLoopStatement(currentRegionId);
        syntaxfileStringstream << "<语句>" << endl;
        return;
    }
    if (currentToken.isTypeof(IFTK))
    {
        parseConditionStatement(currentRegionId);
        syntaxfileStringstream << "<语句>" << endl;
        return;
    }
    if (currentToken.isTypeof(SWITCHTK))
    {
        parseSituationStatement(currentRegionId);
        syntaxfileStringstream << "<语句>" << endl;
        return;
    }
    if (currentToken.isTypeof(SCANFTK))
    {
        parseReadStatement(currentRegionId);
        if (!currentToken.isTypeof(SEMICN))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), SemicnMissing);
            ungetToken();
        }
        getToken();
        syntaxfileStringstream << "<语句>" << endl;
        return;
    }
    if (currentToken.isTypeof(PRINTFTK))
    {
        parseWriteStatement(currentRegionId);
        if (!currentToken.isTypeof(SEMICN))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), SemicnMissing);
            ungetToken();
        }
        getToken();
        syntaxfileStringstream << "<语句>" << endl;
        return;
    }
    if (currentToken.isTypeof(RETURNTK))
    {
        parseRetStatemant(currentRegionId);
        if (!currentToken.isTypeof(SEMICN))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), SemicnMissing);
            ungetToken();
        }

        getToken();
        syntaxfileStringstream << "<语句>" << endl;
        return;
    }
    if (currentToken.isTypeof(LBRACE))
    {
        getToken();
        parseStatementList(currentRegionId);
        assert(currentToken.isTypeof(RBRACE));
        getToken();
        syntaxfileStringstream << "<语句>" << endl;
        return;
    }
    if (previewToken(ASSIGN))
    {
        parseAssignStatement(currentRegionId);
        if (!currentToken.isTypeof(SEMICN))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), SemicnMissing);
            ungetToken();
        }
        getToken();
        syntaxfileStringstream << "<语句>" << endl;
        return;
    }
    if (SymbolTable::isRetFunc(currentToken.getText()))
    {
        parseRetFuncCallStatement(currentRegionId);
        if (!currentToken.isTypeof(SEMICN))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), SemicnMissing);
            ungetToken();
        }
        getToken();
        syntaxfileStringstream << "<语句>" << endl;
        return;
    }
    if (SymbolTable::isNonRetFunc(currentToken.getText()))
    {
        parseNonRetFuncCallStatement(currentRegionId);
        if (!currentToken.isTypeof(SEMICN))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), SemicnMissing);
            ungetToken();
        }
        getToken();
        syntaxfileStringstream << "<语句>" << endl;
        return;
    }
    parseIdentifier(currentRegionId, false); // must be a statement with SEMICN starting with unknown varFactor
    skipTo(SEMICN);
    getToken();
}

// <语句列> ::= {<语句>} ::= <语句>{<语句>}|<空>
void SyntaxAnalysis::parseStatementList(int currentRegionId)
{
    while (currentToken.isTypeof(WHILETK) || currentToken.isTypeof(FORTK) || currentToken.isTypeof(IFTK) || currentToken.isTypeof(IDENFR) || currentToken.isTypeof(SCANFTK) || currentToken.isTypeof(PRINTFTK) || currentToken.isTypeof(SWITCHTK) || currentToken.isTypeof(SEMICN) || currentToken.isTypeof(RETURNTK) || currentToken.isTypeof(LBRACE))
    {
        parseStatement(currentRegionId);
    }
    syntaxfileStringstream << "<语句列>" << endl;
}

// <步长> ::= <无符号整数>
int SyntaxAnalysis::parseStep()
{
    int step = parseUnsignedInteger();
    syntaxfileStringstream << "<步长>" << endl;
    return step;
}

// <类型标识符> ::= int|char
void SyntaxAnalysis::parseTypeIdentifier()
{
    assert(currentToken.isTypeof(INTTK) || currentToken.isTypeof(CHARTK));
    getToken();
}

// <无符号整数> ::= <数字>{<数字>}
int SyntaxAnalysis::parseUnsignedInteger()
{
    assert(currentToken.isTypeof(INTCON));
    int val = currentToken.getValue();
    getToken();
    syntaxfileStringstream << "<无符号整数>" << endl;
    return val;
}

// <值参数表> ::= <表达式>{,<表达式>}|<空>
void SyntaxAnalysis::parseValArgTable(int currentRegionId, string matchFuncName)
{
    Symbol matchFunc;
    matchFunc = SymbolTable::getFuncByName(matchFuncName);
    if (matchFunc.getKind() == UndefSymKind)
    {
        Error::outputError(currentToken.getLineNumber(), UndefinedName);
    }
    vector<SymbolType> tempArgType, matchArgType = matchFunc.getArgType();
    SymbolType targetType = UndefSymType;
    vector<IntermediateCodeItem> argList;
    while (currentToken.isTypeof(PLUS) || currentToken.isTypeof(MINU) || currentToken.isTypeof(IDENFR) || currentToken.isTypeof(LPARENT) || currentToken.isTypeof(INTCON) || currentToken.isTypeof(CHARCON))
    {
        targetType = UndefSymType;
        IntermediateCodeItem targetItem;
        parseExpression(currentRegionId, targetType, targetItem);
        argList.push_back(targetItem);
        tempArgType.push_back(targetType);
        if (!currentToken.isTypeof(COMMA))
        {
            break;
        }
        getToken();
    }
    for (int i = 0; i < (int)argList.size(); i++)
    {
        IntermediateCode::insert(PushArg, {argList[i], IntermediateCodeItem::create(ImmIntItem, to_string(i)), IntermediateCodeItem::create(LabelItem, matchFunc.getName())});
    }
    if (tempArgType.size() != matchArgType.size())
    {
        Error::outputError(currentToken.getLineNumber(), ArgCountMismatch);
    }
    else
    {
        for (int i = 0; i < (int)tempArgType.size(); i++)
        {
            if (tempArgType[i] != matchArgType[i])
            {
                Error::outputError(currentToken.getLineNumber(), ArgTypeMismatch);
            }
        }
    }
    syntaxfileStringstream << "<值参数表>" << endl;
}

// <变量定义> ::= <变量定义无初始化>|<变量定义及初始化>
void SyntaxAnalysis::parseVarDefinition(int currentRegionId)
{
    if (previewToken(ASSIGN))
    {
        parseVarDefinitionInit(currentRegionId);
        syntaxfileStringstream << "<变量定义>" << endl;
        return;
    }
    parseVarDefinitionNonInit(currentRegionId);
    syntaxfileStringstream << "<变量定义>" << endl;
}

// <变量定义及初始化> ::= <类型标识符><标识符>=<常量>|<类型标识符><标识符>'['<无符号整数>']'='{'<常量>{,<常量>}'}'|<类型标识符><标识符>'['<无符号整数>']''['<无符号整数>']'='{''{'<常量>{,<常量>}'}'{,'{'<常量>{,<常量>}'}'}'}'
void SyntaxAnalysis::parseVarDefinitionInit(int currentRegionId)
{
    SymbolType defSymbolType = tokenType2SymbolType(currentToken);
    parseTypeIdentifier();
    Token tempVarToken = currentToken;
    parseIdentifier(currentRegionId, true);
    Symbol targetSymbol;
    SymbolType targetType = UndefSymType;
    IntermediateCodeItem immItem, arrItem, idxItem;
    string tempConst;
    if (currentToken.isTypeof(ASSIGN))
    {
        SymbolTable::insertSym(currentRegionId, tempVarToken, VarSym, defSymbolType);
        getToken();
        tempConst = parseConstValue(targetType);
        if (targetType != defSymbolType)
        {
            Error::outputError(currentToken.getLineNumber(), ConstTypeMismatch);
        }
        // When `ConstTypeMismatch` error occurs, the codeItem should be created based on the wrong type to avoid illegal call of `create`.
        immItem = (targetType == CharSym) ? IntermediateCodeItem::create(ImmCharItem, tempConst) : IntermediateCodeItem::create(ImmIntItem, tempConst);
        targetSymbol = SymbolTable::globalSymTable.back();
        IntermediateCode::insert(Assign, {immItem, IntermediateCodeItem::create(SymItem, to_string(targetSymbol.getId()))});
        syntaxfileStringstream << "<变量定义及初始化>" << endl;
        return;
    }
    if (currentToken.isTypeof(LBRACK))
    {
        getToken();
        vector<int> defineArrayDim(2);
        vector<int> initArrayDim(2);
        if (!currentToken.isTypeof(INTCON))
        {
            Error::outputError(currentToken.getLineNumber(), IllegalArrayIndex);
            getToken();
        }
        else
        {
            defineArrayDim[0] = currentToken.getValue();
            parseUnsignedInteger();
        }
        if (!currentToken.isTypeof(RBRACK))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), RbrackMissing);
            ungetToken();
        }
        getToken();
        if (!currentToken.isTypeof(LBRACK))
        {
            SymbolTable::insertSym(currentRegionId, tempVarToken, ArrSym, defSymbolType, defineArrayDim);
            assert(currentToken.isTypeof(ASSIGN));
            getToken();
            assert(currentToken.isTypeof(LBRACE));
            getToken();
            while (!currentToken.isTypeof(RBRACE))
            {
                tempConst = parseConstValue(targetType);
                if (targetType != defSymbolType)
                {
                    Error::outputError(currentToken.getLineNumber(), ConstTypeMismatch);
                }
                targetSymbol = SymbolTable::globalSymTable.back();
                arrItem = IntermediateCodeItem::create(SymItem, to_string(targetSymbol.getId()));
                idxItem = IntermediateCodeItem::create(ImmIntItem, to_string(initArrayDim[0]));
                immItem = (targetType == CharSym) ? IntermediateCodeItem::create(ImmCharItem, tempConst) : IntermediateCodeItem::create(ImmIntItem, tempConst);
                IntermediateCode::insert(SaveArr, {arrItem, idxItem, immItem});
                initArrayDim[0] += 1;
                if (!currentToken.isTypeof(COMMA))
                {
                    break;
                }
                getToken();
            }
            if (initArrayDim[0] != defineArrayDim[0])
            {
                Error::outputError(currentToken.getLineNumber(), ArrayInitMismatch);
            }
            assert(currentToken.isTypeof(RBRACE));
            getToken();
            syntaxfileStringstream << "<变量定义及初始化>" << endl;
        }
        else
        {
            getToken();
            if (!currentToken.isTypeof(INTCON))
            {
                Error::outputError(currentToken.getLineNumber(), IllegalArrayIndex);
                getToken();
            }
            else
            {
                defineArrayDim[1] = currentToken.getValue();
                parseUnsignedInteger();
            }
            if (!currentToken.isTypeof(RBRACK))
            {
                Error::outputError(getRelativeToken(-1).getLineNumber(), RbrackMissing);
                ungetToken();
            }
            getToken();
            SymbolTable::insertSym(currentRegionId, tempVarToken, ArrSym, defSymbolType, defineArrayDim);
            assert(currentToken.isTypeof(ASSIGN));
            getToken();
            assert(currentToken.isTypeof(LBRACE));
            getToken();
            int currentInitDim = 0;
            while (!currentToken.isTypeof(RBRACE))
            {
                currentInitDim = 0;
                assert(currentToken.isTypeof(LBRACE));
                getToken();
                while (!currentToken.isTypeof(RBRACE))
                {
                    tempConst = parseConstValue(targetType);
                    if (targetType != defSymbolType)
                    {
                        Error::outputError(currentToken.getLineNumber(), ConstTypeMismatch);
                    }
                    targetSymbol = SymbolTable::globalSymTable.back();
                    arrItem = IntermediateCodeItem::create(SymItem, to_string(targetSymbol.getId()));
                    idxItem = IntermediateCodeItem::create(ImmIntItem, to_string(initArrayDim[0] * defineArrayDim[1] + currentInitDim));
                    immItem = (targetType == CharSym) ? IntermediateCodeItem::create(ImmCharItem, tempConst) : IntermediateCodeItem::create(ImmIntItem, tempConst);
                    IntermediateCode::insert(SaveArr, {arrItem, idxItem, immItem});
                    currentInitDim += 1;
                    if (!currentToken.isTypeof(COMMA))
                    {
                        break;
                    }
                    getToken();
                }
                if (currentInitDim != defineArrayDim[1])
                {
                    Error::outputError(currentToken.getLineNumber(), ArrayInitMismatch);
                }
                assert(currentToken.isTypeof(RBRACE));
                getToken();
                initArrayDim[0] += 1;
                if (!currentToken.isTypeof(COMMA))
                {
                    break;
                }
                getToken();
            }
            if (initArrayDim[0] != defineArrayDim[0])
            {
                Error::outputError(currentToken.getLineNumber(), ArrayInitMismatch);
            }
            assert(currentToken.isTypeof(RBRACE));
            getToken();
            syntaxfileStringstream << "<变量定义及初始化>" << endl;
            return;
        }
        return;
    }
    logfileStringstream << "Something wrong with SyntaxAnalysis::parseVarDefinitionInit()." << endl;
}

// <变量定义无初始化> ::= <类型标识符>(<标识符>|<标识符>'['<无符号整数>']'|<标识符>'['<无符号整数>']''['<无符号整数>']'){,(<标识符>|<标识符>'['<无符号整数>']'|<标识符>'['<无符号整数>']''['<无符号整数>']')}
void SyntaxAnalysis::parseVarDefinitionNonInit(int currentRegionId)
{
    SymbolType defSymbolType = tokenType2SymbolType(currentToken);
    parseTypeIdentifier();
    Token tempVarToken;
    while (true)
    {
        tempVarToken = currentToken;
        parseIdentifier(currentRegionId, true);
        if (!currentToken.isTypeof(LBRACK))
        {
            SymbolTable::insertSym(currentRegionId, tempVarToken, VarSym, defSymbolType);
        }
        else
        {
            vector<int> defineArrayDim;
            while (currentToken.isTypeof(LBRACK))
            {
                getToken();
                if (!currentToken.isTypeof(INTCON))
                {
                    defineArrayDim.push_back(0);
                    Error::outputError(currentToken.getLineNumber(), IllegalArrayIndex);
                    getToken();
                }
                else
                {
                    defineArrayDim.push_back(currentToken.getValue());
                    parseUnsignedInteger();
                }
                if (!currentToken.isTypeof(RBRACK))
                {
                    Error::outputError(getRelativeToken(-1).getLineNumber(), RbrackMissing);
                    ungetToken();
                }
                getToken();
            }
            if (defineArrayDim.size() == 1)
            {
                defineArrayDim.push_back(0);
            }
            SymbolTable::insertSym(currentRegionId, tempVarToken, ArrSym, defSymbolType, defineArrayDim);
        }
        if (!currentToken.isTypeof(COMMA))
        {
            break;
        }
        getToken();
    }
    syntaxfileStringstream << "<变量定义无初始化>" << endl;
}

// <变量说明> ::= <变量定义>;{<变量定义>;}
void SyntaxAnalysis::parseVarDescription(int currentRegionId)
{
    while ((currentToken.isTypeof(INTTK) || currentToken.isTypeof(CHARTK)) && !getRelativeToken(2).isTypeof(LPARENT)) // the only conflict is with <有返回值函数定义>
    {
        parseVarDefinition(currentRegionId);
        if (!currentToken.isTypeof(SEMICN))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), SemicnMissing);
            ungetToken();
        }
        getToken();
    }
    syntaxfileStringstream << "<变量说明>" << endl;
}

// <写语句> ::= printf'('<字符串>,<表达式>')'|printf'('<字符串>')'|printf'('<表达式>')'
void SyntaxAnalysis::parseWriteStatement(int currentRegionId)
{
    assert(currentToken.isTypeof(PRINTFTK));
    getToken();
    assert(currentToken.isTypeof(LPARENT));
    getToken();
    SymbolType tempExprType = UndefSymType;
    IntermediateCodeItem targetItem;
    if (!currentToken.isTypeof(STRCON))
    {
        tempExprType = UndefSymType;
        parseExpression(currentRegionId, tempExprType, targetItem);
        IntermediateCodeItem tempItem;
        // 输出时可能需要类型转换
        if (!Error::hasError && targetItem.isTypeof(SymItem) && targetItem.getSym().getType() != tempExprType)
        {
            tempItem = IntermediateCodeItem::create(SymItem, to_string(tempExprType == CharSym ? SymbolTable::createTempChar(currentRegionId) : SymbolTable::createTempInt(currentRegionId)));
            IntermediateCode::insert(Assign, {targetItem, tempItem});
            targetItem = tempItem;
        }
        if (!currentToken.isTypeof(RPARENT))
        {
            Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
            ungetToken();
        }
        IntermediateCode::insert(Write, {targetItem});
        getToken();
        IntermediateCode::insert(WriteOver, {});
        syntaxfileStringstream << "<写语句>" << endl;
        return;
    }
    parseCharString();
    string tempStr = getRelativeToken(-1).getText();
    tempStr = omitEscape(tempStr);
    if (currentToken.isTypeof(COMMA))
    {
        getToken();
        tempExprType = UndefSymType;
        parseExpression(currentRegionId, tempExprType, targetItem);
        IntermediateCodeItem tempItem;
        // 输出时可能需要类型转换
        if (!Error::hasError && targetItem.isTypeof(SymItem) && targetItem.getSym().getType() != tempExprType)
        {
            tempItem = IntermediateCodeItem::create(SymItem, to_string(tempExprType == CharSym ? SymbolTable::createTempChar(currentRegionId) : SymbolTable::createTempInt(currentRegionId)));
            IntermediateCode::insert(Assign, {targetItem, tempItem});
            targetItem = tempItem;
        }
        IntermediateCode::insert(Write, {IntermediateCodeItem::create(StrItem, to_string(SymbolTable::createGlobalStr(tempStr)))});
        IntermediateCode::insert(Write, {targetItem});
    }
    else
    {
        IntermediateCode::insert(Write, {IntermediateCodeItem::create(StrItem, to_string(SymbolTable::createGlobalStr(tempStr)))});
    }
    if (!currentToken.isTypeof(RPARENT))
    {
        Error::outputError(getRelativeToken(-1).getLineNumber(), RparentMissing);
        ungetToken();
    }
    getToken();
    IntermediateCode::insert(WriteOver, {});
    syntaxfileStringstream << "<写语句>" << endl;
}
