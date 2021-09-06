#include <vector>
#include <algorithm>
#include <cassert>

#include "../include/RegisterManager.h"
#include "../include/StreamManager.h"

using namespace std;

vector<Register> RegisterManager::busyRegList;
vector<Register> RegisterManager::freeRegList = {$t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7, $t8, $t9};

Register RegisterManager::allocReg()
{
    Register freeReg = $0;
    freeReg = freeRegList.back();
    freeRegList.pop_back();
    busyRegList.push_back(freeReg);
    return freeReg;
}

void RegisterManager::collectReg(Register reg)
{
    vector<Register>::iterator i = find(busyRegList.begin(), busyRegList.end(), reg);
    if (i == busyRegList.end())
    {
        return; // 某些寄存器不是人为分配而是默认使用的 例如$v0
    }
    freeRegList.push_back(*i);
    busyRegList.erase(i);
    return;
}
