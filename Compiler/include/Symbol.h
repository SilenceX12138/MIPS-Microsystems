#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <string>
#include <vector>

#include "Token.h"

using namespace std;

enum SymbolKind
{
    UndefSymKind,
    ConstSym,
    VarSym,
    ArrSym,
    FuncSym,
};

enum SymbolType
{
    UndefSymType,
    IntSym,
    CharSym,
    StrSym,
};

enum FunctionRetType
{
    UndefRetType,
    VoidRet,
    IntRet,
    CharRet,
};

class Symbol
{
private:
    // basic attr
    int id;
    int validRegionId;
    Token symbolToken;
    SymbolKind symbolKind;
    SymbolType symbolType;
    // const
    int constIntValue;
    char constCharValue;
    string constStrValue;
    // array
    vector<int> arrayDim; // default to be {0, 0}
    // function
    FunctionRetType retType;
    vector<SymbolType> argType;
    int stackframeSize; // memory to alloc for a function call
    // active record
    int addr;           // temp const&var's offset to current region's $sp

    static string showName(const Symbol &s);
    static string showKind(const Symbol &s);
    static string showType(const Symbol &s);
    static string showConst(const Symbol &s);
    static string showDim(const Symbol &s);
    static string showRet(const Symbol &s);
    static string showArg(const Symbol &s);

public:
    static int symbolCnt;

    Symbol();
    Symbol(const Symbol &s);
    // 整型常量
    Symbol(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, int constIntValue);
    // 字符型常量
    Symbol(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, char constCharValue);
    // 字符串型常量
    Symbol(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, string constStrValue);
    // 简单变量
    Symbol(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType);
    // 数组变量
    Symbol(int validRegionId, Token symbolToken, SymbolKind symbolKind, SymbolType symbolType, vector<int> arrayDim);
    // 函数
    Symbol(int validRegionId, Token symbolToken, SymbolKind symbolKind, FunctionRetType retType, vector<SymbolType> argType);
    friend ostream &operator<<(ostream &output, const Symbol &t);

    // 从1开始的Symbol主码=符号表索引+1
    int getId();
    int getValidRegionId();
    // 获取符号对应的token的原始text 在符号为标识符和字符串常量时返回的是名字
    string getName();
    // 获取符号对应的token的小写text 在符号为标识符和字符串常量时返回的是小写名字
    string getLowerName();
    SymbolKind getKind();
    SymbolType getType();
    FunctionRetType getRetType();
    int getConstIntValue();
    char getConstCharValue();
    string getConstStrValue();
    // 获取指定维度大小
    int getArrDim(int dim);
    // 获取数组元素个数
    int getArrCnt();
    // 获取参数类型列表
    vector<SymbolType> getArgType();
    // 变量获取栈地址
    int getAddr();
    // 函数获取栈大小
    int getStackFrameSize();
    // 是否是全局符号
    bool isGlobal();
    void setArgType(vector<SymbolType> argType);
    void setAddr(int addr);
    void setStackFrameSize(int size);
};

extern Symbol nullSym;

#endif