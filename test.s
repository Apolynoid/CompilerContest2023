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
	sw	zero, 12(sp)
	lw	a0, 12(sp)
	addi	sp, sp, 16
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	a,@object                       # @a
	.bss
	.globl	a
	.p2align	4
a:
	.zero	400
	.size	a, 400

	.section	".note.GNU-stack","",@progbits
