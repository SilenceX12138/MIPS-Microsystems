.text
	#ori $t0,10			#can be removed
	ori $t1,10
	ori $t2,1
	
	beq $t0,$t1,end_loop
	nop
	
	jal addone
	nop
	
	end_loop:
		nop
		jal end
		
	addone:
		addu $t1,$t1,$t2
		jr $ra
		
	end:
	
