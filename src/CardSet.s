	.file	"CardSet.cpp"
	.text
	.p2align 4,,15
	.globl	_ZN5poker8toStringB5cxx11ENS_5ColorE
	.type	_ZN5poker8toStringB5cxx11ENS_5ColorE, @function
_ZN5poker8toStringB5cxx11ENS_5ColorE:
.LFB2807:
	.cfi_startproc
	movq	%rdi, %rax
	cmpl	$1, %esi
	je	.L3
	jle	.L11
	cmpl	$2, %esi
	je	.L6
	cmpl	$3, %esi
	jne	.L2
	leaq	16(%rdi), %rdx
	movb	$83, 16(%rdi)
	movq	%rdx, (%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	leaq	16(%rdi), %rdx
	movb	$72, 16(%rdi)
	movq	%rdx, (%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	testl	%esi, %esi
	jne	.L2
	leaq	16(%rdi), %rdx
	movb	$67, 16(%rdi)
	movq	%rdx, (%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	ret
	.p2align 4,,10
	.p2align 3
.L2:
	leaq	16(%rax), %rdx
	movb	$63, 16(%rax)
	movq	%rdx, (%rax)
	movq	$1, 8(%rax)
	movb	$0, 17(%rax)
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	leaq	16(%rdi), %rdx
	movb	$68, 16(%rdi)
	movq	%rdx, (%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	ret
	.cfi_endproc
.LFE2807:
	.size	_ZN5poker8toStringB5cxx11ENS_5ColorE, .-_ZN5poker8toStringB5cxx11ENS_5ColorE
	.p2align 4,,15
	.globl	_ZN5poker8toStringB5cxx11ENS_4RankE
	.type	_ZN5poker8toStringB5cxx11ENS_4RankE, @function
_ZN5poker8toStringB5cxx11ENS_4RankE:
.LFB2808:
	.cfi_startproc
	cmpl	$12, %esi
	ja	.L13
	leaq	16(%rdi), %rax
	movl	%esi, %esi
	movq	%rax, (%rdi)
	jmp	*.L15(,%rsi,8)
	.section	.rodata
	.align 8
	.align 4
.L15:
	.quad	.L14
	.quad	.L16
	.quad	.L17
	.quad	.L18
	.quad	.L19
	.quad	.L20
	.quad	.L21
	.quad	.L22
	.quad	.L23
	.quad	.L24
	.quad	.L25
	.quad	.L26
	.quad	.L27
	.text
	.p2align 4,,10
	.p2align 3
.L26:
	movb	$75, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
.L29:
	movq	%rdi, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L27:
	movb	$65, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L14:
	movb	$50, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L16:
	movb	$51, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L17:
	movb	$52, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L18:
	movb	$53, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L19:
	movb	$54, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L20:
	movb	$55, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L21:
	movb	$56, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L22:
	movb	$57, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L23:
	movb	$84, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L24:
	movb	$74, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L25:
	movb	$81, 16(%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L13:
	leaq	16(%rdi), %rax
	movb	$63, 16(%rdi)
	movq	%rax, (%rdi)
	movq	$1, 8(%rdi)
	movb	$0, 17(%rdi)
	jmp	.L29
	.cfi_endproc
.LFE2808:
	.size	_ZN5poker8toStringB5cxx11ENS_4RankE, .-_ZN5poker8toStringB5cxx11ENS_4RankE
	.align 2
	.p2align 4,,15
	.globl	_ZNK5poker4Card8toStringB5cxx11Ev
	.type	_ZNK5poker4Card8toStringB5cxx11Ev, @function
_ZNK5poker4Card8toStringB5cxx11Ev:
.LFB2809:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2809
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	subq	$80, %rsp
	.cfi_def_cfa_offset 112
	movzbl	(%rsi), %edx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	leal	0(,%rdx,4), %eax
	movl	%edx, %ecx
	addl	%edx, %eax
	sall	$4, %eax
	subl	%edx, %eax
	shrw	$10, %ax
	movl	%eax, %edx
	leal	(%rdx,%rdx), %eax
	movl	%edx, %esi
	addl	%edx, %eax
	leal	(%rsi,%rax,4), %eax
	subl	%eax, %ecx
	movzbl	%cl, %eax
	cmpb	$1, %dl
	je	.L32
	jb	.L33
	cmpb	$2, %dl
	je	.L34
	cmpb	$3, %dl
	jne	.L73
	leaq	32(%rsp), %r12
	movb	$83, 48(%rsp)
	leaq	16(%r12), %rdx
	movb	$0, 49(%rsp)
	movq	%rdx, 32(%rsp)
	movq	$1, 40(%rsp)
.L36:
	movq	%rsp, %rbp
	cmpb	$12, %al
	ja	.L37
	jmp	*.L39(,%rax,8)
	.section	.rodata
	.align 8
	.align 4
.L39:
	.quad	.L37
	.quad	.L38
	.quad	.L40
	.quad	.L41
	.quad	.L42
	.quad	.L43
	.quad	.L44
	.quad	.L45
	.quad	.L46
	.quad	.L47
	.quad	.L48
	.quad	.L49
	.quad	.L50
	.text
	.p2align 4,,10
	.p2align 3
.L34:
	leaq	32(%rsp), %r12
	movb	$72, 48(%rsp)
	leaq	16(%r12), %rdx
	movb	$0, 49(%rsp)
	movq	%rdx, 32(%rsp)
	movq	$1, 40(%rsp)
	jmp	.L36
	.p2align 4,,10
	.p2align 3
.L73:
	leaq	32(%rsp), %r12
	movb	$63, 48(%rsp)
	leaq	16(%r12), %rdx
	movb	$0, 49(%rsp)
	movq	%rdx, 32(%rsp)
	movq	$1, 40(%rsp)
	jmp	.L36
	.p2align 4,,10
	.p2align 3
.L33:
	leaq	32(%rsp), %r12
	movb	$67, 48(%rsp)
	leaq	16(%r12), %rdx
	movb	$0, 49(%rsp)
	movq	%rdx, 32(%rsp)
	movq	$1, 40(%rsp)
	jmp	.L36
	.p2align 4,,10
	.p2align 3
.L32:
	leaq	32(%rsp), %r12
	movb	$68, 48(%rsp)
	leaq	16(%r12), %rdx
	movb	$0, 49(%rsp)
	movq	%rdx, 32(%rsp)
	movq	$1, 40(%rsp)
	jmp	.L36
	.p2align 4,,10
	.p2align 3
.L49:
	leaq	16(%rsp), %rax
	movb	$75, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	.p2align 4,,10
	.p2align 3
.L51:
	movq	40(%rsp), %rdx
	movq	32(%rsp), %rsi
	leaq	1(%rdx), %rax
	cmpq	$15, %rax
	jbe	.L52
	leaq	16(%r12), %rcx
	cmpq	%rcx, %rsi
	je	.L52
	cmpq	48(%rsp), %rax
	ja	.L52
	leaq	16(%rbp), %rcx
	movl	$1, %r8d
	xorl	%edx, %edx
	xorl	%esi, %esi
	movq	%r12, %rdi
.LEHB0:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm
.L61:
	leaq	16(%rbx), %rdx
	movq	%rdx, (%rbx)
	movq	(%rax), %rcx
	leaq	16(%rax), %rdx
	cmpq	%rdx, %rcx
	je	.L74
	movq	%rcx, (%rbx)
	movq	16(%rax), %rcx
	movq	%rcx, 16(%rbx)
.L55:
	movq	8(%rax), %rcx
	addq	$16, %rbp
	movq	%rcx, 8(%rbx)
	movq	%rdx, (%rax)
	movq	(%rsp), %rdi
	movq	$0, 8(%rax)
	movb	$0, 16(%rax)
	cmpq	%rbp, %rdi
	je	.L56
	call	_ZdlPv
.L56:
	movq	32(%rsp), %rdi
	addq	$16, %r12
	cmpq	%r12, %rdi
	je	.L30
	call	_ZdlPv
.L30:
	movq	72(%rsp), %rsi
	xorq	%fs:40, %rsi
	movq	%rbx, %rax
	jne	.L75
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L48:
	.cfi_restore_state
	leaq	16(%rsp), %rax
	movb	$81, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L47:
	leaq	16(%rsp), %rax
	movb	$74, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L46:
	leaq	16(%rsp), %rax
	movb	$84, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L45:
	leaq	16(%rsp), %rax
	movb	$57, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L44:
	leaq	16(%rsp), %rax
	movb	$56, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L43:
	leaq	16(%rsp), %rax
	movb	$55, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L42:
	leaq	16(%rsp), %rax
	movb	$54, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L41:
	leaq	16(%rsp), %rax
	movb	$53, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L40:
	leaq	16(%rsp), %rax
	movb	$52, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L38:
	leaq	16(%rsp), %rax
	movb	$51, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L37:
	leaq	16(%rbp), %rax
	movb	$50, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L50:
	leaq	16(%rsp), %rax
	movb	$65, 16(%rsp)
	movq	%rax, (%rsp)
	movq	$1, 8(%rsp)
	movb	$0, 17(%rsp)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L52:
	movq	%rbp, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_appendEPKcm
.LEHE0:
	jmp	.L61
	.p2align 4,,10
	.p2align 3
.L74:
	movq	16(%rax), %rsi
	movq	24(%rax), %rdi
	movq	%rsi, 16(%rbx)
	movq	%rdi, 24(%rbx)
	jmp	.L55
.L75:
	call	__stack_chk_fail
.L67:
	movq	(%rsp), %rdi
	addq	$16, %rbp
	movq	%rax, %rbx
	cmpq	%rbp, %rdi
	je	.L69
	vzeroupper
	call	_ZdlPv
.L59:
	movq	32(%rsp), %rdi
	addq	$16, %r12
	cmpq	%r12, %rdi
	je	.L60
	call	_ZdlPv
.L60:
	movq	%rbx, %rdi
.LEHB1:
	call	_Unwind_Resume
.LEHE1:
.L69:
	vzeroupper
	jmp	.L59
	.cfi_endproc
.LFE2809:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA2809:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2809-.LLSDACSB2809
.LLSDACSB2809:
	.uleb128 .LEHB0-.LFB2809
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L67-.LFB2809
	.uleb128 0
	.uleb128 .LEHB1-.LFB2809
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSE2809:
	.text
	.size	_ZNK5poker4Card8toStringB5cxx11Ev, .-_ZNK5poker4Card8toStringB5cxx11Ev
	.align 2
	.p2align 4,,15
	.globl	_ZNK5poker7CardSet15rankTexasHoldemEv
	.type	_ZNK5poker7CardSet15rankTexasHoldemEv, @function
_ZNK5poker7CardSet15rankTexasHoldemEv:
.LFB2830:
	.cfi_startproc
	vmovdqa	(%rdi), %xmm1
	vpshufd	$177, %xmm1, %xmm2
	vpand	%xmm2, %xmm1, %xmm0
	vpshufd	$78, %xmm0, %xmm3
	vpand	%xmm3, %xmm0, %xmm0
	vptest	%xmm0, %xmm0
	jne	.L95
	vpaddd	%xmm1, %xmm2, %xmm3
	xorl	%r8d, %r8d
	vpshufd	$78, %xmm3, %xmm0
	vpaddd	%xmm3, %xmm0, %xmm0
	vmovd	%xmm0, %ecx
	vmovd	%xmm0, %esi
	andl	$178956970, %esi
	leal	(%rcx,%rcx), %edx
	popcntl	%esi, %r8d
	andl	%esi, %edx
	jne	.L96
	testl	%r8d, %r8d
	je	.L97
	cmpl	$1, %r8d
	je	.L98
	cmpl	$2, %r8d
	je	.L99
	xorl	%edx, %edx
	movl	$1, %r8d
	vmovd	%xmm0, %eax
	tzcntl	%esi, %edx
	andl	$-178956971, %eax
	shlx	%edx, %r8d, %edx
	movl	%edx, %ecx
	xorl	%edx, %esi
	shrl	%ecx
	xorl	%eax, %ecx
	movq	%rsi, %rax
	salq	$28, %rax
	bsrl	%ecx, %edx
	shlx	%edx, %r8d, %edx
	orq	%rax, %rdx
	movabsq	$144115188075855872, %rax
	orq	%rdx, %rax
.L81:
	vpor	%xmm2, %xmm1, %xmm1
	vpshufd	$78, %xmm1, %xmm0
	vpor	%xmm0, %xmm1, %xmm1
	vmovd	%xmm1, %edx
	vmovd	%xmm1, %ecx
	leal	0(,%rdx,4), %esi
	shrl	$26, %ecx
	andl	%edx, %esi
	orl	%ecx, %edx
	movl	%esi, %ecx
	sall	$8, %edx
	sall	$4, %ecx
	andl	%ecx, %edx
	andl	%esi, %edx
	jne	.L100
.L85:
	xorl	%esi, %esi
	xorl	%ecx, %ecx
	popcntl	(%rdi), %esi
	cmpl	$4, %esi
	setg	%cl
	movl	$0, %r8d
	movl	$1, %r9d
	movl	$2, %r10d
	subl	$1, %ecx
	cmpl	$4, %esi
	cmovg	%esi, %r8d
	xorl	%esi, %esi
	popcntl	4(%rdi), %esi
	cmpl	$4, %esi
	cmovg	%r9d, %ecx
	cmovg	%esi, %r8d
	xorl	%esi, %esi
	popcntl	8(%rdi), %esi
	cmpl	$4, %esi
	cmovg	%r10d, %ecx
	movl	$3, %r10d
	cmovle	%r8d, %esi
	xorl	%r8d, %r8d
	popcntl	12(%rdi), %r8d
	cmpl	$4, %r8d
	cmovg	%r10d, %ecx
	cmovg	%r8d, %esi
	cmpl	$-1, %ecx
	jne	.L101
	ret
	.p2align 4,,10
	.p2align 3
.L97:
	xorl	%eax, %eax
	movl	$1, %edx
	tzcntl	%ecx, %eax
	shlx	%eax, %edx, %esi
	vmovd	%xmm0, %eax
	xorl	%esi, %eax
	tzcntl	%eax, %eax
	shlx	%eax, %edx, %eax
	orl	%esi, %eax
	xorl	%ecx, %eax
	jmp	.L81
	.p2align 4,,10
	.p2align 3
.L101:
	movslq	%ecx, %rcx
	movl	(%rdi,%rcx,4), %eax
	leal	0(,%rax,4), %edi
	movl	%eax, %ecx
	andl	%eax, %edi
	shrl	$26, %ecx
	orl	%eax, %ecx
	movl	%edi, %r8d
	sall	$8, %ecx
	sall	$4, %r8d
	andl	%r8d, %ecx
	testl	%ecx, %edi
	jne	.L102
	cmpl	$6, %esi
	je	.L103
	cmpl	$7, %esi
	je	.L104
.L89:
	movabsq	$360287970189639680, %rdx
	orq	%rdx, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L98:
	xorl	%eax, %eax
	salq	$28, %rsi
	tzcntl	%ecx, %eax
	shlx	%eax, %r8d, %edx
	vmovd	%xmm0, %eax
	xorl	%edx, %eax
	tzcntl	%eax, %eax
	shlx	%eax, %r8d, %eax
	orl	%edx, %eax
	movabsq	$72057594037927936, %rdx
	xorl	%ecx, %eax
	orq	%rdx, %rsi
	orq	%rsi, %rax
	jmp	.L81
	.p2align 4,,10
	.p2align 3
.L95:
	vpor	%xmm2, %xmm1, %xmm1
	vmovd	%xmm0, %eax
	vpshufd	$78, %xmm1, %xmm2
	vpor	%xmm2, %xmm1, %xmm1
	vmovd	%xmm1, %edx
	xorl	%eax, %edx
	salq	$28, %rax
	bsrl	%edx, %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movabsq	$504403158265495552, %rdx
	orq	%rdx, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L96:
	bsrl	%edx, %edx
	movl	$1, %r9d
	movl	$31, %r8d
	shlx	%edx, %r9d, %edx
	cmpl	%edx, %esi
	je	.L80
	movq	%rdx, %rax
	xorl	%edx, %esi
	xorl	%ecx, %ecx
	movabsq	$432345564227567616, %rdx
	salq	$28, %rax
	lzcntl	%esi, %ecx
	subl	%ecx, %r8d
	orq	%rdx, %rax
	orq	%r8, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L100:
	movabsq	$288230376151711744, %rcx
	bsrl	%edx, %eax
	cltq
	orq	%rcx, %rax
	jmp	.L85
	.p2align 4,,10
	.p2align 3
.L99:
	vmovd	%xmm0, %eax
	salq	$28, %rsi
	movabsq	$144115188075855872, %rdx
	andl	$-178956971, %eax
	orq	%rdx, %rsi
	bsrl	%eax, %ecx
	movl	$1, %eax
	shlx	%ecx, %eax, %eax
	orq	%rsi, %rax
	jmp	.L81
	.p2align 4,,10
	.p2align 3
.L80:
	movl	%r8d, %edx
	xorl	%eax, %eax
	lzcntl	%ecx, %eax
	subl	%eax, %edx
	vmovd	%xmm0, %eax
	movabsq	$216172782113783808, %rcx
	shlx	%edx, %r9d, %edx
	xorl	%edx, %eax
	lzcntl	%eax, %eax
	subl	%eax, %r8d
	shlx	%r8d, %r9d, %eax
	orl	%edx, %eax
	movl	%esi, %edx
	salq	$28, %rdx
	orq	%rcx, %rdx
	orq	%rdx, %rax
	jmp	.L81
.L102:
	bsrl	%edx, %eax
	movabsq	$576460752303423488, %rdx
	movl	%eax, %eax
	orq	%rdx, %rax
	ret
.L103:
	xorl	%edx, %edx
	tzcntl	%eax, %edx
	shlx	%edx, %r9d, %r9d
	xorl	%r9d, %eax
	jmp	.L89
.L104:
	xorl	%edx, %edx
	tzcntl	%eax, %edx
	shlx	%edx, %r9d, %ecx
	movl	%eax, %edx
	xorl	%ecx, %edx
	tzcntl	%edx, %edx
	shlx	%edx, %r9d, %edx
	orl	%ecx, %edx
	xorl	%edx, %eax
	jmp	.L89
	.cfi_endproc
.LFE2830:
	.size	_ZNK5poker7CardSet15rankTexasHoldemEv, .-_ZNK5poker7CardSet15rankTexasHoldemEv
	.section	.rodata._ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_.str1.1,"aMS",@progbits,1
.LC0:
	.string	"vector::_M_emplace_back_aux"
	.section	.text._ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_,"axG",@progbits,_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	.type	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_, @function
_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_:
.LFB3215:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdi, %rbx
	movq	8(%rdi), %rdi
	subq	(%rbx), %rdi
	cmpq	$-1, %rdi
	je	.L129
	movq	%rsi, %r14
	movl	$1, %r12d
	testq	%rdi, %rdi
	je	.L107
	addq	%rdi, %rdi
	jc	.L109
	movq	%rdi, %r12
.L107:
	movq	%r12, %rdi
	call	_Znwm
	movq	8(%rbx), %r8
	movq	(%rbx), %rdi
	movq	%rax, %rbp
	addq	%rax, %r12
	leaq	1(%rax), %r13
	movq	%r8, %rax
	subq	%rdi, %rax
	addq	%rbp, %rax
	je	.L110
	movzbl	(%r14), %edx
	movb	%dl, (%rax)
.L110:
	cmpq	%rdi, %r8
	je	.L111
	movq	%rdi, %rdx
	movq	%rbp, %rcx
	.p2align 4,,10
	.p2align 3
.L113:
	testq	%rcx, %rcx
	je	.L112
	movzbl	(%rdx), %esi
	movb	%sil, (%rcx)
.L112:
	addq	$1, %rdx
	addq	$1, %rcx
	cmpq	%r8, %rdx
	jne	.L113
	subq	%rdi, %rdx
	leaq	1(%rbp,%rdx), %r13
.L111:
	testq	%rdi, %rdi
	je	.L114
	call	_ZdlPv
.L114:
	movq	%rbp, (%rbx)
	movq	%r13, 8(%rbx)
	movq	%r12, 16(%rbx)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L129:
	.cfi_restore_state
	movl	$.LC0, %edi
	call	_ZSt20__throw_length_errorPKc
.L109:
	movq	$-1, %r12
	jmp	.L107
	.cfi_endproc
.LFE3215:
	.size	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_, .-_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	.text
	.align 2
	.p2align 4,,15
	.globl	_ZNK5poker7CardSet12toCardVectorEv
	.type	_ZNK5poker7CardSet12toCardVectorEv, @function
_ZNK5poker7CardSet12toCardVectorEv:
.LFB2814:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA2814
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rsi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movl	$12, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	movq	$0, (%rdi)
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	$0, 8(%rdi)
	movq	$0, 16(%rdi)
.L221:
	movl	(%r12), %eax
	testb	$4, %al
	jne	.L322
.L131:
	testb	$16, %al
	jne	.L323
.L138:
	testb	$64, %al
	jne	.L324
.L145:
	testb	$1, %ah
	jne	.L325
.L152:
	testb	$4, %ah
	jne	.L326
.L159:
	testb	$16, %ah
	jne	.L327
.L166:
	testb	$64, %ah
	jne	.L328
.L173:
	testl	$65536, %eax
	jne	.L329
.L180:
	testl	$262144, %eax
	jne	.L330
.L187:
	testl	$1048576, %eax
	jne	.L331
.L194:
	testl	$4194304, %eax
	jne	.L332
.L201:
	testl	$16777216, %eax
	jne	.L333
.L208:
	testl	$67108864, %eax
	jne	.L334
.L215:
	addl	$13, %ebp
	addq	$4, %r12
	cmpb	$64, %bpl
	jne	.L221
	movq	8(%rsp), %rdi
	xorq	%fs:40, %rdi
	movq	%rbx, %rax
	jne	.L335
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L334:
	.cfi_restore_state
	movb	%bpl, 7(%rsp)
	movq	8(%rbx), %rax
	cmpq	16(%rbx), %rax
	je	.L336
	testq	%rax, %rax
	je	.L220
	movb	%bpl, (%rax)
.L220:
	addq	$1, %rax
	movq	%rax, 8(%rbx)
	jmp	.L215
	.p2align 4,,10
	.p2align 3
.L333:
	leal	-1(%rbp), %ecx
	movq	8(%rbx), %rdx
	movb	%cl, 7(%rsp)
	cmpq	16(%rbx), %rdx
	je	.L337
	testq	%rdx, %rdx
	je	.L214
	movb	%cl, (%rdx)
.L214:
	addq	$1, %rdx
	movq	%rdx, 8(%rbx)
	jmp	.L208
	.p2align 4,,10
	.p2align 3
.L332:
	leal	-2(%rbp), %ecx
	movq	8(%rbx), %rdx
	movb	%cl, 7(%rsp)
	cmpq	16(%rbx), %rdx
	je	.L338
	testq	%rdx, %rdx
	je	.L207
	movb	%cl, (%rdx)
.L207:
	addq	$1, %rdx
	movq	%rdx, 8(%rbx)
	jmp	.L201
	.p2align 4,,10
	.p2align 3
.L331:
	leal	-3(%rbp), %ecx
	movq	8(%rbx), %rdx
	movb	%cl, 7(%rsp)
	cmpq	16(%rbx), %rdx
	je	.L339
	testq	%rdx, %rdx
	je	.L200
	movb	%cl, (%rdx)
.L200:
	addq	$1, %rdx
	movq	%rdx, 8(%rbx)
	jmp	.L194
	.p2align 4,,10
	.p2align 3
.L330:
	leal	-4(%rbp), %ecx
	movq	8(%rbx), %rdx
	movb	%cl, 7(%rsp)
	cmpq	16(%rbx), %rdx
	je	.L340
	testq	%rdx, %rdx
	je	.L193
	movb	%cl, (%rdx)
.L193:
	addq	$1, %rdx
	movq	%rdx, 8(%rbx)
	jmp	.L187
	.p2align 4,,10
	.p2align 3
.L329:
	leal	-5(%rbp), %ecx
	movq	8(%rbx), %rdx
	movb	%cl, 7(%rsp)
	cmpq	16(%rbx), %rdx
	je	.L341
	testq	%rdx, %rdx
	je	.L186
	movb	%cl, (%rdx)
.L186:
	addq	$1, %rdx
	movq	%rdx, 8(%rbx)
	jmp	.L180
	.p2align 4,,10
	.p2align 3
.L328:
	leal	-6(%rbp), %ecx
	movq	8(%rbx), %rdx
	movb	%cl, 7(%rsp)
	cmpq	16(%rbx), %rdx
	je	.L342
	testq	%rdx, %rdx
	je	.L179
	movb	%cl, (%rdx)
.L179:
	addq	$1, %rdx
	movq	%rdx, 8(%rbx)
	jmp	.L173
	.p2align 4,,10
	.p2align 3
.L327:
	leal	-7(%rbp), %ecx
	movq	8(%rbx), %rdx
	movb	%cl, 7(%rsp)
	cmpq	16(%rbx), %rdx
	je	.L343
	testq	%rdx, %rdx
	je	.L172
	movb	%cl, (%rdx)
.L172:
	addq	$1, %rdx
	movq	%rdx, 8(%rbx)
	jmp	.L166
	.p2align 4,,10
	.p2align 3
.L326:
	leal	-8(%rbp), %ecx
	movq	8(%rbx), %rdx
	movb	%cl, 7(%rsp)
	cmpq	16(%rbx), %rdx
	je	.L344
	testq	%rdx, %rdx
	je	.L165
	movb	%cl, (%rdx)
.L165:
	addq	$1, %rdx
	movq	%rdx, 8(%rbx)
	jmp	.L159
	.p2align 4,,10
	.p2align 3
.L325:
	leal	-9(%rbp), %ecx
	movq	8(%rbx), %rdx
	movb	%cl, 7(%rsp)
	cmpq	16(%rbx), %rdx
	je	.L345
	testq	%rdx, %rdx
	je	.L158
	movb	%cl, (%rdx)
.L158:
	addq	$1, %rdx
	movq	%rdx, 8(%rbx)
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L324:
	leal	-10(%rbp), %ecx
	movq	8(%rbx), %rdx
	movb	%cl, 7(%rsp)
	cmpq	16(%rbx), %rdx
	je	.L346
	testq	%rdx, %rdx
	je	.L151
	movb	%cl, (%rdx)
.L151:
	addq	$1, %rdx
	movq	%rdx, 8(%rbx)
	jmp	.L145
	.p2align 4,,10
	.p2align 3
.L323:
	leal	-11(%rbp), %ecx
	movq	8(%rbx), %rdx
	movb	%cl, 7(%rsp)
	cmpq	16(%rbx), %rdx
	je	.L347
	testq	%rdx, %rdx
	je	.L144
	movb	%cl, (%rdx)
.L144:
	addq	$1, %rdx
	movq	%rdx, 8(%rbx)
	jmp	.L138
	.p2align 4,,10
	.p2align 3
.L322:
	leal	-12(%rbp), %ecx
	movq	8(%rbx), %rdx
	movb	%cl, 7(%rsp)
	cmpq	16(%rbx), %rdx
	je	.L348
	testq	%rdx, %rdx
	je	.L137
	movb	%cl, (%rdx)
.L137:
	addq	$1, %rdx
	movq	%rdx, 8(%rbx)
	jmp	.L131
	.p2align 4,,10
	.p2align 3
.L336:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
.LEHB2:
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	jmp	.L215
	.p2align 4,,10
	.p2align 3
.L337:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	movl	(%r12), %eax
	jmp	.L208
	.p2align 4,,10
	.p2align 3
.L338:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	movl	(%r12), %eax
	jmp	.L201
	.p2align 4,,10
	.p2align 3
.L339:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	movl	(%r12), %eax
	jmp	.L194
	.p2align 4,,10
	.p2align 3
.L340:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	movl	(%r12), %eax
	jmp	.L187
	.p2align 4,,10
	.p2align 3
.L341:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	movl	(%r12), %eax
	jmp	.L180
	.p2align 4,,10
	.p2align 3
.L342:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	movl	(%r12), %eax
	jmp	.L173
	.p2align 4,,10
	.p2align 3
.L343:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	movl	(%r12), %eax
	jmp	.L166
	.p2align 4,,10
	.p2align 3
.L344:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	movl	(%r12), %eax
	jmp	.L159
	.p2align 4,,10
	.p2align 3
.L345:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	movl	(%r12), %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L346:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	movl	(%r12), %eax
	jmp	.L145
	.p2align 4,,10
	.p2align 3
.L347:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
	movl	(%r12), %eax
	jmp	.L138
	.p2align 4,,10
	.p2align 3
.L348:
	leaq	7(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNSt6vectorIN5poker4CardESaIS1_EE19_M_emplace_back_auxIJS1_EEEvDpOT_
.LEHE2:
	movl	(%r12), %eax
	jmp	.L131
.L225:
	movq	(%rbx), %rdi
	movq	%rax, %rbp
	testq	%rdi, %rdi
	je	.L294
	vzeroupper
	call	_ZdlPv
.L223:
	movq	%rbp, %rdi
.LEHB3:
	call	_Unwind_Resume
.LEHE3:
.L335:
	call	__stack_chk_fail
.L294:
	vzeroupper
	jmp	.L223
	.cfi_endproc
.LFE2814:
	.section	.gcc_except_table
.LLSDA2814:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2814-.LLSDACSB2814
.LLSDACSB2814:
	.uleb128 .LEHB2-.LFB2814
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L225-.LFB2814
	.uleb128 0
	.uleb128 .LEHB3-.LFB2814
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSE2814:
	.text
	.size	_ZNK5poker7CardSet12toCardVectorEv, .-_ZNK5poker7CardSet12toCardVectorEv
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.type	_GLOBAL__sub_I__ZN5poker8toStringB5cxx11ENS_5ColorE, @function
_GLOBAL__sub_I__ZN5poker8toStringB5cxx11ENS_5ColorE:
.LFB3371:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE3371:
	.size	_GLOBAL__sub_I__ZN5poker8toStringB5cxx11ENS_5ColorE, .-_GLOBAL__sub_I__ZN5poker8toStringB5cxx11ENS_5ColorE
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN5poker8toStringB5cxx11ENS_5ColorE
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.ident	"GCC: (Gentoo 6.4.0 p1.1) 6.4.0"
	.section	.note.GNU-stack,"",@progbits
