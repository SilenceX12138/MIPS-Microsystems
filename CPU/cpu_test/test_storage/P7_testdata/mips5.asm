ori $2, $0, 0x1234
ori $3 $0, 0x5678
li $s0, 0x00007f10
li $t0, 0x00000009
li $t1, 0x0000000b
sw $t0, 4($s0)
sw $t1, 0($s0)
ori $t2, $0, 0xff11
mtc0 $t2, $12

divu $2, $3
mflo $4
divu $4, $3
mflo $2
divu $4, $2
mflo $3

ori $k0, $0, 0x1111
