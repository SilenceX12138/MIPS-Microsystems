.text 0x00003000
li $s0, 0x80000010
li $s1, 0x80000003
add $t0, $s0, $s1
addu $t1, $s0, $s1
li $s0, 0x00000010
sub $t0, $s1, $s0
li $s0, 0x7fffffff
addi $t0, $s0, 1
mtlo $0
lw $t0, 3($0)
mult $s0, $s1
mflo $a0
lh $t0, 1($0)
li $s0, 0x00003000
lb $t0, 0($s0)
div $s0, $s1
sw $t0, 1($0)
mflo $a0
sh $t0, 3($0)
li $s0, 0x00007f10
mtlo $s0
sb $t0, 0($s0)
mflo, $t0
sw $t0, 8($s0)
li $t0, 0x00003071
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
