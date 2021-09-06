#include <vector>

#include "../include/Instruction.h"
#include "../include/StreamManager.h"

using namespace std;

void lw(Register reg, int offset, Register r)
{
    targetfileStringStream << "lw $" << reg << ", " << offset << "($" << r << ")" << endl;
}

void sw(Register reg, int offset, Register r)
{
    targetfileStringStream << "sw $" << reg << ", " << offset << "($" << r << ")" << endl;
}

void la(Register reg, string name)
{
    targetfileStringStream << "la $" << reg << ", " << name << endl;
}

void li(Register reg, int imm)
{
    targetfileStringStream << "li $" << reg << ", " << imm << endl;
}

void sll(Register reg1, Register reg2, int imm)
{
    targetfileStringStream << "sll $" << reg1 << ", $" << reg2 << ", " << imm << endl;
}

void add(Register reg1, Register reg2, int imm)
{
    targetfileStringStream << "add $" << reg1 << ", $" << reg2 << ", " << imm << endl;
}

void add(Register reg1, Register reg2, Register reg3)
{
    targetfileStringStream << "add $" << reg1 << ", $" << reg2 << ", $" << reg3 << endl;
}

void move(Register reg1, Register reg2)
{
    targetfileStringStream << "move $" << reg1 << ", $" << reg2 << endl;
}

void syscall()
{
    targetfileStringStream << "syscall" << endl;
}

void j(string label)
{
    targetfileStringStream << "j " << label << endl;
}

void jal(string label)
{
    targetfileStringStream << "jal " << label << endl;
}

void jr(Register reg)
{
    targetfileStringStream << "jr $" << reg << endl;
}

void bgt(Register reg1, Register reg2, string label)
{
    targetfileStringStream << "bgt $" << reg1 << ", $" << reg2 << ", " << label << endl;
}

void bge(Register reg1, Register reg2, string label)
{
    targetfileStringStream << "bge $" << reg1 << ", $" << reg2 << ", " << label << endl;
}

void blt(Register reg1, Register reg2, string label)
{
    targetfileStringStream << "blt $" << reg1 << ", $" << reg2 << ", " << label << endl;
}

void ble(Register reg1, Register reg2, string label)
{
    targetfileStringStream << "ble $" << reg1 << ", $" << reg2 << ", " << label << endl;
}

void beq(Register reg1, Register reg2, string label)
{
    targetfileStringStream << "beq $" << reg1 << ", $" << reg2 << ", " << label << endl;
}

void bne(Register reg1, Register reg2, string label)
{
    targetfileStringStream << "bne $" << reg1 << ", $" << reg2 << ", " << label << endl;
}

void mflo(Register reg)
{
    targetfileStringStream << "mflo $" << reg << endl;
}
