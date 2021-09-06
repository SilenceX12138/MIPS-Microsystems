#ifndef _INTERMEDIATECODEITEM_H_
#define _INTERMEDIATECODEITEM_H_

#include <iostream>

#include "../include/Symbol.h"

using namespace std;

enum IntermediateCodeItemType
{
    UndefItem, // initial type
    // immediate number
    ImmItem,     // including immediate int and immediate char
    ImmIntItem,  // immInt field stores immediate number
    ImmCharItem, // immInt field stores immediate number
    // register
    RegItem, // reg field stores index of register
    // symbol
    StrItem, // index field stores index of corresponding symbol
    SymItem, // index field stores index of corresponding symbol
    // label
    LabelItem, // label field stores label name
};

class IntermediateCodeItem
{
private:
    IntermediateCodeItemType type;
    int index;
    int immInt;
    int reg;
    string label;

public:
    IntermediateCodeItem();
    IntermediateCodeItem(const IntermediateCodeItem &o);
    static IntermediateCodeItem create(IntermediateCodeItemType type, string strText);
    int getType();
    // 获取中间代码项对应的符号的在符号表中的物理位置
    int getSymIndex();
    int getImmInt();
    // 获取寄存器类型本身的编号
    int getReg();
    string getLabel();
    bool isTypeof(IntermediateCodeItemType expectedType);
    // 返回对应的符号
    Symbol getSym();
    // 对于立即数和常量返回值
    bool getVal(int &val);
    friend ostream &operator<<(ostream &output, const IntermediateCodeItem &t);
};

extern IntermediateCodeItem nullItem;

#endif