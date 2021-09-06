#ifndef _INTERMEDIATECODE_H_
#define _INTERMEDIATECODE_H_

#include <vector>

#include "IntermediateCodeItem.h"

using namespace std;

enum IntermediateCodeType
{
    UndefCode,
    // I/O
    Read,      // scanf(t0)
    Write,     // printf(t0)
    WriteOver, // printf('\n')
    // calculate
    Assign,  // t2 = t0
    Add,     // t2 = t0 + t1
    Sub,     // t2 = t0 - t1
    Mult,    // t2 = t0 * t1
    Div,     // t2 = t0 / t1
    LoadArr, // t2 = t0[t1]
    SaveArr, // t0[t1] = t2
    // function
    PushArg, // push t0 to t3(..., t1, ...) 
    Call,    // call t3
    Ret,     // return t0(nullable)
    Label,   // generate label t3
    // branch
    BGT, // branch to t3 if t0 > t1
    BGE, // branch to t3 if t0 >= t1
    BLT, // branch to t3 if t0 < t1
    BLE, // branch to t3 if t0 <= t1
    BEQ, // branch to t3 if t0 == t1
    BNE, // branch to t3 if t0 != t1
    GOTO // goto t3
};

extern const string INTERMEDIATECODE_TABLE[];

class IntermediateCode
{
public:
    IntermediateCodeType type;
    // usual format: op1 op2 target label
    vector<IntermediateCodeItem> itemList;

    static vector<IntermediateCode> intermediateCodeList;

    IntermediateCode();
    IntermediateCode(IntermediateCodeType type, vector<IntermediateCodeItem> itemList);
    IntermediateCode(const IntermediateCode &o);
    // 生成中间代码文件
    static void startIntermediateCodeGenerate();
    // 插入中间代码
    static void insert(IntermediateCodeType type, vector<IntermediateCodeItem> itemList);
    // 复制[start, end)区间内的中间代码
    static void dup(int start, int end);
    friend ostream &operator<<(ostream &output, const IntermediateCode &t);
};

#endif