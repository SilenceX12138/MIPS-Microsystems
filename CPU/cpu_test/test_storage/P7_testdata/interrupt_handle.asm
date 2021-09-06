ori $k0, $0, 0
ori $k1, $0, 0x7f00
sw $k0, 0($k1)
ori $30, $0, 1
lw $k0, 4($k1)
addu $k0, $30, $k0
sw $k0, 4($k1)
ori $k0, $0, 0x3014
mtc0 $k0, $14
eret
