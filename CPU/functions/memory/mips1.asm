#cal_set={add,sub,or,and,sll,sllv,srl,srlv}
#Timer  0x7f00-0x7f0b
#UART   0x7f10-0x7f2b
#Switch 0x7f2c-0x7f33
#LED    0x7f34-0x7f37
#Tube   0x7f38-0x7f3f
#Key    0x7f40-0x7f43

.text
	initial:
		li $t0 0xfc01
		mtc0 $t0, $12
		
	wait_data:
		j wait_data
		nop
		
.ktext 0x4180
	lw $k0,0x7f2c($0)			#use $k0 as A
	sll $k0,$k0,2					#align
	srl $k0,$k0,2
	lw $k1,0x7f30($0)			#use $k1 as B
	lw $t1,0x7f40($0)			#use $t1 as key

	
	beq $t1,1,write
	nop
	beq $t1,2,show
	nop
	
	j return 
	nop
	
	write:
		sw $k1,0x7f38($0)
		sw $k1,0($k0)
		
		j return
		nop
	
	show:
		lw $t2,0($k0)
		sw $t2,0x7f38($0)
		
		j return
		nop
	
	return:
		eret
	