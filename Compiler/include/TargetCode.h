#ifndef _TARGETCODE_H_
#define _TARGETCODE_H_

#include "IntermediateCode.h"
#include "RegisterManager.h"

// 目标代码生成类寄存器分配策略
// 1. 寄存器只能通过load2Reg分配
// 2. 所有分配的寄存器都需要collect 也即是说出现load2Reg参数个数小于等于1的情况时 尾部需要collectReg
// 3. save2Mem不会回收寄存器
class TargetCode
{
private:
    static IntermediateCode currentCode;

public:
    static void startTargetCodeGenerate();
    // 返回第一个全局变量初始化结束后的第一条中间语句索引
    static int setGlobalDataImg();
    static void transCode(int idx);
    static void transRead();
    static void transWrite();
    static void transWriteOver();
    static void transAssign();
    static void transCal(string instr);
    static void transLoadArr();
    static void transSaveArr();
    static void transLabel();
    static void transRet();
    static void transCall();
    static void transPushArg();
    static void transBranch();
    static void transGOTO();
    // 将item的值加载到寄存器并返回存储值的寄存器
    //  1. 默认分配寄存器 也可自定义目标寄存器
    //  2. item为空时仅分配寄存器
    //  3. iWtem分类
    //     reg: 寄存器间赋值
    //     imm: 寄存器赋常量
    //     str: 加载地址到指定寄存器
    //     sym: 从内存加载值
    static Register load2Reg(IntermediateCodeItem item = nullItem, Register reg = $0);
    // 将寄存器值reg保存到item的内存位置
    static void save2Mem(IntermediateCodeItem item, Register reg);
    static void comment(string content);
    static void comment();
};

#endif