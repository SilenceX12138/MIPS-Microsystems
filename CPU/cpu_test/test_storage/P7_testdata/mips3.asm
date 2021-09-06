.text 0x00003000
li $s0, 0x00007f00
li $t0, 0x00000010
li $t1, 0x00000009
sw $t0, 4($s0)
sw $t1, 0($s0)
li $s0, 0x00007f10
li $t0, 0x00000111
li $t1, 0x0000000b
sw $t0, 4($s0)
sw $t1, 0($s0)
ori $v0, $0, 0xff11
mtc0 $v0, $12
go:
beq $0, $0, go
nop


.ktext 0x00004180
mfc0 $k0, $13
mfc0 $k1, $14
srl $k0, $k0, 2
andi $k0, $k0, 0x001f
beq $k0, $0, return
nop
addiu $k1, $k1, 4
mtc0 $k1, $14
eret
return:
mfc0 $k0, $13
srl $k0, $k0, 10
andi $k0, $k0, 0x003f
li $t0, 1
li $t1, 2
li $t2, 4
or $v0, $t0, $k0
beq $v0, $0, pass1
nop

pass1:
or $v0, $t0, $k0
beq $v0, $0, pass2
nop
li $s0, 0x00007f00
lw $t0, 0($s0)
ori $t0, $t0, 0x0001
sw $t0, 0($s0)
j pass3

pass2:
or $v0, $t0, $k0
beq $v0, $0, pass3
nop
lw $a0, 0($0)
addiu $a0, $a0, 1
sw $a0, 0($0)
j pass3

pass3:
eret
ori $s0, $0, 0xffff