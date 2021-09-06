init:
lui $1, 0xc15
lui $2, 0xc6
lui $3, 0x54e5
lui $4, 0xf24
lui $5, 0x1505
lui $6, 0x1c37
lui $7, 0x580e
lui $8, 0x1c71
lui $9, 0x6301
lui $10, 0x21d8
lui $11, 0x4a9
lui $12, 0x3968
lui $13, 0x1207
lui $14, 0x3841
lui $15, 0x373d
lui $16, 0x1f80
lui $17, 0x4884
lui $18, 0x33bc
lui $19, 0x5c3b
lui $20, 0xd74
lui $21, 0x7e16
lui $22, 0x51fa
lui $23, 0xce4
lui $24, 0x97
lui $25, 0x1f96
lui $26, 0x5e04
lui $27, 0x7368
lui $28, 0x1867
lui $29, 0x3456
lui $30, 0x5073
lui $31, 0x3a4b
test_div:
ori $8, $13, 0x3fe4
div $4, $8
mflo $31
ori $4, $25, 0x519e
div $7, $4
mflo $31
ori $31, $14, 0x30ef
div $14, $31
mfhi $1
ori $10, $15, 0x4454
div $26, $10
mfhi $25
ori $3, $23, 0x7a4f
div $27, $3
mfhi $11
ori $29, $17, 0x579b
div $1, $29
mfhi $8
ori $16, $9, 0x6e35
div $12, $16
mfhi $9
ori $29, $20, 0x3528
div $10, $29
mfhi $21
ori $26, $2, 0x4726
div $24, $26
mflo $12
ori $21, $26, 0x224a
div $17, $21
mflo $14
ori $9, $10, 0x2d9b
div $6, $9
mfhi $26
ori $10, $27, 0x1928
div $22, $10
mflo $18
ori $19, $31, 0x33d9
div $7, $19
mflo $21
ori $3, $20, 0x1e3f
div $29, $3
mflo $30
ori $11, $30, 0x6411
div $22, $11
mflo $15
ori $29, $16, 0xe1a
div $7, $29
mfhi $23
ori $19, $18, 0x3cba
div $18, $19
mflo $14
ori $10, $22, 0x5f52
div $16, $10
mfhi $25
ori $2, $0, 0x372e
div $27, $2
mflo $27
ori $4, $19, 0x14c9
div $9, $4
mfhi $30
ori $1, $19, 0x3483
div $12, $1
mflo $17
ori $10, $9, 0x5c22
div $22, $10
mflo $18
ori $15, $6, 0x6cac
div $24, $15
mfhi $3
ori $30, $23, 0x1483
div $11, $30
mfhi $21
ori $28, $16, 0x3bcf
div $8, $28
mfhi $14
ori $18, $10, 0x398e
div $3, $18
mflo $18
ori $17, $19, 0x69e8
div $20, $17
mflo $0
ori $17, $4, 0x6e9c
div $1, $17
mfhi $31
ori $13, $7, 0x489e
div $1, $13
mfhi $8
ori $10, $10, 0x263b
div $11, $10
mflo $21
ori $15, $4, 0x4364
divu $26, $15
mflo $31
ori $30, $20, 0x21ea
divu $3, $30
mfhi $18
ori $28, $15, 0x3dd3
divu $18, $28
mfhi $23
ori $7, $16, 0x4613
divu $8, $7
mflo $12
ori $12, $6, 0x5c47
divu $25, $12
mfhi $3
ori $22, $23, 0x7e49
divu $14, $22
mflo $25
ori $12, $14, 0x12b8
divu $29, $12
mflo $7
ori $20, $19, 0x2dc2
divu $26, $20
mfhi $28
ori $30, $28, 0x15d9
divu $3, $30
mflo $0
ori $7, $16, 0x6817
divu $0, $7
mfhi $17
ori $1, $2, 0xa76
divu $6, $1
mfhi $22
ori $25, $2, 0x6e39
divu $0, $25
mfhi $28
ori $5, $27, 0xf0a
divu $16, $5
mfhi $0
ori $11, $23, 0x2bb7
divu $30, $11
mflo $14
ori $20, $26, 0x7b9f
divu $23, $20
mflo $23
ori $16, $30, 0x302e
divu $2, $16
mflo $24
ori $8, $16, 0x73eb
divu $26, $8
mfhi $0
ori $29, $24, 0x610f
divu $16, $29
mfhi $21
ori $13, $28, 0x27a7
divu $28, $13
mflo $20
ori $2, $29, 0x5f98
divu $9, $2
mflo $19
ori $21, $23, 0x5d31
divu $0, $21
mflo $17
ori $1, $16, 0x5f0c
divu $1, $1
mfhi $1
ori $1, $31, 0x2264
divu $6, $1
mfhi $5
ori $19, $7, 0x6735
divu $2, $19
mflo $30
ori $16, $3, 0x3fb7
divu $5, $16
mflo $25
ori $13, $21, 0x3f1b
divu $2, $13
mflo $1
ori $8, $16, 0x4994
divu $10, $8
mflo $28
ori $7, $27, 0x7c05
divu $1, $7
mflo $4
ori $13, $27, 0x6bfa
divu $16, $13
mflo $18
ori $28, $13, 0x70b0
divu $6, $28
mfhi $22
lhu $27, 0x88e($0)
ori $28, $0, 0x2765
divu $14, $28
mfhi $29
srav $8, $5, $1
ori $6, $13, 0x5b8c
divu $23, $6
mflo $30
sll $25, $22, 0x15
sltiu $11, $5, 0xaac
lw $25, 0x948($0)
mtlo $10
mfhi $30
and $4, $17, $29
mthi $9
mfhi $20
ori $27, $8, 0x6ac0
divu $27, $27
mflo $12
sltiu $26, $7, 0x405e
slt $6, $3, $14
ori $26, $11, 0x7971
div $17, $26
mflo $31
mtlo $24
mfhi $30
srlv $8, $21, $0
addi $19, $7, 0x5f7
slti $25, $23, 0x42
ori $8, $6, 0x1b47
div $5, $8
mflo $0
sw $22, 0x6ac($0)
or $26, $16, $30
ori $27, $0, 0x7ed9
div $9, $27
mfhi $8
ori $31, $5, 0x5070
ori $28, $6, 0x2160
div $14, $28
mfhi $31
mfhi $16
or $7, $14, $27
sw $1, 0xb90($0)
mflo $1
xori $5, $17, 0x38c0
madd $16, $12
mfhi $29
ori $20, $5, 0xf63
divu $9, $20
mflo $9
srlv $14, $25, $6
nor $6, $10, $7
maddu $15, $3
mflo $9
or $14, $3, $21
msub $25, $1
mfhi $14
lbu $18, 0x8ee($0)
sw $6, 0x568($0)
sra $19, $28, 0x3
ori $18, $10, 0x63aa
div $11, $18
mflo $20
ori $8, $11, 0x1fb2
divu $7, $8
mflo $0
ori $7, $4, 0x42ad
divu $17, $7
mfhi $17
nor $29, $3, $12
sw $20, 0xcd4($0)
addiu $25, $6, 0x1d69
ori $2, $15, 0x2357
divu $8, $2
mfhi $8
ori $9, $21, 0x1c41
div $19, $9
mfhi $20
multu $23, $11
mfhi $11
mult $3, $23
mfhi $27
lw $1, 0x92c($0)
msub $21, $19
mflo $18
addi $13, $8, 0x157f
ori $8, $31, 0x4716
div $25, $8
mfhi $17
slti $9, $12, 0x7ca9
xor $20, $5, $17
ori $6, $14, 0x6a26
divu $11, $6
mflo $10
ori $14, $29, 0x1ee0
div $28, $14
mfhi $23
sw $21, 0xe48($0)
multu $11, $22
mfhi $31
lhu $12, 0xc16($0)
lbu $4, 0x2ca($0)
slt $16, $28, $12
sw $30, 0x1fc($0)
ori $27, $25, 0x56f5
div $18, $27
mfhi $9
sw $10, 0xeec($0)
ori $21, $5, 0x17f1
div $8, $21
mflo $19
ori $27, $2, 0x61f8
ori $25, $13, 0x33a7
div $30, $25
mflo $3
mflo $30
ori $16, $15, 0x3f4b
div $20, $16
mfhi $0
ori $18, $21, 0x6991
divu $3, $18
mflo $12
lw $6, 0x82c($0)
addu $13, $24, $30
addi $10, $30, 0x32de
ori $16, $10, 0x9e0
divu $9, $16
mfhi $21
ori $20, $31, 0x4e9
divu $31, $20
mflo $28
multu $9, $22
mfhi $21
lb $7, 0xf0c($0)
srav $12, $22, $28
madd $24, $22
mflo $30
lw $9, 0x1a0($0)
ori $5, $13, 0x374c
div $13, $5
mflo $19
ori $8, $19, 0x4d82
div $23, $8
mflo $9
sw $3, 0xad8($0)
ori $14, $15, 0x338f
div $8, $14
mflo $13
maddu $18, $29
mfhi $16
maddu $1, $10
mflo $20
mtlo $0
mflo $9
ori $18, $15, 0x565e
divu $4, $18
mflo $4
lbu $23, 0xbc2($0)
madd $15, $7
mflo $14
maddu $28, $7
mfhi $6
sll $21, $24, 0x1b
ori $5, $3, 0xa22
div $19, $5
mfhi $15
andi $11, $19, 0x342c
ori $26, $21, 0x6f62
div $28, $26
mfhi $4
ori $31, $10, 0xdf8
divu $27, $31
mflo $26
ori $14, $20, 0x32d2
divu $18, $14
mfhi $16
ori $8, $15, 0x35ac
div $14, $8
mflo $10
maddu $21, $17
mflo $21
lhu $26, 0x67c($0)
ori $20, $2, 0x5fde
div $5, $20
mflo $20
sw $20, 0xb44($0)
lh $21, 0x910($0)
msub $26, $17
mflo $19
msub $20, $9
mfhi $13
ori $3, $5, 0x4e0d
div $23, $3
mflo $3
ori $3, $5, 0x58e9
divu $10, $3
mfhi $21
ori $15, $15, 0x323d
divu $14, $15
mfhi $1
sra $25, $3, 0x4
lh $11, 0x134($0)
ori $14, $15, 0x54f8
divu $8, $14
mfhi $14
ori $23, $24, 0x786a
div $4, $23
mflo $13
lbu $8, 0x4e7($0)
maddu $17, $8
mfhi $26
slti $16, $3, 0x172c
sw $31, 0xf4($0)
sw $27, 0xc00($0)
sltiu $0, $14, 0x4a6c
msub $15, $20
mfhi $22
and $30, $30, $24
addu $15, $2, $5
sw $3, 0xc68($0)
mult $15, $5
mflo $5
ori $20, $7, 0x24d7
div $6, $20
mflo $9
ori $29, $4, 0x1d27
divu $3, $29
mflo $28
subu $1, $9, $29
ori $20, $1, 0x701a
divu $10, $20
mflo $20
lhu $10, 0x73a($0)
madd $7, $31
mflo $26
srav $29, $6, $2
ori $14, $12, 0x91a
div $15, $14
mflo $27
srav $15, $10, $15
ori $13, $15, 0x49c2
divu $21, $13
mflo $14
xori $30, $31, 0x36de
lw $15, 0xd80($0)
lh $26, 0xd9a($0)
maddu $23, $5
mfhi $26
sw $20, 0xbbc($0)
ori $8, $6, 0x549f
div $1, $8
mfhi $25
slt $30, $9, $14
srl $17, $10, 0x7
slt $16, $6, $6
mthi $14
mfhi $8
mtlo $19
mflo $25
ori $22, $31, 0x2d49
div $10, $22
mflo $25
ori $26, $3, 0x676f
divu $9, $26
mflo $25
mthi $30
mflo $13
multu $5, $17
mflo $14
maddu $6, $29
mflo $3
lb $8, 0x99b($0)
ori $1, $7, 0xa27
divu $11, $1
mfhi $6
msub $3, $2
mfhi $11
maddu $25, $0
mfhi $4
mult $19, $16
mfhi $26
ori $22, $21, 0x6d66
div $23, $22
mfhi $3
sll $8, $4, 0x19
ori $14, $6, 0x2a57
divu $28, $14
mfhi $18
ori $22, $12, 0x293b
div $15, $22
mflo $8
mthi $5
mfhi $30
ori $8, $4, 0x3c65
div $13, $8
mflo $2
slt $14, $7, $29
mult $27, $25
mflo $22
mtlo $24
mfhi $17
ori $25, $22, 0x3c43
divu $28, $25
mfhi $26
mult $10, $23
mfhi $3
mtlo $28
mflo $30
ori $19, $19, 0x45dd
div $26, $19
mflo $10
ori $28, $23, 0x33b8
divu $29, $28
mflo $29
ori $2, $28, 0x1d0f
divu $3, $2
mflo $13
maddu $30, $4
mfhi $21
ori $14, $28, 0x2bd2
divu $2, $14
mflo $17
mtlo $18
mflo $15
multu $6, $5
mfhi $31
mthi $17
mflo $22
ori $15, $17, 0x138d
divu $4, $15
mfhi $16
mthi $30
mfhi $11
addu $23, $21, $22
lbu $14, 0xb62($0)
madd $3, $2
mflo $22
addu $20, $12, $10
addu $0, $13, $28
slti $6, $25, 0x3f26
lw $5, 0x5b8($0)
mtlo $3
mfhi $26
ori $7, $13, 0x618c
divu $0, $7
mfhi $22
xor $2, $12, $18
lw $1, 0x654($0)
sw $19, 0xd94($0)
ori $9, $29, 0xe38
divu $2, $9
mfhi $9
slt $22, $19, $31
and $17, $25, $11
addiu $3, $11, 0x5769
multu $22, $13
mfhi $5
lh $21, 0x948($0)
lb $5, 0x97b($0)
addi $25, $13, 0x2add
addu $4, $29, $20
mtlo $15
mflo $5
xori $7, $16, 0xc8d
addiu $6, $11, 0x3600
ori $3, $9, 0x14e7
divu $10, $3
mflo $22
srav $30, $22, $2
ori $11, $2, 0x62b3
div $30, $11
mflo $15
ori $1, $30, 0x2947
divu $20, $1
mfhi $27
sw $21, 0x864($0)
ori $24, $14, 0x7976
mthi $0
mflo $23
lb $22, 0x40e($0)
ori $19, $30, 0x70a7
divu $5, $19
mflo $17
ori $31, $25, 0x525f
divu $24, $31
mflo $9
addiu $5, $19, 0x384f
multu $27, $23
mflo $25
ori $3, $1, 0x7d10
div $23, $3
mfhi $9
ori $16, $13, 0x2960
divu $23, $16
mflo $22
ori $5, $4, 0x7942
divu $7, $5
mfhi $22
xor $6, $13, $17
xori $11, $14, 0x15f7
ori $19, $30, 0x28ed
div $0, $19
mfhi $8
xor $3, $6, $3
mtlo $20
mflo $6
ori $9, $11, 0x29a5
div $17, $9
mflo $5
ori $22, $28, 0x69d0
divu $25, $22
mfhi $5
ori $30, $6, 0x55d0
div $27, $30
mfhi $22
lbu $31, 0x97e($0)
msub $13, $9
mflo $14
lbu $31, 0x75a($0)
mult $16, $26
mfhi $15
sw $17, 0x5f8($0)
lw $4, 0xdac($0)
lh $8, 0x88e($0)
ori $6, $30, 0x669d
divu $17, $6
mfhi $22
ori $31, $3, 0x51a2
sw $28, 0xc48($0)
sra $7, $24, 0x15
ori $23, $14, 0x4b9
divu $31, $23
mflo $29
lw $14, 0xa90($0)
nor $26, $23, $17
ori $9, $24, 0x4baf
divu $15, $9
mflo $5
sw $5, 0xb0c($0)
sw $15, 0x94c($0)
mflo $12
ori $31, $28, 0x53fc
divu $29, $31
mflo $0
ori $18, $29, 0x7eb6
div $6, $18
mfhi $25
maddu $6, $8
mfhi $18
addiu $10, $18, 0x5f27
mthi $25
mfhi $31
msub $12, $20
mfhi $4
addiu $30, $28, 0x78a
sw $23, 0xec0($0)
slti $30, $10, 0x7b77
subu $16, $1, $19
andi $22, $11, 0x653e
lb $28, 0x71($0)
ori $27, $22, 0x7bde
divu $8, $27
mfhi $31
sw $6, 0x4a8($0)
lh $6, 0x6e($0)
mtlo $27
mfhi $27
lh $31, 0x16c($0)
slti $11, $28, 0x6f3b
ori $2, $29, 0x70fa
div $8, $2
mfhi $24
ori $18, $1, 0x180d
div $29, $18
mflo $3
ori $17, $2, 0x4588
divu $22, $17
mflo $18
msub $31, $11
mflo $0
ori $24, $3, 0x4502
divu $23, $24
mflo $13
sw $7, 0x750($0)
maddu $3, $21
mflo $27
srav $30, $4, $4
mult $8, $1
mflo $23
madd $1, $17
mfhi $6
maddu $20, $6
mfhi $16
lw $13, 0x82c($0)
mult $7, $12
mfhi $24
madd $24, $3
mflo $2
sw $3, 0xfe8($0)
ori $3, $25, 0x3de6
ori $6, $12, 0x5142
div $9, $6
mflo $25
ori $31, $27, 0x58f1
div $8, $31
mflo $13
madd $14, $26
mfhi $21
sw $27, 0x2b8($0)
mflo $3
addi $18, $31, 0x6394
ori $7, $21, 0x3767
div $15, $7
mfhi $14
sw $14, 0x1d8($0)
ori $26, $20, 0x5a29
div $9, $26
mfhi $29
madd $14, $19
mflo $3
madd $9, $10
mflo $26
maddu $11, $7
mflo $19
lhu $15, 0x368($0)
ori $5, $9, 0x6504
div $21, $5
mfhi $17
ori $7, $21, 0x2efd
divu $19, $7
mflo $12
ori $12, $28, 0xe01
divu $4, $12
mfhi $5
ori $29, $6, 0x3c0b
divu $29, $29
mfhi $19
ori $25, $17, 0x5422
div $13, $25
mflo $23
mthi $18
mfhi $11
sw $26, 0xcf4($0)
srav $31, $4, $21
mtlo $0
mfhi $22
lb $25, 0x6b1($0)
maddu $22, $8
mfhi $31
maddu $23, $6
mfhi $30
mthi $31
mflo $0
ori $20, $5, 0x1e1c
divu $0, $20
mflo $12
lb $28, 0x86($0)
ori $12, $7, 0x56fd
div $6, $12
mfhi $24
ori $30, $22, 0x1a00
divu $16, $30
mflo $19
mtlo $5
mfhi $3
ori $22, $27, 0x701c
div $24, $22
mfhi $23
sw $28, 0x5a8($0)
subu $23, $26, $10
ori $29, $10, 0xf06
div $20, $29
mflo $30
and $11, $13, $23
sltu $29, $19, $22
ori $19, $13, 0x3bec
div $17, $19
mflo $24
mthi $17
mfhi $2
mult $27, $10
mflo $1
xor $9, $20, $29
sw $6, 0xacc($0)
ori $29, $16, 0x434a
divu $18, $29
mfhi $1
msub $23, $6
mflo $11
sw $15, 0x20($0)
maddu $15, $23
mfhi $5
ori $21, $18, 0x1349
div $6, $21
mflo $10
ori $13, $20, 0x56b3
div $20, $13
mfhi $10
xor $22, $28, $7
lhu $16, 0x11e($0)
mflo $7
ori $3, $28, 0x5151
divu $31, $3
mfhi $26
msub $21, $29
mfhi $13
madd $26, $24
mflo $1
lh $28, 0x5c0($0)
xor $6, $11, $17
mtlo $31
mflo $31
lb $14, 0x491($0)
multu $2, $30
mfhi $7
mthi $4
mfhi $5
lhu $14, 0x8ea($0)
ori $8, $21, 0x44c1
divu $6, $8
mfhi $7
lb $31, 0x2b5($0)
mtlo $6
mfhi $9
mtlo $5
mfhi $0
mthi $1
mflo $14
addu $1, $18, $7
sw $18, 0x9b4($0)
subu $13, $31, $22
ori $12, $21, 0x3919
divu $23, $12
mfhi $25
ori $25, $17, 0x7bf8
div $23, $25
mfhi $7
madd $29, $26
mfhi $11
msub $6, $19
mfhi $6
ori $18, $14, 0x5621
divu $11, $18
mfhi $8
xori $8, $9, 0x3456
lbu $27, 0x917($0)
sw $13, 0xc2c($0)
subu $12, $12, $5
sw $17, 0x7a4($0)
ori $31, $18, 0x510b
div $21, $31
mflo $29
sltiu $13, $1, 0x4103
mflo $25
sltu $12, $10, $15
multu $27, $7
mfhi $21
lbu $29, 0x90d($0)
sw $12, 0x410($0)
ori $15, $14, 0x3e6f
divu $3, $15
mfhi $4
nor $10, $14, $7
msub $31, $21
mflo $17
addi $16, $6, 0x6b54
addiu $5, $18, 0x6e5
sw $29, 0x358($0)
ori $5, $20, 0x1268
divu $8, $5
mflo $19
sw $20, 0xf80($0)
maddu $24, $11
mflo $21
slt $9, $11, $27
ori $7, $26, 0x1497
div $15, $7
mflo $27
multu $20, $28
mfhi $1
mthi $26
mfhi $13
ori $22, $22, 0x2dd0
div $13, $22
mflo $9
mflo $21
addi $2, $2, 0x2af8
sw $12, 0xd90($0)
lbu $23, 0xc9d($0)
ori $10, $4, 0x1038
div $7, $10
mfhi $16
maddu $12, $9
mfhi $26
ori $3, $10, 0x34d1
div $14, $3
mfhi $23
msub $16, $30
mfhi $1
multu $14, $4
mflo $26
ori $1, $28, 0x6465
lb $28, 0xed5($0)
ori $29, $29, 0x390f
div $6, $29
mfhi $11
ori $17, $4, 0x511a
sw $27, 0x770($0)
mtlo $29
mfhi $27
mtlo $4
mfhi $26
sw $7, 0x3bc($0)
ori $27, $28, 0x46d4
div $30, $27
mflo $16
ori $29, $29, 0x4b0d
div $31, $29
mfhi $20
ori $7, $22, 0x35b6
srl $30, $17, 0xf
lb $26, 0x869($0)
ori $1, $11, 0x3565
divu $0, $1
mfhi $20
lb $9, 0x97a($0)
