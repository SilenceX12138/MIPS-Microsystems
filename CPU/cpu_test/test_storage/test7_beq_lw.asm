ori $2,$0,0x2414
sw $2,0($0)
lw $1,0($0)
beq $1,$2,exit1
ori $3,$0,0xe242
ori $3,$0,0x928e
exit1:
sw $3,4($0)
lw $4,4($0)
beq $3,$4,exit2
ori $5,$0,0x4e32
ori $5,$0,0xff8e
exit2:
sw $5,8($0)
lw $6,8($0)
nop
beq $6,$5,exit3
ori $7,$0,0x3554
ori $7,$0,0x355e
exit3:
sw $7,12($0)
lw $8,12($0)
nop
beq $7,$8,exit4
ori $9,$0,0x3784
ori $9,$0,0xf22e
exit4:
sw $9,16($0)
lw $10,16($0)
nop
nop
beq $9,$10,exit5
ori $11,$0,0x672e
ori $11,$0,0xf22e
exit5:
sw $11,20($0)
lw $12,20($0)
nop
nop
beq $12,$11,exit6
ori $13,$0,0x5345
ori $13,$0,0xf277
exit6:



