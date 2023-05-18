//・C言語からアセンブリファイルを作って読む
#include <stdio.h>

int main(void)
{
    printf("%s", "hello world");

    return 0;
}

//GCCの場合、-Sオプションをつけて以下のようにコンパイルすると、(ファイル名).sというアセンブリファイルが出力される
//gcc -S (ファイル名).c 

.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0	sdk_version 13, 1
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90

//・疑似命令(14~18行目)
//機械語に変換されない部分
//_TEXT、_mainなどのセグメント(=プログラムの領域)を宣言している

_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp//ベースレジスタをスタックに格納する
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp//ベースレジスタにスタックポインタを格納する
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	leaq	L_.str(%rip), %rdi
	leaq	L_.str.1(%rip), %rsi
	movb	$0, %al
	callq	_printf//printf関数を呼び出す
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp//ベースレジスタをスタックからポップする
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%s"

L_.str.1:                               ## @.str.1
	.asciz	"hello world"

.subsections_via_symbols

//オペコード(movqなど)・オペランド(%rsp、%rbpなど)に分かれている
//movq...データをレジスタ・メモリに格納する
//push...スタックにデータを積む
//pop...スタックからデータを取り出す
