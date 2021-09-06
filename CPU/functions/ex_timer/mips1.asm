#cal_set={add,sub,or,and,sll,sllv,srl,srlv}
#Timer  0x7f00-0x7f0b
#UART   0x7f10-0x7f2b
#Switch 0x7f2c-0x7f33
#LED    0x7f34-0x7f37
#Tube   0x7f38-0x7f3f
#Key    0x7f40-0x7f43

.text
	initial:
		li $t0,0xfc01				#allow all IRQ
		mtc0 $t0,$12
		li $t0,0xffffffff		#set timer continuously count mode
		sw $t0,0x7f00($0)
		li $t0,10000000			#set count-down time for timer
		sw $t0,0x7f04($0)		
		
	wait_key:
		j wait_key
		nop
	
.ktext 0x4180
	lw $k1,0x7f2c($0)			#use $k1 as new val to count down
	lw $t2,0x7f38($0)			#use $t2 as tube's current val
	li $s1,2
	
	slt $s2,$k1,$s1
	
	beq $k1,0,reset
	nop
	beq $s2,1,one_second	#if new_val<2 count down for 1s 
	nop
	beq $s2,0,two_second	#if new_val>=2 count down for 2s
	nop
	
	j return 
	nop
	
	one_second:
		li $k0,10000000			#set count-down time for timer
		sw $k0,0x7f04($0)
		
		j continue
		nop
		
	two_second:
		li $k0,20000000			#set count-down time for timer
		sw $k0,0x7f04($0)
		
		j continue
		nop
		
	continue:
		beq $t2,9,reset
		nop
		
		addi $t2,$t2,1
		sw $t2,0x7f38($0)
		
		j return
		nop
	
	reset:
		sw $0,0x7f38($0)

	return:
		eret
	
	
	
	
	
