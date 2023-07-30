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
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
	li	a0, 10
	sw	a0, 8(sp)
	li	a0, -1
	sw	a0, 4(sp)
	li	a0, 9
	sw	a0, 12(sp)
	lw	a0, 12(sp)
	addi	sp, sp, 16
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
