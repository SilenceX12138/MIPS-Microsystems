#ifndef _REGISTERMANAGER_H_
#define _REGISTERMANAGER_H_

#include <vector>
#include <map>

using namespace std;

enum Register
{
    $0,                                         // $0 0
    $at,                                        // $at 1
    $v0, $v1,                                   // $v0-$v1 2-3
    $a0, $a1, $a2, $a3,                         // $a0-$a3 4-7
    $t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7,     // $t0-$t7 8-15
    $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7,     // $s0-$s7 16-23
    $t8, $t9,                                   // $t8-$t9 24-25
    $k0, $k1,                                   // $k0-$k1 26-27
    $gp,                                        // $gp 28
    $sp,                                        // $sp 29
    $fp,                                        // $fp 30
    $ra,                                        // $ra 31
};

class RegisterManager
{
private:
    static vector<Register> busyRegList;
    static vector<Register> freeRegList;

public:
    // 返回分配的寄存器
    static Register allocReg();
    // 回收指定的寄存器
    static void collectReg(Register reg);
};

#endif