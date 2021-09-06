#include "lib.h"
#include <unistd.h>
#include <mmu.h>
#include <env.h>
#include <trap.h>

void syscall_putchar(char ch)
{
	msyscall(SYS_putchar, (int)ch, 0, 0, 0, 0);
}

u_int syscall_getenvid(void)
{
	return msyscall(SYS_getenvid, 0, 0, 0, 0, 0);
}

void syscall_yield(void)
{
	msyscall(SYS_yield, 0, 0, 0, 0, 0);
}

int syscall_env_destroy(u_int envid)
{
	return msyscall(SYS_env_destroy, envid, 0, 0, 0, 0);
}
int syscall_set_pgfault_handler(u_int envid, void (*func)(void), u_int xstacktop)
{
	return msyscall(SYS_set_pgfault_handler, envid, (int)func, xstacktop, 0, 0);
}

int syscall_mem_alloc(u_int envid, u_int va, u_int perm)
{
	return msyscall(SYS_mem_alloc, envid, va, perm, 0, 0);
}

int syscall_mem_map(u_int srcid, u_int srcva, u_int dstid, u_int dstva, u_int perm)
{
	return msyscall(SYS_mem_map, srcid, srcva, dstid, dstva, perm);
}

int syscall_mem_unmap(u_int envid, u_int va)
{
	return msyscall(SYS_mem_unmap, envid, va, 0, 0, 0);
}

int syscall_set_env_status(u_int envid, u_int status)
{
	return msyscall(SYS_set_env_status, envid, status, 0, 0, 0);
}

int syscall_set_trapframe(u_int envid, struct Trapframe *tf)
{
	return msyscall(SYS_set_trapframe, envid, (int)tf, 0, 0, 0);
}

void syscall_panic(char *msg)
{
	msyscall(SYS_panic, (int)msg, 0, 0, 0, 0);
}

int syscall_ipc_can_send(u_int envid, u_int value, u_int srcva, u_int perm)
{
	return msyscall(SYS_ipc_can_send, envid, value, srcva, perm, 0);
}

void syscall_ipc_recv(u_int dstva)
{
	msyscall(SYS_ipc_recv, dstva, 0, 0, 0, 0);
}

int syscall_cgetc()
{
	return msyscall(SYS_cgetc, 0, 0, 0, 0, 0);
}

int syscall_write_dev(u_int va, u_int dev, u_int offset)
{
	return msyscall(SYS_write_dev, va, dev, offset, 0, 0);
}

int syscall_read_dev(u_int va, u_int dev, u_int offset)
{
	return msyscall(SYS_read_dev, va, dev, offset, 0, 0);
}

int syscall_init_PV_var(int init_value)
{
	return msyscall(SYS_init_PV_var, init_value, 0, 0, 0, 0);
}

void syscall_P(int pv_id)
{
	return msyscall(SYS_P, pv_id, 0, 0, 0, 0);
}

void syscall_V(int pv_id)
{
	return msyscall(SYS_V, pv_id, 0, 0, 0, 0);
}

int syscall_check_PV_value(int pv_id)
{
	return msyscall(SYS_check_PV_value, pv_id, 0, 0, 0, 0);
}

void syscall_release_PV_var(int pv_id)
{
	return msyscall(SYS_release_PV_var, pv_id, 0, 0, 0, 0);
}
