	.text
	.attribute	4, 16
	.attribute	5, "rv64i2p0"
	.file	"test.ll"
	.globl	func                            # -- Begin function func
	.p2align	2
	.type	func,@function
func:                                   # @func
	.cfi_startproc
# %bb.0:                                # %label_entry
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
                                        # kill: def $x11 killed $x10
	addiw	a0, a0, -1
	sw	a0, 12(sp)
	sw	a0, 8(sp)
	j	.LBB0_1
.LBB0_1:                                # %label_ret
	lw	a0, 8(sp)
	addi	sp, sp, 16
	ret
.Lfunc_end0:
	.size	func, .Lfunc_end0-func
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %label_entry
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
	sd	ra, 8(sp)                       # 8-byte Folded Spill
	.cfi_offset ra, -8
	lui	a1, %hi(a)
	li	a0, 10
	sw	a0, %lo(a)(a1)
	call	func@plt
	sw	a0, 0(sp)
	sw	a0, 4(sp)
	j	.LBB1_1
.LBB1_1:                                # %label_ret
	lw	a0, 4(sp)
	ld	ra, 8(sp)                       # 8-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	a,@object                       # @a
	.section	.sbss,"aw",@nobits
	.globl	a
	.p2align	2
a:
	.word	0                               # 0x0
	.size	a, 4

	.section	".note.GNU-stack","",@progbits
