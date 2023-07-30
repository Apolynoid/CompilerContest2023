
.global FourWhile
.type FourWhile, @function
FourWhile:
FourWhile_label_entry:
	addi	sp, sp, -4
	addi	sp, sp, -4
	li	t6, 5
	sw	t6, 0(sp)
	addi	sp, sp, -4
	addi	sp, sp, -4
	li	t6, 6
	sw	t6, 4(sp)
	li	t6, 7
	sw	t6, 0(sp)
	addi	sp, sp, -4
	li	t6, 10
	sw	t6, 0(sp)
	j	FourWhile_label_0
FourWhile_label_ret:
	lw	t0, 16(sp)
	mv	a0, t0
	ret
FourWhile_label_0:
	lw	t1, 12(sp)
	li	t6, 20
	blt	t1, t6, FourWhile_label_1
	j	FourWhile_label_2
FourWhile_label_1:
	lw	t2, 12(sp)
	li	t6, 3
	add	t3, t2, t6
	sw	t3, 12(sp)
	j	FourWhile_label_3
FourWhile_label_2:
	lw	t4, 12(sp)
	lw	t5, 8(sp)
	addi	sp, sp, -4
	sw	s0, 0(sp)
	lw	s0, 4(sp)
	addi	sp, sp, -4
	sw	s1, 0(sp)
	addi	sp, sp, -4
	sw	s0, 0(sp)
	add	s1, t5, s0
	addi	sp, sp, -4
	sw	s2, 0(sp)
	addi	sp, sp, -4
	sw	s1, 0(sp)
	add	s2, t4, s1
	addi	sp, sp, -4
	sw	s3, 0(sp)
	lw	s3, 28(sp)
	addi	sp, sp, -4
	sw	s4, 0(sp)
	addi	sp, sp, -4
	sw	s2, 0(sp)
	addi	sp, sp, -4
	sw	s3, 0(sp)
	add	s4, s2, s3
	addi	sp, sp, -4
	sw	s4, 0(sp)
	sw	s4, 56(sp)
	j	FourWhile_label_ret
FourWhile_label_3:
	addi	sp, sp, -4
	sw	s5, 0(sp)
	lw	s5, 52(sp)
	li	t6, 10
	addi	sp, sp, -4
	sw	s5, 0(sp)
	blt	s5, t6, FourWhile_label_4
	j	FourWhile_label_5
FourWhile_label_4:
	addi	sp, sp, -4
	sw	s6, 0(sp)
	lw	s6, 60(sp)
	addi	sp, sp, -4
	sw	s7, 0(sp)
	li	t6, 1
	addi	sp, sp, -4
	sw	s6, 0(sp)
	add	s7, s6, t6
	addi	sp, sp, -4
	sw	s7, 0(sp)
	sw	s7, 72(sp)
	j	FourWhile_label_6
FourWhile_label_5:
	addi	sp, sp, -4
	sw	s8, 0(sp)
	lw	s8, 76(sp)
	addi	sp, sp, -4
	sw	s9, 0(sp)
	addi	sp, sp, -4
	sw	s8, 0(sp)
	addi	s9, s8, -2
	addi	sp, sp, -4
	sw	s9, 0(sp)
	sw	s9, 88(sp)
	j	FourWhile_label_0
FourWhile_label_6:
	addi	sp, sp, -4
	sw	s10, 0(sp)
	lw	s10, 88(sp)
	li	t6, 7
	addi	sp, sp, -4
	sw	s10, 0(sp)
	beq	s10, t6, FourWhile_label_7
	j	FourWhile_label_8
FourWhile_label_7:
	addi	sp, sp, -4
	sw	s11, 0(sp)
	lw	s11, 96(sp)
	addi	sp, sp, -4
	sw	s11, 0(sp)
	addi	zero, s11, -1
	sw	zero, 100(sp)
	j	FourWhile_label_9
FourWhile_label_8:
	lw	zero, 100(sp)
	li	t6, 1
	add	zero, zero, t6
	sw	zero, 100(sp)
	j	FourWhile_label_3
FourWhile_label_9:
	lw	zero, 96(sp)
	li	t6, 20
	blt	zero, t6, FourWhile_label_10
	j	FourWhile_label_11
FourWhile_label_10:
	lw	zero, 96(sp)
	li	t6, 3
	add	zero, zero, t6
	sw	zero, 96(sp)
	j	FourWhile_label_9
FourWhile_label_11:
	lw	zero, 96(sp)
	addi	zero, zero, -1
	sw	zero, 96(sp)
	j	FourWhile_label_6


.global main
.type main, @function
main:
main_label_entry:
	addi	sp, sp, -4
	addi	sp, sp, -24
	sw	t0, 0(sp)
	sw	t1, 4(sp)
	sw	t2, 8(sp)
	sw	t3, 12(sp)
	sw	t4, 16(sp)
	sw	t5, 20(sp)
	call FourWhile
	lw	t0, 0(sp)
	lw	t1, 4(sp)
	lw	t2, 8(sp)
	lw	t3, 12(sp)
	lw	t4, 16(sp)
	lw	t5, 20(sp)
	addi	sp, sp, 24
	mv	t0, a0
	sw	t0, 0(sp)
	j	main_label_ret
main_label_ret:
	lw	t1, 0(sp)
	mv	a0, t1
	ret

