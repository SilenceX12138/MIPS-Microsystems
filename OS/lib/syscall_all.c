#include "../drivers/gxconsole/dev_cons.h"
#include <mmu.h>
#include <env.h>
#include <printf.h>
#include <pmap.h>
#include <sched.h>

extern char *KERNEL_SP;
extern struct Env *curenv;

/* Overview:
 * 	This function is used to print a character on screen.
 * 
 * Pre-Condition:
 * 	`c` is the character you want to print.
 */
void sys_putchar(int sysno, int c, int a2, int a3, int a4, int a5)
{
	printcharc((char)c);
	return;
}

/* Overview:
 * 	This function enables you to copy content of `srcaddr` to `destaddr`.
 *
 * Pre-Condition:
 * 	`destaddr` and `srcaddr` can't be NULL. Also, the `srcaddr` area 
 * 	shouldn't overlap the `destaddr`, otherwise the behavior of this 
 * 	function is undefined.
 *
 * Post-Condition:
 * 	the content of `destaddr` area(from `destaddr` to `destaddr`+`len`) will
 * be same as that of `srcaddr` area.
 */
void *memcpy(void *destaddr, void const *srcaddr, u_int len)
{
	char *dest = destaddr;
	char const *src = srcaddr;

	while (len-- > 0)
	{
		*dest++ = *src++;
	}

	return destaddr;
}

/* Overview:
 *	This function provides the environment id of current process.
 *
 * Post-Condition:
 * 	return the current environment id
 */
u_int sys_getenvid(void)
{
	return curenv->env_id;
}

/* Overview:
 *	This function enables the current process to give up CPU.
 *
 * Post-Condition:
 * 	Deschedule current environment. This function will never return.
 */
/*** exercise 4.6 ***/
void sys_yield(void)
{
	bcopy((void *)KERNEL_SP - sizeof(struct Trapframe),
		  (void *)TIMESTACK - sizeof(struct Trapframe),
		  sizeof(struct Trapframe));
	sched_yield();
}

/* Overview:
 * 	This function is used to destroy the current environment.
 *
 * Pre-Condition:
 * 	The parameter `envid` must be the environment id of a 
 * process, which is either a child of the caller of this function 
 * or the caller itself.
 *
 * Post-Condition:
 * 	Return 0 on success, < 0 when error occurs.
 */
int sys_env_destroy(int sysno, u_int envid)
{
	/*
		printf("[%08x] exiting gracefully\n", curenv->env_id);
		env_destroy(curenv);
	*/
	int r;
	struct Env *e;

	if ((r = envid2env(envid, &e, 0)) < 0)
	{
		return r;
	}

	printf("[%08x] destroying %08x\n", curenv->env_id, e->env_id);
	env_destroy(e);
	return 0;
}

/* Overview:
 * 	Set envid's pagefault handler entry point and exception stack.
 * 
 * Pre-Condition:
 * 	xstacktop points one byte past exception stack.
 *
 * Post-Condition:
 * 	The envid's pagefault handler will be set to `func` and its
 * 	exception stack will be set to `xstacktop`.
 * 	Returns 0 on success, < 0 on error.
 */
/*** exercise 4.12 ***/
int sys_set_pgfault_handler(int sysno, u_int envid, u_int func, u_int xstacktop)
{
	// Your code here.
	struct Env *env;
	int ret;

	ret = envid2env(envid, &env, 0);
	if (ret)
	{
		return ret;
	}

	env->env_pgfault_handler = func;
	env->env_xstacktop = xstacktop;

	return 0;
	//	panic("sys_set_pgfault_handler not implemented");
}

/* Overview:
 * 	Allocate a page of memory and map it at 'va' with permission
 * 	'perm' in the address space of 'envid'.
 *
 * 	If a page is already mapped at 'va', that page is unmapped as a
 * 	side-effect.
 * 
 * Pre-Condition:
 * perm -- PTE_V is required,
 *         PTE_COW is not allowed(return -E_INVAL),
 *         other bits are optional.
 *
 * Post-Condition:
 * Return 0 on success, < 0 on error
 *	- va must be < UTOP
 *	- env may modify its own address space or the address space of its children
 */
/*** exercise 4.3 ***/
int sys_mem_alloc(int sysno, u_int envid, u_int va, u_int perm)
{
	// check whether va's range is legal
	if (va >= UTOP || va < 0)
	{
		return -E_INVAL;
	}

	// Your code here.
	struct Env *env;
	struct Page *ppage;
	int ret = 0;

	// check whether asked permission is legal
	if (!(perm & PTE_V) || (perm & PTE_COW))
	{
		return -E_INVAL;
	}

	// get env of envid
	ret = envid2env(envid, &env, 0);
	if (ret)
	{
		return ret;
	}

	// alloc a page for mapping va
	ret = page_alloc(&ppage);
	if (ret)
	{
		return ret;
	}

	// map va at the alloced physical page
	ret = page_insert(env->env_pgdir, ppage, va, perm);
	if (ret)
	{
		return ret;
	}
	return 0;
}

/* Overview:
 * 	Map the page of memory at 'srcva' in srcid's address space
 * 	at 'dstva' in dstid's address space with permission 'perm'.
 *	 	perm -- PTE_V is required,
 *	         other bits are optional.
 * 	(Probably we should add a restriction that you can't go from
 * 	non-writable to writable?)
 *
 * Post-Condition:
 * 	Return 0 on success, < 0 on error.
 *
 * Note:
 * 	Cannot access pages above UTOP.
 */
/*** exercise 4.4 ***/
int sys_mem_map(int sysno, u_int srcid, u_int srcva, u_int dstid, u_int dstva,
				u_int perm)
{
	// check whether va's range is legal
	if (srcva >= UTOP || dstva >= UTOP || srcva < 0 || dstva < 0)
	{
		return -E_INVAL;
	}

	int ret;
	u_int round_srcva, round_dstva;
	struct Env *srcenv;
	struct Env *dstenv;
	struct Page *ppage;
	Pte *ppte;

	ppage = NULL;
	ret = 0;
	round_srcva = ROUNDDOWN(srcva, BY2PG);
	round_dstva = ROUNDDOWN(dstva, BY2PG);

	//your code here
	//check whether asked permission is legal
	if (!(perm & PTE_V))
	{
		return -E_INVAL;
	}

	// get srcenv
	ret = envid2env(srcid, &srcenv, 0);
	if (ret)
	{
		return ret;
	}

	// get dstenv
	ret = envid2env(dstid, &dstenv, 0);
	if (ret)
	{
		return ret;
	}

	// find physical page of srcva
	// if no page is found, alloc one and map srcva at it.
	ppage = page_lookup(srcenv->env_pgdir, round_srcva, &ppte);
	if (ppage == NULL)
	{
		ret = page_alloc(&ppage);
		if (ret)
		{
			return ret;
		}
		ret = page_insert(srcenv->env_pgdir, ppage, srcva, perm);
		if (ret)
		{
			return ret;
		}
	}
	else
	{
		if (((*ppte) & PTE_R == 0) && ((perm & PTE_R) == 1))
		{
			return -E_INVAL;
		}
	}

	// map dstva at the same physical page of srcva
	ret = page_insert(dstenv->env_pgdir, ppage, dstva, perm);
	if (ret)
	{
		return ret;
	}

	return ret;
}

/* Overview:
 * 	Unmap the page of memory at 'va' in the address space of 'envid'
 *  (if no page is mapped, the function silently succeeds)
 *
 * Post-Condition:
 * 	Return 0 on success, < 0 on error.
 *
 * Cannot unmap pages above UTOP.
 */
/*** exercise 4.5 ***/
int sys_mem_unmap(int sysno, u_int envid, u_int va)
{
	if (va >= UTOP || va < 0)
	{
		return -E_INVAL;
	}

	// Your code here.
	int ret;
	struct Env *env;

	ret = envid2env(envid, &env, 0);
	if (ret)
	{
		return ret;
	}

	page_remove(env->env_pgdir, va);

	return ret;
	//	panic("sys_mem_unmap not implemented");
}

/* Overview:
 * 	Allocate a new environment.
 *
 * Pre-Condition:
 * 	The new child is left as env_alloc created it, except that
 * 	status is set to ENV_NOT_RUNNABLE and the register set is copied
 * 	from the current environment.
 *
 * Post-Condition:
 * 	In the child, the register set is tweaked so sys_env_alloc returns 0.
 * 	Returns envid of new environment, or < 0 on error.
 */
/*** exercise 4.8 ***/
int sys_env_alloc(void)
{
	// Your code here.
	int r;
	struct Env *e;
	// alloc a new env as the template for son env
	r = env_alloc(&e, curenv->env_id);
	if (r)
	{
		return r;
	}
	// copy father's trapframe to son's
	bcopy((void *)(KERNEL_SP - sizeof(struct Trapframe)), &(e->env_tf), sizeof(struct Trapframe));
	// set son's pc epc for start
	e->env_tf.pc = e->env_tf.cp0_epc;
	// set son's $v0 as return value in son env
	e->env_tf.regs[2] = 0;
	// son env cannot be scheduled until father allows
	e->env_status = ENV_NOT_RUNNABLE;
	// priority stays same
	e->env_pri = curenv->env_pri;
	return e->env_id;
	//	panic("sys_env_alloc not implemented");
}

/* Overview:
 * 	Set envid's env_status to status.
 *
 * Pre-Condition:
 * 	status should be one of `ENV_RUNNABLE`, `ENV_NOT_RUNNABLE` and
 * 	`ENV_FREE`. Otherwise return -E_INVAL.
 * 
 * Post-Condition:
 * 	Returns 0 on success, < 0 on error.
 * 	Return -E_INVAL if status is not a valid status for an environment.
 * 	The status of environment will be set to `status` on success.
 */
/*** exercise 4.14 ***/
int sys_set_env_status(int sysno, u_int envid, u_int status)
{
	// Your code here.
	struct Env *env;
	int ret;

	// check whether status is legal
	if (status != ENV_RUNNABLE && status != ENV_NOT_RUNNABLE && status != ENV_FREE)
	{
		return -E_INVAL;
	}

	// get son env
	ret = envid2env(envid, &env, 0);
	if (ret)
	{
		return ret;
	}

	// set son env's status
	env->env_status = status;

	// whe status is ENV_RUNNABLE, insert son env into env_sched_list.
	if (status == ENV_FREE)
	{
		env_destroy(env);
	}

	return 0;
	//	panic("sys_env_set_status not implemented");
}

/* Overview:
 * 	Set envid's trap frame to tf.
 *
 * Pre-Condition:
 * 	`tf` should be valid.
 *
 * Post-Condition:
 * 	Returns 0 on success, < 0 on error.
 * 	Return -E_INVAL if the environment cannot be manipulated.
 *
 * Note: This hasn't be used now?
 */
int sys_set_trapframe(int sysno, u_int envid, struct Trapframe *tf)
{

	return 0;
}

/* Overview:
 * 	Kernel panic with message `msg`. 
 *
 * Pre-Condition:
 * 	msg can't be NULL
 *
 * Post-Condition:
 * 	This function will make the whole system stop.
 */
void sys_panic(int sysno, char *msg)
{
	// no page_fault_mode -- we are trying to panic!
	panic("%s", TRUP(msg));
}

/* Overview:
 * 	This function enables caller to receive message from 
 * 	other process. To be more specific, it will flag 
 * 	the current process so that other process could send 
 * 	message to it.
 *
 * Pre-Condition:
 * 	`dstva` is valid (Note: NULL is also a valid value for `dstva`).
 * 
 * Post-Condition:
 * 	This syscall will set the current process's status to 
 * 	ENV_NOT_RUNNABLE, giving up cpu. 
 */
/*** exercise 4.7 ***/
void sys_ipc_recv(int sysno, u_int dstva)
{
	struct Env *env = curenv;

	if (dstva >= UTOP || dstva < 0) // NULL is legal
	{
		return;
	}

	env->env_ipc_recving = 1;
	env->env_ipc_dstva = dstva;
	env->env_status = ENV_NOT_RUNNABLE;
	sys_yield();
}

/* Overview:
 * 	Try to send 'value' to the target env 'envid'.
 *
 * 	The send fails with a return value of -E_IPC_NOT_RECV if the
 * 	target has not requested IPC with sys_ipc_recv.
 * 	Otherwise, the send succeeds, and the target's ipc fields are
 * 	updated as follows:
 *    env_ipc_recving is set to 0 to block future sends
 *    env_ipc_from is set to the sending envid
 *    env_ipc_value is set to the 'value' parameter
 * 	The target environment is marked runnable again.
 *
 * Post-Condition:
 * 	Return 0 on success, < 0 on error.
 *
 * Hint: the only function you need to call is envid2env.
 */
/*** exercise 4.7 ***/
int sys_ipc_can_send(int sysno, u_int envid, u_int value, u_int srcva,
					 u_int perm)
{

	int r;
	struct Env *e;
	struct Page *p;
	struct Pte *pte;

	// get receive env
	r = envid2env(envid, &e, 0);
	if (r)
	{
		return r;
	}

	// check whether receive env can recive data
	if (!e->env_ipc_recving)
	{
		return -E_IPC_NOT_RECV;
	}

	e->env_ipc_value = value;
	e->env_ipc_recving = 0;
	e->env_ipc_from = curenv->env_id;
	e->env_status = ENV_RUNNABLE;
	e->env_ipc_perm = perm;

	// when srcva is zero, no need to send value.
	if (srcva)
	{
		p = page_lookup(curenv->env_pgdir, srcva, &pte);
		if (p == NULL)
		{
			return -E_INVAL;
		}
		page_insert(e->env_pgdir, p, e->env_ipc_dstva, perm);
	}

	return 0;
}

/* Overview:
 * 	This function is used to write data to device, which is
 * 	represented by its mapped physical address.
 *	Remember to check the validity of device address (see Hint below);
 * 
 * Pre-Condition:
 *      'va' is the startting address of source data, 'len' is the
 *      length of data (in bytes), 'dev' is the physical address of
 *      the device
 * 	
 * Post-Condition:
 *      copy data from 'va' to 'dev' with length 'len'
 *      Return 0 on success.
 *	Return -E_INVAL on address error.
 *      
 * Hint: Use ummapped segment in kernel address space to perform MMIO.
 *	 Physical device address:
 *	* ---------------------------------*
 *	|   device   | start addr | length |
 *	* -----------+------------+--------*
 *	|  console   | 0x10000000 | 0x20   |
 *	|    IDE     | 0x13000000 | 0x4200 |
 *	|    rtc     | 0x15000000 | 0x200  |
 *	* ---------------------------------*
 */
int sys_write_dev(int sysno, u_int va, u_int dev, u_int len)
{
	u_int vdev;

	if (!((dev >= 0x10000000 && dev + len - 1 < 0x10000020) || (dev >= 0x13000000 && dev + len - 1 < 0x13004200) || (dev >= 0x15000000 && dev + len - 1 < 0x15000200)))
	{
		return -E_INVAL;
	}

	vdev = dev + 0xA0000000;

	bcopy(va, vdev, len);

	return 0;
}

/* Overview:
 * 	This function is used to read data from device, which is
 * 	represented by its mapped physical address.
 *	Remember to check the validity of device address (same as sys_read_dev)
 * 
 * Pre-Condition:
 *      'va' is the startting address of data buffer, 'len' is the
 *      length of data (in bytes), 'dev' is the physical address of
 *      the device.
 * 
 * Post-Condition:
 *      copy data from 'dev' to 'va' with length 'len'
 *      Return 0 on success, < 0 on error
 *      
 * Hint: Use ummapped segment in kernel address space to perform MMIO.
 */
int sys_read_dev(int sysno, u_int va, u_int dev, u_int len)
{
	u_int vdev;

	if (!((dev >= 0x10000000 && dev + len - 1 < 0x10000020) || (dev >= 0x13000000 && dev + len - 1 < 0x13004200) || (dev >= 0x15000000 && dev + len - 1 < 0x15000200)))
	{
		return -E_INVAL;
	}

	vdev = dev + 0xA0000000;

	bcopy(vdev, va, len);

	return 0;
}

semaphore sema[101];

static int init_times = 0;

int sys_init_PV_var(int sysno, int init_value)
{
	int i;

	// if (init_times == 0)
	// {
	// 	for (i = 0; i < 101; i++)
	// 	{
	// 		sema[i].pv_id = i + 1;
	// 		sema[i].status = SEMA_FREE;
	// 		sema[i].val = 0;
	// 		sema[i].left = -1;
	// 		sema[i].right = -1;
	// 	}
	// 	init_times++;
	// }

	for (i = 0; i < 101; i++)
	{
		sema[i].pv_id = i + 1;
		if (sema[i].status == SEMA_FREE)
		{
			sema[i].status = SEMA_BUSY;
			sema[i].val = init_value;
			sema[i].left = -1;
			sema[i].right = -1;
			return sema[i].pv_id;
		}
	}

	return -1;
}

void sys_P(int sysno, int pv_id)
{
	if (pv_id < 1 || pv_id > 101)
	{
		return;
	}

	semaphore *tmp_sema;

	tmp_sema = &sema[pv_id - 1];
	if (tmp_sema->status == SEMA_FREE)
	{
		return;
	}
	tmp_sema->val -= 1;
	if (tmp_sema->val < 0)
	{
		curenv->env_status = ENV_NOT_RUNNABLE;
		tmp_sema->right = (tmp_sema->right + 1) % 1024;
		tmp_sema->wait_id_list[tmp_sema->right] = curenv->env_id;
		sys_yield();
	}
}

void sys_V(int sysno, int pv_id)
{
	if (pv_id < 1 || pv_id > 101)
	{
		return;
	}

	semaphore *tmp_sema;
	struct Env *e;

	tmp_sema = &sema[pv_id - 1];
	if (tmp_sema->status == SEMA_FREE)
	{
		return;
	}
	tmp_sema->val += 1;
	if (tmp_sema->val <= 0)
	{
		tmp_sema->left = (tmp_sema->left + 1) % 1024;
		envid2env(tmp_sema->wait_id_list[tmp_sema->left], &e, 0);
		e->env_status = ENV_RUNNABLE;
	}
	sys_yield();
}

int sys_check_PV_value(int sysno, int pv_id)
{
	if (pv_id < 1 || pv_id > 101)
	{
		return -1;
	}

	return sema[pv_id - 1].val;
}

void sys_release_PV_var(int sysno, int pv_id)
{
	if (pv_id < 1 || pv_id > 101)
	{
		return;
	}

	semaphore *tmp_sema;
	struct Env *e;
	int i;

	tmp_sema = &sema[pv_id - 1];
	if (tmp_sema->status == SEMA_FREE)
	{
		return;
	}
	// printf("left: %d, right %d\n", tmp_sema->left, tmp_sema->right);
	if (tmp_sema->right != tmp_sema->left && tmp_sema->right != -1)
	{
		for (i = (tmp_sema->left + 1) % 1024; i != tmp_sema->right; i = (i + 1) % 1024)
		{
			// printf("free1\n");
			envid2env(tmp_sema->wait_id_list[i], &e, 0);
			env_free(e);
		}
		// printf("free2\n");
		envid2env(tmp_sema->wait_id_list[tmp_sema->right], &e, 0);
		env_free(e);
	}

	tmp_sema->val = 0;
	tmp_sema->status = SEMA_FREE;
	tmp_sema->left = -1;
	tmp_sema->right = -1;
}
