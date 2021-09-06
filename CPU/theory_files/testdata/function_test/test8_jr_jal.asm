jal loop1
ori $2,$0,1
ori $3,$0,2
j exit1
ori $4,$0,3
loop1:
jr $31
ori $5,$0,2
exit1:
jal loop2
ori $6,$0,6
ori $7,$0,7
j exit2
ori $8,$0,8
loop2:
ori $9,$0,9
jr $31
ori $10,$0,10
exit2:
jal loop3
ori $11,$0,11
ori $12,$0,12
j exit3
ori $13,$0,13
loop3:
ori $14,$0,14
ori $15,$0,15
jr $31
ori $16,$0,16
exit3:
