li $28, 0
li $29, 0
ori $9, 0x2943
ori $8, $0, 0x3019
mult $8, $9
jr $8
and $10, $9, $8
mfhi $11
mflo $12
or $13, $11, $12

.ktext 0x4180
mfc0 $k0, $12
mfc0 $k0, $13
mfc0 $k0, $14
addu $k0, $k0, 4
mtc0 $k0, $14
mfhi $k0
mflo $k0
li $k0, 0
eret
