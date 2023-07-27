.global func
.type func, @function
func:
func_label_entry:
	addi	sp, sp, -4
	sw	a0, 0(sp)
	addi	sp, sp, -4
	lw	t0, 4(sp)
	addi	t1, t0, -1
	sw	t1, 4(sp)
	lw	t2, 4(sp)
	sw	t2, 0(sp)
	j	func_label_ret
func_label_ret:
	lw	t3, 0(sp)
	mv	a0, t3
	ret


.global main
.type main, @function
main:
main_label_entry:
	addi	sp, sp, -4
	addi	sp, sp, -4
	la	t1, a
	li	t0, 10
	sw	t0, 0(t1)
	lw	t0, 0(t1)
	mv	a0, t0
	call func
	mv	t1, a0
	sw	t1, 0(sp)
	lw	t2, 0(sp)
	sw	t2, 4(sp)
	j	main_label_ret
main_label_ret:
	lw	t3, 4(sp)
	mv	a0, t3
	ret


.data
.global a
a:
  .word 0
  .size a, 4
