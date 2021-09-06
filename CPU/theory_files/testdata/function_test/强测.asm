begin:
ori $3 12288 #0x3000
or $9 $3 $4
sll $9 $9 2
sll $9 $9 3
sll $9 $9 11
addiu $9 $9 122
ori $4 12292
addiu $9 $4 123
ori $5 4
or $7 $4 $5
sll $7 $7 31
sll $7 $7 1
addiu $7 $4 123
ori $6 8
or $8 $4 $0
sll $8 $7 10
sll $8 $8 31
addiu $8 $4 0
or $0 $8 $8
addiu $0 $8 132
#D1,D2,D3���ٵ�����ת��
addu $3  $3 $5
beq  $4 $3 begin #5
nop
addu $3 $3 $6
addu $3 $3 $6
addu $3 $3 $6  
addu $3 $3 $6 
addu $3 $3 $6 #11
addu $3 $3 $6
jr $3
nop
jal check
nop

#E1,E2���ٵ�����ת��
ori $7 $7 16
subu $7 $7 $7
subu $7 $7 $7
ori $7 $7 16
sw $7 ($6)  #DM��8�ŵ�ַ������8
sltu $9 $7 $6
lw  $8  ($6)
nop
nop
addu $8 $8 $8
lw $8 ($7)
sltu $7 $8 $7 
nop
sw  $8  4($8)
nop

#D1,D2,D3���ٵ�������ͣ
lui $8  0
ori $8 $8 16
lw   $7  ($8) #7�Ŷ�����8
beq $7 $3 begin
nop
addu $7 $7 $7
beq $7 $3 begin
nop

#E1��E2���ٵ�������ͣ
lw $7 ($8)
ori $7 $7 32
addu $7 $7 $7
lw $7 ($8)
sw $7 ($5)
sw $7 ($5)
sw $7 ($5)
sltu $7 $8 $5
nop

#M1����ת��
lw $7 ($8)
sw $7 0($7)

lui $4 1
lui $5 1
slt $7 $0 $5 
beq  $4 $5 end
slt $0 $4 $5
nop
check:
jr $ra
slt $0 $0 $4 
nop
end:

      



