.text
	jal loop
	sw $31,4($0)
	
	
	loop:
		lw $1,4($0)
		addi $1,$1,12
		jr $1