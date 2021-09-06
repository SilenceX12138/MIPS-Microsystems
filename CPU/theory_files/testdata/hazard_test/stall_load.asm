.text
	li $t3,3
	sw $t3,4($0)
	lw $4,4($0)
	beq $4,$0,loop
	nop
	
	addi $4,$4,10
	
	loop:
		