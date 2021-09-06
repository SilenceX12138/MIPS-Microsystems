#initial
lui $1,0x2819
ori $1,$1,0x9384
lui $2,0x7cfd
ori $2,$2,0x5738
lui $3,0x883c
ori $3,$3,0x8847
lui $4,0x9382
ori $4,$4,0xacfe
sw $1,0($0)
sw $2,4($0)
sw $3,8($0)
sw $4,12($0)
#lh
ori $5,$0,5
addi $5,$5,1
lh $1,0($5)
ori $6,$0,6
ori $7,$0,7
lh $2,2($6)
xori $5,$2,0x8846
addiu $7,$7,1
lui $4,0xfffe
xor $4,$5,$4
lh $3,2($7)
#lb
ori $1,$0,0x827f
xori $1,$1,0x827e
lb $2,0($1)
addiu $1,$1,2
or $3,$1,$2
lb $3,2($1)
ori $2,$0,0x000e
andi $3,$2,0x0006
ori $2,$0,0x9827
andi $5,$2,0x3826
lb $5,1($3)
#lhu
ori $5,$0,5
addi $5,$5,1
lhu $1,0($5)
ori $6,$0,6
ori $7,$0,7
lhu $2,2($6)
xori $5,$2,0x8846
addiu $7,$7,1
lui $4,0xfffe
xor $4,$5,$4
lhu $3,2($7)
#lbu
ori $1,$0,0x827f
xori $1,$1,0x827e
lbu $2,0($1)
addiu $1,$1,2
or $3,$1,$2
lbu $3,2($1)
ori $2,$0,0x000e
andi $3,$2,0x0006
ori $2,$0,0x9827
andi $5,$2,0x3826
lbu $5,1($3)



