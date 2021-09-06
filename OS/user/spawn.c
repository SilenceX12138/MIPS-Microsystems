#include "lib.h"
#include <mmu.h>
#include <env.h>
#include <kerelf.h>

#define debug 0
#define TMPPAGE (BY2PG)
#define TMPPAGETOP (TMPPAGE + BY2PG)

int init_stack(u_int child, char **argv, u_int *init_esp)
{
	int argc, i, r, tot;
	char *strings;
	u_int *args;

	// Count the number of arguments (argc)
	// and the total amount of space needed for strings (tot)
	tot = 0;
	for (argc = 0; argv[argc]; argc++)
		tot += strlen(argv[argc]) + 1;

	// Make sure everything will fit in the initial stack page
	if (ROUND(tot, 4) + 4 * (argc + 3) > BY2PG)
		return -E_NO_MEM;

	// Determine where to place the strings and the args array
	strings = (char *)TMPPAGETOP - tot;
	args = (u_int *)(TMPPAGETOP - ROUND(tot, 4) - 4 * (argc + 1));

	if ((r = syscall_mem_alloc(0, TMPPAGE, PTE_V | PTE_R)) < 0)
		return r;
	// Replace this with your code to:
	//
	//	- copy the argument strings into the stack page at 'strings'
	char *ctemp, *argv_temp;
	u_int j;
	ctemp = strings;
	for (i = 0; i < argc; i++)
	{
		argv_temp = argv[i];
		for (j = 0; j < strlen(argv[i]); j++)
		{
			*ctemp = *argv_temp;
			ctemp++;
			argv_temp++;
		}
		*ctemp = 0;
		ctemp++;
	}
	//	- initialize args[0..argc-1] to be pointers to these strings
	//	  that will be valid addresses for the child environment
	//	  (for whom this page will be at USTACKTOP-BY2PG!).
	ctemp = (char *)(USTACKTOP - TMPPAGETOP + (u_int)strings);
	for (i = 0; i < argc; i++)
	{
		args[i] = (u_int)ctemp;
		ctemp += strlen(argv[i]) + 1;
	}
	//	- set args[argc] to 0 to null-terminate the args array.
	ctemp--;
	args[argc] = ctemp;
	//	- push two more words onto the child's stack below 'args',
	//	  containing the argc and argv parameters to be passed
	//	  to the child's umain() function.
	u_int *pargv_ptr;
	pargv_ptr = args - 1;
	*pargv_ptr = USTACKTOP - TMPPAGETOP + (u_int)args;
	pargv_ptr--;
	*pargv_ptr = argc;
	//
	//	- set *init_esp to the initial stack pointer for the child
	//
	*init_esp = USTACKTOP - TMPPAGETOP + (u_int)pargv_ptr;
	//	*init_esp = USTACKTOP;	// Change this!

	if ((r = syscall_mem_map(0, TMPPAGE, child, USTACKTOP - BY2PG, PTE_V | PTE_R)) < 0)
		goto error;
	if ((r = syscall_mem_unmap(0, TMPPAGE)) < 0)
		goto error;

	return 0;

error:
	syscall_mem_unmap(0, TMPPAGE);
	return r;
}

int usr_is_elf_format(u_char *binary)
{
	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;
	if (ehdr->e_ident[0] == ELFMAG0 &&
		ehdr->e_ident[1] == ELFMAG1 &&
		ehdr->e_ident[2] == ELFMAG2 &&
		ehdr->e_ident[3] == ELFMAG3)
	{
		return 1;
	}

	return 0;
}

int mem_is_mapped(int va)
{
	return (((Pde *)(*vpd))[va >> PDSHIFT] & PTE_V) && (((Pte *)(*vpt))[va >> PGSHIFT] & PTE_V);
}

#define SPECIALPAGE (0x50000000)

int usr_load_elf(int fd, Elf32_Phdr *ph, int child_envid)
{
	//Hint: maybe this function is useful
	//      If you want to use this func, you should fill it ,it's not hard
	u_int va = ph->p_vaddr;
	u_int sgsize = ph->p_memsz;
	u_int bin_size = ph->p_filesz;
	u_int file_offset = ph->p_offset;
	u_char buf[BY2PG];
	u_int i = 0;
	int r;
	u_int offset = va + i - ROUNDDOWN(va + i, BY2PG);
	int size;
	if (offset)
	{
		r = syscall_mem_alloc(child_envid, va + i, PTE_V | PTE_R);
		if (r < 0)
		{
			return r;
		}
		size = MIN(bin_size - i, BY2PG - offset);
		r = seek(fd, file_offset + i);
		if (r < 0)
		{
			return r;
		}
		r = readn(fd, buf, size);
		if (r < 0)
		{
			return r;
		}
		r = syscall_mem_map(child_envid, va + i, 0, SPECIALPAGE, PTE_V | PTE_R);
		if (r < 0)
		{
			return r;
		}
		user_bcopy((void *)buf, (void *)(SPECIALPAGE + offset), size);
		r = syscall_mem_unmap(0, SPECIALPAGE);
		if (r < 0)
		{
			return r;
		}
		i += size;
	}
	while (i < bin_size)
	{
		size = MIN(BY2PG, bin_size - i);
		r = syscall_mem_alloc(child_envid, va + i, PTE_V | PTE_R);
		if (r < 0)
		{
			return r;
		}
		size = MIN(bin_size - i, BY2PG);
		r = seek(fd, file_offset + i);
		if (r < 0)
		{
			return r;
		}
		r = readn(fd, buf, size);
		if (r < 0)
		{
			return r;
		}
		r = syscall_mem_map(child_envid, va + i, 0, SPECIALPAGE, PTE_V | PTE_R);
		if (r < 0)
		{
			return r;
		}
		user_bcopy((void *)buf, (void *)SPECIALPAGE, size);
		r = syscall_mem_unmap(0, SPECIALPAGE);
		if (r < 0)
		{
			return r;
		}
		i += size;
	}
	offset = va + i - ROUNDDOWN(va + i, BY2PG);
	if (offset)
	{
		size = MIN(sgsize - i, BY2PG - offset);
		r = syscall_mem_map(child_envid, va + i, 0, SPECIALPAGE, PTE_V | PTE_R);
		if (r < 0)
		{
			return r;
		}
		user_bzero((void *)(SPECIALPAGE + offset), size);
		r = syscall_mem_unmap(0, SPECIALPAGE);
		if (r < 0)
		{
			return r;
		}
		i += size;
	}
	while (i < sgsize)
	{
		size = MIN(BY2PG, sgsize - i);
		r = syscall_mem_alloc(child_envid, va + i, PTE_V | PTE_R);
		if (r < 0)
		{
			return r;
		}
		i += size;
	}
	return 0;
}

static int silence_mapper(u_long va, u_int32_t sgsize,
						  u_char *bin, u_int32_t bin_size, u_int child_envid)
{
	u_long i;
	int r;
	int bufaddr = 0x50000000;
	u_long offset = va - ROUNDDOWN(va, BY2PG);

	/*Step 1: load all content of bin into memory. */
	for (i = 0; i < bin_size; i += BY2PG)
	{
		if (syscall_mem_alloc(0, bufaddr, PTE_V | PTE_R))
		{
			return -E_NO_MEM;
		}
		if (i == 0)
		{
			if (BY2PG - offset > bin_size)
			{
				user_bcopy(bin, bufaddr + offset, bin_size);
			}
			else
			{
				user_bcopy(bin, bufaddr + offset, BY2PG - offset);
			}
			i -= offset;
		}
		else
		{
			if (bin_size - i > BY2PG)
			{
				user_bcopy(bin + i, bufaddr, BY2PG);
			}
			else
			{
				user_bcopy(bin + i, bufaddr, bin_size - i);
			}
		}
		syscall_mem_map(0, bufaddr, child_envid, va + i, PTE_V | PTE_R);
		syscall_mem_unmap(0, bufaddr);
	}
	/*Step 2: alloc pages to reach `sgsize` when `bin_size` < `sgsize` */
	while (i < sgsize)
	{
		r = syscall_mem_alloc(child_envid, va + i, PTE_V | PTE_R);
		if (r)
		{
			return -E_NO_MEM;
		}
		i += BY2PG;
	}
	return 0;
}

int silence_load_elf(struct Fd *fd, u_int child_envid)
{
	u_char *binary = (u_char *)fd2data(fd);
	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;
	Elf32_Phdr *phdr = NULL;
	int size = ((struct Filefd *)fd)->f_file.f_size;

	u_char *ptr_ph_table = NULL;
	Elf32_Half ph_entry_count;
	Elf32_Half ph_entry_size;
	int r;

	ptr_ph_table = binary + ehdr->e_phoff;
	ph_entry_count = ehdr->e_phnum;
	ph_entry_size = ehdr->e_phentsize;

	if (!usr_is_elf_format(binary))
	{
		return -1;
	}

	while (ph_entry_count--)
	{
		phdr = (Elf32_Phdr *)ptr_ph_table;
		if (phdr->p_type == PT_LOAD)
		{
			r = silence_mapper(phdr->p_vaddr, phdr->p_memsz, binary + phdr->p_offset, phdr->p_filesz, child_envid);
			if (r != 0)
			{
				return r;
			}
		}
		ptr_ph_table += ph_entry_size;
	}

	return size;
}

int spawn(char *prog, char **argv)
{
	int r;
	int fdnum;
	struct Fd *fd;
	u_int child_envid;
	u_int i, *blk;
	u_int esp;
	int entry_size, text_start, size;
	Elf32_Ehdr *ehdr;
	Elf32_Phdr *phdr;
	// Note 0: some variable may be not used,you can cancel them as you like
	// Step 1: Open the file specified by `prog` (prog is the path of the program)
	if ((r = open(prog, O_RDONLY)) < 0)
	{
		user_panic("spawn ::open line 102 RDONLY wrong !\n");
		return r;
	}
	// Your code begins here
	fdnum = r;
	fd = (struct Fd *)num2fd(fdnum);
	// Before Step 2 , You had better check the "target" spawned is a execute bin
	// char elfbuf[512];
	// r = readn(fd2num(fd), elfbuf, sizeof(Elf32_Ehdr));
	// if (r < 0)
	// {
	// 	user_panic("read Ehdr failed!");
	// }
	// ehdr = (Elf32_Ehdr *)elfbuf;
	// if ((!usr_is_elf_format((u_char *)ehdr)) || ehdr->e_type == E_NOT_EXEC)
	// {
	// 	user_panic("Not elf or exec!");
	// }
	// Step 2: Allocate an env (Hint: using syscall_env_alloc())
	child_envid = syscall_env_alloc();
	if (child_envid < 0)
	{
		user_panic("Alloc env failed!");
	}
	// Step 3: Using init_stack(...) to initialize the stack of the allocated env
	init_stack(child_envid, argv, &esp);
	// Step 3: Map file's content to new env's text segment
	//        Hint 1: what is the offset of the text segment in file? try to use objdump to find out.
	//        Hint 2: using read_map(...)
	//		  Hint 3: Important!!! sometimes ,its not safe to use read_map ,guess why
	//				  If you understand, you can achieve the "load APP" with any method
	// Note1: Step 1 and 2 need sanity check. In other words, you should check whether
	//       the file is opened successfully, and env is allocated successfully.
	// Note2: You can achieve this func in any way ，remember to ensure the correctness
	//        Maybe you can review lab3
	r = silence_load_elf(fd, child_envid);

	if (r < 0)
	{
		return r;
	}
	size = r;

	struct Trapframe *tf;
	//writef("\n::::::::::spawn size : %x  sp : %x::::::::\n", count * entry_size, esp);
	writef("\n::::::::::spawn size : %x  sp : %x::::::::\n", size, esp);
	tf = &(envs[ENVX(child_envid)].env_tf);
	tf->pc = UTEXT;
	tf->regs[29] = esp;

	// Share memory
	u_int pdeno = 0;
	u_int pteno = 0;
	u_int pn = 0;
	u_int va = 0;
	for (pdeno = 0; pdeno < PDX(UTOP); pdeno++)
	{
		if (!((*vpd)[pdeno] & PTE_V))
			continue;
		for (pteno = 0; pteno <= PTX(~0); pteno++)
		{
			pn = (pdeno << 10) + pteno;
			if (((*vpt)[pn] & PTE_V) && ((*vpt)[pn] & PTE_LIBRARY))
			{
				va = pn * BY2PG;

				if ((r = syscall_mem_map(0, va, child_envid, va, (PTE_V | PTE_R | PTE_LIBRARY))) < 0)
				{

					writef("va: %x   child_envid: %x   \n", va, child_envid);
					user_panic("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
					return r;
				}
			}
		}
	}

	if ((r = syscall_set_env_status(child_envid, ENV_RUNNABLE)) < 0)
	{
		writef("set child runnable is wrong\n");
		return r;
	}
	return child_envid;
}

int spawnl(char *prog, char *args, ...)
{
	return spawn(prog, &args);
}
