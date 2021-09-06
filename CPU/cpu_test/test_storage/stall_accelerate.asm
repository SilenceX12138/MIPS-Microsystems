.text
	lb $t3,4($0)
	sw $0,4($0)
	beq $0,$t3,loop
	nop
	
	loop:
		
		