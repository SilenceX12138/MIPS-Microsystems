# MIPS Microsystems

## Overview

This repository contains three projects at core components of MIPS Microsystems.

* [**CPU**](https://github.com/SilenceX12138/MIPS-Microsystems/tree/master/CPU): a `five-stage` pipeline microprocessor that can support 70 instructions and handle basic exceptions and interrupts according to MIPS principles
* [**Operating System**](https://github.com/SilenceX12138/MIPS-Microsystems/tree/master/Operating%20System): an operating system based on MIPS architecture with Linux kernel to support `virtual memory`, process `management` and `system call`
* [**Compiler**](https://github.com/SilenceX12138/MIPS-Microsystems/tree/master/Compiler): a multi-pass compiler for `C0` programming language and MIPS assembly language

## CPU

> **Please refer to the project [README](https://github.com/SilenceX12138/MIPS-Microsystems/tree/master/CPU) for detailed information.**

This is a `32-bit` microprocessor conforms to MIPS architecture.

* This CPU is realized with `Verilog` to make sure that it can be burnt onto a real-world chip or FPGA.

* For displaying the work flow of CPU, changes of memory and registers are printed to the screen, so that the correctness can be checked and evaluated easily.

  <img src="https://i.loli.net/2021/09/09/xk1jZbHDrUfSKFz.png" alt="image-20210909094513682" style="zoom:50%;" />

* Below is an example of simulation result from `XILINX`

  ![lockup.jpg](https://forums.xilinx.com/t5/image/serverpage/image-id/45181i8D2B03B232CCA497/image-size/original?v=1.0&px=-1)

  > Strongly suggest using `ISE` or `Vivado` to develop your own functions.

## Operating System

> **Please refer to the project [README](https://github.com/SilenceX12138/MIPS-Microsystems/tree/master/Operating%20System) for detailed information.**

This is a basic operating system with Linux Kernel under MIPS architecture. When realizing it, all functions are divided into 5 parts below.

* **Lab1**
  * Understand MIPS architecture from operating system
  * Learn the booting process of operating system
  * Capture the structure and function of `ELF` file
* **Lab2**
  * Learn the memory layout of MIPS
  * Capture the memory management with link list
  * Realize memory allocation and releasing
* **Lab3**
  * Create a process and run it
  * Realize clock interrupt
  * Realize process scheduling and combine it with clock interrupt
* **Lab4**
  * Understand how processes communicate with each other
  * Realize `fork` function
  * Handle page fault interrupt
* **Lab5**
  * Understand what file system is
  * Realize device driver
  * Learn the designing concept of microkernel

> **Note: Theoretically, this OS is able to be deployed on an ARM micro controller like `Raspberry PI`.**

