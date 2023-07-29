
.global main
.type main, @function
main:
main_label_entry:
	addi	sp, sp, -4
	mv	a0, t0
	mv	a1, t1
	call __aeabi_memclr4
	mv	t1, a0
	mv	a0, t2
	mv	a1, t1
	call __aeabi_memclr4
	mv	t1, a0
	mv	a0, t3
	mv	a1, t1
	call __aeabi_memclr4
	mv	t1, a0
	mv	a0, t4
	mv	a1, t1
	call __aeabi_memclr4
	mv	t1, a0
	mv	a0, t5
	mv	a1, t1
	call __aeabi_memclr4
	mv	t1, a0
	addi	sp, sp, -4
	sw	s0, 0(sp)
	addi	sp, sp, -4
	sw	s0, 0(sp)
	addi	sp, sp, -4
	sw	s1, 0(sp)
	addi	sp, sp, -4
	sw	s1, 0(sp)
	addi	sp, sp, -4
	sw	s2, 0(sp)
	addi	sp, sp, -4
	sw	s3, 0(sp)
	addi	sp, sp, -4
	sw	s4, 0(sp)
	addi	sp, sp, -4
	sw	s2, 0(sp)
	addi	sp, sp, -4
	sw	s3, 0(sp)
	add	s4, s2, s3
	addi	sp, sp, -4
	sw	s5, 0(sp)
	addi	sp, sp, -4
	sw	s6, 0(sp)
	addi	sp, sp, -4
	sw	s4, 0(sp)
	addi	sp, sp, -4
	sw	s5, 0(sp)
	add	s6, s4, s5
	addi	sp, sp, -4
	sw	s7, 0(sp)
	addi	sp, sp, -4
	sw	s8, 0(sp)
	addi	sp, sp, -4
	sw	s6, 0(sp)
	addi	sp, sp, -4
	sw	s7, 0(sp)
	add	s8, s6, s7
	addi	sp, sp, -4
	sw	s8, 0(sp)
	sw	s8, 72(sp)
	j	main_label_ret
main_label_ret:
	addi	sp, sp, -4
	sw	s9, 0(sp)
	lw	s9, 76(sp)
	addi	sp, sp, -4
	sw	s9, 0(sp)
	lw	s9, 0(sp)
	lw	s8, 8(sp)
	lw	s7, 12(sp)
	lw	s4, 32(sp)
	lw	s3, 44(sp)
	lw	s2, 48(sp)
	lw	s6, 16(sp)
	lw	s1, 64(sp)
	lw	s5, 28(sp)
	lw	s0, 72(sp)
	mv	a0, s9
	ret

  .global __aeabi_memcpy4
  .type __aeabi_memcpy4, @function
__aeabi_memcpy4:
__aeabi_memcpy4_loop:
  lw a3, 0(a1)
  sw a3, 0(a0)
  addi a0, a0, 4
  addi a1, a1, 4
  addi a2, a2, -4
  bnez a3, __aeabi_memcpy4_loop
  ret

  .global __aeabi_memclr4
  .type __aeabi_memclr4, @function
__aeabi_memclr4:
__aeabi_memclr4_loop:
  sw zero, 0(a0)
  addi a0, a0, 4
  addi a1, a1, -1
  bnez a1, __aeabi_memclr4_loop
  ret

  .global __aeabi_memset4
  .type __aeabi_memset4, @function
__aeabi_memset4:
__aeabi_memset4_loop:
  sw a1, 0(a0)
  addi a0, a0, 4
  addi a2, a2, -4
  bnez a2, __aeabi_memset4_loop
  ret

