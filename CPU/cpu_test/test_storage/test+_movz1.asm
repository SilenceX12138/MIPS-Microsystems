#initial
.text
ori $s0 $0 1928
ori $s1 $0 5
ori $s2 $0 65535
ori $s3 $0 8
lui $s5 0xABCD
ori $s6 $t0 0xffff
#initial done
subu $t0 $s0 $s1
addu $t1 $s0 $t0
addu $t2 $s0 $t0
addu $t3 $s0 $t0
sw $t3 0($0)
sw $t2 4($0)
sw $t1 8($0)
subu $t0 $s0 $s2
addu $t1 $t0 $s0
addu $t2 $t0 $s0
subu $t3 $t0 $s0
sw $t1 12($0)
sw $t3 16($0)
sw $t2 20($0)
subu $t0 $s0 $s3
ori $t1 $t0 36
ori $t2 $t0 21
ori $t3 $t0 4
sw $t3 24($0)
sw $t2 28($0)
sw $t1 32($0)
addi $t0 $s1 100
addu $t0 $0 $s3
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 36($0)
sw $t2 40($0)
sw $t1 44($0)
addi $t0 $s1 100
ori $t0 $0 0
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 48($0)
sw $t2 52($0)
sw $t1 56($0)
ori $t0 $s1 178
addu $t1 $s0 $t0
subu $t2 $s0 $t0
addu $t3 $s0 $t0
sw $t3 60($0)
sw $t2 64($0)
sw $t1 68($0)
ori $t0 $s1 971
subu $t1 $t0 $s0
addu $t2 $t0 $s0
subu $t3 $t0 $s0
sw $t1 72($0)
sw $t3 76($0)
sw $t2 80($0)
ori $t0 $s1 6
ori $t1 $t0 9
ori $t2 $t0 6
ori $t3 $t0 2
sw $t2 84($0)
sw $t1 88($0)
sw $t3 92($0)
lw $t0 44($0)
subu $t1 $s0 $t0
subu $t2 $s0 $t0
addu $t3 $s0 $t0
sw $t3 96($0)
sw $t2 100($0)
sw $t1 104($0)
lw $t0 16($0)
addu $t1 $t0 $s0
subu $t2 $t0 $s0
subu $t3 $t0 $s0
sw $t1 108($0)
sw $t3 112($0)
sw $t2 116($0)
lw $t0 84($0)
ori $t1 $t0 100
ori $t2 $t0 100
ori $t3 $t0 100
sw $t3 120($0)
sw $t2 124($0)
sw $t1 128($0)
addi $t0 $0 4
sw $t0 132($0)
lw $t0 132($0)
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 132($0)
sw $t2 136($0)
sw $t1 140($0)
subu $t0 $s0 $s1
addu $t1 $s0 $t0
addu $t2 $s0 $t0
addu $t3 $s0 $t0
sw $t3 144($0)
sw $t2 148($0)
sw $t1 152($0)
subu $t0 $s0 $s1
addu $t1 $t0 $s0
subu $t2 $t0 $s0
subu $t3 $t0 $s0
sw $t1 156($0)
sw $t3 160($0)
sw $t2 164($0)
addu $t0 $s0 $s1
ori $t1 $t0 21
ori $t2 $t0 81
ori $t3 $t0 0
sw $t3 168($0)
sw $t2 172($0)
sw $t1 176($0)
addi $t0 $s1 100
addu $t0 $0 $0
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 180($0)
sw $t2 184($0)
sw $t1 188($0)
addi $t0 $s1 100
ori $t0 $0 0
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 192($0)
sw $t2 196($0)
sw $t1 200($0)
ori $t0 $s1 357
subu $t1 $s0 $t0
addu $t2 $s0 $t0
addu $t3 $s0 $t0
sw $t3 204($0)
sw $t2 208($0)
sw $t1 212($0)
ori $t0 $s1 316
subu $t1 $t0 $s0
subu $t2 $t0 $s0
addu $t3 $t0 $s0
sw $t1 216($0)
sw $t3 220($0)
sw $t2 224($0)
ori $t0 $s1 4
ori $t1 $t0 9
ori $t2 $t0 7
ori $t3 $t0 2
sw $t2 228($0)
sw $t1 232($0)
sw $t3 236($0)
lw $t0 52($0)
addu $t1 $s0 $t0
addu $t2 $s0 $t0
subu $t3 $s0 $t0
sw $t3 240($0)
sw $t2 244($0)
sw $t1 248($0)
lw $t0 240($0)
addu $t1 $t0 $s0
subu $t2 $t0 $s0
addu $t3 $t0 $s0
sw $t1 252($0)
sw $t3 256($0)
sw $t2 260($0)
lw $t0 180($0)
ori $t1 $t0 100
ori $t2 $t0 100
ori $t3 $t0 100
sw $t3 264($0)
sw $t2 268($0)
sw $t1 272($0)
addi $t0 $0 4
sw $t0 276($0)
lw $t0 276($0)
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 276($0)
sw $t2 280($0)
sw $t1 284($0)
addu $t0 $s0 $s1
addu $t1 $s0 $t0
subu $t2 $s0 $t0
subu $t3 $s0 $t0
sw $t3 288($0)
sw $t2 292($0)
sw $t1 296($0)
subu $t0 $s0 $s1
subu $t1 $t0 $s0
addu $t2 $t0 $s0
addu $t3 $t0 $s0
sw $t1 300($0)
sw $t3 304($0)
sw $t2 308($0)
addu $t0 $s0 $s1
ori $t1 $t0 10
ori $t2 $t0 83
ori $t3 $t0 39
sw $t3 312($0)
sw $t2 316($0)
sw $t1 320($0)
addi $t0 $s1 100
addu $t0 $0 $0
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 324($0)
sw $t2 328($0)
sw $t1 332($0)
addi $t0 $s1 100
ori $t0 $0 0
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 336($0)
sw $t2 340($0)
sw $t1 344($0)
ori $t0 $s1 831
addu $t1 $s0 $t0
addu $t2 $s0 $t0
subu $t3 $s0 $t0
sw $t3 348($0)
sw $t2 352($0)
sw $t1 356($0)
ori $t0 $s1 947
subu $t1 $t0 $s0
addu $t2 $t0 $s0
subu $t3 $t0 $s0
sw $t1 360($0)
sw $t3 364($0)
sw $t2 368($0)
ori $t0 $s1 7
ori $t1 $t0 9
ori $t2 $t0 0
ori $t3 $t0 0
sw $t2 372($0)
sw $t1 376($0)
sw $t3 380($0)
lw $t0 136($0)
subu $t1 $s0 $t0
addu $t2 $s0 $t0
addu $t3 $s0 $t0
sw $t3 384($0)
sw $t2 388($0)
sw $t1 392($0)
lw $t0 344($0)
addu $t1 $t0 $s0
addu $t2 $t0 $s0
addu $t3 $t0 $s0
sw $t1 396($0)
sw $t3 400($0)
sw $t2 404($0)
lw $t0 92($0)
ori $t1 $t0 100
ori $t2 $t0 100
ori $t3 $t0 100
sw $t3 408($0)
sw $t2 412($0)
sw $t1 416($0)
addi $t0 $0 4
sw $t0 420($0)
lw $t0 420($0)
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 420($0)
sw $t2 424($0)
sw $t1 428($0)
subu $t0 $s0 $s1
addu $t1 $s0 $t0
subu $t2 $s0 $t0
addu $t3 $s0 $t0
sw $t3 432($0)
sw $t2 436($0)
sw $t1 440($0)
addu $t0 $s0 $s1
addu $t1 $t0 $s0
subu $t2 $t0 $s0
addu $t3 $t0 $s0
sw $t1 444($0)
sw $t3 448($0)
sw $t2 452($0)
subu $t0 $s0 $s1
ori $t1 $t0 3
ori $t2 $t0 79
ori $t3 $t0 51
sw $t3 456($0)
sw $t2 460($0)
sw $t1 464($0)
addi $t0 $s1 100
addu $t0 $0 $0
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 468($0)
sw $t2 472($0)
sw $t1 476($0)
addi $t0 $s1 100
ori $t0 $0 0
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 480($0)
sw $t2 484($0)
sw $t1 488($0)
ori $t0 $s1 148
addu $t1 $s0 $t0
subu $t2 $s0 $t0
subu $t3 $s0 $t0
sw $t3 492($0)
sw $t2 496($0)
sw $t1 500($0)
ori $t0 $s1 205
subu $t1 $t0 $s0
subu $t2 $t0 $s0
subu $t3 $t0 $s0
sw $t1 504($0)
sw $t3 508($0)
sw $t2 512($0)
ori $t0 $s1 3
ori $t1 $t0 4
ori $t2 $t0 3
ori $t3 $t0 3
sw $t2 516($0)
sw $t1 520($0)
sw $t3 524($0)
lw $t0 48($0)
addu $t1 $s0 $t0
subu $t2 $s0 $t0
addu $t3 $s0 $t0
sw $t3 528($0)
sw $t2 532($0)
sw $t1 536($0)
lw $t0 312($0)
subu $t1 $t0 $s0
addu $t2 $t0 $s0
addu $t3 $t0 $s0
sw $t1 540($0)
sw $t3 544($0)
sw $t2 548($0)
lw $t0 532($0)
ori $t1 $t0 100
ori $t2 $t0 100
ori $t3 $t0 100
sw $t3 552($0)
sw $t2 556($0)
sw $t1 560($0)
addi $t0 $0 4
sw $t0 564($0)
lw $t0 564($0)
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 564($0)
sw $t2 568($0)
sw $t1 572($0)
addu $t0 $s0 $s1
subu $t1 $s0 $t0
subu $t2 $s0 $t0
subu $t3 $s0 $t0
sw $t3 576($0)
sw $t2 580($0)
sw $t1 584($0)
subu $t0 $s0 $s1
subu $t1 $t0 $s0
addu $t2 $t0 $s0
subu $t3 $t0 $s0
sw $t1 588($0)
sw $t3 592($0)
sw $t2 596($0)
subu $t0 $s0 $s1
ori $t1 $t0 82
ori $t2 $t0 43
ori $t3 $t0 98
sw $t3 600($0)
sw $t2 604($0)
sw $t1 608($0)
addi $t0 $s1 100
addu $t0 $0 $0
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 612($0)
sw $t2 616($0)
sw $t1 620($0)
addi $t0 $s1 100
ori $t0 $0 0
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 624($0)
sw $t2 628($0)
sw $t1 632($0)
ori $t0 $s1 739
addu $t1 $s0 $t0
subu $t2 $s0 $t0
addu $t3 $s0 $t0
sw $t3 636($0)
sw $t2 640($0)
sw $t1 644($0)
ori $t0 $s1 904
subu $t1 $t0 $s0
addu $t2 $t0 $s0
addu $t3 $t0 $s0
sw $t1 648($0)
sw $t3 652($0)
sw $t2 656($0)
ori $t0 $s1 1
ori $t1 $t0 0
ori $t2 $t0 9
ori $t3 $t0 9
sw $t2 660($0)
sw $t1 664($0)
sw $t3 668($0)
lw $t0 624($0)
addu $t1 $s0 $t0
subu $t2 $s0 $t0
subu $t3 $s0 $t0
sw $t3 672($0)
sw $t2 676($0)
sw $t1 680($0)
lw $t0 412($0)
subu $t1 $t0 $s0
subu $t2 $t0 $s0
addu $t3 $t0 $s0
sw $t1 684($0)
sw $t3 688($0)
sw $t2 692($0)
lw $t0 404($0)
ori $t1 $t0 100
ori $t2 $t0 100
ori $t3 $t0 100
sw $t3 696($0)
sw $t2 700($0)
sw $t1 704($0)
addi $t0 $0 4
sw $t0 708($0)
lw $t0 708($0)
lw $t1 0($t0)
lw $t2 4($t0)
lw $t3 8($t0)
sw $t3 708($0)
sw $t2 712($0)
sw $t1 716($0)
lui $t0 224
subu $t1 $s0 $t0
subu $t2 $s0 $t0
addu $t3 $s0 $t0
sw $t3 720($0)
sw $t2 724($0)
sw $t1 728($0)
lui $t0 469
subu $t1 $t0 $s0
addu $t2 $t0 $s0
addu $t3 $t0 $s0
sw $t1 732($0)
sw $t3 736($0)
sw $t2 740($0)
lui $t0 121
ori $t1 $t0 55
ori $t2 $t0 42
ori $t3 $t0 24
sw $t1 744($0)
sw $t3 748($0)
sw $t2 752($0)
lui $t0 686
sw $t0 756($0)
sw $t0 760($0)
sw $t0 764($0)
#movz
addu $t0 $s0 $s1
movz $t2 $t1 $t0
movz $t3 $t1 $t0
movz $t4 $t1 $t0
addu $t4 $t4 $s0
addu $t3 $t3 $s0
addu $t2 $t2 $s0
sw $t4 768($0)
sw $t3 772($0)
sw $t2 776($0)
addu $t0 $0 $0
movz $t2 $t1 $t0
movz $t3 $t1 $t0
movz $t4 $t1 $t0
addu $t3 $t3 $s0
addu $t2 $t2 $s0
addu $t4 $t4 $s0
sw $t3 780($0)
sw $t2 784($0)
sw $t4 788($0)

subu $t0 $s0 $s1
movz $t2 $t0 $t0
movz $t3 $t0 $t0
movz $t4 $t0 $t0
subu $t4 $t4 $s0
subu $t3 $t3 $s0
subu $t2 $t2 $s0
sw $t4 792($0)
sw $t3 796($0)
sw $t2 800($0)
subu $t0 $0 $0
movz $t2 $t0 $0
movz $t3 $t0 $0
movz $t4 $t0 $0
subu $t3 $t3 $s0
subu $t2 $t2 $s0
subu $t4 $t4 $s0
sw $t3 804($0)
sw $t2 808($0)
sw $t4 812($0)

ori $t0 $s0 100
movz $t2 $t0 $t0
movz $t3 $t0 $t0
movz $t4 $t0 $t0
ori $t4 $t4 17
ori $t3 $t3 10
ori $t2 $t2 123
sw $t4 816($0)
sw $t3 820($0)
sw $t2 824($0)
ori $t0 $0 0
movz $t2 $t0 $0
movz $t3 $t0 $0
movz $t4 $t0 $0
ori $t3 $t3 12
ori $t2 $t2 13
ori $t4 $t4 14
sw $t3 828($0)
sw $t2 832($0)
sw $t4 836($0)

lui $t0 111
movz $t2 $t0 $0
movz $t3 $t0 $0
movz $t4 $t0 $0
sw $t4 840($0)
sw $t3 844($0)
sw $t2 848($0)
lui $t0 0 
movz $t2 $s0 $t0
movz $t3 $s1 $t0
movz $t4 $s2 $t0
sw $t3 852($0)
sw $t2 856($0)
sw $t4 860($0)

lw $t0 4($0)
movz $t2 $t0 $0
movz $t3 $t0 $0
movz $t4 $t0 $0
sw $t3 864($0)
sw $t2 868($0)
sw $t4 872($0)

sw $0 876($0)
lw $t0 876($0)
movz $t2 $s1 $t0
movz $t3 $t2 $t0
movz $t4 $t3 $t0
sw $t3 876($0)
sw $t2 880($0)
sw $t4 884($0)

sw $0 876($0)
lw $t0 876($0)
movz $t2 $s3 $t0
lw $t3 0($t2)
lw $t4 4($t2)
lw $t2 8($t2)
sw $t3 888($0)
sw $t2 892($0)
sw $t4 896($0)






end: beq $0, $0, end
	nop


