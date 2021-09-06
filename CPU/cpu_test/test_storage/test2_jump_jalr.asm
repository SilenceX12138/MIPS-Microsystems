ori $2,$0,0x3000
addi $2,$2,0x001c
jalr $1,$2
xor $3,$1,$2
nor $4,$2,$3
j exit
lui $3,0x2928
addu $3,$3,$1
jr $1
subu $3,$3,$1
exit:
ori $6,$0,0x304c
ori $4,$0,0x304c
sw $4,0($0)
lw $5,0($0)
jalr $1,$5
or $4,$4,$2
subu $6,$6,$2
j exit1
nop
bne $4,$6,target
nor $7,$5,$3
sub $5,$1,$7
target:
jr $1
add $5,$1,$7
exit1: