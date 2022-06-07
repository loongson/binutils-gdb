	.file	1 "a.c"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
.LFB0 = .
	.cfi_startproc
	addi.d	$r3,$r3,-16
	.cfi_rel_offset $r11, 0
	.cfi_def_cfa_offset 16
	st.d	$r22,$r3,8
	.cfi_offset 22, -8
	addi.d	$r22,$r3,16
	.cfi_def_cfa 22, 0
	or	$r12,$r0,$r0
	or	$r4,$r12,$r0
	ld.d	$r22,$r3,8
	.cfi_restore 22
	addi.d	$r3,$r3,16
	.cfi_def_cfa_register 3
	jr	$r1
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 8.3.0 20190222 (Loongson 8.3.0-23 vec)"
