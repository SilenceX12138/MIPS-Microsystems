.text
	ori $t0,10
	ori $t1,10
	ori $t3,1
	loop:
		beq $t0,$t1,end_loop
		nop
		
		subu $t4,$t4,$t3
		ori $t1,0xffff
		addu $t2,$t2,$t1
		lui $t1,0xffff
		ori $t1,0xffff
		addu $t2,$t2,$t1
		lui $t1,0x7fff
		ori $t1,0xffff
		addu $t3,$t2,$t1
		addu $t0,$t0,$t3
		#j loop
		nop
		
	ori $t1,10
	ori $t2,1
	
	beq $t0,$t1,end_loop
	nop
	
	jal addone
	nop
	
	end_jal_loop:
		nop
		jal end
		
	addone:
		addu $t1,$t1,$t2
		jr $ra
		
	end_loop:
		ori $t5,10
		lb $t0,0($0)
		lb $t1,1($0)
		lb $t2,2($0)
		lb $t3,3($0)
		lb $t4,4($0)
		lb $t5,5($0)
		lb $t6,6($0)
		lb $t7,7($0)
		
	end:
		
