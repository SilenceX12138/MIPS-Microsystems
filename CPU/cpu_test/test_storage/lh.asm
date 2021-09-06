.text
	li $t1,'a'
	li $t2,'b'
	li $t3,'c'
	li $t4,'d'
	li $t5,'e'
	li $t6,'f'
	li $t7,'g'
	
	sh $t1,0($0)
	sh $t2,2($0)
	sh $t3,4($0)
	sh $t4,6($0)
	sh $t5,8($0)
	sh $t6,10($0)
	sh $t7,12($0)
	
	lh $t1,12($0)
	lh $t2,10($0)
	lh $t3,8($0)
	lh $t4,6($0)
	lh $t5,4($0)
	lh $t6,2($0)
	lh $t7,0($0)
	