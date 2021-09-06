#ifndef _SYNTAXANALYSIS_H_
#define _SYNTAXANALYSIS_H_

#include <string>
#include <vector>
#include <cassert>

#include "Error.h"
#include "IntermediateCode.h"
#include "LexicalAnalysis.h"
#include "SymbolTable.h"

using namespace std;

extern bool hasRet;
extern int whileCnt;
extern int forCnt;
extern int ifCnt;
extern int switchCnt;

class SyntaxAnalysis
{
private:
    static Token currentToken;

    static void getToken();
    // only use in error handling
    static void ungetToken();
    // preview till semicolon
    static bool previewToken(int expectedCategory);
    static Token getRelativeToken(int relativePosition);
    static void skipTo(int endCategory);

    static void parseAddOp();
    static void parseArgTable(int currentRegionId, vector<SymbolType> &argType);
    static void parseAssignStatement(int currentRegionId);
    static void parseCharString();
    static void parseCharacter();
    static void parseCompoundStatement(int currentRegionId);
    static void parseCondition(int currentRegionId, IntermediateCodeItem &leftItem, IntermediateCodeItem &rightItem, IntermediateCodeType &relaCode, int &lstart, int &lend, int &rstart, int &rend);
    static void parseConditionStatement(int currentRegionId);
    static void parseConstDefinition(int currentRegionId);
    static void parseConstDescription(int currentRegionId);
    static string parseConstValue(SymbolType &targetType);
    static void parseDeclarationHead(int currentRegionId, FunctionRetType &funcRetType, Token &funcToken);
    static void parseExpression(int currentRegionId, SymbolType &targetType, IntermediateCodeItem &result);
    static void parseFactor(int currentRegionId, SymbolType &targetType, IntermediateCodeItem &result);
    static Symbol parseIdentifier(int currentRegionId, bool isDefinition);
    static string parseInteger();
    static void parseItem(int currentRegionId, SymbolType &targetType, IntermediateCodeItem &result);
    static void parseLoopStatement(int currentRegionId);
    static void parseMainFunc(int currentRegionId);
    static void parseMultOp();
    static void parseNonRetFuncCallStatement(int currentRegionId);
    static void parseNonRetFuncDefinition(int currentRegionId);
    static void parseProgram(int currentRegionId);
    static void parseReadStatement(int currentRegionId);
    static void parseRelationOp(IntermediateCodeType &relaCode);
    static void parseRetFuncCallStatement(int currentRegionId);
    static void parseRetFuncDefinition(int currentRegionId);
    static void parseRetStatemant(int currentRegionId);
    static void parseSituationDefaultStatement(int currentRegionId);
    static void parseSituationStatement(int currentRegionId);
    static void parseSituationSubStatement(int currentRegionId, SymbolType matchType, IntermediateCodeItem matchItem, int switchSeq, int caseCnt);
    // 返回情况个数
    static int parseSituationTable(int currentRegionId, SymbolType matchType, IntermediateCodeItem matchItem, int switchSeq);
    static void parseStatement(int currentRegionId);
    static void parseStatementList(int currentRegionId);
    static int parseStep();
    static void parseTypeIdentifier();
    static int parseUnsignedInteger();
    static void parseValArgTable(int currentRegionId);
    static void parseValArgTable(int currentRegionId, string matchFuncName);
    static void parseVarDefinition(int currentRegionId);
    static void parseVarDefinitionInit(int currentRegionId);
    static void parseVarDefinitionNonInit(int currentRegionId);
    static void parseVarDescription(int currentRegionId);
    static void parseWriteStatement(int currentRegionId);

public:
    static void startSyntaxAnalyze();
};

#endif