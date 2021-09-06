.ktext 0x4180
li $t7 10 #1010 暂时停止计数
li $s7 0x7f00
sw $t7 0($s7)
li $t7 11#1011
mfc0 $29 $12
lui $28 0x8000
and $27 $28 $29
mfc0 $28 $14#存储EPC
beq $27 $0 notadd4
nop
addi $28 $28 4#若BD位为1,EPC+8
notadd4:
	addi $28 $28 4
	sw $28 0($0)
	lw $28 0($0)
	mtc0 $28 $14#简单检测转发/暂停
	mfc0 $29 $14
	addi $29 $29 4
	addi $29 $29 -4
	mtc0 $29 $14
	sw $t7 0($s7)#再次开始计数
	eret
	nop
	
.text
li $28 0
li $29 0
li $t0 0xfffd
mtc0 $t0 $12
li $s0 0x7f00
li $t0 11#1011
sw $t0 4($s0)#定时器0初值
sw $t0 0($s0)#定时器0开始
#下面就是那些异常了,可以考察当异常中断同时发生时是否出错
li $28 0
li $29 0
lui $t0 0x8000
lui $t1 0x8000
li $t2 0x7ffffffe
add $t2 $t0 $t1# 加法溢出
multu $2 $3
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
sub $t2 $0 $t1# 减法溢出
multu $2 $3
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
addi $t2 $t2 2# 加法溢出
multu $2 $3
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
li $s0 0x2fffc
li $s1 0x7f00
li $s2 0x7f10
sw $t0 0($s0)
addi $s0 $s0 4
sw $t0 0($s0)#sw 超范围
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
lw $t2 0($s0)#lw 超范围
sw $0 0($s1)
sw $0 4($s1)
sw $0 8($s1)# sw计数器
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
sw $0 12($s1)# sw超范围
sw $0 0($s2)
sw $0 4($s2)
sw $0 8($s2)# sw计数器
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
sw $0 12($s2)# sw超范围
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
lw $t2 0($s1)
lw $t2 12($s1)# lw超范围
sb $0 0($s1)#sb 写定时器
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
sb $0 0($s2)#sb 写定时器
sh $0 0($s1)#sh 写定时器
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
sh $0 0($s2)#sh 写定时器
lb $t2 0($s1)#lb 读定时器
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
lbu $t2 0($s1)#lbu 读定时器
lh $t2 0($s2)#lh 读定时器
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
lhu $t2 0($s2)#lhu 读定时器
jal test_delayedbranching
sw $t0 2($0) #sw不对齐
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
sh $t0 1($0) #sh不对齐
lw $t1 2($0) #lw不对齐
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
lh $t0 1($0) #lh不对齐
lhu $t0 1($0) #lhu不对齐
movz $t2 $t1 $0#RI
#乘除指令一箩筐
li $2 0xffffffff
li $3 0x87654321
multu $2 $3
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5
mfhi $4 
mflo $5
mthi $5
mtlo $4
mfhi $4 
mflo $5
multu $4 $5

end:
	j end
	nop
	

 test_delayedbranching:
 	addi $ra $ra 1#PC不对齐
 	jr $ra 
 	nop








