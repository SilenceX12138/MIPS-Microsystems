/*
 * operations on IDE disk.
 */

#include "fs.h"
#include "lib.h"
#include <mmu.h>

// Overview:
// 	read data from IDE disk. First issue a read request through
// 	disk register and then copy data from disk buffer
// 	(512 bytes, a sector) to destination array.
//
// Parameters:
//	diskno: disk number.
// 	secno: start sector number.
// 	dst: destination for data read from IDE disk.
// 	nsecs: the number of sectors to read.
//
// Post-Condition:
// 	If error occurred during read the IDE disk, panic.
//
// Hint: use syscalls to access device registers and buffers
void ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs)
{
	// 0x200: the size of a sector: 512 bytes.
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = 0;
	u_int dev_addr = 0x13000000;
	char read_op = 0;
	int r;

	while (offset_begin + offset < offset_end)
	{
		u_int total_offset = offset_begin + offset;
		// set IDE ID
		if (syscall_write_dev(&diskno, dev_addr + 0x10, 4))
		{
			user_panic("ide_read has problem 1\n");
		}
		// set offset
		if (syscall_write_dev(&total_offset, dev_addr + 0x00, 4))
		{
			user_panic("ide_read has problem 2\n");
		}
		// set read_op
		if (syscall_write_dev(&read_op, dev_addr + 0x20, 1))
		{
			user_panic("ide_read has problem 3\n");
		}
		// get return value
		if (syscall_read_dev(&r, dev_addr + 0x30, 4))
		{
			user_panic("ide_read has problem 4\n");
		}
		if (r == 0)
		{
			user_panic("ide_read has problem 5\n");
		}
		// read data
		if (syscall_read_dev((u_int)(dst + offset), dev_addr + 0x4000, 0x200))
		{
			user_panic("ide_read has problem 6\n");
		}

		offset += 0x200;
	}
}

// Overview:
// 	write data to IDE disk.
//
// Parameters:
//	diskno: disk number.
//	secno: start sector number.
// 	src: the source data to write into IDE disk.
//	nsecs: the number of sectors to write.
//
// Post-Condition:
//	If error occurred during read the IDE disk, panic.
//
// Hint: use syscalls to access device registers and buffers
void ide_write(u_int diskno, u_int secno, void *src, u_int nsecs)
{
	// Your code here
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = 0;
	u_int dev_addr = 0x13000000;
	char write_op = 1;
	int r;

	writef("diskno: %d\n", diskno);

	while (offset_begin + offset < offset_end)
	{
		u_int total_offset = offset_begin + offset;
		// set IDE ID
		if (syscall_write_dev(&diskno, dev_addr + 0x10, 4))
		{
			user_panic("ide_write has problem 1\n");
		}
		// set offset
		if (syscall_write_dev(&total_offset, dev_addr + 0x00, 4))
		{
			user_panic("ide_write has problem 2\n");
		}
		// write data
		if (syscall_write_dev((u_int)(src + offset), dev_addr + 0x4000, 0x200))
		{
			user_panic("ide_write has problem 4\n");
		}
		// set operation
		if (syscall_write_dev(&write_op, dev_addr + 0x20, 1))
		{
			user_panic("ide_write has problem 3\n");
		}
		// get return value
		if (syscall_read_dev(&r, dev_addr + 0x30, 4))
		{
			user_panic("ide_write has problem 5\n");
		}
		if (r == 0)
		{
			user_panic("ide_write has problem 6\n");
		}
		offset += 0x200;
	}
}
