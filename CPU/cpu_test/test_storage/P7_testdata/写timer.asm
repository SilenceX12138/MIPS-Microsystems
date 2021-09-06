li $28, 0
li $29, 0
ori $2, $0, 0xfc01
mtc0 $2, $12
ori $9, 0x0009
ori $8, $0, 0x7f00
ori $10, $0, 0x0006
mult $8, $9
sw $9, 0($8)
sw $10, 4($8)
lw $11, 0($8)
lw $11, 4($8)
lw $11, 8($8)
and $10, $9, $8
mfhi $11
mflo $12
or $13, $11, $12

.ktext 0x4180
mfc0 $k0, $12
mfc0 $k0, $13
mfc0 $k0, $14
mtc0 $k0, $14
mfhi $k0
mflo $k0
ori $9, 0x0009
sw $9, 0($8)
li $k0, 0
eret
