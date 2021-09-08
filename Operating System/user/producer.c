#include "lib.h"

// int count = 0;

void umain(void)
{
    // int sema1 = syscall_init_PV_var(1);
    // int sema2 = syscall_init_PV_var(2);
    // int sema3 = syscall_init_PV_var(3);
    // int sema4 = syscall_init_PV_var(1);
    // int sema5 = syscall_init_PV_var(1);
    // int sema6 = syscall_init_PV_var(1);
    // int sema7 = syscall_init_PV_var(1);
    // int sema8 = syscall_init_PV_var(1);
    // int sema9 = syscall_init_PV_var(1);
    // int sema0 = syscall_init_PV_var(1);

    // writef("sema1: %d, sema2: %d, sema3: %d, sema4: %d, sema5: %d, sema6: %d, sema7: %d, sema8: %d, sema9: %d, sema0: %d, \n", sema1, sema2, sema3, sema4, sema5, sema6, sema7, sema8, sema9, sema0);

    int n;
    for (n = 0; n < 101; n++)
    {
        int sema = syscall_init_PV_var(1);
        writef("loop: %d, sema: %d\n", n, sema);
        syscall_release_PV_var(sema);
    }
    /*
    syscall_P(sema1);
    writef("sema1: %d\n", syscall_check_PV_value(sema1));
    writef("sema2: %d\n", syscall_check_PV_value(sema2));

    int r = fork();
    int i, j;
    if (r == 0)
    {
        r = fork();
        if (r == 0)
        {

            r = fork();
            if (r == 0)
            {
                for (i = 0; i < 1000000; i++)
                    ;
                int val = syscall_check_PV_value(sema1);
                writef("the val is %d\n", val);
                syscall_release_PV_var(sema1);
            }
            else
            {
                syscall_P(sema1);
            }
        }
        else
        {
            syscall_P(sema1);
        }
    }
    else
    {
        syscall_P(sema1);
    }
*/
}
