.text
	li $3,3
	li $2,3
	beq $3,$0,loop
	addi $3,$3,1
	
	addu $4,$4,$3
	
	loop: