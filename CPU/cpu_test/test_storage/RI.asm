.text 0x3000
	addi $t1,$t1,10
	bc1f 2,loop1
	addi $t2,$t2,1

	loop1:
	
	
.text 0x4080
	eret