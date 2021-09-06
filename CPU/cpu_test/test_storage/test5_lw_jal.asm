ori $2,$0,5643
sw $2,0($0)
jal loop1
lw $1,-0x3010($31)
loop1:
ori $3,$0,8768
sw $3,4($0)
jal loop2
nop
loop2:
lw $4,-0x301c($31)
