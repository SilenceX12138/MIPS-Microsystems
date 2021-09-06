.ktext 0x4180
_entry:
	ori	$k0, $0, 0x1000
	# sw	$sp, -4($k0)
	mfc0	$k1, $12
	sw	$k1, -8($k0)
	
	addiu	$k0, $k0, -256
	move	$sp, $k0
	
	j	_save_context
	nop
	
_main_handler:
	mfc0	$k0, $14
	addu	$k0, $k0, 4
	mtc0	$k0, $14
	j	_restore_context
	nop
	
_restore:
	eret
	
_save_context:
	sw  	$1, 4($sp)
	sw  	$2, 8($sp)    
	sw  	$3, 12($sp)    
	sw  	$4, 16($sp)    
	sw  	$5, 20($sp)    
	sw  	$6, 24($sp)    
	sw  	$7, 28($sp)    
	sw  	$8, 32($sp)    
	sw  	$9, 36($sp)    
	sw  	$10, 40($sp)    
	sw  	$11, 44($sp)    
	sw  	$12, 48($sp)    
	sw  	$13, 52($sp)    
	sw  	$14, 56($sp)    
	sw  	$15, 60($sp)    
	sw  	$16, 64($sp)    
	sw  	$17, 68($sp)    
	sw  	$18, 72($sp)    
	sw  	$19, 76($sp)    
	sw  	$20, 80($sp)    
	sw  	$21, 84($sp)    
	sw  	$22, 88($sp)    
	sw  	$23, 92($sp)    
	sw  	$24, 96($sp)    
	sw  	$25, 100($sp)    
	sw  	$26, 104($sp)    
blez $13 loop4
	sw  	$27, 108($sp)    
	# sw  	$28, 112($sp)    
	# sw  	$29, 116($sp)    
	sw  	$30, 120($sp)    
	sw  	$31, 124($sp)
	mfhi 	$k0
	sw 	$k0, 128($sp)
	mflo 	$k0
	sw 	$k0, 132($sp)
	j	_main_handler
	nop
	


_restore_context:
	lw 	$1, 4($sp)
	lw  	$2, 8($sp)    
	lw  	$3, 12($sp)    
	lw  	$4, 16($sp)    
	lw  	$5, 20($sp)    
	lw  	$6, 24($sp)    
	lw  	$7, 28($sp)    
	lw  	$8, 32($sp)    
	lw  	$9, 36($sp)    
	lw  	$10, 40($sp)    
	lw  	$11, 44($sp)    
	lw  	$12, 48($sp)    
	lw  	$13, 52($sp)    
	lw  	$14, 56($sp)    
	lw  	$15, 60($sp)    
	lw  	$16, 64($sp)    
	lw  	$17, 68($sp)    
	lw  	$18, 72($sp)    
	lw  	$19, 76($sp)    
	lw  	$20, 80($sp)    
	lw  	$21, 84($sp)    
	lw  	$22, 88($sp)    
	lw  	$23, 92($sp)    
	lw  	$24, 96($sp)    
	lw  	$25, 100($sp)    
	lw  	$26, 104($sp)    
	lw  	$27, 108($sp)    
	# lw  	$28, 112($sp)    
	# lw  	$29, 116($sp)    
	lw  	$30, 120($sp)    
	lw  	$31, 124($sp)    
	lw 	$k0, 128($sp)
	mthi 	$k0
	lw 	$k0, 132($sp)
	mtlo 	$k0
    	j 	_restore	
	nop

.text
#0x3000
li $28 0
#0x3004
li $29 0
#0x3008
mtc0 $0 $12
#0x300c
srl $24 $3 12
#0x3010
sltiu $7 $17 6694
#0x3014
srl $31 $17 24
#0x3018
xor $7 $22 $3
#0x301c
slti $20 $30 1194
#0x3020
ori $12 $11 0xdfa5
#0x3024
sllv $4 $1 $24
#0x3028
sh $9 10($0)
#0x302c
lw $5 112($0)
#0x3030
slt $31 $17 $11
#0x3034
sra $17 $14 7
#0x3038
xor $22 $18 $8
#0x303c
xori $15 $6 0xdfc9
#0x3040
mflo $13
#0x3044
sw $16 12($0)
#0x3048
andi $30 $22 0xf8be
#0x304c
lbu $1 2($0)
#0x3050
lb $1 12($0)
#0x3054
xori $16 $12 0xfdb7
#0x3058
mflo $26
#0x305c
srlv $10 $11 $18
#0x3060
mult $12 $18
#0x3064
srlv $11 $21 $7
#0x3068
addu $25 $14 $15
#0x306c
li $15 -4992
#0x3070
divu $19 $15
#0x3074
sll $14 $14 31
#0x3078
srav $20 $17 $2
#0x307c
srl $8 $8 31
#0x3080
srav $30 $23 $30
#0x3084
slt $18 $9 $7
#0x3088
sw $10 4($0)
#0x308c
mflo $18
#0x3090
sltu $14 $26 $6
#0x3094
lb $13 1($0)
#0x3098
mtlo $22
#0x309c
sllv $31 $22 $14
#0x30a0
blez $6 loop9
#0x30a4
xor $10 $7 $20
#0x30a8
sw $18 56($0)
#0x30ac
addiu $14 $19 30161
#0x30b0
add $6 $1 $30
#0x30b4
sw $20 16($0)
#0x30b8
xori $18 $25 0x1a64
#0x30bc
addu $19 $2 $23
#0x30c0
addi $30 $17 29429
#0x30c4
andi $15 $8 0xd312
#0x30c8
sltiu $12 $6 29459
#0x30cc
sltiu $4 $26 15332
#0x30d0
and $13 $9 $23
#0x30d4
nor $5 $11 $12
#0x30d8
nor $25 $3 $22
#0x30dc
addi $26 $5 -18885
#0x30e0
sllv $25 $5 $6
#0x30e4
sltiu $24 $14 8484
#0x30e8
add $11 $26 $23
#0x30ec
mthi $6
#0x30f0
andi $30 $20 0x1592
#0x30f4
lw $13 0($0)
#0x30f8
jal loop1
#0x30fc
sub $18 $13 $19
#0x3100
srl $25 $23 23
#0x3104
lw $17 20($0)
#0x3108
lh $25 8($0)
#0x310c
addi $20 $9 -31877
#0x3110
mfhi $27
#0x3114
slti $9 $9 -30790
#0x3118
mthi $22
#0x311c
nor $15 $31 $18
#0x3120
lw $10 24($0)
#0x3124
multu $3 $10
#0x3128
srlv $13 $25 $7
#0x312c
sh $2 0($0)
#0x3130
srav $5 $25 $20
#0x3134
xor $13 $31 $9
#0x3138
lui $5 0xba13
#0x313c
sllv $12 $2 $11
#0x3140
subu $27 $22 $25
#0x3144
lui $26 0x370d
#0x3148
bne $4 $21 loop4
#0x314c
lh $2 12($0)
#0x3150
slti $16 $24 -1635
#0x3154
sw $13 120($0)
#0x3158
sllv $23 $4 $2
#0x315c
mflo $20
#0x3160
srav $17 $27 $13
#0x3164
slti $22 $15 10382
#0x3168
j loop2
#0x316c
xori $14 $9 0x3a41
#0x3170
andi $2 $13 0x41da
#0x3174
sll $13 $15 17
#0x3178
srl $3 $4 1
#0x317c
nor $17 $27 $14
#0x3180
or $9 $18 $22
#0x3184
mfhi $2
#0x3188
lh $3 18($0)
#0x318c
srl $14 $17 13
#0x3190
mtlo $10
#0x3194
lb $25 25($0)
#0x3198
xor $22 $1 $6
#0x319c
lh $2 50($0)
#0x31a0
addu $13 $22 $20
#0x31a4
sll $18 $21 16
#0x31a8
mtlo $22
#0x31ac
addiu $4 $15 2629
#0x31b0
sub $19 $16 $31
#0x31b4
srl $21 $11 16
#0x31b8
addiu $7 $23 22445
#0x31bc
srav $16 $8 $11
#0x31c0
nor $6 $3 $11
#0x31c4
mtlo $23
#0x31c8
sh $30 52($0)
#0x31cc
sb $17 15($0)
#0x31d0
addu $23 $22 $24
#0x31d4
mthi $17
#0x31d8
lh $30 18($0)
#0x31dc
xor $20 $14 $10
#0x31e0
sltiu $25 $7 31967
#0x31e4
lw $24 116($0)
#0x31e8
lh $20 26($0)
#0x31ec
lb $21 5($0)
#0x31f0
sw $15 4($0)
#0x31f4
sra $4 $12 15
#0x31f8
addiu $13 $18 409
#0x31fc
sll $10 $7 2
#0x3200
mfhi $2
#0x3204
sltu $26 $2 $31
#0x3208
sb $27 19($0)
#0x320c
mult $27 $30
#0x3210
addiu $3 $10 9054
#0x3214
lw $9 104($0)
#0x3218
lw $17 12($0)
#0x321c
add $15 $24 $27
#0x3220
andi $20 $3 0x49e7
#0x3224
mthi $30
#0x3228
sltu $2 $1 $4
#0x322c
sh $30 56($0)
#0x3230
sub $5 $17 $7
#0x3234
srl $24 $9 17
#0x3238
sub $4 $17 $3
#0x323c
sw $20 36($0)
#0x3240
sh $20 20($0)
#0x3244
sll $24 $1 29
#0x3248
and $16 $22 $20
#0x324c
xor $15 $19 $20
#0x3250
lhu $20 24($0)
#0x3254
lw $8 96($0)
#0x3258
xori $22 $18 0xd083
#0x325c
add $17 $1 $1
#0x3260
sll $25 $9 31
#0x3264
andi $16 $15 0xbfa2
loop1:
#0x3268
addu $24 $8 $3
#0x326c
sll $25 $7 6
#0x3270
slt $17 $26 $24
#0x3274
slt $26 $15 $17
#0x3278
and $20 $30 $19
#0x327c
sh $20 24($0)
#0x3280
mfhi $3
#0x3284
lui $23 0x23e5
#0x3288
srav $4 $6 $14
#0x328c
sra $21 $26 27
#0x3290
sltiu $22 $13 27623
#0x3294
sllv $6 $8 $13
#0x3298
add $9 $26 $16
#0x329c
lh $12 30($0)
#0x32a0
mfhi $25
#0x32a4
sra $20 $19 7
#0x32a8
mtlo $31
#0x32ac
lbu $16 7($0)
#0x32b0
lb $5 26($0)
#0x32b4
mtlo $14
#0x32b8
addiu $31 $3 20708
#0x32bc
sub $13 $17 $1
#0x32c0
sll $24 $16 8
#0x32c4
addiu $17 $15 32152
#0x32c8
addu $31 $15 $10
#0x32cc
mult $21 $6
#0x32d0
sltu $31 $12 $11
#0x32d4
addiu $16 $15 8416
#0x32d8
andi $26 $3 0x6bd8
#0x32dc
multu $31 $22
#0x32e0
srl $7 $31 2
#0x32e4
srlv $1 $5 $20
#0x32e8
li $5 11742
#0x32ec
divu $4 $5
#0x32f0
mtlo $25
#0x32f4
slt $15 $21 $17
#0x32f8
lhu $24 26($0)
#0x32fc
mtlo $18
#0x3300
sub $20 $15 $21
#0x3304
addi $11 $20 -18297
#0x3308
addiu $19 $11 24735
#0x330c
mult $3 $9
#0x3310
xor $8 $27 $31
#0x3314
sltu $16 $16 $7
#0x3318
ori $25 $21 0x2b26
#0x331c
sll $27 $27 20
#0x3320
sra $11 $5 1
#0x3324
lw $23 80($0)
#0x3328
andi $22 $19 0x6fe3
#0x332c
lh $4 6($0)
#0x3330
add $21 $17 $6
#0x3334
multu $14 $22
#0x3338
andi $16 $19 0x6d2c
#0x333c
srav $22 $25 $23
#0x3340
sw $19 20($0)
#0x3344
multu $4 $25
#0x3348
lh $23 16($0)
#0x334c
addiu $5 $4 22583
#0x3350
addi $2 $24 22360
#0x3354
ori $27 $18 0x969c
#0x3358
multu $25 $12
#0x335c
mflo $18
#0x3360
addi $16 $19 -5662
#0x3364
sllv $11 $9 $22
#0x3368
xor $16 $12 $14
#0x336c
mflo $11
#0x3370
sw $6 8($0)
#0x3374
mult $5 $10
#0x3378
subu $26 $24 $10
#0x337c
sw $19 28($0)
#0x3380
lh $10 2($0)
#0x3384
sub $6 $5 $10
#0x3388
slti $7 $17 -5934
#0x338c
mthi $17
#0x3390
lw $10 16($0)
#0x3394
multu $13 $4
#0x3398
add $7 $22 $11
#0x339c
lh $5 20($0)
#0x33a0
addiu $17 $18 26770
#0x33a4
sltiu $21 $31 4874
#0x33a8
sub $23 $1 $30
#0x33ac
sllv $20 $16 $26
#0x33b0
sb $27 30($0)
#0x33b4
srav $20 $27 $7
#0x33b8
mflo $6
#0x33bc
mfhi $25
#0x33c0
mflo $12
#0x33c4
srl $9 $11 17
#0x33c8
blez $22 loop3
#0x33cc
addu $20 $2 $9
#0x33d0
sltu $14 $6 $11
#0x33d4
add $8 $25 $13
#0x33d8
lh $26 4($0)
#0x33dc
sw $8 28($0)
#0x33e0
andi $11 $9 0x2d7a
#0x33e4
lh $13 46($0)
#0x33e8
sltiu $11 $24 18428
#0x33ec
mult $8 $21
#0x33f0
sltiu $10 $25 32191
#0x33f4
mtlo $3
#0x33f8
sltiu $12 $10 8905
#0x33fc
sllv $31 $5 $12
#0x3400
sll $25 $18 4
#0x3404
srlv $26 $1 $6
#0x3408
lbu $21 0($0)
#0x340c
subu $12 $26 $24
#0x3410
sll $14 $18 2
#0x3414
add $30 $15 $31
#0x3418
srlv $22 $14 $1
#0x341c
andi $10 $23 0xbd08
#0x3420
lh $10 30($0)
#0x3424
lh $12 2($0)
#0x3428
sw $17 16($0)
#0x342c
lui $30 0xb702
#0x3430
mthi $13
#0x3434
andi $10 $21 0xf9bb
#0x3438
slti $8 $3 -24635
#0x343c
bgez $16 loop3
#0x3440
subu $1 $5 $10
#0x3444
xori $2 $22 0x10ed
#0x3448
multu $22 $16
#0x344c
lh $26 26($0)
#0x3450
addu $25 $9 $31
#0x3454
addu $8 $4 $25
#0x3458
mtlo $7
#0x345c
addu $9 $17 $2
#0x3460
srav $5 $25 $25
#0x3464
srav $4 $27 $14
#0x3468
lw $3 28($0)
#0x346c
mult $11 $22
#0x3470
xor $31 $25 $10
#0x3474
sw $20 64($0)
#0x3478
slti $16 $31 -22090
#0x347c
sra $9 $24 30
#0x3480
mflo $7
#0x3484
mfhi $27
#0x3488
sh $15 34($0)
#0x348c
sll $21 $8 21
#0x3490
sw $31 16($0)
#0x3494
slti $15 $7 609
#0x3498
lh $5 34($0)
#0x349c
mthi $13
#0x34a0
subu $8 $22 $23
#0x34a4
or $23 $11 $1
#0x34a8
lbu $8 2($0)
#0x34ac
mflo $3
#0x34b0
nor $24 $27 $20
#0x34b4
slt $5 $14 $6
#0x34b8
sll $10 $15 29
#0x34bc
sll $11 $21 18
#0x34c0
and $25 $10 $17
#0x34c4
slt $23 $27 $2
#0x34c8
sll $10 $7 0
#0x34cc
lh $24 60($0)
#0x34d0
mflo $3
#0x34d4
addiu $20 $18 31372
#0x34d8
mfhi $22
#0x34dc
lb $22 22($0)
#0x34e0
lh $22 16($0)
#0x34e4
slti $3 $23 -22700
#0x34e8
sw $30 124($0)
#0x34ec
sw $23 24($0)
#0x34f0
srlv $27 $10 $10
#0x34f4
blez $22 loop4
#0x34f8
mfhi $17
#0x34fc
sw $16 84($0)
#0x3500
sra $4 $12 5
#0x3504
xor $14 $10 $21
#0x3508
ori $24 $18 0x8755
#0x350c
addi $5 $31 -31554
#0x3510
sltiu $3 $2 5249
#0x3514
andi $3 $24 0x1e2c
#0x3518
mult $13 $5
#0x351c
sub $23 $4 $1
#0x3520
slt $8 $18 $9
#0x3524
srl $9 $20 6
#0x3528
sltiu $6 $13 19607
#0x352c
mthi $27
#0x3530
lw $10 100($0)
#0x3534
srl $30 $23 16
#0x3538
lui $19 0xd3e5
#0x353c
subu $5 $22 $8
#0x3540
mult $8 $30
#0x3544
sll $11 $25 20
#0x3548
mfhi $13
#0x354c
subu $10 $27 $21
#0x3550
addi $6 $6 2604
#0x3554
beq $15 $30 loop1
#0x3558
lh $23 18($0)
#0x355c
multu $27 $10
#0x3560
sh $26 26($0)
#0x3564
sra $8 $9 23
#0x3568
andi $31 $2 0x0896
#0x356c
srav $10 $13 $11
#0x3570
sb $24 0($0)
#0x3574
add $4 $15 $10
#0x3578
lb $31 27($0)
#0x357c
or $31 $9 $12
#0x3580
ori $9 $13 0xb664
#0x3584
mflo $11
#0x3588
sb $20 26($0)
#0x358c
ori $1 $17 0x474d
#0x3590
lw $31 68($0)
#0x3594
mfhi $17
#0x3598
lb $10 15($0)
#0x359c
nor $14 $31 $21
#0x35a0
srav $14 $22 $22
#0x35a4
slt $31 $24 $7
#0x35a8
sltiu $17 $18 20955
#0x35ac
nor $21 $30 $9
#0x35b0
mtlo $24
#0x35b4
lb $22 7($0)
#0x35b8
sb $30 8($0)
#0x35bc
sw $31 28($0)
#0x35c0
sh $20 0($0)
#0x35c4
sub $1 $20 $22
#0x35c8
mflo $4
#0x35cc
li $21 19941
#0x35d0
divu $5 $21
#0x35d4
lh $4 28($0)
#0x35d8
sllv $3 $27 $30
#0x35dc
sh $16 8($0)
#0x35e0
sllv $4 $16 $24
#0x35e4
subu $16 $12 $17
#0x35e8
slt $2 $15 $20
#0x35ec
addi $3 $13 15937
#0x35f0
sll $22 $22 13
#0x35f4
slti $18 $7 -21264
#0x35f8
bltz $11 loop8
#0x35fc
lbu $5 5($0)
#0x3600
multu $17 $13
#0x3604
mfhi $27
#0x3608
addu $27 $14 $6
#0x360c
sltu $5 $8 $11
#0x3610
mfhi $18
#0x3614
addu $5 $26 $9
#0x3618
sb $11 7($0)
#0x361c
subu $17 $27 $27
#0x3620
sw $12 56($0)
#0x3624
and $19 $10 $16
#0x3628
andi $12 $26 0xdaaa
#0x362c
add $21 $11 $4
#0x3630
lbu $17 24($0)
#0x3634
lb $3 21($0)
#0x3638
mult $14 $9
#0x363c
mflo $18
#0x3640
ori $25 $15 0xba7d
loop6:
#0x3644
ori $5 $18 0xf3e7
#0x3648
sh $31 42($0)
#0x364c
lh $27 24($0)
#0x3650
sub $30 $7 $15
#0x3654
bltz $13 loop6
#0x3658
multu $7 $4
#0x365c
ori $8 $24 0xb143
#0x3660
sw $27 16($0)
#0x3664
sltu $20 $7 $21
#0x3668
sltu $24 $17 $6
#0x366c
sltiu $30 $2 27064
#0x3670
sllv $20 $12 $5
#0x3674
li $10 22549
#0x3678
div $29 $10
#0x367c
beq $20 $2 loop8
#0x3680
xori $12 $18 0x5e5c
#0x3684
sh $15 58($0)
#0x3688
mfhi $4
#0x368c
multu $19 $19
#0x3690
or $23 $30 $23
#0x3694
subu $15 $26 $13
#0x3698
mfhi $5
#0x369c
srl $13 $8 5
#0x36a0
addu $2 $1 $16
#0x36a4
mult $27 $22
#0x36a8
addu $4 $4 $18
#0x36ac
addiu $12 $11 19549
#0x36b0
sltiu $13 $27 9703
#0x36b4
addiu $7 $17 15473
#0x36b8
sltu $13 $3 $27
#0x36bc
sll $16 $7 1
#0x36c0
lw $27 20($0)
#0x36c4
addu $13 $5 $12
#0x36c8
lh $1 4($0)
#0x36cc
sub $31 $22 $26
#0x36d0
mult $17 $25
#0x36d4
bgez $3 loop1
#0x36d8
srav $2 $21 $2
#0x36dc
or $17 $26 $24
#0x36e0
mult $3 $19
#0x36e4
addiu $26 $26 21024
#0x36e8
lb $31 3($0)
#0x36ec
li $15 4969
#0x36f0
divu $31 $15
#0x36f4
lw $18 28($0)
#0x36f8
and $24 $23 $22
#0x36fc
lb $16 25($0)
#0x3700
sub $15 $10 $25
#0x3704
sra $27 $17 9
#0x3708
xori $5 $3 0x09e3
#0x370c
slti $3 $17 -12697
#0x3710
addu $22 $22 $23
#0x3714
lhu $5 16($0)
#0x3718
lw $4 12($0)
#0x371c
lbu $24 6($0)
#0x3720
mult $14 $2
#0x3724
mthi $7
#0x3728
slt $27 $19 $31
#0x372c
srlv $19 $12 $1
#0x3730
xor $14 $4 $4
#0x3734
mult $12 $11
#0x3738
sllv $10 $25 $20
#0x373c
lbu $13 1($0)
#0x3740
mtlo $30
#0x3744
sub $27 $27 $14
#0x3748
nor $4 $27 $30
#0x374c
addi $19 $18 -17784
#0x3750
srlv $13 $24 $1
#0x3754
sb $19 6($0)
#0x3758
mtlo $27
#0x375c
mflo $30
#0x3760
mtlo $13
#0x3764
lui $21 0x3c8d
#0x3768
srav $25 $25 $11
#0x376c
lw $16 20($0)
#0x3770
lw $15 116($0)
#0x3774
or $14 $8 $7
#0x3778
sh $16 10($0)
#0x377c
sltiu $10 $31 8248
#0x3780
lui $19 0xfe18
#0x3784
sra $18 $26 23
#0x3788
sb $10 1($0)
#0x378c
lbu $10 9($0)
#0x3790
add $22 $6 $1
#0x3794
or $13 $25 $6
#0x3798
slt $26 $15 $2
#0x379c
sra $2 $16 27
#0x37a0
ori $2 $15 0x1508
loop5:
#0x37a4
sw $3 20($0)
#0x37a8
addu $11 $22 $1
#0x37ac
srlv $24 $14 $21
#0x37b0
sltu $21 $18 $10
#0x37b4
or $19 $5 $11
#0x37b8
addi $10 $23 -4843
#0x37bc
sw $26 4($0)
#0x37c0
lhu $2 4($0)
#0x37c4
ori $3 $30 0x3a8f
#0x37c8
addiu $31 $6 693
#0x37cc
slt $4 $23 $30
#0x37d0
mtlo $22
#0x37d4
sll $23 $6 12
#0x37d8
mfhi $25
#0x37dc
sra $20 $20 8
#0x37e0
add $15 $3 $14
#0x37e4
and $24 $24 $7
#0x37e8
srl $19 $13 29
#0x37ec
mflo $8
#0x37f0
sh $2 28($0)
#0x37f4
mthi $24
#0x37f8
ori $27 $25 0x5354
#0x37fc
addu $10 $25 $21
#0x3800
sra $19 $3 5
#0x3804
srav $2 $10 $5
#0x3808
subu $20 $30 $17
#0x380c
j loop6
#0x3810
add $2 $27 $30
#0x3814
sh $13 0($0)
#0x3818
lbu $17 13($0)
#0x381c
add $7 $5 $3
#0x3820
srlv $27 $16 $25
#0x3824
lb $11 21($0)
#0x3828
sb $6 0($0)
#0x382c
sub $6 $6 $3
#0x3830
slti $26 $11 -3341
#0x3834
mfhi $18
#0x3838
subu $10 $18 $9
#0x383c
mthi $16
#0x3840
bgez $28 loop5
#0x3844
sra $11 $7 21
#0x3848
sltiu $26 $11 19449
#0x384c
ori $7 $2 0x112e
#0x3850
slti $6 $20 6025
#0x3854
addi $7 $26 -21019
#0x3858
srav $1 $25 $13
#0x385c
sllv $18 $26 $2
#0x3860
sw $6 4($0)
#0x3864
sll $23 $16 12
#0x3868
multu $4 $24
#0x386c
addu $11 $18 $12
#0x3870
and $10 $14 $6
#0x3874
nor $21 $10 $23
#0x3878
lw $22 28($0)
#0x387c
sltiu $17 $17 9364
#0x3880
addi $10 $11 19565
#0x3884
sub $21 $10 $17
#0x3888
lh $20 12($0)
#0x388c
mflo $20
#0x3890
sltu $10 $25 $19
#0x3894
sh $31 24($0)
#0x3898
mfhi $20
#0x389c
multu $2 $16
#0x38a0
sh $22 26($0)
#0x38a4
lh $18 4($0)
#0x38a8
lw $12 68($0)
#0x38ac
addiu $25 $16 4556
#0x38b0
slti $17 $20 32344
#0x38b4
or $7 $21 $4
#0x38b8
mthi $13
#0x38bc
addu $5 $17 $15
#0x38c0
lb $2 10($0)
#0x38c4
srav $11 $2 $14
#0x38c8
nor $2 $7 $22
#0x38cc
slt $21 $25 $20
#0x38d0
srlv $31 $23 $12
#0x38d4
srlv $10 $19 $2
#0x38d8
mult $18 $10
#0x38dc
addi $24 $10 -12260
#0x38e0
andi $20 $25 0x3a14
#0x38e4
andi $30 $22 0x86c4
#0x38e8
sh $25 46($0)
#0x38ec
and $5 $15 $17
#0x38f0
xori $19 $30 0xd0f6
#0x38f4
bgtz $23 loop3
#0x38f8
lui $13 0x696c
#0x38fc
sllv $3 $26 $1
#0x3900
lh $17 8($0)
#0x3904
bltz $22 loop1
#0x3908
addiu $22 $25 10487
#0x390c
lw $30 0($0)
#0x3910
slt $22 $7 $16
#0x3914
sw $30 8($0)
#0x3918
lui $10 0x4484
#0x391c
lw $10 124($0)
#0x3920
addi $30 $9 31970
#0x3924
lh $11 34($0)
#0x3928
ori $12 $20 0xec19
#0x392c
sra $24 $31 13
#0x3930
sra $9 $12 8
#0x3934
sw $21 28($0)
#0x3938
add $14 $4 $7
#0x393c
mfhi $14
#0x3940
sltu $10 $2 $31
#0x3944
sh $8 62($0)
#0x3948
sltiu $30 $6 5850
#0x394c
addiu $9 $15 1620
loop8:
#0x3950
lbu $31 11($0)
#0x3954
sw $31 96($0)
#0x3958
srl $4 $30 25
#0x395c
slti $23 $8 29504
#0x3960
xor $27 $1 $8
#0x3964
li $22 -24524
#0x3968
div $27 $22
#0x396c
sllv $31 $13 $8
#0x3970
addiu $9 $16 274
#0x3974
sllv $6 $31 $19
#0x3978
xor $19 $18 $27
#0x397c
j loop8
#0x3980
mthi $25
#0x3984
lhu $6 14($0)
#0x3988
bgez $24 loop4
#0x398c
and $13 $31 $24
#0x3990
lb $12 12($0)
#0x3994
lui $18 0x6bb7
#0x3998
or $17 $12 $5
#0x399c
and $20 $17 $22
#0x39a0
srav $7 $19 $9
#0x39a4
sra $19 $11 21
#0x39a8
jal loop1
#0x39ac
sw $25 108($0)
#0x39b0
addu $9 $22 $21
#0x39b4
addu $26 $26 $6
#0x39b8
sw $18 20($0)
#0x39bc
mthi $18
#0x39c0
sll $4 $3 17
#0x39c4
lhu $1 26($0)
#0x39c8
add $21 $2 $18
#0x39cc
lw $18 32($0)
#0x39d0
xori $19 $21 0x510d
#0x39d4
sb $26 7($0)
#0x39d8
lh $27 56($0)
#0x39dc
lw $16 12($0)
#0x39e0
slt $23 $7 $7
#0x39e4
or $6 $25 $1
#0x39e8
andi $21 $23 0x386b
#0x39ec
and $16 $31 $6
#0x39f0
lw $9 16($0)
#0x39f4
ori $6 $1 0x6c59
#0x39f8
lb $8 26($0)
#0x39fc
slti $14 $4 -1291
#0x3a00
srav $31 $27 $31
#0x3a04
slti $10 $16 32185
#0x3a08
sll $2 $15 11
#0x3a0c
sltiu $24 $27 7840
#0x3a10
lh $26 60($0)
#0x3a14
mult $31 $5
#0x3a18
sw $31 24($0)
#0x3a1c
lb $20 25($0)
#0x3a20
mthi $20
#0x3a24
or $31 $10 $22
#0x3a28
bgtz $18 loop0
#0x3a2c
addu $9 $20 $16
loop7:
#0x3a30
slti $13 $22 12036
#0x3a34
subu $21 $4 $27
#0x3a38
jal loop7
#0x3a3c
add $3 $6 $26
#0x3a40
mthi $10
#0x3a44
xor $1 $15 $30
#0x3a48
bgtz $27 loop8
#0x3a4c
sub $25 $10 $5
#0x3a50
srlv $26 $22 $2
#0x3a54
sra $22 $23 12
#0x3a58
sh $14 24($0)
#0x3a5c
nor $20 $18 $24
#0x3a60
sh $12 8($0)
#0x3a64
subu $15 $15 $25
#0x3a68
addi $22 $11 17023
#0x3a6c
srav $6 $30 $24
#0x3a70
andi $7 $25 0x977e
#0x3a74
sllv $8 $8 $15
#0x3a78
lhu $11 6($0)
#0x3a7c
mtlo $16
#0x3a80
srl $5 $26 22
#0x3a84
or $24 $6 $30
#0x3a88
sll $13 $7 23
#0x3a8c
ori $18 $12 0x0ba1
#0x3a90
mfhi $25
#0x3a94
addu $10 $2 $9
#0x3a98
or $5 $23 $18
#0x3a9c
mtlo $1
#0x3aa0
andi $30 $26 0xf7a1
#0x3aa4
lh $13 60($0)
#0x3aa8
lw $25 0($0)
#0x3aac
sll $6 $27 22
#0x3ab0
lui $10 0x3d5f
#0x3ab4
srl $24 $23 18
#0x3ab8
slti $11 $22 -25709
#0x3abc
sb $20 20($0)
#0x3ac0
lhu $9 6($0)
#0x3ac4
sub $12 $18 $17
#0x3ac8
sltiu $12 $1 28398
#0x3acc
srav $13 $6 $3
#0x3ad0
lh $30 42($0)
#0x3ad4
or $15 $10 $12
#0x3ad8
addu $6 $13 $13
#0x3adc
xor $15 $18 $1
#0x3ae0
srlv $12 $26 $23
#0x3ae4
lbu $1 20($0)
#0x3ae8
lb $14 23($0)
#0x3aec
add $27 $22 $14
#0x3af0
and $30 $9 $3
#0x3af4
li $3 23802
#0x3af8
div $3 $3
#0x3afc
nor $20 $11 $17
#0x3b00
lui $11 0x72fd
#0x3b04
li $19 -4027
#0x3b08
divu $21 $19
#0x3b0c
slt $12 $18 $19
#0x3b10
mflo $10
#0x3b14
sh $10 30($0)
#0x3b18
lw $18 32($0)
#0x3b1c
addu $25 $25 $3
#0x3b20
addiu $25 $1 11899
#0x3b24
mult $15 $19
#0x3b28
and $13 $31 $9
#0x3b2c
lbu $8 16($0)
#0x3b30
addu $7 $3 $1
#0x3b34
xor $1 $3 $2
#0x3b38
sw $31 116($0)
#0x3b3c
sb $11 5($0)
#0x3b40
ori $25 $26 0xdea5
#0x3b44
mtlo $4
#0x3b48
xor $9 $19 $21
#0x3b4c
lb $24 18($0)
#0x3b50
sll $15 $15 26
#0x3b54
mfhi $2
#0x3b58
beq $27 $21 loop6
#0x3b5c
addu $23 $3 $14
#0x3b60
sub $11 $16 $17
#0x3b64
mtlo $25
#0x3b68
mult $19 $24
#0x3b6c
sra $26 $13 30
#0x3b70
sw $27 4($0)
#0x3b74
sub $7 $2 $22
#0x3b78
and $1 $16 $13
#0x3b7c
sra $8 $22 10
#0x3b80
blez $13 loop9
#0x3b84
mthi $16
#0x3b88
slt $9 $31 $3
#0x3b8c
bne $15 $27 loop9
#0x3b90
lui $1 0x4e04
#0x3b94
sh $26 4($0)
#0x3b98
sub $15 $2 $7
#0x3b9c
sub $21 $16 $12
loop2:
#0x3ba0
mfhi $26
#0x3ba4
ori $18 $22 0x6044
#0x3ba8
sra $19 $20 16
#0x3bac
sll $14 $25 3
#0x3bb0
bgtz $13 loop4
#0x3bb4
and $9 $7 $2
#0x3bb8
jal loop7
loop3:
#0x3bbc
xori $2 $4 0xee00
#0x3bc0
sltu $25 $20 $21
#0x3bc4
lhu $26 14($0)
#0x3bc8
or $10 $21 $14
#0x3bcc
lw $6 112($0)
#0x3bd0
srlv $20 $30 $26
#0x3bd4
addiu $2 $30 26345
#0x3bd8
slt $3 $10 $1
#0x3bdc
lw $7 0($0)
#0x3be0
lui $6 0x303c
#0x3be4
sllv $20 $17 $15
#0x3be8
lb $4 14($0)
#0x3bec
mfhi $31
#0x3bf0
xor $15 $27 $4
#0x3bf4
sub $5 $3 $16
#0x3bf8
srlv $16 $13 $1
#0x3bfc
sll $4 $13 11
#0x3c00
xori $19 $18 0x0174
#0x3c04
lw $23 20($0)
#0x3c08
xori $4 $24 0x2095
#0x3c0c
srl $2 $23 27
#0x3c10
sb $24 1($0)
#0x3c14
add $20 $23 $13
#0x3c18
mtlo $8
#0x3c1c
blez $6 loop5
loop0:
#0x3c20
sw $5 16($0)
#0x3c24
slt $8 $7 $18
#0x3c28
mflo $22
#0x3c2c
and $4 $17 $8
#0x3c30
addu $21 $7 $21
#0x3c34
ori $25 $26 0x5e40
#0x3c38
slti $7 $31 -364
#0x3c3c
mtlo $20
#0x3c40
mult $8 $30
#0x3c44
sw $14 4($0)
#0x3c48
mtlo $4
#0x3c4c
or $14 $14 $27
#0x3c50
or $2 $17 $22
#0x3c54
lui $14 0xa57b
#0x3c58
lui $15 0x3e23
#0x3c5c
sw $13 28($0)
#0x3c60
sw $12 116($0)
#0x3c64
jal loop5
#0x3c68
sw $30 4($0)
#0x3c6c
sh $11 0($0)
#0x3c70
lw $7 108($0)
#0x3c74
sll $13 $3 4
#0x3c78
slt $13 $16 $23
#0x3c7c
mflo $15
#0x3c80
andi $1 $21 0xdeaf
#0x3c84
lh $19 4($0)
#0x3c88
lh $18 10($0)
#0x3c8c
sltu $23 $14 $1
#0x3c90
andi $13 $14 0xdbcc
#0x3c94
sra $30 $21 2
#0x3c98
lbu $5 13($0)
#0x3c9c
and $12 $27 $10
#0x3ca0
sltiu $25 $30 31620
#0x3ca4
addu $13 $2 $27
#0x3ca8
lh $17 12($0)
#0x3cac
slti $30 $11 -27379
#0x3cb0
multu $25 $12
#0x3cb4
bgez $21 loop6
#0x3cb8
addu $27 $1 $9
#0x3cbc
mult $26 $8
#0x3cc0
lh $19 46($0)
#0x3cc4
lbu $18 20($0)
#0x3cc8
lbu $13 2($0)
#0x3ccc
xori $30 $26 0xab04
#0x3cd0
sw $12 84($0)
#0x3cd4
addu $15 $9 $22
#0x3cd8
lbu $18 23($0)
#0x3cdc
sub $25 $24 $19
#0x3ce0
srav $19 $30 $4
#0x3ce4
lui $3 0x232b
#0x3ce8
mfhi $26
#0x3cec
lb $9 17($0)
#0x3cf0
lh $1 52($0)
#0x3cf4
sb $21 26($0)
#0x3cf8
addiu $6 $6 21808
#0x3cfc
lw $24 52($0)
#0x3d00
j loop6
#0x3d04
srl $27 $21 18
#0x3d08
lw $12 4($0)
#0x3d0c
srlv $11 $10 $14
#0x3d10
nor $25 $15 $4
#0x3d14
or $11 $10 $15
#0x3d18
sllv $17 $3 $9
#0x3d1c
srav $11 $1 $30
#0x3d20
multu $14 $25
#0x3d24
srlv $9 $9 $3
#0x3d28
xor $5 $14 $21
#0x3d2c
mult $27 $3
#0x3d30
li $3 -11192
#0x3d34
divu $11 $3
#0x3d38
sb $27 21($0)
#0x3d3c
addu $9 $8 $14
#0x3d40
sw $17 20($0)
#0x3d44
sh $18 2($0)
#0x3d48
xor $7 $18 $14
#0x3d4c
lw $7 12($0)
#0x3d50
lb $11 5($0)
#0x3d54
srav $30 $14 $15
#0x3d58
slti $31 $20 19409
#0x3d5c
add $24 $30 $23
#0x3d60
sra $11 $2 19
#0x3d64
sw $9 20($0)
#0x3d68
mthi $16
#0x3d6c
beq $13 $25 loop1
#0x3d70
sllv $12 $16 $13
#0x3d74
lw $6 12($0)
#0x3d78
multu $27 $27
#0x3d7c
addu $25 $6 $6
#0x3d80
lui $31 0x30be
#0x3d84
sh $24 30($0)
#0x3d88
sh $17 4($0)
#0x3d8c
add $11 $15 $1
#0x3d90
lbu $26 30($0)
#0x3d94
srav $27 $27 $26
#0x3d98
sw $6 20($0)
#0x3d9c
lh $13 20($0)
#0x3da0
lh $10 14($0)
#0x3da4
xori $6 $2 0x7570
#0x3da8
srl $25 $3 28
#0x3dac
sw $5 24($0)
#0x3db0
and $7 $25 $30
#0x3db4
slt $18 $24 $22
#0x3db8
mthi $18
#0x3dbc
srav $7 $19 $15
#0x3dc0
sltu $31 $30 $30
#0x3dc4
addi $13 $11 -3462
#0x3dc8
sw $11 28($0)
#0x3dcc
mult $17 $6
#0x3dd0
lui $13 0xab47
#0x3dd4
sltu $31 $1 $10
#0x3dd8
sra $4 $21 20
#0x3ddc
lh $6 24($0)
#0x3de0
lh $18 14($0)
#0x3de4
sltiu $15 $17 24737
#0x3de8
mult $13 $1
#0x3dec
mfhi $22
#0x3df0
sh $14 40($0)
#0x3df4
lh $11 42($0)
#0x3df8
or $6 $30 $1
#0x3dfc
mtlo $18
#0x3e00
nor $23 $3 $10
#0x3e04
beq $20 $24 loop3
#0x3e08
lhu $1 18($0)
#0x3e0c
lw $12 0($0)
#0x3e10
mult $27 $17
#0x3e14
blez $17 loop3
#0x3e18
lb $30 8($0)
#0x3e1c
mthi $16
#0x3e20
sub $3 $14 $5
#0x3e24
add $27 $4 $8
#0x3e28
lw $14 12($0)
#0x3e2c
add $31 $1 $6
#0x3e30
addiu $16 $10 17965
#0x3e34
sb $19 2($0)
#0x3e38
sub $30 $13 $26
#0x3e3c
xor $17 $9 $14
#0x3e40
sra $3 $17 29
#0x3e44
sltiu $5 $9 28580
#0x3e48
lw $5 24($0)
#0x3e4c
lw $26 20($0)
#0x3e50
lw $19 24($0)
loop4:
#0x3e54
sll $26 $12 21
#0x3e58
addiu $4 $13 31698
loop9:
#0x3e5c
lw $8 0($0)
#0x3e60
bgez $20 loop5
#0x3e64
addi $14 $3 -20159
#0x3e68
nor $22 $19 $3
#0x3e6c
mfhi $18
#0x3e70
lhu $15 16($0)
#0x3e74
multu $8 $27
#0x3e78
lh $16 26($0)
#0x3e7c
sllv $4 $10 $21
#0x3e80
sw $31 60($0)
#0x3e84
lhu $15 30($0)
#0x3e88
lbu $16 1($0)
#0x3e8c
or $24 $7 $2
#0x3e90
sltiu $20 $6 2812
#0x3e94
sw $16 60($0)
#0x3e98
xori $6 $16 0x3ca2
#0x3e9c
addiu $17 $4 10507
#0x3ea0
sltiu $19 $22 11363
#0x3ea4
sltiu $8 $5 29308
#0x3ea8
xori $18 $26 0x2b50
#0x3eac
or $31 $1 $16
#0x3eb0
sll $22 $8 13
#0x3eb4
srlv $18 $6 $31
#0x3eb8
bgez $27 loop9
#0x3ebc
xori $17 $18 0x9bb3
#0x3ec0
and $12 $24 $30
#0x3ec4
lb $26 29($0)
#0x3ec8
sb $14 25($0)
#0x3ecc
multu $2 $9
#0x3ed0
mtlo $6
#0x3ed4
and $23 $1 $1
#0x3ed8
srlv $30 $27 $19
#0x3edc
sw $1 28($0)
#0x3ee0
nor $13 $6 $22
#0x3ee4
mthi $9
#0x3ee8
mtlo $3
#0x3eec
lh $7 22($0)
#0x3ef0
lw $5 0($0)
#0x3ef4
addiu $23 $16 28293
#0x3ef8
jal loop8
#0x3efc
slti $22 $3 -8974
#0x3f00
multu $18 $14
#0x3f04
lb $23 4($0)
#0x3f08
sw $17 48($0)
#0x3f0c
mtlo $1
#0x3f10
addu $6 $18 $22
#0x3f14
xori $19 $10 0x0506
#0x3f18
lui $22 0x50ae
#0x3f1c
sltiu $30 $14 7024
#0x3f20
lh $23 4($0)
#0x3f24
subu $21 $3 $3
#0x3f28
subu $30 $16 $31
#0x3f2c
lw $8 20($0)
#0x3f30
sllv $2 $23 $15
#0x3f34
sra $16 $4 17
#0x3f38
lw $18 0($0)
#0x3f3c
slti $26 $26 -10662
#0x3f40
subu $25 $1 $22
#0x3f44
mult $9 $9
#0x3f48
lbu $7 2($0)
#0x3f4c
sll $7 $31 14
#0x3f50
lw $9 12($0)
#0x3f54
mult $15 $3
#0x3f58
slt $15 $27 $13
#0x3f5c
multu $12 $17
#0x3f60
xori $5 $20 0x426d
#0x3f64
subu $4 $25 $24
#0x3f68
subu $9 $15 $23
#0x3f6c
mflo $27
#0x3f70
beq $6 $7 loop4
#0x3f74
xor $3 $19 $22
#0x3f78
sra $31 $3 6
#0x3f7c
add $22 $27 $18
#0x3f80
mfhi $25
#0x3f84
sllv $1 $27 $10
#0x3f88
addiu $23 $13 27744
#0x3f8c
lbu $19 26($0)
#0x3f90
xor $17 $7 $22
#0x3f94
srl $7 $7 6
#0x3f98
li $24 6478
#0x3f9c
div $28 $24
#0x3fa0
and $24 $27 $19
#0x3fa4
mflo $15
#0x3fa8
nor $19 $31 $20
#0x3fac
xori $19 $14 0x5450
#0x3fb0
mtlo $21
#0x3fb4
lh $12 0($0)
#0x3fb8
addi $25 $2 21242
#0x3fbc
bgtz $1 loop0
#0x3fc0
addiu $23 $8 14067
#0x3fc4
mtlo $11
#0x3fc8
subu $10 $3 $7
tail_loop_0:
#0x3fcc
j tail_loop_0
#0x3fd0
nop