	.text
	.attribute	4, 16
	.attribute	5, "rv64i2p0"
	.file	"test.ll"
	.globl	deepWhileBr                     # -- Begin function deepWhileBr
	.p2align	2
	.type	deepWhileBr,@function
deepWhileBr:                            # @deepWhileBr
	.cfi_startproc
# %bb.0:                                # %label_entry
	addi	sp, sp, -32
	.cfi_def_cfa_offset 32
	sd	ra, 24(sp)                      # 8-byte Folded Spill
	sd	s0, 16(sp)                      # 8-byte Folded Spill
	.cfi_offset ra, -8
	.cfi_offset s0, -16
	addi	s0, sp, 32
	.cfi_def_cfa s0, 0
	sw	a0, -20(s0)
	sw	a1, -24(s0)
	addw	a0, a0, a1
	sw	a0, -32(s0)
	li	a0, 74
	li	a1, 42
	li	a2, 100
.LBB0_1:                                # %label_0
                                        # =>This Inner Loop Header: Depth=1
	lw	a3, -32(s0)
	blt	a0, a3, .LBB0_6
# %bb.2:                                # %label_1
                                        #   in Loop: Header=BB0_1 Depth=1
	mv	a4, sp
	addi	a3, a4, -16
	mv	sp, a3
	lw	a5, -32(s0)
	sw	a1, -16(a4)
	bge	a5, a2, .LBB0_1
# %bb.3:                                # %label_3
                                        #   in Loop: Header=BB0_1 Depth=1
	lw	a4, -32(s0)
	lw	a5, 0(a3)
	addw	a4, a4, a5
	sw	a4, -32(s0)
	blt	a4, a2, .LBB0_1
# %bb.4:                                # %label_5
                                        #   in Loop: Header=BB0_1 Depth=1
	mv	a5, sp
	addi	a4, a5, -16
	mv	sp, a4
	lw	a3, 0(a3)
	slliw	a3, a3, 1
	sw	a3, -16(a5)
	bnez	zero, .LBB0_1
# %bb.5:                                # %label_7
                                        #   in Loop: Header=BB0_1 Depth=1
	lw	a3, 0(a4)
	slliw	a3, a3, 1
	sw	a3, -32(s0)
	j	.LBB0_1
.LBB0_6:                                # %label_2
	lw	a0, -32(s0)
	sw	a0, -28(s0)
	addi	sp, s0, -32
	ld	ra, 24(sp)                      # 8-byte Folded Reload
	ld	s0, 16(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end0:
	.size	deepWhileBr, .Lfunc_end0-deepWhileBr
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
	li	a0, 2
	sw	a0, 0(sp)
	li	a0, 2
	li	a1, 2
	call	deepWhileBr@plt
	sw	a0, 4(sp)
	lw	a0, 4(sp)
	ld	ra, 8(sp)                       # 8-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
