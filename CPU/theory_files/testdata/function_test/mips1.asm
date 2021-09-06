.text
	li $t1,10
	li $t2,15
	xori $t1,101
	and $t3,$t1,$t2
	sllv $t3,$t1,$t3
	li $t3,15
	li $s1,10
	bne $t3,$s1,skip
	and $t4,$t3,$t1
	sllv $t4,$t2,$t3
	xori $t2,100
	sll $t4,$t2,10
	back:
	li $s2,3
	beq $s1,$s2,end
	and $t5,$t4,$t2
	li $t5,129
	skip: 
		beq $s4,$s5,real_end
		xori $t3,101
		xori $t3,3
		beq $t3,$t3,back
		li $s1,3
		bne $t3,$s1,end
		nop
	and $t6,$t3,$t5
	
	end:
		li $s5,10
		li $s4,10
		jal skip
		sllv $t3,$s4,$s5
		
	real_end:
		sllv $s4,$s5,$s3
		