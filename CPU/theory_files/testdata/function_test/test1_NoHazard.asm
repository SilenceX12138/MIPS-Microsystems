ori $1,$0,0x1234
ori $2,$0,0xfffe
lui $3,0xffff
lui $4,0x1919
lui $5,0x1287
addu $6,$1,$2
subu $7,$2,$1
addu $8,$2,$3
subu $9,$4,$5
sw $6,0($0)
sw $7,4($0)
sw $8,8($0)
sw $9,12($0)
lw $10,0($0)
lw $11,4($0)
lw $12,8($0)
beq $1,$2,target
lw $13,12($0)
ori $2,$0,0x1234
nop
nop
beq $1,$2,target
lw $14,12($0)
nop
nop
target:
sw $1,16($0)