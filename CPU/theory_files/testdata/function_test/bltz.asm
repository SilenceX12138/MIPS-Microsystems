.text
	li $t1,10
	li $t2,-20
	li $t3,30
	
	bltz $t1,loop1
	nop
	
	bltz $t2,loop2
	nop

	loop1:
		addi $t3,$t3,-30
		
	loop2:
		addi $t2,$t2,10
		addi $0,$t3,10
		
	bltz $t2,loop2
	nop
	
	