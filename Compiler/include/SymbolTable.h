#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include <iostream>
#include <string>
#include <vector>

#include "Symbol.h"

using namespace std;

class SymbolTable
{
public:
    static vector<Symbol> globalSymTable;

    // 整型常量
    static int insertSym(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, int constIntValue);
    // 字符型常量
    static int insertSym(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, char constCharValue);
    // 字符串型常量
    static int insertSym(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, string constStrValue);
    // 简单变量
    static int insertSym(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType);
    // 数组变量
    static int insertSym(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, vector<int> arrayDim);
    // 函数
    static int insertSym(int validRegionId, Token symbolToken, SymbolKind symbolKind, FunctionRetType retType, vector<SymbolType> argType);
    // 更新函数参数列表
    static void updateSym(int regionId, vector<SymbolType> argType);
    // 在当前作用域内查找名字是否已经被使用
    static bool searchInCurrentRegion(int currentValidRegionId, string symLowerName);
    static bool searchInCurrentRegion(int currentValidRegionId, string symLowerName, Symbol &targetSymbol);
    // 在全局作用域内查找名字是否已经被使用
    static bool searchInAllRegion(int currentValidRegionId, string symLowerName, Symbol &targetSymbol);
    // 未找到时返回`nullSym` 需要外部进行非法检查
    static Symbol getRegionById(int regionId);
    // 未找到时返回`nullSym` 需要外部进行非法检查
    static Symbol getFuncByName(string funcname);
    static int getUpperRegionId(int currentRegionId);
    // 函数名原样查找
    static bool isRetFunc(string funcname);
    // 函数名原样查找
    static bool isNonRetFunc(string funcname);
    static void setFuncMemImg(int funcId);
    static int createTempInt(int currentRegionId);
    static int createTempChar(int currentRegionId);
    static int createGlobalStr(string text);
    // 输出符号表
    static void display();
};

#endif