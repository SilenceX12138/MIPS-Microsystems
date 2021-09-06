#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <string>
#include <vector>

#include "IntermediateCodeItem.h"
#include "RegisterManager.h"

using namespace std;

void lw(Register reg, int offset, Register r);
void sw(Register reg, int offset, Register r);
void la(Register reg, string name);
void li(Register reg, int imm);
void move(Register reg1, Register reg2);
void sll(Register reg1, Register reg2, int imm);
void add(Register reg1, Register reg2, int imm);
void add(Register reg1, Register reg2, Register reg3);
void syscall();
void j(string label);
void jal(string label);
void jr(Register reg = $ra);
void bgt(Register reg1, Register reg2, string label);
void bge(Register reg1, Register reg2, string label);
void blt(Register reg1, Register reg2, string label);
void ble(Register reg1, Register reg2, string label);
void beq(Register reg1, Register reg2, string label);
void bne(Register reg1, Register reg2, string label);
void mflo(Register reg);

#endif // __INSTRUCTION_H__