
.global FourWhile
.type FourWhile, @function
FourWhile:
FourWhile_start:
	addi	sp, sp, -176
	j	FourWhile_label_entry
FourWhile_label_entry:
	li	t6, 5
	sw	t6, 168(sp)
	li	t6, 6
	sw	t6, 164(sp)
	li	t6, 7
	sw	t6, 160(sp)
	li	t6, 10
	sw	t6, 156(sp)
	j	FourWhile_label_0
FourWhile_label_ret:
	lw	t6, 172(sp)
	sw	t6, 152(sp)
	lw	t6, 152(sp)
	mv	a0, t6
	addi	sp, sp, 176
	ret
FourWhile_label_0:
	lw	t6, 168(sp)
	sw	t6, 148(sp)
	li	t6, 20
	lw	t5, 148(sp)
	blt	t5, t6, FourWhile_label_1
	j	FourWhile_label_2
FourWhile_label_1:
	lw	t6, 168(sp)
	sw	t6, 140(sp)
	lw	t4, 136(sp)
	li	t6, 3
	lw	t5, 140(sp)
	add	t4, t5, t6
	sw	t4, 136(sp)
	lw	t6, 136(sp)
	sw	t6, 168(sp)
	j	FourWhile_label_3
FourWhile_label_2:
	lw	t6, 168(sp)
	sw	t6, 132(sp)
	lw	t6, 164(sp)
	sw	t6, 128(sp)
	lw	t6, 156(sp)
	sw	t6, 124(sp)
	lw	t4, 120(sp)
	lw	t5, 128(sp)
	lw	t6, 124(sp)
	add	t4, t5, t6
	sw	t4, 120(sp)
	lw	t4, 116(sp)
	lw	t5, 132(sp)
	lw	t6, 120(sp)
	add	t4, t5, t6
	sw	t4, 116(sp)
	lw	t6, 160(sp)
	sw	t6, 112(sp)
	lw	t4, 108(sp)
	lw	t5, 116(sp)
	lw	t6, 112(sp)
	add	t4, t5, t6
	sw	t4, 108(sp)
	lw	t6, 108(sp)
	sw	t6, 172(sp)
	j	FourWhile_label_ret
FourWhile_label_3:
	lw	t6, 164(sp)
	sw	t6, 104(sp)
	li	t6, 10
	lw	t5, 104(sp)
	blt	t5, t6, FourWhile_label_4
	j	FourWhile_label_5
FourWhile_label_4:
	lw	t6, 164(sp)
	sw	t6, 96(sp)
	lw	t4, 92(sp)
	li	t6, 1
	lw	t5, 96(sp)
	add	t4, t5, t6
	sw	t4, 92(sp)
	lw	t6, 92(sp)
	sw	t6, 164(sp)
	j	FourWhile_label_6
FourWhile_label_5:
	lw	t6, 164(sp)
	sw	t6, 88(sp)
	lw	t4, 84(sp)
	lw	t5, 88(sp)
	addi	t4, t5, -2
	sw	t4, 84(sp)
	lw	t6, 84(sp)
	sw	t6, 164(sp)
	j	FourWhile_label_0
FourWhile_label_6:
	lw	t6, 160(sp)
	sw	t6, 80(sp)
	li	t6, 7
	lw	t5, 80(sp)
	beq	t5, t6, FourWhile_label_7
	j	FourWhile_label_8
FourWhile_label_7:
	lw	t6, 160(sp)
	sw	t6, 72(sp)
	lw	t4, 68(sp)
	lw	t5, 72(sp)
	addi	t4, t5, -1
	sw	t4, 68(sp)
	lw	t6, 68(sp)
	sw	t6, 160(sp)
	j	FourWhile_label_9
FourWhile_label_8:
	lw	t6, 160(sp)
	sw	t6, 64(sp)
	lw	t4, 60(sp)
	li	t6, 1
	lw	t5, 64(sp)
	add	t4, t5, t6
	sw	t4, 60(sp)
	lw	t6, 60(sp)
	sw	t6, 160(sp)
	j	FourWhile_label_3
FourWhile_label_9:
	lw	t6, 156(sp)
	sw	t6, 56(sp)
	li	t6, 20
	lw	t5, 56(sp)
	blt	t5, t6, FourWhile_label_10
	j	FourWhile_label_11
FourWhile_label_10:
	lw	t6, 156(sp)
	sw	t6, 48(sp)
	lw	t4, 44(sp)
	li	t6, 3
	lw	t5, 48(sp)
	add	t4, t5, t6
	sw	t4, 44(sp)
	lw	t6, 44(sp)
	sw	t6, 156(sp)
	j	FourWhile_label_9
FourWhile_label_11:
	lw	t6, 156(sp)
	sw	t6, 40(sp)
	lw	t4, 36(sp)
	lw	t5, 40(sp)
	addi	t4, t5, -1
	sw	t4, 36(sp)
	lw	t6, 36(sp)
	sw	t6, 156(sp)
	j	FourWhile_label_6


.global main
.type main, @function
main:
main_start:
	addi	sp, sp, -48
	j	main_label_entry
main_label_entry:
	sw	t0, 0(sp)
	sw	t1, 4(sp)
	sw	t2, 8(sp)
	sw	t3, 12(sp)
	call FourWhile
	lw	t0, 0(sp)
	lw	t1, 4(sp)
	lw	t2, 8(sp)
	lw	t3, 12(sp)
	addi	sp, sp, 32
	mv	t0, a0
	sw	t0, 12(sp)
	j	main_label_ret
main_label_ret:
	lw	t1, 12(sp)
	mv	a0, t1
	addi	sp, sp, 16
	ret

