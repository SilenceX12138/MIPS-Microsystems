li $28, 0
li $29, 0
mtc0 $0, $12
mtc0 $0, $13
lui $9, 0x4111
ori $9, $9, 0x1111
lui $8, 0x4111
ori $8, $8, 0x1111
jal jump
add $10, $8, $9
addu $10, $8, $9
jump:
lui $9, 0x9111
ori $9, $9, 0x1111
sub $10, $8, $9
subu $10, $8, $9
and $10, $9, $8
mfhi $11
mflo $12
or $13, $11, $12

.ktext 0x4180
mfhi $k0
mflo $k0
mfc0 $k0, $12
mfc0 $k0, $13
mfc0 $k0, $14
addu $k0, $k0, 8
mtc0 $k0, $14
eret
