#include "../include/Instruction.h"
#include "../include/RegisterManager.h"
#include "../include/StreamManager.h"
#include "../include/SymbolTable.h"
#include "../include/IntermediateCode.h"
#include "../include/TargetCode.h"
#include "../include/utils.h"

IntermediateCode TargetCode::currentCode;

void TargetCode::startTargetCodeGenerate()
{
    int funcStart = setGlobalDataImg();
    for (int i = funcStart; i < (int)IntermediateCode::intermediateCodeList.size(); i++)
    {
        transCode(i);
    }
}

int TargetCode::setGlobalDataImg()
{
    int endPos = 0;
    targetfileStringStream << ".data" << endl;
    for (int i = 0; i < (int)SymbolTable::globalSymTable.size(); i++)
    {
        Symbol tempSymbol = SymbolTable::globalSymTable[i];
        if (tempSymbol.getType() == StrSym)
        {
            targetfileStringStream << tempSymbol.getName() << ": .asciiz "
                                   << "\"" << tempSymbol.getConstStrValue() << "\"" << endl;
        }
    }
    targetfileStringStream << endl
                           << ".text" << endl;
    comment("GLOBAL INIT STARTS");
    for (int i = 0; i < (int)IntermediateCode::intermediateCodeList.size(); i++)
    {
        if (IntermediateCode::intermediateCodeList[i].type == Label)
        {
            endPos = i;
            break; // 第一个函数前的全局常量和变量需要被初始化
        }
        transCode(i);
    }
    comment("GLOBAL INIT ENDS");
    comment("JUMP TO MAIN");
    int mainStackSize = SymbolTable::getFuncByName("main").getStackFrameSize();
    add($sp, $sp, -1 * mainStackSize);
    // jal
    jal("main");
    // recover stack
    add($sp, $sp, mainStackSize);
    comment("RETURN FROM MAIN");
    comment("EXIT");
    li($v0, 10);
    syscall();
    return endPos;
}

void TargetCode::transCode(int idx)
{
    currentCode = IntermediateCode::intermediateCodeList[idx];
    comment();
    switch (currentCode.type)
    {
    case Read:
        transRead();
        break;
    case Write:
        transWrite();
        break;
    case WriteOver:
        transWriteOver();
        break;
    case Assign:
        transAssign();
        break;
    case Add:
        transCal("addu");
        break;
    case Sub:
        transCal("subu");
        break;
    case Mult:
        transCal("mul");
        break;
    case Div:
        transCal("div");
        break;
    case LoadArr:
        transLoadArr();
        break;
    case SaveArr:
        transSaveArr();
        break;
    case Label:
        transLabel();
        break;
    case Ret:
        transRet();
        break;
    case Call:
        transCall();
        break;
    case PushArg:
        transPushArg();
        break;
    case BGT:
    case BGE:
    case BLT:
    case BLE:
    case BEQ:
    case BNE:
        transBranch();
        break;
    case GOTO:
        transGOTO();
        break;
    default:
        break;
    }
}

void TargetCode::transRead()
{
    IntermediateCodeItem tempItem = currentCode.itemList[0];
    li($v0, tempItem.getSym().getType() == IntSym ? 5 : 12);
    syscall();
    save2Mem(tempItem, $v0);
}

void TargetCode::transWrite()
{
    IntermediateCodeItem tempItem = currentCode.itemList[0];
    load2Reg(tempItem, $a0);
    li($v0, tempItem.isTypeof(ImmCharItem) ? 11 : tempItem.isTypeof(ImmIntItem) ? 1 : tempItem.isTypeof(StrItem) ? 4 : (tempItem.getSym().getType() == CharSym) ? 11 : 1);
    syscall();
}

void TargetCode::transWriteOver()
{
    li($a0, 10);
    li($v0, 11);
    syscall();
}

void TargetCode::transAssign()
{
    IntermediateCodeItem tempItem = currentCode.itemList[0];
    IntermediateCodeItem targetItem = currentCode.itemList[2];
    Register targetReg = load2Reg(tempItem);
    save2Mem(targetItem, targetReg);
    RegisterManager::collectReg(targetReg);
}

void TargetCode::transCal(string instr)
{
    IntermediateCodeItem tempItem1 = currentCode.itemList[0];
    IntermediateCodeItem tempItem2 = currentCode.itemList[1];
    IntermediateCodeItem targetItem = currentCode.itemList[2];
    Register targetReg = load2Reg();
    int tempVal1, tempVal2;
    bool isVal1 = tempItem1.getVal(tempVal1);
    bool isVal2 = tempItem2.getVal(tempVal2);
    if (isVal1 && isVal2)
    {
        int tempImm = 0;
        if (instr == "addu")
        {
            tempImm = tempVal1 + tempVal2;
        }
        else if (instr == "subu")
        {
            tempImm = tempVal1 - tempVal2;
        }
        else if (instr == "mul")
        {
            tempImm = tempVal1 * tempVal2;
        }
        else if (instr == "div")
        {
            tempImm = tempVal1 / tempVal2;
        }
        li(targetReg, tempImm);
    }
    else if (isVal2 && instr == "mul")
    {
        Register tempReg1 = load2Reg(tempItem1);
        int idx = log2(tempVal2);
        if (idx != -1 && instr == "mul")
        {
            sll(targetReg, tempReg1, idx);
        }
        else
        {
            targetfileStringStream << instr << " $" << targetReg << ", $" << tempReg1 << ", " << tempVal2 << endl;
        }
        RegisterManager::collectReg(tempReg1);
    }
    else
    {
        Register tempReg1 = load2Reg(tempItem1);
        Register tempReg2 = load2Reg(tempItem2);
        if (instr == "div")
        {
            targetfileStringStream << instr << " $" << tempReg1 << ", $" << tempReg2 << endl;
            mflo(targetReg);
        }
        else
        {
            targetfileStringStream << instr << " $" << targetReg << ", $" << tempReg1 << ", $" << tempReg2 << endl;
        }
        RegisterManager::collectReg(tempReg1);
        RegisterManager::collectReg(tempReg2);
    }
    save2Mem(targetItem, targetReg);
    RegisterManager::collectReg(targetReg);
}

// t2 = t0[t1]
void TargetCode::transLoadArr()
{
    IntermediateCodeItem arrItem = currentCode.itemList[0];
    IntermediateCodeItem idxItem = currentCode.itemList[1];
    IntermediateCodeItem targetItem = currentCode.itemList[2];
    Register idxReg = load2Reg(idxItem, $v0); // 使用$v0存储数组索引
    Register targetReg = load2Reg();
    sll(idxReg, idxReg, 2);
    add(idxReg, idxReg, arrItem.getSym().getAddr());
    add(idxReg, idxReg, arrItem.getSym().isGlobal() ? $gp : $sp);
    lw(targetReg, 0, (Register)idxReg);
    save2Mem(targetItem, targetReg);
    RegisterManager::collectReg(idxReg);
    RegisterManager::collectReg(targetReg);
}

// t0[t1] = t2
void TargetCode::transSaveArr()
{
    IntermediateCodeItem arrItem = currentCode.itemList[0];
    IntermediateCodeItem idxItem = currentCode.itemList[1];
    IntermediateCodeItem valItem = currentCode.itemList[2];
    Register idxReg = load2Reg(idxItem, $v0); // 使用$v0存储数组索引
    Register valReg = load2Reg(valItem);
    sll(idxReg, idxReg, 2);
    add(idxReg, idxReg, arrItem.getSym().getAddr());
    add(idxReg, idxReg, arrItem.getSym().isGlobal() ? $gp : $sp);
    sw(valReg, 0, (Register)idxReg);
    RegisterManager::collectReg(idxReg);
    RegisterManager::collectReg(valReg);
}

void TargetCode::transLabel()
{
    targetfileStringStream << currentCode.itemList[3].getLabel() << ":" << endl;
}

void TargetCode::transRet()
{
    IntermediateCodeItem retVal = currentCode.itemList[0];
    if (!currentCode.itemList[0].isTypeof(UndefItem))
    {
        load2Reg(retVal, $v0);
    }
    jr($ra);
}

void TargetCode::transCall()
{
    IntermediateCodeItem callee = currentCode.itemList[3];
    Symbol tempFunc = SymbolTable::getFuncByName(callee.getLabel());
    comment("Call Block Begins");
    // save $ra
    sw($ra, 0, $sp);
    // alloc stack
    add($sp, $sp, -1 * tempFunc.getStackFrameSize());
    // jal
    jal(callee.getLabel());
    // recover stack
    add($sp, $sp, tempFunc.getStackFrameSize());
    // recover $ra
    lw($ra, 0, $sp);
    comment("Call Block Ends");
}

void TargetCode::transPushArg()
{
    IntermediateCodeItem arg = currentCode.itemList[0];
    IntermediateCodeItem argIdx = currentCode.itemList[1];
    IntermediateCodeItem callee = currentCode.itemList[3];
    Symbol tempFunc = SymbolTable::getFuncByName(callee.getLabel());
    Register tempReg = load2Reg(arg);
    sw(tempReg, -1 * tempFunc.getStackFrameSize() + 4 + argIdx.getImmInt() * 4, $sp);
    RegisterManager::collectReg(tempReg);
}

void TargetCode::transBranch()
{
    IntermediateCodeItem leftItem = currentCode.itemList[0];
    IntermediateCodeItem rightItem = currentCode.itemList[1];
    string label = currentCode.itemList[3].getLabel();
    Register leftReg = load2Reg(leftItem);
    Register rightReg = load2Reg(rightItem);
    switch (currentCode.type)
    {
    case BGT:
        bgt(leftReg, rightReg, label);
        break;
    case BGE:
        bge(leftReg, rightReg, label);
        break;
    case BLT:
        blt(leftReg, rightReg, label);
        break;
    case BLE:
        ble(leftReg, rightReg, label);
        break;
    case BEQ:
        beq(leftReg, rightReg, label);
        break;
    case BNE:
        bne(leftReg, rightReg, label);
        break;
    default:
        break;
    }
    RegisterManager::collectReg(leftReg);
    RegisterManager::collectReg(rightReg);
}

void TargetCode::transGOTO()
{
    string label = currentCode.itemList[3].getLabel();
    j(label);
}

Register TargetCode::load2Reg(IntermediateCodeItem item, Register reg)
{
    if (item.isTypeof(UndefItem))
    {
        return RegisterManager::allocReg();
    }
    if (item.isTypeof(RegItem))
    {
        if (reg != $0) // 寄存器间赋值
        {
            move(reg, (Register)item.getReg());
            return reg;
        }
        return (Register)item.getReg(); // 返回寄存器
    }
    Register tempReg = reg == $0 ? RegisterManager::allocReg() : reg;
    if (item.isTypeof(ImmItem))
    {
        li(tempReg, item.getImmInt());
    }
    else if (item.isTypeof(StrItem))
    {
        la(tempReg, item.getSym().getName());
    }
    else
    {
        Symbol tempSymbol = item.getSym();
        if (tempSymbol.getKind() == ConstSym)
        {
            li(tempReg, tempSymbol.getConstIntValue());
        }
        else
        {
            lw(tempReg, tempSymbol.getAddr(), tempSymbol.isGlobal() ? $gp : $sp);
        }
    }
    return tempReg;
}

void TargetCode::save2Mem(IntermediateCodeItem item, Register reg)
{
    Symbol tempSymbol = item.getSym();
    sw(reg, tempSymbol.getAddr(), tempSymbol.isGlobal() ? $gp : $sp);
}

void TargetCode::comment(string content)
{
    targetfileStringStream << "# <-----" << content << "----->" << endl;
}

void TargetCode::comment()
{
    if (currentCode.type == Label)
    {
        targetfileStringStream << endl;
    }
    targetfileStringStream << "# " << currentCode << endl;
}
