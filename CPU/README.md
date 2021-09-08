# MIPS CPU

> There may be some display mistakes due to GitHub Markdown interpreter, so you can download and read this tutorial.

**The full text has a total of `6138` words, and the recommended reading time is `1~2` hours.**

This project contains a CPU of MIPS structure, a `five-stage` pipeline microprocessor that can support 70 instructions and handle basic exceptions and interrupts according to MIPS principles. Hope you can enjoy it!


## Chapter One Model Top View

<img src="https://i.loli.net/2021/09/08/PqKcgBIjZ6afVm9.png" alt="image-20210908210822976" style="zoom:67%;" />



## Chapter 2 Data Path

1. Implementation method

Engineering method of formal modeling

1. Specific steps

1. Establish a separate model containing each data path component.
2. Determine the input port connection relationship (interface relationship) and functional requirements of each component one by one according to the instruction set.
3.Integrate the data path containing the forwarding multi-selector and integrate the function of the components.

3. Matters needing attention

1. When determining the interface relationship and adding new components, you should follow the idea of ​​``high cohesion and low coupling'', and you need to connect according to the relationship between components rather than just functional classification.

The NPC address calculation of the eg.beq instruction is not completed by the ALU, but the address calculation is encapsulated in the NPC by adding a selector to avoid the interface relationship between the ALU and the PC and complicate the design.

1. The integrated data path not only needs to determine the connection relationship of the ports, but also integrate all the functions that a certain component needs to implement, and sequence and code the functions.
2. Horizontal sorting of table signals: **Op→Sel→We**
3. The order of module port declaration:

| clk | 1st |
| --- | --- |
| reset | 1st |
| Op | 2nd |
| Sel | 3rd |
| We | 4th |

4. Module interface relationship (see the datapath folder for the table)

5. Module function list and number (form controller folder)

6. Module specifications

a) PC:

Module function: output the address of the program currently executed in IM.

Precautions:

1.The PC outputs the byte address, and the IM uses the word address, which needs to be shifted.
2. The PC needs to support the **Sync** reset function.
3. Compared with a single cycle, the PC output is separated from ADD4 and NPC, because NPC is designed to decode and is placed in the ID segment.

PC port definition

| NameInterface | PC |
| --- | --- |
| Direction | Description |
| PC4 | I | Normal PC+4 |
| NPC | I | get branch or jump PC |
| PC | O | output PC |

b)NPC

Module function: Calculate the byte address of the next instruction.

Note: NPC is the only combinational logic component that drives the PC, so the address calculation of the branch instruction needs to be encapsulated in the NPC

NPC port definition

| NameInterface | NPC |
| --- | --- |
| Direction | Description |
| Ins | I | instruction |
| PC | I | get PC |
| equ | I | get sig whether two nums equal |
| NPC | O | output NPC |

c) IM

Module function: store program instructions and output current execution instructions.

Note: IM is a combinational logic component, and the current instruction is valid throughout the cycle.

M port definition
| NameInterface | IM |
| --- | --- |
| Direction | Description |
| PC | I | get PC |
| Ins | O | output instruction executing now |

c) RF

Module function: general register file, read and write operands in instructions.

Precautions:

  1.RF is a sequential logic component and needs to support the **synchronous** reset function.

  2. The internal forwarding of RF can be replaced by forwarding from W to D.
     RF port definition

     | NameInterface | RF |
     | --- | --- |
     | Direction | Description |
     | Ins | I | instruction |
     | RFWe | I | enable RF to be changed |
     | RD1 | O | output R[rs] |
     | RD2 | O | output R[rt] |

d) ALU

Module function: Carry out arithmetic operations in instructions.

Note: The selection signal of the A3 and WD ports must be constructed strictly in accordance with the generated sequence number table.

ALU port definition

| NameInterface | ALU |
| --- | --- |
| Direction | Description |
| A | I | operator1 |
| B | I | operator2 |
| ALU.C | O | result of calculation |
| Zero | O | whether two nums equal |

f)DM

Module function: memory read and write

Note: DM is a sequential logic component and needs to support **synchronization** reset function.

DM port definition

| NameInterface | DM |
| --- | --- |
| Direction | Description |
| Addr | I | addr of memory |
| WD | I | word to write |
| DMWe | I | enable DM to be changed |
| RD | O | data accessible in memory |

g)EXT

Module function: shift and expand immediate data.

Note: The operation of immediate data should be encapsulated in EXT as much as possible for execution.

EXT port definition
| NameInterface | EXT |
| --- | --- |
| Direction | Description |
| Imm | I | Immediate num to be operated |
| Ext | I | Result after operation |

## Chapter 3 Main Controller Design

1. Control signal generation

Method: Use the slicing operation to determine the instruction, and generate a control signal for each instruction separately.

2. Command signal generation

a) Specific steps:

1. Determine the type of instruction: R-type instructions are generated by funct, and the other two instructions are generated by opcode.
2. The instruction is sliced ​​and extracted, and the instruction signal is generated through the AND operation.

b) Matters needing attention:

1. When generating instructions, you need to use **instruction type** to control the output.

eg. The imm field of the I/J instruction may generate an R-type instruction at the same time, but the output signal of the modified R-type instruction cannot be made effective, so the instruction type needs to be added to the judgment signal. On the contrary, because the all-zero opcode field of R is not Corresponding to I/J instructions, so there is no need to add instruction type judgment to generate I/J instructions.

1. Controller port declaration sequence:

| Ins | 1st |
| --- | --- |
| Op | 1st |
| Sel | 2nd |
| We | 3rd |

2.When generating the operation signal, follow the signal table (including the number) corresponding to the instruction to generate it.

3. Operation signal generation

a) Specific steps:

1. Generate instruction signal according to instruction set RTL description
2. Use the if statement to generate the operation signal corresponding to the instruction
3. Generate control signal codes for instructions

b) Matters needing attention:

1. The operating signal is directly generated using constants and annotated.

eg.ALUOp=5; //description of ALUOp5

1.Each instruction needs to assign values ​​to all operating signals, and all unused ones are treated as 0.

(Not assigning a value will keep the command signal value unchanged, causing confusion in the operation signal.)

1. The operation serial number used in the controller and the operation serial number used in each sub-module must be the same.

4. Specific realization pattern

<img src="https://i.loli.net/2021/09/08/7UYbOuwlhCK81ij.png" alt="image-20210908211910436" style="zoom: 67%;" />

Slicing operation generates command signal

<img src="https://i.loli.net/2021/09/08/1XDcUOgb5w9slxZ.png" alt="image-20210908211916465" style="zoom:67%;" />

Command-oriented operation signal generation

## Chapter 4 CPU Test

1. Test instruction set

MIPS-C0 {addu, subu, ori, lw, sw, beq, lui, jal, jr,nop}

1. Instructions for test program design
  1. Comprehensive testing

eg1. Consider +/+-/-- three situations when data comparison is involved

eg2. The branch instruction considers the forward and backward jump methods

  1. The number of instructions cannot exceed the IM memory limit
  2. Do not use instructions other than the instruction set
  3. Compare according to Mars

1. Test program documentation (see the test folder of the compressed package)

1. Test process

    1. Perform functional tests one by one when adding instructions (don't deliberately consider taking risks, just ensure that the functions are correct)
    2. After the instruction is added, according to 6 types of forwarding, 3 types of pauses to generate 9 types of **feature templates**
    3. Replace the template according to the instruction fetch feature

1. Instruction test expected output (see the integrated output of the evaluation machine)

## Chapter 5 Thinking of Optimizing Design

* When the machine code is converted from hexadecimal to binary **Previous**** 0 cannot be omitted (the bit width is guaranteed to be 32 bits)

* **When accessing IM and DM, the physical address value (**byte** address eg.PC) needs to be **divided by **** 4** to become the logical address value (**word** address) **

* After changing** the number of instructions **cannot** in the txt file **delete directly** change the line and test the CPU again (the address of the branch and jump instructions may change)

* The **non-sequential** operation of the instruction (eg. read)** operation can be considered to be completed in the low-level period before the rising edge

  * eg.sb can obtain the corresponding word of the memory and wait for the rising edge to be written into the memory after the combinational logic operation is performed outside the module

* Block assignment is used in the initial block

* Automatic for reusable functions is placed after function ****

  * eg.function automatic [name];

* MUX adopts **parameter** naming **operation** to avoid conflicts and facilitate modification.

* Instructions are all expressed in ** uppercase ** to prevent duplication with verilog keywords.

* Use comments to explain the constants after each operation signal corresponding to the instruction

* In the control signal table, the serial number can only be incremented and cannot be inserted midway.

* The non-blocking assignment of the PC allows the write to the register file to be completed **before** the failure of RFWe.

* The overall flow of Ins, and the analysis is completed in each flow level.

* Internal forwarding can be replaced by forwarding from **W** to **D**

* The connotation of the **load** feature in violent forwarding: the instruction can only determine the data to be written to the register at the **W** level.

* There must be various levels of **write enable signal** in the judgment conditions of forwarding and pause to avoid **errors that cannot be written by** data **redirecting or pause

* stall\_load and stall\_beq can be valid at the same time (there can be **more than one** pause feature valid at the same time)

* The essence of the role of $signed(): the highest bit of the current number is parsed as the sign bit

  1.$signed(PC)+4+$signed(Imm)\*4;

  When the bit width of Imm is different from PC, adding $signed can make imm perform sign extension, so that it can be added to PC to get the correct result.

  2. $signed(B)\&gt;\&gt;\&gt; shamt realizes right shift of arithmetic

  When B\&gt;\&gt;\&gt;shamt, B is an unsigned number by default, so the high bits are automatically filled with 0.

  3. The impact of $signed() on size comparison

  When the bit width is different, it will be compared after **sign expansion.When the bit width is the same, it will be directly compared according to the signed number.

* Negative number** means **-** 32&#39;d4

* Commands such as lwr/lwl/sw have enough time for the load command to fetch memory data because the stage of using rt is at the M level, so there is no need to pause even if there is a conflict with the load command.

* For instructions with special memory access methods (eg.movz/lwpl), the both attribute is used. The essence is to ensure that the control signal will not change from **D**** level**, so it is not necessary Change the risk control module to judge the suspension of this instruction.

* madd is a special type of R instruction (the op field is not 0)

* Only sequential logic components need timescale to determine the time granularity

* When comparing wire/reg and negative numbers, if the bit width is the same, it has nothing to do with whether there is $signed()

* The difference between unsigned multiplication and signed multiplication is reflected in **negative multiplication**

* For registers that may not be written **directly read**, initialization is required.
  * eg.RF/HI/LO need to be initialized, but the pipeline register is not needed.
  
* The essence of output reg is a **register** of the **current module**, so it can be used in the module as a judgment condition (the value is the value of the rising edge **before**).

* Steps to add instructions:

  ①Write out RTL-level operations

  ②Confirm the instruction behavior in MARS (pay special attention to whether the link register needs to meet the jump condition)

  ③Create datapath (**New port** is highlighted in the table)

  ④Establish a control signal table

  ⑤Change the datapath (after modifying the module, make corresponding changes at the top level **declare a signal when adding a port**)

  ⑥Generate control signal

  ⑦Local test (comprehensive)

* IM only restricts external interrupts, and does not restrict exception handling.

* CP0 can be imagined to be placed in M ​​level

* The comparison between RST and RST\_ext when judging overflow requires **signed**: $signed(A+B) and $signed(A)+$signed(B)

  * The former will calculate A+B and **after truncation**, perform sign bit extension
  * The latter will directly sign-extend the result and assign it to the lvalue

* CP0 is initialized to all 0s except PRId
* Safe BD position judgment method: D-level judgment

* DM\_RD and CP0\_RD **not merged** because CP0 is not addressed in memory but DM\_RD and Pr\_RD can be merged

* When an exception occurs, clear **all** pipeline registers, including W-level (M-level abnormal instructions can not be executed)

* When an exception/interruption occurs, M-level instructions cannot write to the memory

* Cause is a read-only memory, which cannot be changed by the programmer, but can only be changed by the hardware's own information (eg. exception).

* The external device number of the Cause register: The interrupt request signal output by Timer0 is connected to **HWInt[2]** (the lowest interrupt bit), and the interrupt request signal output by Timer1 is connected to **HWInt[3]**, from MIPS Micro The interrupt request signal outside the system is connected to **HWInt[4]**.

* $15 refers to the register number 15 (do not look at the value in $15)

* GPR[$15] is the value of the register

* Common cathode digital tube lights up with 0 signal

* The operation implemented in the exception adopts the method of first **unified jump** using eret after each label

* The operation of updating the value is placed in the outer loop, and the specific operation is placed in the exception

## Chapter 6 Violent Forwarding & Reflections on Engineering Methods

1. Essential Thoughts

The essential ideas of the two are the same:

When the result of the previous command is too late to be used, forwarding is used.

There is no way to use a pause before the new value is ready.

1. The difference in implementation method

1. Violent forwarding
  1. Forwarding: Regardless of the register requirements of the current instruction, as long as there is a data hazard in the machine code, it will be forwarded. Because of the existence of the pause mechanism, when the instruction actually uses the register value, it must be a new value; if it is not used, the new value It will not have an impact.
  2. Pause: Based on the analysis of all instruction memory access methods, three separate characteristics are extracted: store/both/single can realize any pause mechanism through the combination of the three. (The two are obtained by observation in the Excel table. (One row can cover all cases)
2. Engineering method

Based on the known instruction set, the instructions are divided into different categories according to the memory access method (Tnew&amp;Tuse), and then the forwarding and suspension are analyzed in detail.

  1. Forwarding: forwarding only when the instruction is needed, **do not forwarding if not needed**, but there may be hidden needs that have not been met (eg.sw uses rt at M level. If you only consider rt forwarding at M level, Maybe there is no conflict at this time (the change to rt has been quietly completed before sw is used), so rt has not been updated. Therefore, the forwarding of rt needs to be considered at each level before).
  2. Pause: Determine whether to pause or not after comparing the time according to the specific behavior of each instruction category.

1. The accelerated thoughts of violent forwarding

Compared with the engineering method, the disadvantage of violent forwarding is that if the analysis of the behavioral characteristics of the instruction is not comprehensive, it will cause unnecessary suspension. (eg.lw and addi’s rt conflict, if the suspension judgment is only based on load, it will be suspended. , But not actually needed)

Therefore, violent forwarding has accelerated optimization points in the three instruction features.

1. load
  1. Determine whether rt will be used by ALU (ALU\_B\_Sel==0)

Q: Is there a situation where the command does not use alu but the control signal of ALU\_B\_Sel selects rt by default, and the redundant stall\_load is caused?

A: If ALU\_B\_Sel is defaulted to 0, that is, there is no need to use ALU. It can only be a jump instruction or branch instruction, and when these instructions are suspended because the load is at E level, it is not because of rt So, there is no alu without using rt, but the unexpected stall\_load caused by ALU\_B\_Sel=0 is valid

  1. Determine whether the register written by load is $0 (A3\_E==0)
1. both
  1. Determine whether the write register is $0 (A3\_E/A3\_M/A3\_W==0)
2. single
  1. Determine whether the write register is $0 (A3\_E/A3\_M/A3\_W==0)

## Chapter 7 Thinking about the CPU structure of the pipeline

Q1: Why is the ADD4 module set up for ordinary PC updates, instead of maintaining the integrity of the structure so that the NPC is always allowed to drive the PC?

A1: The five-stage pipeline separates the PC and NPC in different areas. Due to the existence of the D pipeline stage register in the middle, there is a one-cycle delay in the value transfer between the two, that is, the PC obtained by the NPC is the PC in the previous clock cycle Therefore, PC+4 cannot be completed by the NPC, and ADD4 needs to be set separately to complete the ordinary update. At the same time, this clock delay causes the PC (module) to be updated to the new PC (value) output of the NPC corresponding to the D-level pipeline register The address time is delayed by one cycle, which is why it is necessary to set a delay slot for branch and jump instructions. Moreover, because NPC is related to instructions, it is not placed in IF but in ID.

Q2: The specific impact of the delay slot on jal and beq.

A2:

1. jal

When the instruction in D is jal, NPC calculates the PC value that needs to be jumped to and the PC value that needs to be jumped back. When the next rising edge of the clock comes, jal enters the E level, but the one that enters the D level does not need to be jumped The instruction at the PC that arrives, because the PC is only updated at the rising edge that has just arrived, so it enters the D-level instruction that originally followed jal, which is the delay slot instruction. So when calculating the PC value that needs to be jumped back , You need to change the PC+8 corresponding to jal instead of +4.

1. beq

When the instruction in D is beq, the analysis of the delay slot instruction is the same as jal. However, when calculating the PC value that needs to be jumped to, it is not necessary to use PC+8+offset. Because compilation optimization refers to the transition from high-level language to assembly language At the time, the order of instructions is adjusted, that is, the delay slot is filled. Therefore, for the machine code generated by the assembler that has been filled, the offset corresponding to the CPU executing beq has been considered in MARS. Therefore, the PC calculation formula of beq is not affected by the delay slot.

Q3: The reason why CMP is set separately for level D and the difference from the comparison function in ALU.

A3: The control hazard of the pipeline CPU comes from the uncertainty of the execution direction of the branch statement. If beq is allowed to flow too deep in the pipeline, when a jump needs to occur, it will cause the forced emptying of the pipeline, which will have a greater impact on performance. Therefore, if the comparison link of beq is advanced to the ID part, the loss of emptying can be minimized. If the delay slot technology is used, a full-speed pipeline that does not consider pauses can be realized. Therefore, the CMP is set to serve the NPC of the branch instruction, and in the ALU The comparison function of is to satisfy the operation of other instructions (eg.slt). Therefore, the two are only similar in function, but the components and meanings of the drive are completely different.

## Chapter 8 Project Environment Precautions

* First run for 100ns and then 10ns for progressive realization **Command debugging**

* When adding a new control signal that is not available in other commands, you can start with always ** Separately ** Set this signal to zero **

* Due to the invariance of verilog signals, nop needs to be **separately** defined for command signals.

* New port uses **underscore** nomenclature

* Check whether **IM** is updated to the content in code.txt before checking the cpu

* The calculation formula contains both signed numbers and unsigned numbers, and it is all handled as **unsigned numbers**, so $signed() is used for each register in beq's instruction calculation.

* After creating a new verilog project, add source can add all .v files, but it will not change the path of the .v files.

* When the slicing area value contains variables, if the bit width is a variable, use **loop** for bit assignment, otherwise use prompt format for slicing.

  * eg.in[sel\*4+3: sel\*4] does not work.

* Prompt: in[(sel\*4+3)-:4]

* aligned adj. Word alignment (byte address is a multiple of 4)

* When the returned result is empty, it may be that the file size exceeds 4MB.

* Three operations of pause:

1. Freeze the **PC** value: Keep the next instruction corresponding to the D pipeline level instruction unchanged.
2. Freeze **D** flow level
3. Clear **E** pipeline level

* **Synchronous** Clearing to zero is equivalent to not letting Ins\_D enter E and inserting a null instruction.

* The forwarded value ** can only be from the register, otherwise it will oscillate.

* The instance generated by the custom module must be named, and the instance name and port name in different files can be the same.

* **Macro** definitions in different .v files will not affect each other when **not included.

* When considering the delay slot, if the instruction that jal jumps to and the delay slot instruction are the same, the delay slot instruction will be executed twice.

* 16KB IM exceeds the MARS limit (MARS up to 1024\*4B=4KB)

* The initial value of the $28/$29 register in MARS is not 0, so the generated test program needs to set these two registers to zero first.

* $signed() has different characteristics in the always and ternary operators, and the always statement is used uniformly.

* The while loop cannot be used to jump out of the break, and all the jump out conditions are directly used as the loop judgment conditions.

* Delay slot exceptions cannot be handled in MARS

## Chapter 9 Analysis of Forwarding Suspension Mechanism

**1. Stall mechanism (Stall)**

1. The meaning of the suspension

Pause is the most straightforward way to solve data hazards. Pause is to immediately determine whether there will be conflicts with other pipeline instructions after Ins\_D completes the decoding at the ID level. If so, pause the update of the instructions and wait for the conflict. After disappearing, the pipeline reads new instructions.

2. Judgment of suspension

The judgment of suspension needs to adopt the Tuse/Tnew model. Tuse means that it is currently at the **ID** level (only the ID level needs to be considered, because the conflict that occurs when each instruction enters the pipeline can already be judged.) There are still several clock cycles for instructions to use register file data. Tnew represents the clock cycles required for other levels of instructions to generate new register values ​​and store them in the pipeline register. When a data hazard is generated, Tuse and Tnew are judged, if Tuse\&lt;Tnew shows that there is no way to get the latest register value required by ID-level instructions at normal times, and the pause method is used to achieve the reduction of Tnew and the constant change of Tuse.

3. The realization of the suspension

According to the memory access characteristics of the instruction, it is implemented by violent forwarding.

4. Tuse&amp;Tnew mechanism analysis

①Data requirement Tuse: When the instruction is at **D**** level**, the corresponding data must be used after how many clock cycles have passed.

eg1. beq Tuse=0/addu Tuse=1

eg2. sw needs the data of GPR[rs] at the EXE level to calculate the address, and needs GPR[rt] at the MEM level to store the value, so for the rs data, its Tuse\_rs=1, for the rt data, its Tuse\_rt=2. (A command can have two Tuse values)

②Data output Tnew: A certain instruction located in **a** pipeline stage, how many clock cycles it takes to calculate the result and store it in the pipeline stage register.

eg. For the addu instruction, when it is at the EX level, the result has not been stored in the pipeline stage register, so its Tnew=1 at this time, and when it is at the MEM or WB level, the result has been written into the pipeline at this time Level register, so Tnew=0 at this time.

Feature 1: It is a **dynamic value**, each instruction has a different Tnew value at different stages of the pipeline

Feature 2: An instruction will only have one Tnew value at a time (an instruction has only one result)

**Two, forwarding mechanism (Forwarding)**

1. The meaning of forwarding

Forwarding is a mechanism adopted to optimize the suspension resolution of data hazards. The essence of data hazards is that instructions exchange data through the register file. (And does not include pipeline registers, because the effective data of the pipeline registers will eventually be written to the register file) At the same time, the DM All read and write operations occur in the MEM stage. There will be no D-level read similar to RF in the middle. The time interval of W-level write is for other instructions to read and access. Therefore, the only possible data hazards are RS and RD1 and RD2 corresponding to RD1 and RD2. RT register.

2. Judgment of forwarding

The theoretical basis of forwarding is the same as the suspension, which is the Tnew/Tuse model. In the suspension, we only need to analyze the type relationship between Ins\_D and the subsequent levels of instructions, because the suspension depends on the Tuse of Ins\_D and others. The relationship between Tnew at all levels. However, in the forwarding mechanism, the new value of the register may be required at the D/E/M level, so it is necessary to discuss the types of sub-instructions at all levels when judging. Depending on the data path, it is also That is, the value of Tuse/Tnew at all levels, we can divide the instructions into 9 categories (the nop type is set to avoid the type remaining unchanged when a null instruction occurs). According to different types of rs/rt Tuse/Tnew When Tnew≤Tuse, forwarding can be used to resolve data conflicts.

3. Realization of forwarding

First of all, it is clear that the source of forwarding can only be the pipeline register or RF itself, otherwise it will increase the delay of the CPU critical path. Therefore, the forwarding can transmit the V1/V2 of all levels to the required port through the MUX. When the data is risky, choose the data that is close to the level for forwarding, because the nearest data must be the latest. Therefore, a separate controller is set up for forwarding to judge the D/E/M/W level signals. Among them, If the conflict occurs between W and D, since the new value is about to be written to the register, the internal forwarding of the register can be used, but the forwarding of W to D can also be used to simplify the combinatorial logic inside the RF. At the same time, it should be noted that any The access to register 0 can only forward the value of 0, even if the value of $0 read by the D stage is always stored in the pipeline register, it is equivalent to making the selection signal of each stage of pipeline MUX to be 0.