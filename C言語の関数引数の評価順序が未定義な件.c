//・C言語の関数引数の評価順序が未定義な件
//以下のように、関数の引数として複数の関数を与えた場合、評価順序は未定義である。

#include <stdio.h>

int A()
{
    printf("A");
    return 1;
}

int B()
{
    printf("B");
    return 2;
}

int C()
{
    printf("C");
    return 3;
}

int add(int a, int b, int c)
{
    return a + b + c;
}

int main()
{
    int result = add(A(), B(), C());
    return 0;
}

//x86-64 gcc 14.1でコンパイルした結果

// A:
//         push    rbp
//         mov     rbp, rsp
//         mov     edi, 65
//         call    putchar
//         mov     eax, 1
//         pop     rbp
//         ret
// B:
//         push    rbp
//         mov     rbp, rsp
//         mov     edi, 66
//         call    putchar
//         mov     eax, 2
//         pop     rbp
//         ret
// C:
//         push    rbp
//         mov     rbp, rsp
//         mov     edi, 67
//         call    putchar
//         mov     eax, 3
//         pop     rbp
//         ret
// add:
//         push    rbp
//         mov     rbp, rsp
//         mov     DWORD PTR [rbp-4], edi
//         mov     DWORD PTR [rbp-8], esi
//         mov     DWORD PTR [rbp-12], edx
//         mov     edx, DWORD PTR [rbp-4]
//         mov     eax, DWORD PTR [rbp-8]
//         add     edx, eax
//         mov     eax, DWORD PTR [rbp-12]
//         add     eax, edx
//         pop     rbp
//         ret
// main:
//         push    rbp
//         mov     rbp, rsp
//         push    r12
//         push    rbx
//         sub     rsp, 16
//         mov     eax, 0
//         call    C
//         mov     r12d, eax
//         mov     eax, 0
//         call    B
//         mov     ebx, eax
//         mov     eax, 0
//         call    A
//         mov     edx, r12d
//         mov     esi, ebx
//         mov     edi, eax
//         call    add
//         mov     DWORD PTR [rbp-20], eax
//         mov     eax, 0
//         add     rsp, 16
//         pop     rbx
//         pop     r12
//         pop     rbp
//         ret

//81、84、87行目を見れば分かる通り、C->B->Aの順番で実行されている。

//なお、このPCでコンパイルすると、A->B->Cの順で実行される。

// 	.section	__TEXT,__text,regular,pure_instructions
// 	.build_version macos, 12, 0	sdk_version 13, 1
// 	.globl	_A                              ## -- Begin function A
// 	.p2align	4, 0x90
// _A:                                     ## @A
// 	.cfi_startproc
// ## %bb.0:
// 	pushq	%rbp
// 	.cfi_def_cfa_offset 16
// 	.cfi_offset %rbp, -16
// 	movq	%rsp, %rbp
// 	.cfi_def_cfa_register %rbp
// 	leaq	L_.str(%rip), %rdi
// 	movb	$0, %al
// 	callq	_printf
// 	movl	$1, %eax
// 	popq	%rbp
// 	retq
// 	.cfi_endproc
//                                         ## -- End function
// 	.globl	_B                              ## -- Begin function B
// 	.p2align	4, 0x90
// _B:                                     ## @B
// 	.cfi_startproc
// ## %bb.0:
// 	pushq	%rbp
// 	.cfi_def_cfa_offset 16
// 	.cfi_offset %rbp, -16
// 	movq	%rsp, %rbp
// 	.cfi_def_cfa_register %rbp
// 	leaq	L_.str.1(%rip), %rdi
// 	movb	$0, %al
// 	callq	_printf
// 	movl	$2, %eax
// 	popq	%rbp
// 	retq
// 	.cfi_endproc
//                                         ## -- End function
// 	.globl	_C                              ## -- Begin function C
// 	.p2align	4, 0x90
// _C:                                     ## @C
// 	.cfi_startproc
// ## %bb.0:
// 	pushq	%rbp
// 	.cfi_def_cfa_offset 16
// 	.cfi_offset %rbp, -16
// 	movq	%rsp, %rbp
// 	.cfi_def_cfa_register %rbp
// 	leaq	L_.str.2(%rip), %rdi
// 	movb	$0, %al
// 	callq	_printf
// 	movl	$3, %eax
// 	popq	%rbp
// 	retq
// 	.cfi_endproc
//                                         ## -- End function
// 	.globl	_add                            ## -- Begin function add
// 	.p2align	4, 0x90
// _add:                                   ## @add
// 	.cfi_startproc
// ## %bb.0:
// 	pushq	%rbp
// 	.cfi_def_cfa_offset 16
// 	.cfi_offset %rbp, -16
// 	movq	%rsp, %rbp
// 	.cfi_def_cfa_register %rbp
// 	movl	%edi, -4(%rbp)
// 	movl	%esi, -8(%rbp)
// 	movl	%edx, -12(%rbp)
// 	movl	-4(%rbp), %eax
// 	addl	-8(%rbp), %eax
// 	addl	-12(%rbp), %eax
// 	popq	%rbp
// 	retq
// 	.cfi_endproc
//                                         ## -- End function
// 	.globl	_main                           ## -- Begin function main
// 	.p2align	4, 0x90
// _main:                                  ## @main
// 	.cfi_startproc
// ## %bb.0:
// 	pushq	%rbp
// 	.cfi_def_cfa_offset 16
// 	.cfi_offset %rbp, -16
// 	movq	%rsp, %rbp
// 	.cfi_def_cfa_register %rbp
// 	subq	$16, %rsp
// 	movl	$0, -4(%rbp)
// 	callq	_A
// 	movl	%eax, -16(%rbp)                 ## 4-byte Spill
// 	callq	_B
// 	movl	%eax, -12(%rbp)                 ## 4-byte Spill
// 	callq	_C
// 	movl	-16(%rbp), %edi                 ## 4-byte Reload
// 	movl	-12(%rbp), %esi                 ## 4-byte Reload
// 	movl	%eax, %edx
// 	callq	_add
// 	movl	%eax, -8(%rbp)
// 	xorl	%eax, %eax
// 	addq	$16, %rsp
// 	popq	%rbp
// 	retq
// 	.cfi_endproc
//                                         ## -- End function
// 	.section	__TEXT,__cstring,cstring_literals
// L_.str:                                 ## @.str
// 	.asciz	"A"

// L_.str.1:                               ## @.str.1
// 	.asciz	"B"

// L_.str.2:                               ## @.str.2
// 	.asciz	"C"

// .subsections_via_symbols


//実行順を担保するためには、以下のように一度変数に取ることが必要。。

// int a = A();
// int b = B();
// int c = C();

// add(a, b, c);