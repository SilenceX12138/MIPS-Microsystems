ori $2,$0,1
ori $3,$0,3
sw $3,4($0)
sw $2,8($0)
addu $1,$2,$3
lw $4,0($1)
ori $5,$0,4
addu $1,$1,$5
nop
lw $6,0($1)
sw $6,12($0)
addu $1,$1,$5
nop
nop
lw $7,0($1)
