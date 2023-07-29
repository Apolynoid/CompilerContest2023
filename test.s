	.text
	.attribute	4, 16
	.attribute	5, "rv64i2p0"
	.file	"test.ll"
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %label_entry
	addi	sp, sp, -240
	.cfi_def_cfa_offset 240
	sd	ra, 232(sp)                     # 8-byte Folded Spill
	sd	s0, 224(sp)                     # 8-byte Folded Spill
	sd	s1, 216(sp)                     # 8-byte Folded Spill
	sd	s2, 208(sp)                     # 8-byte Folded Spill
	sd	s3, 200(sp)                     # 8-byte Folded Spill
	sd	s4, 192(sp)                     # 8-byte Folded Spill
	sd	s5, 184(sp)                     # 8-byte Folded Spill
	sd	s6, 176(sp)                     # 8-byte Folded Spill
	sd	s7, 168(sp)                     # 8-byte Folded Spill
	.cfi_offset ra, -8
	.cfi_offset s0, -16
	.cfi_offset s1, -24
	.cfi_offset s2, -32
	.cfi_offset s3, -40
	.cfi_offset s4, -48
	.cfi_offset s5, -56
	.cfi_offset s6, -64
	.cfi_offset s7, -72
	addi	a0, sp, 132
	li	a1, 32
	call	__aeabi_memclr4@plt
	addi	a0, sp, 100
	li	a1, 32
	call	__aeabi_memclr4@plt
	li	s0, 1
	sw	s0, 100(sp)
	li	s1, 2
	sw	s1, 104(sp)
	li	s2, 3
	sw	s2, 108(sp)
	li	s3, 4
	sw	s3, 112(sp)
	li	s4, 5
	sw	s4, 116(sp)
	li	s5, 6
	sw	s5, 120(sp)
	li	s6, 7
	sw	s6, 124(sp)
	li	s7, 8
	sw	s7, 128(sp)
	addi	a0, sp, 68
	li	a1, 32
	call	__aeabi_memclr4@plt
	sw	s0, 68(sp)
	sw	s1, 72(sp)
	sw	s2, 76(sp)
	sw	s3, 80(sp)
	sw	s4, 84(sp)
	sw	s5, 88(sp)
	sw	s6, 92(sp)
	sw	s7, 96(sp)
	addi	a0, sp, 36
	li	a1, 32
	call	__aeabi_memclr4@plt
	sw	s0, 36(sp)
	sw	s1, 40(sp)
	sw	s2, 44(sp)
	sw	s4, 52(sp)
	sw	s6, 60(sp)
	sw	s7, 64(sp)
	addi	a0, sp, 4
	li	a1, 32
	call	__aeabi_memclr4@plt
	lw	a0, 56(sp)
	lw	a1, 88(sp)
	sw	a0, 4(sp)
	sw	a1, 8(sp)
	sw	s2, 12(sp)
	sw	s3, 16(sp)
	sw	s4, 20(sp)
	sw	s5, 24(sp)
	lw	a2, 148(sp)
	sw	s6, 28(sp)
	sw	s7, 32(sp)
	addw	a0, a0, a1
	addw	a0, a0, a2
	addiw	a0, a0, 8
	sw	a0, 164(sp)
	ld	ra, 232(sp)                     # 8-byte Folded Reload
	ld	s0, 224(sp)                     # 8-byte Folded Reload
	ld	s1, 216(sp)                     # 8-byte Folded Reload
	ld	s2, 208(sp)                     # 8-byte Folded Reload
	ld	s3, 200(sp)                     # 8-byte Folded Reload
	ld	s4, 192(sp)                     # 8-byte Folded Reload
	ld	s5, 184(sp)                     # 8-byte Folded Reload
	ld	s6, 176(sp)                     # 8-byte Folded Reload
	ld	s7, 168(sp)                     # 8-byte Folded Reload
	addi	sp, sp, 240
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
