lui $2,0xffff
ori $2,$2,0xfffe
bgezal $2,target1
ori $2,$0,0x3829
addi $3,$2,0x0001
sw $3,0($0)
lw $4,0($0)
bgezal $4,target2
subu $3,$4,$3
ori $2,$0,122
ori $5,$0,9282
j exit1
ori $4,$5,129
target1:
ori $8,$0,2988
addu $7,$8,$2
target2:
ori $8,$31,0
jr $31
subu $2,$2,$3
exit1:
ori $3,$0,9292
ori $4,$0,9292
subu $4,$4,$3
bgezal $4,target3
ori $5,$31,0
lui $8,0x928e
j exit2
subu $8,$8,$5
target3:
jr $31
sw $5,4($0)
exit2:
sw $31,8($0)
nop
nop







