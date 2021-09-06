.text 0x00003000
ori $v0, $0, 0xff11
mtc0 $v0, $12
li $s0, 0x80000010
li $s1, 0x80000003
add $t0, $s0, $s1
lw $t0, 3($0)
sw $t0, 1($0)
sw $t0, 8($s0)
li $t0, 0x00003031
jr $t0
mflo, $t0
lwl $t1, -100($t2)
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
srl $k1, $k1, 2
sll $k1, $k1, 2
mtc0 $k1, $14
return:
eret
mult $k0, $k1