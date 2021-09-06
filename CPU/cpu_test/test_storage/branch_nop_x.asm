.ktext 0x4180
	li $3,1
	addi $2,$2,1
	li $5,0
	
	eret
	beq $2,$3,loop1
	nop
	
.text 0x3000
	loop1:
		addi $4,$4,4
		
	li $5,0x7fffffff
	li $6,0x7fffffff
	
	beq $4,$4,loop2
	add $7,$5,$6
	
	loop2:
		addi $4,$4,4
		