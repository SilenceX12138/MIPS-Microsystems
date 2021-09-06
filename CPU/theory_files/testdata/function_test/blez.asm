.text
	li $t0,10
	li $t1,-2
	
	blez $t0,loop1
	slti $s1,$t0,-2
	
	blez $t1,loop2
	slti $s2,$t1,-10
	
	blez $t2,loop3
	slti $s3,$t1,-2
	
	loop1:
		addiu $s1,$s1,1
		
	loop2:
		slti $t4,$t1,-2 
		addiu $t1,$t1,1
		addiu $s2,$s2,1
		
	loop3:
		addiu $s3,$s3,1
		
	blez $t1,loop2
	nop
