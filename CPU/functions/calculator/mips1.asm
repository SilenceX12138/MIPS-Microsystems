#cal_set={add,sub,or,and,sll,sllv,srl,srlv}
#Timer  0x7f00-0x7f0b
#UART   0x7f10-0x7f2b
#Switch 0x7f2c-0x7f33
#LED    0x7f34-0x7f37
#Tube   0x7f38-0x7f3f
#Key    0x7f40-0x7f43

.text
	initial:
		li $t0,0xfc01	#set SR's IM and IE all 1
		mtc0 $t0,$12

	wait_key:
		li $k0,0
		j wait_key
		nop
	
.ktext 0x4180
	lw $t1,0x7f2c($0)	#use $t1 as a
	lw $t2,0x7f30($0)	#use $t2 as b
	lw $k0,0x7f40($0) 	#use $k0 as key
	
	beq $k0,1,cal_add
	nop
	beq $k0,2,cal_sub
	nop
	beq $k0,4,cal_or
	nop
	beq $k0,8,cal_and
	nop
	beq $k0,16,cal_sll
	nop
	beq $k0,32,cal_sllv
	nop
	beq $k0,64,cal_srl
	nop
	beq $k0,128,cal_srlv
	nop
	
	j return
	nop
	
	cal_add:
		lw $t1,0x7f2c($0)	#use $t1 as a
		lw $t2,0x7f30($0)	#use $t2 as b
		addu $t4,$t1,$t2
		sw $t4,0x7f38($0) 	#store result in tube
		
		j return
		nop
	
	cal_sub:
		lw $t1,0x7f2c($0)	#use $t1 as a
		lw $t2,0x7f30($0)	#use $t2 as b
		subu $t4,$t1,$t2
		sw $t4,0x7f38($0)
		
		j return
		nop
	
	cal_or:
		lw $t1,0x7f2c($0)	#use $t1 as a
		lw $t2,0x7f30($0)	#use $t2 as b
		or $t4,$t1,$t2
		sw $t4,0x7f38($0)
		
		j return
		nop
	
	cal_and:
		lw $t1,0x7f2c($0)	#use $t1 as a
		lw $t2,0x7f30($0)	#use $t2 as b
		and $t4,$t1,$t2
		sw $t4,0x7f38($0)
		
		j return
		nop
		
	cal_sll:
		lw $t1,0x7f2c($0)	#use $t1 as a
		lw $t2,0x7f30($0)	#use $t2 as b
		sll $t4,$t1,1
		sw $t4,0x7f38($0)
		
		j return
		nop
		
	cal_sllv:
		lw $t1,0x7f2c($0)	#use $t1 as a
		lw $t2,0x7f30($0)	#use $t2 as b
		sllv $t4,$t1,$t2
		sw $t4,0x7f38($0)
		
		j return
		nop
		
	cal_srl:
		lw $t1,0x7f2c($0)	#use $t1 as a
		lw $t2,0x7f30($0)	#use $t2 as b
		srl $t4,$t1,1
		sw $t4,0x7f38($0)
		
		j return
		nop
		
	cal_srlv:
		lw $t1,0x7f2c($0)	#use $t1 as a
		lw $t2,0x7f30($0)	#use $t2 as b
		srlv $t4,$t1,$t2
		sw $t4,0x7f38($0)
		
		j return
		nop
		
	return:
		eret
	
	
		
		
		
		