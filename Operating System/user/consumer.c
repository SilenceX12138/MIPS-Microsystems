#include "lib.h"

void umain(void)
{
    int empty = syscall_init_PV_var(1);
    int full = syscall_init_PV_var(0);
    int mutex = syscall_init_PV_var(1);
    writef("empty %d full %d mutex %d\n", empty, full, mutex);
    int time = 0;
    int r = fork();
    if (r == 0)
    {
        int i = 0;
        for (i = 0;; i++)
        {
            syscall_P(empty);
            writef("produce %d\n", i);
            syscall_V(full);
        }
    }
    else
    {
        int j = 0;
        for (j = 0;; j++)
        {
            syscall_P(full);
            writef("consume %d\n", j);
            syscall_V(empty);
        }
    }
}
