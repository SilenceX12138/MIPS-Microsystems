ori $1,$0,2039
ori $2,$0,3934
j exit
addu $3,$1,$2
exit:
sw $3,0($0)