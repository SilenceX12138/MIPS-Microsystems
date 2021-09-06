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

