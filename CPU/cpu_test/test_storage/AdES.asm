.text 0x3000
	li $t1,2
	li $t2,2
	
	beq $t1,$t2,loop1
	sw $t2,0($t1)
	addi $5,$5,1

	loop1:
	
.text 0x4180
	addi $t1,$t1,1
	eret
	sw $t5,0($0)