li $2, 0xffff0000
li $3, 0x0000ffff
mtc0 $3, $14
mfc0 $3, $14
sw $2, 0($0)
lw $3, 0($0)
mtc0 $3, $14
mfc0 $3, $14
addu $3, $3, $3
jal go
mtc0 $31, $14
go:
mfc0 $3, $14
nop
mult $2, $3
mflo $4