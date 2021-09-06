.text
	li $3,0x7fffffff
	li $4,0x7fffffff
	mult $3,$4
	add $5,$3,$4
	mflo $5
	
.ktext 0x4180
	li $3,0
	eret
