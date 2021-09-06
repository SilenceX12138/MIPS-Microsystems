.text
lui $1,0xffff
ori $1,$1,0xfffe
lui $2,0xffff
ori $2,$2,0xffff
mult $1,$2
mflo $2
bgtz $2,t1
ori $3,$0,3
ori $3,$0,4
t1:
ori $1,$0,1
lui $2,0xffff
ori $2,$2,0xfffe
mult $1,$2
mflo $2
bltz $2,t2
ori $3,$0,3
ori $3,$0,4
t2:
ori $1,$0,1
lui $2,0xffff
ori $2,$2,0xfffe
multu $1,$2
mflo $2
bltz $2,t3
ori $3,$0,3
ori $3,$0,4
t3:
ori $1,$0,1
lui $2,0xffff
ori $2,$2,0xfffe
div $2,$1
mflo $2
bgtz $2,t4
ori $3,$0,3
ori $3,$0,4
t4:
ori $1,$0,1
lui $2,0xffff
ori $2,$2,0xfffe
divu $2,$1
mflo $2
bgez $2,t5
ori $3,$0,3
ori $3,$0,4
t5:
lui $1,0xffff
ori $1,$1,0xfffe
lui $2,0xffff
ori $2,$2,0xffff
div $1,$2
mflo $2
bgtz $2,t6
ori $3,$0,3
ori $3,$0,4
t6:
lui $1,0xffff
ori $1,$1,0xfffe
lui $2,0xffff
ori $2,$2,0xffff
divu $1,$2
mflo $2
blez $2,t7
ori $3,$0,3
ori $3,$0,4
t7:
lui $1,0xffff
ori $1,$1,0xfffe
lui $2,0xffff
ori $2,$2,0xffff
divu $1,$2
mflo $2
bgez $2,t8
ori $3,$0,3
ori $3,$0,4
t8:
lui $1,0xffff
ori $1,$1,0xfffe
lui $2,0xffff
ori $2,$2,0xffff
multu $1,$2
mflo $2
ori $4,$0,2
bgtz $2,t11
ori $3,$0,3
ori $3,$0,4
t11:
lui $1,0xffff
ori $1,$0,0xfffc
lui $2,0xffff
ori $2,$2,0xfffe
multu $1,$2
mflo $2
xori $4,$4,3     
bltz $2,t21
ori $3,$0,3
ori $3,$0,4
t21:
ori $1,$0,1
lui $2,0xffff
ori $2,$2,0xfffe
mult $1,$2
mflo $2
addi $8,$4,3
bltz $2,t31
ori $3,$0,3
ori $3,$0,4
t31:
ori $1,$0,1
lui $2,0xffff
ori $2,$2,0xfffe
div $2,$1
mflo $2
andi $8,$4,5
bgtz $2,t41
ori $3,$0,3
ori $3,$0,4
t41:
lui $1,0xffff
ori $1,$1,0xffff
ori $2,$0,2
divu $2,$1
mflo $2
addiu $5,$4,5
bgez $2,t51
ori $3,$0,3
ori $3,$0,4
t51:
lui $1,0xffff
ori $1,$1,0xffff
ori $2,$2,2
div $2,$1
mflo $2
nor $8,$4,$5
bgtz $2,t61
ori $3,$0,3
ori $3,$0,4
t61:
lui $1,0xffff
ori $1,$1,0xfffe
lui $2,0xffff
ori $2,$2,0xffff
divu $1,$2
mflo $2
nor $6,$1,$2
blez $2,t71
ori $3,$0,3
ori $3,$0,4
t71:
lui $1,0xffff
ori $1,$1,0xfffe
lui $2,0xffff
ori $2,$2,0xffff
divu $1,$2
mflo $2
and $5,$1,$2
bgez $2,t81
ori $3,$0,3
ori $3,$0,4
t81:
lui $1,0xffff
ori $1,$1,0xfffe
lui $2,0xffff
ori $2,$2,0xffff
mult $1,$2
mflo $2
ori $4,$0,2
ori $5,$0,3
beq $4,$2,t12
ori $3,$0,3
ori $3,$0,4
t12:
lui $1,0xffff
ori $1,$0,0xfffc
lui $2,0xffff
ori $2,$2,0xfffe
multu $1,$2
mflo $2
xori $4,$4,3
ori $5,$0,8     
bne $2,$5,t22
ori $3,$0,3
ori $3,$0,4
t22:
ori $1,$0,1
lui $2,0xffff
ori $2,$2,0xfffe
mthi $2
mfhi $2
addi $8,$4,3
addi $8,$8,1
bne $8,$2,t32
ori $3,$0,3
ori $3,$0,4
t32:
ori $1,$0,2
ori $2,$2,9
div $2,$1
mfhi $2
andi $8,$4,5
ori $5,$0,1
bne $5,$2,t42
ori $3,$0,3
ori $3,$0,4
t42:
lui $1,0xffff
ori $1,$1,0xffff
ori $2,$0,2
divu $2,$1
mflo $2
addiu $5,$4,5
sub $5,$5,$4
bgez $2,t52
ori $3,$0,3
ori $3,$0,4
t52:
lui $1,0xffff
ori $1,$1,0xffff
ori $2,$2,2
div $2,$1
mflo $2
nor $8,$4,$5
subu $7,$8,$2
bgtz $2,t62
ori $3,$0,3
ori $3,$0,4
t62:
lui $1,0xffff
ori $1,$1,0xfffe
lui $2,0xffff
ori $2,$2,0xffff
divu $1,$2
mflo $2
nor $6,$1,$2
add $6,$3,$4
blez $2,t72
ori $3,$0,3
ori $3,$0,4
t72:
lui $1,0xffff
ori $1,$1,0xfffe
lui $2,0xffff
ori $2,$2,0xffff
divu $1,$2
mflo $2
and $5,$1,$2
and $3,$4,$5
bgez $2,t82
ori $3,$0,3
ori $3,$0,4
t82:
beq $0,$0,t82
nop











