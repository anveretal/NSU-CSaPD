# x86-64 gcc 14.2

```
pi_f:
        pushq   %rbp
        movq    %rsp, %rbp
        movl    %edi, -36(%rbp)
        pxor    %xmm0, %xmm0
        movsd   %xmm0, -8(%rbp)
        movl    $1, -12(%rbp)
        movl    $1, -16(%rbp)
        movl    $0, -20(%rbp)
        jmp     .L2
.L3:
        pxor    %xmm1, %xmm1
        cvtsi2sdl       -12(%rbp), %xmm1
        pxor    %xmm2, %xmm2
        cvtsi2sdl       -16(%rbp), %xmm2
        movsd   .LC1(%rip), %xmm0
        divsd   %xmm2, %xmm0
        mulsd   %xmm1, %xmm0
        movsd   -8(%rbp), %xmm1
        addsd   %xmm1, %xmm0
        movsd   %xmm0, -8(%rbp)
        addl    $2, -16(%rbp)
        negl    -12(%rbp)
        addl    $1, -20(%rbp)
.L2:
        movl    -20(%rbp), %eax
        cmpl    -36(%rbp), %eax
        jl      .L3
        movsd   -8(%rbp), %xmm0
        popq    %rbp
        ret
.LC2:
        .string "Input n: "
.LC3:
        .string "%d"
.LC4:
        .string "Answer: %0.14f\n"
main:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $32, %rsp
        movl    %edi, -20(%rbp)
        movq    %rsi, -32(%rbp)
        movl    $.LC2, %edi
        movl    $0, %eax
        call    printf
        leaq    -4(%rbp), %rax
        movq    %rax, %rsi
        movl    $.LC3, %edi
        movl    $0, %eax
        call    __isoc99_scanf
        movl    -4(%rbp), %eax
        movl    %eax, %edi
        call    pi_f
        movq    %xmm0, %rax
        movq    %rax, %xmm0
        movl    $.LC4, %edi
        movl    $1, %eax
        call    printf
        movl    $0, %eax
        leave
        ret
.LC1:
        .long   0
        .long   1074790400
```
