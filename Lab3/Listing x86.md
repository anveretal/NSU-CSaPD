# x86 CompCert 3.12

```
__stringlit_1:
        .ascii  "Input n: \000"
__stringlit_3:
        .ascii  "Answer: %0.14f\012\000"
__stringlit_2:
        .ascii  "%d\000"
pi_f:
        subl    $28, %esp
        leal    32(%esp), %eax
        movl    %eax, 0(%esp)
        movl    %ebx, 4(%esp)
        movl    0(%eax), %ebx
        xorpd   %xmm1, %xmm1
        movl    $1, %eax
        movl    $1, %ecx
        xorl    %edx, %edx
.L107:
        cmpl    %ebx, %edx
        jge     .L108
        cvtsi2sd %eax, %xmm2
        movsd   .L110, %xmm0 # 4
        cvtsi2sd %ecx, %xmm3
        divsd   %xmm3, %xmm0
        mulsd   %xmm0, %xmm2
        addsd   %xmm2, %xmm1
        leal    2(%ecx), %ecx
        imull   $-1, %eax
        leal    1(%edx), %edx
        jmp     .L107
.L108:
        movsd   %xmm1, 8(%esp)
        fldl    8(%esp)
        movl    4(%esp), %ebx
        addl    $28, %esp
        ret
.L110:  .long       0x0, 0x40100000
main:
        subl    $28, %esp
        leal    32(%esp), %eax
        movl    %eax, 12(%esp)
        leal    __stringlit_1, %edx
        movl    %edx, 0(%esp)
        call    printf
        leal    __stringlit_2, %eax
        leal    24(%esp), %edx
        movl    %edx, 4(%esp)
        movl    %eax, 0(%esp)
        call    __isoc99_scanf
        movl    24(%esp), %ecx
        movl    %ecx, 0(%esp)
        call    pi_f
        fstpl   16(%esp)
        movsd   16(%esp), %xmm1
        leal    __stringlit_3, %eax
        movsd   %xmm1, 4(%esp)
        movl    %eax, 0(%esp)
        call    printf
        xorl    %eax, %eax
        addl    $28, %esp
        ret
```
