#include <iomanip>
#include <sstream>

#include "../include/Error.h"
#include "../include/StreamManager.h"
#include "../include/SymbolTable.h"

using namespace std;

vector<Symbol> SymbolTable::globalSymTable;

// 整型常量
int SymbolTable::insertSym(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, int constIntValue)
{
    if (searchInCurrentRegion(validRegionId, symbolToken.getLowerText()))
    {
        Error::outputError(symbolToken.getLineNumber(), DuplicateName);
    }
    Symbol newInt = Symbol(validRegionId, symbolToken, symbolKind, symbolType, constIntValue);
    globalSymTable.push_back(newInt);
    return newInt.getId();
}

// 字符型常量
int SymbolTable::insertSym(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, char constCharValue)
{
    if (searchInCurrentRegion(validRegionId, symbolToken.getLowerText()))
    {
        Error::outputError(symbolToken.getLineNumber(), DuplicateName);
    }
    Symbol newChar = Symbol(validRegionId, symbolToken, symbolKind, symbolType, constCharValue);
    globalSymTable.push_back(newChar);
    return newChar.getId();
}

// 字符串型常量
int SymbolTable::insertSym(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, string constStrValue)
{
    if (searchInCurrentRegion(validRegionId, symbolToken.getLowerText()))
    {
        Error::outputError(symbolToken.getLineNumber(), DuplicateName);
    }
    Symbol newStr = Symbol(validRegionId, symbolToken, symbolKind, symbolType, constStrValue);
    globalSymTable.push_back(newStr);
    return newStr.getId();
}

// 简单变量
int SymbolTable::insertSym(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType)
{
    if (searchInCurrentRegion(validRegionId, symbolToken.getLowerText()))
    {
        Error::outputError(symbolToken.getLineNumber(), DuplicateName);
    }
    Symbol newVar = Symbol(validRegionId, symbolToken, symbolKind, symbolType);
    globalSymTable.push_back(newVar);
    return newVar.getId();
}

// 数组变量
int SymbolTable::insertSym(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, vector<int> arrayDim)
{
    if (searchInCurrentRegion(validRegionId, symbolToken.getLowerText()))
    {
        Error::outputError(symbolToken.getLineNumber(), DuplicateName);
    }
    Symbol newArr = Symbol(validRegionId, symbolToken, symbolKind, symbolType, arrayDim);
    globalSymTable.push_back(newArr);
    return newArr.getId();
}

// 函数
int SymbolTable::insertSym(int validRegionId, Token symbolToken, SymbolKind symbolKind, FunctionRetType retType, vector<SymbolType> argType)
{
    if (searchInCurrentRegion(validRegionId, symbolToken.getLowerText()))
    {
        Error::outputError(symbolToken.getLineNumber(), DuplicateName);
    }
    Symbol newFunc = Symbol(validRegionId, symbolToken, symbolKind, retType, argType);
    globalSymTable.push_back(newFunc);
    return newFunc.getId();
}

// 更新函数参数列表
void SymbolTable::updateSym(int regionId, vector<SymbolType> argType)
{
    for (int i = 0; i < (int)globalSymTable.size(); i++)
    {
        if (globalSymTable[i].getId() == regionId)
        {
            globalSymTable[i].setArgType(argType);
        }
    }
}

bool SymbolTable::searchInCurrentRegion(int currentRegionId, string symLowerName)
{
    for (int i = 0; i < (int)globalSymTable.size(); i++)
    {
        if (globalSymTable[i].getValidRegionId() == currentRegionId && globalSymTable[i].getLowerName() == symLowerName)
        {
            return true;
        }
    }
    return false;
}

bool SymbolTable::searchInCurrentRegion(int currentRegionId, string symLowerName, Symbol &targetSymbol)
{
    for (int i = 0; i < (int)globalSymTable.size(); i++)
    {
        if (globalSymTable[i].getValidRegionId() == currentRegionId && globalSymTable[i].getLowerName() == symLowerName)
        {
            targetSymbol = globalSymTable[i];
            return true;
        }
    }
    return false;
}

bool SymbolTable::searchInAllRegion(int currentRegionId, string symLowerName, Symbol &targetSymbol)
{
    if (searchInCurrentRegion(currentRegionId, symLowerName, targetSymbol))
    {
        return true;
    }
    int tempCurrentRegionId = currentRegionId;
    while (true)
    {
        int upperRegionId = getUpperRegionId(tempCurrentRegionId);
        if (upperRegionId == -1)
        {
            return false;
        }
        tempCurrentRegionId = upperRegionId;
        if (searchInCurrentRegion(tempCurrentRegionId, symLowerName, targetSymbol))
        {
            return true;
        }
    }
    return false;
}

Symbol SymbolTable::getRegionById(int regionId)
{
    for (int i = 0; i < (int)globalSymTable.size(); i++)
    {
        if (globalSymTable[i].getId() == regionId)
        {
            return globalSymTable[i];
        }
    }
    return nullSym;
}

Symbol SymbolTable::getFuncByName(string funcname)
{
    for (int i = 0; i < (int)globalSymTable.size(); i++)
    {
        if (globalSymTable[i].getKind() == FuncSym && globalSymTable[i].getName() == funcname)
        {
            return globalSymTable[i];
        }
    }
    return nullSym;
}

int SymbolTable::getUpperRegionId(int currentRegionId)
{
    if (currentRegionId == 0)
    {
        return -1;
    }
    return getRegionById(currentRegionId).getValidRegionId();
}

bool SymbolTable::isRetFunc(string funcname)
{
    Symbol tempFunc = getFuncByName(funcname);
    return (tempFunc.getRetType() == IntRet || tempFunc.getRetType() == CharRet);
}

bool SymbolTable::isNonRetFunc(string funcname)
{
    Symbol tempFunc = getFuncByName(funcname);
    return tempFunc.getRetType() == VoidRet;
}

void SymbolTable::display()
{
    logfileStringstream << endl
                        << endl
                        << "/******************************Symbol Table Content BEGIN******************************/" << endl
                        << endl;
    logfileStringstream << left << setw(5) << "ID"
                        << left << setw(10) << "Valid ID"
                        << left << setw(20) << "Name"
                        << left << setw(10) << "Kind"
                        << left << setw(10) << "Type"
                        << left << setw(15) << "Const Value"
                        << left << setw(10) << "Addr"
                        << left << setw(10) << "Dim"
                        << left << setw(10) << "Return"
                        << left << setw(20) << "Arg"
                        << left << setw(5) << "Stack" << endl;
    for (int i = 0; i < (int)globalSymTable.size(); i++)
    {
        logfileStringstream << globalSymTable[i] << endl;
    }
    logfileStringstream << endl
                        << endl
                        << "/******************************Symbol Table Content END******************************/" << endl
                        << endl;
}

void SymbolTable::setFuncMemImg(int funcId)
{
    int baseAddr = 4; // 为$ra分配栈空间
    int tempFuncPos = -1;
    for (int i = 0; i < (int)globalSymTable.size(); i++)
    {
        if (globalSymTable[i].getValidRegionId() == funcId && globalSymTable[i].getKind() == VarSym)
        {
            globalSymTable[i].setAddr(baseAddr);
            baseAddr += 4; // int and char both takes up 4 bytes
        }
        else if (globalSymTable[i].getValidRegionId() == funcId && globalSymTable[i].getKind() == ArrSym)
        {
            globalSymTable[i].setAddr(baseAddr);
            baseAddr += 4 * globalSymTable[i].getArrCnt();
        }
        if (globalSymTable[i].getId() == funcId)
        {
            tempFuncPos = i;
        }
    }
    // 为全局变量设置栈地址时没有对应的作用域函数
    if (tempFuncPos != -1)
    {
        globalSymTable[tempFuncPos].setStackFrameSize(baseAddr);
    }
}

int SymbolTable::createTempInt(int currentRegionId)
{
    int newId = globalSymTable.back().getId() + 1;
    string newName = "temp_int_$" + to_string(newId);
    insertSym(currentRegionId, Token(IDENFR, newName, -1), VarSym, IntSym);
    return newId;
}

int SymbolTable::createTempChar(int currentRegionId)
{
    int newId = globalSymTable.back().getId() + 1;
    string newName = "temp_char_$" + to_string(newId);
    insertSym(currentRegionId, Token(IDENFR, newName, -1), VarSym, CharSym);
    return newId;
}

int SymbolTable::createGlobalStr(string text)
{
    int newId = globalSymTable.back().getId() + 1;
    string newName = "global_str_$" + to_string(newId);
    insertSym(0, Token(STRCON, newName, -1), ConstSym, StrSym, text);
    return newId;
}
