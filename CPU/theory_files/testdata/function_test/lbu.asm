.text
	li $1,0xff
	li $2,0xee
	li $3,0xdd
	li $4,0xcc
	
	sb $1,0($0)
	sb $2,1($0)
	sb $3,2($0)
	sb $4,3($0)
	
	lbu $t1,0($0)
	lbu $t2,1($0)
	lbu $t3,2($0)
	lbu $t4,3($0)
	
	lb $s1,0($0)
	lb $s2,1($0)
	lb $s3,2($0)
	lb $s4,3($0)
	