ori $1,$0,122
jal loop1
addu $2,$31,$1
loop1:
ori $3,$0,239
jal loop2
addu $4,$3,$31
loop2:
jal loop3
ori $5,$0,23
loop3:
addu $6,$31,$5
jal loop4
ori $7,$0,55
loop4:
addu $8,$7,$31

