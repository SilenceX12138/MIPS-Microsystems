.data
	stack: .space 1000

.text
	ori $t1,0xffff
	addu $t2,$t2,$t1
	lui $t1,0xffff
	ori $t1,0xffff
	addu $t2,$t2,$t1
	lui $t1,0x7fff
	ori $t1,0xffff
	addu $t3,$t2,$t1
	sw $t1,4($0)
	sw $t2,16($0)
	subu $t3,$t3,$t3
	ori $t3,20
	sw $t3,stack($t3)
