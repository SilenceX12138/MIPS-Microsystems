// implement fork from user space

#include "lib.h"
#include <mmu.h>
#include <env.h>

/* ----------------- help functions ---------------- */

/* Overview:
 * 	Copy `len` bytes from `src` to `dst`.
 *
 * Pre-Condition:
 * 	`src` and `dst` can't be NULL. Also, the `src` area 
 * 	 shouldn't overlap the `dest`, otherwise the behavior of this 
 * 	 function is undefined.
 */
void user_bcopy(const void *src, void *dst, size_t len)
{
	void *max;

	//	writef("~~~~~~~~~~~~~~~~ src:%x dst:%x len:%x\n",(int)src,(int)dst,len);
	max = dst + len;

	// copy machine words while possible
	if (((int)src % 4 == 0) && ((int)dst % 4 == 0))
	{
		while (dst + 3 < max)
		{
			*(int *)dst = *(int *)src;
			dst += 4;
			src += 4;
		}
	}

	// finish remaining 0-3 bytes
	while (dst < max)
	{
		*(char *)dst = *(char *)src;
		dst += 1;
		src += 1;
	}

	//for(;;);
}

/* Overview:
 * 	Sets the first n bytes of the block of memory 
 * pointed by `v` to zero.
 * 
 * Pre-Condition:
 * 	`v` must be valid.
 *
 * Post-Condition:
 * 	the content of the space(from `v` to `v`+ n) 
 * will be set to zero.
 */
void user_bzero(void *v, u_int n)
{
	char *p;
	int m;

	p = v;
	m = n;

	while (--m >= 0)
	{
		*p++ = 0;
	}
}
/*--------------------------------------------------------------*/

/* Overview:
 * 	Custom page fault handler - if faulting page is copy-on-write,
 * 	map in our own private writable copy.
 * 
 * Pre-Condition:
 * 	`va` is the address which leads to a TLB'S exception.
 *
 * Post-Condition:
 *  Launch a user_panic if `va` is not a copy-on-write page.
 * 	Otherwise, this handler should map a private writable copy of 
 * 	the faulting page at correct address.
 */
/*** exercise 4.13 ***/
static void pgfault(u_int va)
{
	u_int *tmp = USTACKTOP; // alloc memory from invalid memory
	int r;
	int perm;
	//	writef("fork.c:pgfault():\t va:%x\n",va);

	// check whether perm is legal
	perm = ((Pte *)(*vpt))[VPN(va)] & (0xfff);
	if (!(perm & PTE_COW))
	{
		user_panic("the page isn't copy-on-write");
	}

	// alloc a page for tmp with private wiritable permission
	// be cautious to use user-state function instead of kernel-state ones
	r = syscall_mem_alloc(0, tmp, PTE_V | PTE_R);
	if (r)
	{
		user_panic("memory cannot be alloced in pgfault");
	}

	// copy va's content to tmp for curenv to write
	va = ROUNDDOWN(va, BY2PG);
	user_bcopy((void *)va, (void *)tmp, BY2PG);

	// map va at tmp
	r = syscall_mem_map(0, tmp, 0, va, PTE_V | PTE_R);
	if (r)
	{
		user_panic("cannot map va at tmp in pgfault");
	}

	// unmap tmp at newly alloc page
	// mainly to reduce pp_ref of this page
	r = syscall_mem_unmap(0, tmp);
	if (r)
	{
		user_panic("cannot unmap tmp in pgfault");
	}
}

/* Overview:
 * 	Map our virtual page `pn` (address pn*BY2PG) into the target `envid`
 * 	at the same virtual address. 
 *
 * Post-Condition:
 *  if the page is writable or copy-on-write, the new mapping must be 
 * 	created copy-on-write and then our mapping must be marked 
 * 	copy on write as well. In another word, both of the new mapping and
 * 	our mapping should be copy-on-write if the page is writable or 
 * 	copy-on-write.
 * 
 * Hint:
 * 	PTE_LIBRARY indicates that the page is shared between processes.
 * 	A page with PTE_LIBRARY may have PTE_R at the same time. You
 * 	should process it correctly.
 */
/*** exercise 4.10 ***/
static void duppage(u_int envid, u_int pn)
{
	u_int addr;
	u_int perm;
	int r;

	addr = pn * BY2PG;
	perm = ((Pte *)(*vpt))[pn] & (0xfff);
	if (((perm & PTE_R) != 0) && !(perm & PTE_LIBRARY) && !(perm & PTE_COW))
	{
		perm |= PTE_COW;
		r = syscall_mem_map(0, addr, envid, addr, perm);
		if (r)
		{
			user_panic("duppage in fork.c has problem 1");
		}
		r = syscall_mem_map(0, addr, 0, addr, perm);
		if (r)
		{
			user_panic("duppage in fork.c has problem 2");
		}
	}
	else
	{
		r = syscall_mem_map(0, addr, envid, addr, perm);
		if (r)
		{
			user_panic("duppage in fork.c has problem 3");
		}
	}
	//	user_panic("duppage not implemented");
}

/* Overview:
 * 	User-level fork. Create a child and then copy our address space
 * 	and page fault handler setup to the child.
 *
 * Hint: use vpd, vpt, and duppage.
 * Hint: remember to fix "env" in the child process!
 * Note: `set_pgfault_handler`(user/pgfault.c) is different from 
 *       `syscall_set_pgfault_handler`. 
 */
/*** exercise 4.9 4.15***/
extern void __asm_pgfault_handler(void);
int fork(void)
{
	// Your code here.
	u_int newenvid;
	extern struct Env *envs;
	extern struct Env *env;
	u_int i;
	int r;

	//The parent installs pgfault using set_pgfault_handler
	set_pgfault_handler(pgfault);

	//alloc a new env
	newenvid = syscall_env_alloc();
	if (newenvid < 0)
	{
		return newenvid;
	}
	else if (newenvid == 0)
	{
		// point env at son env when in son env
		env = envs + ENVX(syscall_getenvid());
		return 0;
	}

	// duplicate valid pages in father env to son env
	for (i = 0; i < UTOP - BY2PG * 2; i += BY2PG)
	{
		if ((((Pde *)(*vpd))[PDX(i)] & PTE_V) && (((Pte *)(*vpt))[i >> PGSHIFT] & PTE_V))
		{
			duppage(newenvid, VPN(i));
		}
	}

	// alloc an exception stack for son env
	r = syscall_mem_alloc(newenvid, UXSTACKTOP - BY2PG, PTE_V | PTE_R);
	if (r)
	{
		return r;
	}

	// install pgfault_handler for son env
	r = syscall_set_pgfault_handler(newenvid, __asm_pgfault_handler, UXSTACKTOP);
	if (r)
	{
		return r;
	}

	// set son env ENV_RUNNABLE and insert it into env_sched_list
	r = syscall_set_env_status(newenvid, ENV_RUNNABLE);
	if (r)
	{
		return r;
	}

	return newenvid;
}

// Challenge!
int sfork(void)
{
	user_panic("sfork not implemented");
	return -E_INVAL;
}
