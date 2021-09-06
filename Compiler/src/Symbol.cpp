#include <algorithm>
#include <iomanip>
#include <iostream>

#include "../include/Symbol.h"

using namespace std;

int Symbol::symbolCnt = 0; // GLOBAL's symbol id is 0, valid symbol's id starts at 1.
Symbol nullSym = Symbol();

Symbol::Symbol()
{
    id = -1;
    validRegionId = -1;
    symbolToken = Token();
    symbolKind = UndefSymKind;
    symbolType = UndefSymType;
    constIntValue = 0;
    constCharValue = '\0';
    constStrValue = "";
    arrayDim.clear();
    retType = UndefRetType;
    argType.clear();
    stackframeSize = -1;
    addr = -1;
}

Symbol::Symbol(const Symbol &s)
{
    this->id = s.id;
    this->validRegionId = s.validRegionId;
    this->symbolToken = s.symbolToken;
    this->symbolKind = s.symbolKind;
    this->symbolType = s.symbolType;
    this->constIntValue = s.constIntValue;
    this->constCharValue = s.constCharValue;
    this->constStrValue = s.constStrValue;
    this->arrayDim = s.arrayDim;
    this->retType = s.retType;
    this->argType = s.argType;
    this->stackframeSize = s.stackframeSize;
    this->addr = s.addr;
}

// 整型常量
Symbol::Symbol(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, int constIntValue)
{
    this->id = ++symbolCnt;
    this->validRegionId = validRegionId;
    this->symbolToken = symbolToken;
    this->symbolKind = symbolKind;
    this->symbolType = symbolType;
    this->constIntValue = constIntValue;
    this->constCharValue = '\0';
    this->constStrValue = "";
    this->arrayDim.clear();
    this->retType = UndefRetType;
    this->argType.clear();
    this->stackframeSize = -1;
    this->addr = -1;
}

// 字符型常量
Symbol::Symbol(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, char constCharValue)
{
    this->id = ++symbolCnt;
    this->validRegionId = validRegionId;
    this->symbolToken = symbolToken;
    this->symbolKind = symbolKind;
    this->symbolType = symbolType;
    this->constIntValue = (int)constCharValue;
    this->constCharValue = constCharValue;
    this->constStrValue = "";
    this->arrayDim.clear();
    this->retType = UndefRetType;
    this->argType.clear();
    this->stackframeSize = -1;
    this->addr = -1;
}

// 字符串型常量
Symbol::Symbol(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, string constStrValue)
{
    this->id = ++symbolCnt;
    this->validRegionId = validRegionId;
    this->symbolToken = symbolToken;
    this->symbolKind = symbolKind;
    this->symbolType = symbolType;
    this->constIntValue = 0;
    this->constCharValue = '\0';
    this->constStrValue = constStrValue;
    this->arrayDim.clear();
    this->retType = UndefRetType;
    this->argType.clear();
    this->stackframeSize = -1;
    this->addr = -1;
}

// 简单变量
Symbol::Symbol(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType)
{
    this->id = ++symbolCnt;
    this->validRegionId = validRegionId;
    this->symbolToken = symbolToken;
    this->symbolKind = symbolKind;
    this->symbolType = symbolType;
    this->constIntValue = 0;
    this->constCharValue = '\0';
    this->constStrValue = "";
    this->arrayDim.clear();
    this->retType = UndefRetType;
    this->argType.clear();
    this->stackframeSize = -1;
    this->addr = -1;
}

// 数组变量
Symbol::Symbol(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, vector<int> arrayDim)
{
    this->id = ++symbolCnt;
    this->validRegionId = validRegionId;
    this->symbolToken = symbolToken;
    this->symbolKind = symbolKind;
    this->symbolType = symbolType;
    this->constIntValue = 0;
    this->constCharValue = '\0';
    this->constStrValue = "";
    this->arrayDim = arrayDim;
    this->retType = UndefRetType;
    this->argType.clear();
    this->stackframeSize = -1;
    this->addr = -1;
}

// 函数
Symbol::Symbol(int validRegionId, Token symbolToken, SymbolKind symbolKind, FunctionRetType retType, vector<SymbolType> argType)
{
    this->id = ++symbolCnt;
    this->validRegionId = validRegionId;
    this->symbolToken = symbolToken;
    this->symbolKind = symbolKind;
    this->symbolType = UndefSymType;
    this->constIntValue = 0;
    this->constCharValue = '\0';
    this->constStrValue = "";
    this->arrayDim.clear();
    this->retType = retType;
    this->argType = argType;
    this->stackframeSize = -1;
    this->addr = -1;
}

int Symbol::getId()
{
    return id;
}

int Symbol::getValidRegionId()
{
    return validRegionId;
}

string Symbol::getName()
{
    return this->symbolToken.getText();
}

string Symbol::getLowerName()
{
    return symbolToken.getLowerText();
}

SymbolKind Symbol::getKind()
{
    return symbolKind;
}

SymbolType Symbol::getType()
{
    return symbolType;
}

FunctionRetType Symbol::getRetType()
{
    return retType;
}

int Symbol::getConstIntValue()
{
    return constIntValue;
}

char Symbol::getConstCharValue()
{
    return constCharValue;
}

string Symbol::getConstStrValue()
{
    return constStrValue;
}

int Symbol::getArrDim(int dim)
{
    return arrayDim[dim];
}

int Symbol::getArrCnt()
{
    return arrayDim[0] * max(arrayDim[1], 1);
}

vector<SymbolType> Symbol::getArgType()
{
    return argType;
}

int Symbol::getAddr()
{
    return addr;
}

int Symbol::getStackFrameSize()
{
    return stackframeSize;
}

bool Symbol::isGlobal()
{
    return this->validRegionId == 0;
}

void Symbol::setArgType(vector<SymbolType> argType)
{
    this->argType = argType;
}

void Symbol::setAddr(int addr)
{
    this->addr = addr;
}

void Symbol::setStackFrameSize(int size)
{
    this->stackframeSize = size;
}

ostream &operator<<(ostream &output, const Symbol &t)
{
    output << left << setw(5) << t.id
           << left << setw(10) << t.validRegionId
           << left << setw(20) << Symbol::showName(t)
           << left << setw(10) << Symbol::showKind(t)
           << left << setw(10) << Symbol::showType(t)
           << left << setw(15) << Symbol::showConst(t)
           << left << setw(10) << t.addr
           << left << setw(10) << Symbol::showDim(t)
           << left << setw(10) << Symbol::showRet(t)
           << left << setw(20) << Symbol::showArg(t)
           << left << setw(5) << t.stackframeSize;
    return output;
}

string Symbol::showName(const Symbol &s)
{
    Token t = s.symbolToken;
    return t.getText();
}

string Symbol::showKind(const Symbol &s)
{
    switch (s.symbolKind)
    {
    case ConstSym:
        return "const";
    case VarSym:
        return "var";
    case ArrSym:
        return "arr";
    case FuncSym:
        return "func";
    default:
        return "undefined";
    }
}

string Symbol::showType(const Symbol &s)
{
    switch (s.symbolType)
    {
    case IntSym:
        return "int";
    case CharSym:
        return "char";
    case StrSym:
        return "str";
    default:
        return "undefined";
    }
}

string Symbol::showConst(const Symbol &s)
{
    if (s.symbolKind != ConstSym)
    {
        return "/";
    }
    switch (s.symbolType)
    {
    case IntSym:
        return to_string(s.constIntValue);
    case CharSym:
        return string(1, s.constCharValue);
    case StrSym:
        return s.constStrValue;
    default:
        return "undefined";
    }
}

string Symbol::showDim(const Symbol &s)
{
    if (s.symbolKind != ArrSym)
    {
        return "/";
    }
    string dim = "";
    for (int i = 0; i < (int)s.arrayDim.size(); i++)
    {
        if (s.arrayDim[i] != 0)
        {
            dim += "[" + to_string(s.arrayDim[i]) + "]";
        }
    }
    return dim;
}

string Symbol::showRet(const Symbol &s)
{
    if (s.symbolKind != FuncSym)
    {
        return "/";
    }
    switch (s.retType)
    {
    case VoidRet:
        return "void";
    case IntRet:
        return "int";
    case CharRet:
        return "char";
    default:
        return "undefined";
    }
}

string Symbol::showArg(const Symbol &s)
{
    if (s.symbolKind != FuncSym)
    {
        return "/";
    }
    string arg = "";
    for (int i = 0; i < (int)s.argType.size(); i++)
    {
        switch (s.argType[i])
        {
        case IntSym:
            arg += "int, ";
            break;
        case CharSym:
            arg += "char, ";
            break;
        case StrSym:
            arg += "str, ";
            break;
        default:
            arg += "undefined, ";
            break;
        }
    }
    return arg;
}
