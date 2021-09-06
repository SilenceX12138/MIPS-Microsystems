#initial
lui $1,0x2819
ori $1,$1,0x9384
lui $2,0x7cfd
ori $2,$2,0x5738
lui $3,0x883c
ori $3,$3,0x8847
lui $4,0x9382
ori $4,$4,0xacfe
sw $1,0($0)
sw $2,4($0)
sw $3,8($0)
sw $4,12($0)
#lh
jal l4
lh $1,-0x3038($31)
lh $2,-0x3036($31)
lh $3,-0x3034($31)
l4:
jal l5
ori $1,$0,29
addi $1,$1,1
l5:
lh $4,-0x3042($31)
lh $5,-0x3040($31)
lh $6,-0x303e($31)
jal l6
ori $1,$0,3
or $1,$1,$4
l6:
andi $1,$1,29
lh $7,-0x3054($31)
lh $8,-0x3052($31)
lh $9,-0x305c($31)
#lhu
jal l1
lhu $1,-0x307c($31)
lhu $2,-0x307a($31)
lhu $3,-0x3070($31)
l1:
jal l2
ori $1,$0,29
addi $1,$1,1
l2:
lhu $4,-0x3088($31)
lhu $5,-0x3086($31)
lhu $6,-0x3084($31)
jal l3
ori $1,$0,3
or $1,$1,$4
l3:
andi $1,$1,29
lhu $7,-0x3098($31)
lhu $8,-0x3096($31)
lhu $9,-0x309a($31)
#lb
ori $2,$0,0x30c8
jalr $1,$2
lb $3,-0x30c3($1)
ori $4,$0,7
ori $2,$0,0
lb $4,-0x30c2($1)
lb $5,-0x30c1($1)
lb $6,-0x30be($1)
#lbu
ori $2,$0,0x30e8
jalr $1,$2
lbu $3,-0x30e3($1)
ori $4,$0,7
ori $2,$0,0
lbu $4,-0x30e2($1)
lbu $5,-0x30e1($1)
lbu $6,-0x30de($1)
