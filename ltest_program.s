	.file	"ltest_program.ll"
	.text
	.globl	sub
	.align	16, 0x90
	.type	sub,@function
sub:                                    # @sub
	.cfi_startproc
# BB#0:                                 # %entry
	subq	$24, %rsp
.Ltmp1:
	.cfi_def_cfa_offset 32
	movl	%edi, 4(%rsp)
	movl	%esi, (%rsp)
	movl	%esi, 4(%rsp)
	movl	$1, 8(%rsp)
	movb	$1, %al
	testb	%al, %al
	jne	.LBB0_6
	.align	16, 0x90
.LBB0_1:                                # %loop
                                        # =>This Inner Loop Header: Depth=1
	movl	4(%rsp), %eax
	cmpl	(%rsp), %eax
	jbe	.LBB0_3
# BB#2:                                 # %then
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	$0, 12(%rsp)
	movl	$0, 16(%rsp)
	movb	$0, 22(%rsp)
	movl	16(%rsp), %eax
	addl	%eax, 12(%rsp)
	jmp	.LBB0_5
	.align	16, 0x90
.LBB0_3:                                # %ifcont22
                                        #   in Loop: Header=BB0_1 Depth=1
	movb	$0, 23(%rsp)
	movl	(%rsp), %eax
	cmpl	4(%rsp), %eax
	jne	.LBB0_5
# BB#4:                                 # %then26
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	(%rsp), %eax
	movl	%eax, 4(%rsp)
.LBB0_5:                                # %ifcont30
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	8(%rsp)
	js	.LBB0_1
.LBB0_6:                                # %afterloop
	movl	$3, %edi
	movl	$.L__unnamed_1, %esi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	addq	$24, %rsp
	ret
.Ltmp2:
	.size	sub, .Ltmp2-sub
	.cfi_endproc

	.globl	add
	.align	16, 0x90
	.type	add,@function
add:                                    # @add
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rax
.Ltmp4:
	.cfi_def_cfa_offset 16
	movl	%edi, (%rsp)
	movb	$0, 7(%rsp)
	movb	$0, 7(%rsp)
	movl	$2, %edi
	movl	$3, %esi
	callq	sub
	popq	%rdx
	ret
.Ltmp5:
	.size	add, .Ltmp5-add
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rax
.Ltmp7:
	.cfi_def_cfa_offset 16
	movl	$2, %edi
	movl	$3, %esi
	callq	sub
	popq	%rdx
	ret
.Ltmp8:
	.size	main, .Ltmp8-main
	.cfi_endproc

	.type	.L__unnamed_1,@object   # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"yolo %d"
	.size	.L__unnamed_1, 8


	.section	".note.GNU-stack","",@progbits
