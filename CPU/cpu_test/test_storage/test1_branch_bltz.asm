lui $2,0xffff
ori $2,$2,0xfffe
bltz $2,target
ori $2,$0,2119
xori $3,$2,2395
andi $3,$3,4937
addiu $4,$3,7887
target: 
bltz $3,target1
addi $3,$2,293
ori $3,$0,2039
target1:
bltz $0,target2
add $4,$4,2345
ori $4,$0,9392
ori $5,$0,9236
nor $4,$4,$5
target2:
sub $6,$4,$3
lui $4,0xffff
ori $3,$0,0xfffe
ori $2,$0,4
or $5,$0,$2
or $2,$3,$4
sw $2,0($5)
lw $6,4($0)
bltz $6,target3
ori $3,$0,2582
ori $4,$0,8378
ori $2,$0,4526
nor $6,$3,$4
nor $5,$2,$3
xor $7,$3,$6
xor $8,$3,$2
target3:
bltz $8,target4
and $3,$3,$4
and $4,$7,$8
target4:




