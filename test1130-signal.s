	.file	"test1130-signal.c"
	.text
	.section	.rodata
.LC0:
	.string	"sigchld_handler"
	.text
	.globl	sigchld_handler
	.type	sigchld_handler, @function
sigchld_handler:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	movl	$3, %edi
	call	sleep@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	sigchld_handler, .-sigchld_handler
	.section	.rodata
.LC1:
	.string	"fork"
.LC2:
	.string	"before wait"
.LC3:
	.string	"ps -ef | grep ttt"
.LC4:
	.string	"wait pid is %d\n"
.LC5:
	.string	"after wait"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	sigchld_handler(%rip), %rsi
	movl	$17, %edi
	call	signal@PLT
	movl	$0, -12(%rbp)
	jmp	.L4
.L7:
	call	fork@PLT
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jne	.L5
	movl	$2, %edi
	call	sleep@PLT
	movl	$0, %edi
	call	exit@PLT
.L5:
	cmpl	$-1, -4(%rbp)
	jne	.L6
	leaq	.LC1(%rip), %rdi
	call	perror@PLT
	movl	$-1, %edi
	call	exit@PLT
.L6:
	addl	$1, -12(%rbp)
.L4:
	cmpl	$4, -12(%rbp)
	jle	.L7
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	leaq	.LC3(%rip), %rdi
	call	system@PLT
	jmp	.L8
.L9:
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
.L8:
	movl	$0, %edi
	call	wait@PLT
	movl	%eax, -8(%rbp)
	cmpl	$-1, -8(%rbp)
	jne	.L9
	leaq	.LC5(%rip), %rdi
	call	puts@PLT
	leaq	.LC3(%rip), %rdi
	call	system@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
