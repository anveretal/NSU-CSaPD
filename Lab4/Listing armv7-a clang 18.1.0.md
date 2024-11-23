# armv7-a clang 18.1.0

```
pi_f:
        push    {r11, lr}
        mov     r11, sp
        sub     sp, sp, #48
        str     r0, [r11, #-4]
        mov     r0, #0
        str     r0, [r11, #-12]
        str     r0, [r11, #-16]
        mov     r1, #1
        str     r1, [r11, #-20]
        str     r1, [sp, #24]
        str     r0, [sp, #20]
        b       .LBB0_1
.LBB0_1:
        ldr     r0, [sp, #20]
        ldr     r1, [r11, #-4]
        cmp     r0, r1
        bge     .LBB0_4
        b       .LBB0_2
.LBB0_2:
        ldr     r0, [r11, #-20]
        bl      __aeabi_i2d
        str     r0, [sp, #4]
        str     r1, [sp, #8]
        ldr     r0, [sp, #24]
        bl      __aeabi_i2d
        mov     r2, r0
        mov     r3, r1
        mov     r0, #0
        mov     r1, #1048576
        orr     r1, r1, #1073741824
        bl      __aeabi_ddiv
        mov     r2, r0
        ldr     r0, [sp, #4]
        mov     r3, r1
        ldr     r1, [sp, #8]
        ldr     r12, [r11, #-16]
        str     r12, [sp, #12]
        ldr     r12, [r11, #-12]
        str     r12, [sp, #16]
        bl      __aeabi_dmul
        ldr     r2, [sp, #12]
        ldr     r3, [sp, #16]
        bl      __aeabi_dadd
        str     r1, [r11, #-12]
        str     r0, [r11, #-16]
        ldr     r0, [sp, #24]
        add     r0, r0, #2
        str     r0, [sp, #24]
        ldr     r0, [r11, #-20]
        rsb     r0, r0, #0
        str     r0, [r11, #-20]
        b       .LBB0_3
.LBB0_3:
        ldr     r0, [sp, #20]
        add     r0, r0, #1
        str     r0, [sp, #20]
        b       .LBB0_1
.LBB0_4:
        ldr     r0, [r11, #-16]
        ldr     r1, [r11, #-12]
        mov     sp, r11
        pop     {r11, lr}
        bx      lr

main:
        push    {r11, lr}
        mov     r11, sp
        sub     sp, sp, #24
        mov     r2, #0
        str     r2, [sp, #4]
        str     r2, [r11, #-4]
        str     r0, [r11, #-8]
        str     r1, [sp, #12]
        ldr     r0, .LCPI1_0
.LPC1_0:
        add     r0, pc, r0
        bl      printf
        ldr     r0, .LCPI1_1
.LPC1_1:
        add     r0, pc, r0
        add     r1, sp, #8
        bl      __isoc99_scanf
        ldr     r0, [sp, #8]
        bl      pi_f
        mov     r2, r0
        mov     r3, r1
        ldr     r0, .LCPI1_2
.LPC1_2:
        add     r0, pc, r0
        bl      printf
        ldr     r0, [sp, #4]
        mov     sp, r11
        pop     {r11, lr}
        bx      lr
.LCPI1_0:
        .long   .L.str-(.LPC1_0+8)
.LCPI1_1:
        .long   .L.str.1-(.LPC1_1+8)
.LCPI1_2:
        .long   .L.str.2-(.LPC1_2+8)

.L.str:
        .asciz  "Input n: "

.L.str.1:
        .asciz  "%d"

.L.str.2:
        .asciz  "Answer: %0.14f\n"
```