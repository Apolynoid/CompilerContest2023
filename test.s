
.global ififElse
.type ififElse, @function
ififElse:
ififElse_label_entry:
	addi	sp, sp, -4
	addi	sp, sp, -4
	li	t6, 5
	sw	t6, 0(sp)
	addi	sp, sp, -4
	li	t6, 10
	sw	t6, 0(sp)
	lw	t0, 4(sp)
	li	t6, 5
	beq	zero, t6, ififElse_label_1
	j	ififElse_label_0
ififElse_label_ret:
	lw	t1, 8(sp)
	mv	a0, t1
	ret
ififElse_label_0:
	lw	t2, -12(sp)
	li	t6, 10
	beq	zero, t6, ififElse_label_3
	j	ififElse_label_2
ififElse_label_1:
	lw	t3, -8(sp)
	sw	t3, -4(sp)
	j	ififElse_label_ret
ififElse_label_2:
	li	t6, 25
	sw	t6, -8(sp)
	j	ififElse_label_4
ififElse_label_3:
	lw	t4, -8(sp)
	li	t6, 15
	add	t5, t4, t6
	sw	t5, -8(sp)
	j	ififElse_label_4
ififElse_label_4:
	j	ififElse_label_1


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
	call ififElse
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

