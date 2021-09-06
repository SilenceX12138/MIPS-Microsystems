#ifndef __OPTIMIZATION_H__
#define __OPTIMIZATION_H__

class Optmization
{

private:
    // 删去跳转到紧接的下一条指令的J指令
    static void peep();
    // 将乘加运算指令中的立即数后置
    static void moveImm();

public:
    static void startOptimize();
};

#endif // __OPTIMIZATION_H__