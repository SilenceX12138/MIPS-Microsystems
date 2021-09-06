init:
lui $1, 0x7d59
lui $2, 0x12fd
lui $3, 0x7ec7
lui $4, 0x783c
lui $5, 0x4c90
lui $6, 0x67ea
lui $7, 0x7d8d
lui $8, 0x337b
lui $9, 0x635b
lui $10, 0x7c33
lui $11, 0x1ff8
lui $12, 0x72ae
lui $13, 0x65a6
lui $14, 0x1be3
lui $15, 0x1a71
lui $16, 0xeea
lui $17, 0x2546
lui $18, 0x7a4f
lui $19, 0x188b
lui $20, 0x74c2
lui $21, 0x4e8a
lui $22, 0x7c56
lui $23, 0x6e37
lui $24, 0x60b3
lui $25, 0x4313
lui $26, 0x77e8
lui $27, 0x693b
lui $28, 0x3ac0
lui $29, 0x16e6
lui $30, 0xcc5
lui $31, 0x56e0
test_mul:
nor $7, $11, $1
addu $10, $3, $15
mfhi $12
slti $6, $22, 0x4418
addu $12, $2, $29
mflo $6
sw $3, 0x800($0)
addu $11, $27, $0
mfhi $28
lhu $30, 0x282($0)
addu $18, $15, $24
mfhi $12
sw $20, 0x31c($0)
addu $4, $12, $24
mflo $22
lw $1, 0x554($0)
addu $30, $14, $25
mflo $15
subu $27, $11, $21
addu $22, $3, $31
mflo $24
nor $10, $31, $16
addu $2, $12, $25
mfhi $1
xori $0, $5, 0x1bbb
addu $19, $4, $26
mflo $3
sw $15, 0x378($0)
addu $1, $12, $21
mfhi $13
lhu $23, 0xb58($0)
addu $9, $31, $11
mfhi $3
xori $8, $19, 0x52c9
addu $22, $11, $9
mfhi $1
sll $8, $26, 0x0
addu $11, $1, $11
mflo $19
sw $10, 0xed0($0)
addu $5, $30, $7
mfhi $19
lw $12, 0xa8($0)
addu $27, $26, $9
mflo $17
sw $6, 0x400($0)
mult $5, $29
mflo $5
srav $29, $9, $16
mult $8, $6
mflo $28
addiu $20, $15, 0x131b
mult $15, $11
mfhi $29
xor $0, $12, $2
mult $30, $2
mflo $30
andi $18, $21, 0xaed
mult $19, $12
mflo $16
nor $7, $4, $19
mult $2, $20
mflo $7
sra $17, $21, 0x5
mult $15, $20
mflo $25
srlv $1, $29, $15
mult $24, $13
mflo $17
sw $18, 0x1f4($0)
mult $9, $12
mfhi $14
sltiu $9, $30, 0x4d92
mult $7, $13
mfhi $14
sw $4, 0xb18($0)
mult $9, $25
mfhi $16
xor $27, $21, $22
mult $25, $11
mflo $15
ori $4, $27, 0x454c
mult $2, $2
mflo $5
sw $18, 0xa9c($0)
mult $1, $13
mflo $20
slt $29, $18, $24
mult $5, $17
mfhi $10
addu $21, $10, $1
multu $13, $4
mflo $15
sw $27, 0x2cc($0)
multu $16, $0
mflo $4
sw $20, 0xfcc($0)
multu $31, $12
mflo $23
sll $9, $12, 0x12
multu $1, $4
mfhi $29
sllv $11, $21, $25
multu $23, $13
mfhi $28
and $8, $21, $3
multu $6, $6
mfhi $8
lbu $30, 0x198($0)
multu $8, $10
mflo $27
sw $16, 0x708($0)
multu $23, $10
mflo $18
sw $23, 0x6d4($0)
multu $28, $13
mfhi $3
slt $14, $4, $4
multu $11, $17
mfhi $27
or $28, $31, $20
multu $10, $23
mfhi $12
ori $9, $2, 0x37f2
multu $11, $21
mflo $6
sllv $1, $5, $31
multu $14, $28
mflo $4
sltu $7, $13, $12
multu $10, $17
mfhi $3
nor $5, $1, $21
multu $12, $2
mfhi $1
sw $26, 0x504($0)
madd $14, $7
mflo $17
lbu $9, 0xa51($0)
madd $8, $10
mfhi $29
andi $5, $5, 0x7c8c
madd $18, $29
mflo $15
addiu $19, $7, 0x54b7
madd $5, $27
mfhi $18
and $23, $5, $3
madd $4, $6
mfhi $27
sw $19, 0x8e0($0)
madd $26, $18
mfhi $15
sw $21, 0x2d8($0)
madd $29, $13
mfhi $31
srlv $30, $15, $29
madd $3, $15
mfhi $15
sw $2, 0x668($0)
madd $0, $22
mfhi $15
sw $5, 0x6ac($0)
madd $23, $20
mflo $14
lh $20, 0x12($0)
madd $29, $9
mfhi $4
sw $17, 0x308($0)
madd $11, $8
mfhi $28
srav $7, $19, $0
madd $25, $3
mfhi $14
lbu $29, 0x204($0)
madd $22, $20
mfhi $30
srlv $2, $7, $14
madd $7, $30
mflo $6
slti $5, $8, 0xb72
maddu $12, $9
mflo $8
addi $16, $18, 0xd46
maddu $1, $9
mfhi $1
sw $16, 0x6dc($0)
maddu $30, $8
mflo $15
sw $1, 0xe40($0)
maddu $22, $22
mfhi $13
srl $1, $7, 0x7
maddu $1, $18
mfhi $18
sllv $0, $15, $9
maddu $24, $3
mfhi $25
lw $4, 0x8b0($0)
maddu $27, $4
mfhi $14
and $25, $25, $31
maddu $5, $29
mfhi $20
lb $14, 0x628($0)
maddu $12, $20
mflo $7
lw $19, 0xd00($0)
maddu $19, $30
mfhi $16
lh $31, 0x668($0)
maddu $9, $16
mfhi $18
sltiu $7, $23, 0x1a8e
maddu $6, $2
mfhi $26
srlv $3, $27, $28
maddu $16, $0
mfhi $28
lhu $19, 0x978($0)
maddu $27, $5
mfhi $28
addu $4, $18, $21
maddu $22, $12
mflo $24
or $3, $30, $8
msub $4, $22
mfhi $26
or $16, $24, $9
msub $11, $20
mfhi $26
or $3, $0, $0
msub $11, $22
mflo $23
lhu $11, 0xae0($0)
msub $3, $3
mflo $28
sw $7, 0x634($0)
msub $10, $26
mfhi $30
sw $22, 0x304($0)
msub $0, $23
mfhi $31
slt $27, $25, $26
msub $26, $1
mflo $3
sra $25, $2, 0x9
msub $2, $25
mfhi $15
srav $20, $12, $11
msub $8, $18
mflo $20
lw $23, 0x8ac($0)
msub $5, $30
mfhi $13
lb $18, 0xf84($0)
msub $5, $4
mfhi $2
lhu $0, 0x6be($0)
msub $2, $25
mflo $29
sw $23, 0x7d4($0)
msub $24, $3
mflo $0
lh $1, 0x34c($0)
msub $11, $30
mflo $30
lw $27, 0x718($0)
msub $31, $24
mflo $31
addi $24, $11, 0x345f
mthi $21
mfhi $0
lw $31, 0xa64($0)
mthi $23
mflo $9
sra $12, $19, 0x8
mthi $25
mfhi $15
subu $27, $8, $3
mthi $28
mflo $30
xor $29, $24, $17
mthi $24
mfhi $27
and $31, $27, $9
mthi $11
mfhi $17
nor $3, $14, $21
mthi $23
mfhi $16
sw $19, 0x79c($0)
mthi $18
mfhi $21
xor $11, $23, $12
mthi $20
mflo $23
lw $13, 0x508($0)
mthi $3
mflo $30
lbu $23, 0xc5e($0)
mthi $17
mflo $15
sw $21, 0x2a8($0)
mthi $11
mfhi $2
srav $14, $22, $9
mthi $29
mflo $15
addi $23, $13, 0x5925
mthi $8
mflo $5
sltu $20, $22, $11
mthi $11
mfhi $0
sw $2, 0x79c($0)
mtlo $15
mflo $4
sll $13, $24, 0xe
mtlo $23
mfhi $2
lh $8, 0xdfc($0)
mtlo $16
mflo $1
sw $29, 0xacc($0)
mtlo $3
mflo $29
lw $11, 0x424($0)
mtlo $2
mflo $5
sw $19, 0x318($0)
mtlo $28
mfhi $29
addu $6, $4, $5
mtlo $3
mflo $14
xor $27, $2, $21
mtlo $21
mflo $16
slt $22, $20, $31
mtlo $29
mflo $28
lw $13, 0xaf8($0)
mtlo $4
mflo $0
addi $14, $21, 0x6f59
mtlo $8
mflo $18
sll $0, $31, 0x13
mtlo $20
mflo $20
sw $27, 0x78c($0)
mtlo $13
mfhi $29
lb $1, 0x963($0)
mtlo $24
mflo $26
and $20, $5, $20
mtlo $12
mfhi $25
maddu $30, $6
mfhi $19
maddu $15, $21
mfhi $15
maddu $5, $13
mflo $30
mthi $4
mfhi $26
addu $28, $22, $24
mfhi $9
lb $24, 0x759($0)
lhu $5, 0x9e2($0)
srl $5, $15, 0x10
and $12, $1, $3
xor $23, $11, $9
msub $28, $14
mfhi $12
madd $30, $25
mflo $15
addu $22, $9, $12
mfhi $14
nor $26, $11, $23
msub $19, $11
mfhi $21
mtlo $28
mfhi $1
maddu $23, $17
mflo $21
mthi $6
mflo $7
msub $14, $1
mflo $21
mtlo $2
mfhi $5
sw $14, 0x108($0)
lh $12, 0xc84($0)
addiu $12, $27, 0x7a7e
mtlo $6
mflo $11
srlv $17, $30, $25
srav $20, $4, $31
mthi $20
mfhi $12
multu $22, $22
mfhi $20
addu $5, $27, $19
mfhi $28
sw $17, 0x7e8($0)
sw $16, 0xe34($0)
sw $19, 0x850($0)
andi $3, $17, 0x63c9
sw $5, 0xac8($0)
multu $21, $11
mflo $14
maddu $25, $5
mfhi $6
madd $11, $13
mfhi $16
multu $29, $21
mflo $5
addu $3, $25, $6
mfhi $10
sra $20, $22, 0x1f
mtlo $26
mfhi $6
multu $24, $11
mflo $23
addu $9, $5, $26
madd $1, $23
mflo $27
sw $26, 0x858($0)
lb $10, 0xb7c($0)
madd $21, $21
mflo $11
sw $20, 0x434($0)
multu $30, $17
mflo $4
sllv $6, $29, $19
sw $16, 0x158($0)
lb $10, 0x222($0)
and $6, $1, $30
lhu $16, 0xc42($0)
sw $10, 0x6fc($0)
multu $18, $31
mflo $16
sltiu $20, $18, 0x6efb
addu $25, $23, $10
addu $2, $21, $19
mflo $20
srav $4, $25, $12
lhu $19, 0x5de($0)
maddu $13, $17
mflo $17
maddu $25, $9
mflo $26
mthi $4
mfhi $24
mthi $23
mflo $26
sw $4, 0x4c4($0)
mthi $27
mfhi $10
lbu $22, 0xbcd($0)
lw $26, 0x834($0)
msub $0, $23
mfhi $14
srlv $10, $7, $17
mult $3, $21
mflo $13
lhu $9, 0x78a($0)
sw $25, 0x638($0)
lbu $22, 0xc04($0)
sw $4, 0xe24($0)
sw $9, 0xd28($0)
madd $20, $8
mflo $14
andi $30, $30, 0x7545
mult $21, $27
mfhi $26
lhu $23, 0xfae($0)
addiu $4, $0, 0x26c2
lb $23, 0x280($0)
madd $6, $17
mfhi $5
mult $13, $17
mfhi $3
addu $18, $17, $12
mflo $3
mtlo $31
mfhi $30
madd $24, $30
mflo $4
lw $21, 0x2e4($0)
mult $6, $22
mflo $29
sw $6, 0x538($0)
addi $9, $24, 0x3ab7
madd $26, $27
mflo $15
madd $27, $14
mflo $15
subu $24, $14, $30
sw $0, 0x618($0)
sw $27, 0x258($0)
madd $7, $22
mfhi $18
mthi $11
mflo $15
addu $21, $30, $18
mfhi $27
maddu $1, $22
mflo $7
mtlo $21
mflo $0
mthi $30
mflo $23
multu $14, $12
mfhi $31
lh $9, 0x588($0)
sw $23, 0xe4($0)
sw $7, 0x5b4($0)
lbu $6, 0xd9a($0)
sltiu $6, $20, 0x5cce
lh $19, 0xb0($0)
msub $3, $18
mfhi $21
sw $10, 0x788($0)
andi $17, $3, 0x4ee6
multu $21, $30
mfhi $11
sw $9, 0xc9c($0)
lbu $26, 0xf7e($0)
ori $5, $11, 0x70a
maddu $18, $27
mfhi $15
xori $15, $28, 0x5550
mult $19, $24
mfhi $28
multu $27, $4
mfhi $30
maddu $26, $17
mfhi $2
sw $2, 0xfcc($0)
sw $13, 0xd00($0)
sra $14, $18, 0x1e
sw $1, 0xcbc($0)
lw $22, 0x3dc($0)
maddu $11, $23
mfhi $7
addu $29, $18, $2
mflo $18
addu $25, $12, $30
mfhi $29
mthi $27
mflo $24
mult $31, $12
mflo $2
srl $10, $17, 0x1d
multu $6, $5
mflo $27
sw $21, 0xf30($0)
multu $31, $4
mfhi $9
msub $3, $5
mflo $10
addu $0, $15, $2
mfhi $31
lb $27, 0xb28($0)
lb $7, 0xf($0)
msub $7, $10
mfhi $15
slt $1, $7, $2
sw $30, 0xd80($0)
sll $23, $19, 0x1
sw $30, 0xa2c($0)
sw $15, 0xb30($0)
srlv $15, $17, $26
sltiu $29, $10, 0x33dc
xor $1, $7, $21
lb $13, 0xe48($0)
lhu $27, 0x93e($0)
lhu $24, 0x48a($0)
subu $14, $26, $28
sw $17, 0x5dc($0)
sw $1, 0xe8($0)
srlv $23, $3, $25
sra $22, $5, 0x14
mthi $16
mfhi $27
lhu $16, 0x9d2($0)
madd $20, $8
mflo $11
madd $28, $21
mfhi $8
lh $1, 0xce($0)
addu $14, $15, $31
mfhi $15
mult $27, $0
mfhi $24
lw $12, 0x1c8($0)
sw $23, 0xafc($0)
multu $23, $17
mfhi $21
mult $15, $28
mflo $15
maddu $18, $30
mfhi $14
lb $11, 0xf34($0)
mtlo $21
mfhi $2
msub $15, $19
mflo $9
lhu $29, 0x2fa($0)
madd $8, $19
mflo $1
multu $2, $4
mflo $1
lw $7, 0xf3c($0)
mult $6, $2
mfhi $9
addu $22, $26, $6
mfhi $10
sw $15, 0x95c($0)
mtlo $26
mfhi $24
addiu $10, $23, 0x79f9
sw $13, 0x824($0)
and $2, $15, $14
maddu $22, $15
mflo $23
addu $16, $25, $27
mfhi $19
srlv $5, $15, $5
srlv $16, $6, $19
srlv $14, $15, $14
multu $15, $2
mfhi $21
mtlo $30
mflo $16
nor $26, $24, $27
multu $17, $6
mflo $0
msub $11, $4
mflo $8
mult $23, $14
mflo $4
mthi $2
mflo $24
slt $24, $1, $4
sw $3, 0xd48($0)
lw $4, 0xc90($0)
msub $6, $9
mfhi $1
lhu $11, 0xb10($0)
