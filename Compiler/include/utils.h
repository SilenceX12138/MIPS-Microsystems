#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

#include "IntermediateCode.h"
#include "Symbol.h"

using namespace std;

// initialize all IO streams
void initialStream();
// create files containing analysis result
void createAnalyzefile();
void createLogfile();
void createErrorfile();
void createMipsfile();
void createProcfile();
// +, -, *, /, _, a-z, A-Z, 0-9
bool isLegalCharacter(char c);
// ASCII code has to be among 32, 33, 35~126.
bool isLegalString(string s);
// translate INTTK/CHARTK into symbol type
SymbolType tokenType2SymbolType(Token t);
// translate INTTK/CHARTK into function return type
FunctionRetType tokenType2RetType(Token t);
// 对关系运算符取反并返回对应的中间代码
IntermediateCodeType revLogic(IntermediateCodeType raw);
// 将关系运算符转换为中间代码类型
IntermediateCodeType token2RelaCode(Token t);
// 将字符串中的转义字符'\'全部变成"\\"
string omitEscape(string str);
// 判断数是不是2的整数次幂 不是返回-1 否则返回几次方
int log2(int num);

#endif