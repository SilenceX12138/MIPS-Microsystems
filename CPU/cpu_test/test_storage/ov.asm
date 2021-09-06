.text	0x4180
	li $t1,0
	eret

.text 0x3000
	li $t1,0x7fffffff
	li $t2,0x7fffffff
	add $t3,$t2,$t1
	mult $t1,$t2
	mflo $3
	addi $3,$3,1
	
	
