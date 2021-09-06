ori $2,$0,0x1234
ori $1,$0,0x1234
beq $1,$2,exit1
ori $3,$0,0x1342
ori $3,$0,0x928e
exit1:
ori $4,0x1342
beq $3,$4,exit2
ori $5,$0,0x1e42
ori $5,$0,0xff8e
exit2:
ori $6,$0,0x1e42
nop
beq $6,$5,exit3
ori $7,$0,0x1e54
ori $7,$0,0xfcae
exit3:
ori $8,$0,0x1e54
nop
beq $7,$8,exit4
ori $9,$0,0x2354
ori $9,$0,0xf22e
exit4:
ori $10,0x2354
nop
nop
beq $9,$10,exit5
ori $11,$0,0x342e
ori $11,$0,0xf22e
exit5:
ori $12,$0,0x342e
nop
nop
beq $12,$11,exit6
ori $13,$0,0x2345
ori $13,$0,0xf277
exit6:



