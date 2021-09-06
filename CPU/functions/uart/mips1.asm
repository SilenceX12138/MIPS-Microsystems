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
		li $t0,0x20000217
		sw $t0, 0x7f38($0)

	wait_data:
		j wait_data
		nop

.ktext 0x00004180
	mfc0 $k0, $13
	andi $k0, $k0, 0x0800	#check IRQ from uart
	
	beq $k0, $0, return		#not uart's IRQ
	nop
	
	lw $k1, 0x7f10($0)		#read data means sending data to display facility
	sw $k1, 0x7f10($0)		#receive data
	
	return:
	eret