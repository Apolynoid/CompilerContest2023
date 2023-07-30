
.global func
.type func, @function
func:
func_label_entry:
	addi	sp, sp, -4
	sw	a0, 0(sp)
	addi	sp, sp, -4
	lw	t0, 0(sp)
	addi	t0, t0, -1
	sw	t0, 0(sp)
	lw	t0, 0(sp)
	sw	t0, 0(sp)
	j	func_label_ret
func_label_ret:
	lw	t0, 0(sp)
	mv	a0, t0
	ret


.global main
.type main, @function
main:
main_label_entry:
	addi	sp, sp, -4
	addi	sp, sp, -4
	la	t0, a
	li	t6, 10
	sw	t6, 0(t0)
	la	t0, a
	lw	t1, 0(t0)
	mv	a0, t1
	addi	sp, sp, -24
	sw	t0, 0(sp)
	sw	t1, 4(sp)
	sw	t2, 8(sp)
	sw	t3, 12(sp)
	sw	t4, 16(sp)
	sw	t5, 20(sp)
	call func
	lw	t0, 0(sp)
	lw	t1, 4(sp)
	lw	t2, 8(sp)
	lw	t3, 12(sp)
	lw	t4, 16(sp)
	lw	t5, 20(sp)
	addi	sp, sp, 24
	sw	t1, 0(sp)
	lw	t1, 0(sp)
	sw	t1, 0(sp)
	j	main_label_ret
main_label_ret:
	lw	t1, 0(sp)
	mv	a0, t1
	ret


.data
.global a
a:
  .word 0
  .size a, 4
