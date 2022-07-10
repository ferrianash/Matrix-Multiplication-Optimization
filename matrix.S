# file name: matrix.S
.text
    .type matrix, @function
    .globl matrix
matrix:
    testq   %rcx, %rcx      # if n <= 0 then exit
    jle     EXIT

    pushq   %rbx            # push callee-saved registers
    pushq   %rbp
    pushq   %r12
    pushq   %r13
    pushq   %r14
    pushq   %r15
    subq    $512, %rsp

    # prepare works #
    xorq    %r15, %r15
    movq    %r15, 32(%rsp)          # rsp[32] = 0
    movq    %r15, 40(%rsp)          # rsp[40] = 0
    leaq    (,%rcx, 8), %r15        # 8*n

    # call malloc #
    movq    %rdi, 0(%rsp)           # a
    movq    %rsi, 8(%rsp)           # b
    movq    %rdx, 16(%rsp)          # c
    movq    %rcx, 24(%rsp)          # n

    movq    %rcx, %rdi              # tmp = t8n
    imulq   %r15, %rdi              # tmp *= n
    call    malloc@PLT              # b2 = malloc(tmp)

    # retrans matrix b into b2 #
    movq    8(%rsp), %rbx           # rbx = b
    movq    24(%rsp), %rdx          # rdx = n
    leaq    (, %r15, 4), %rcx       # t32n = t8n * 4
    movq    %rax, %r8               # b2in0 = b2
    leaq    (%r8, %r15), %r9        # b2in1 = b2in0 + t8n
    leaq    (%r9, %r15), %r10       # b2in2 = b2in1 + t8n
    leaq    (%r10, %r15), %r11      # b2in3 = b2in2 + t8n
    xorq    %rsi, %rsi              # i = 0
L1:    
    leaq    (%rbx, %rsi, 8), %r12   # bjni = b + i * 8
    xorq    %r13, %r13              # t8j = 0
    xorq    %rdi, %rdi              # j = 0
L2:
    movq    (%r12), %rbp            # tmp = (bjni)
    movq    %rbp, (%r8, %r13)       # (b2in0, t8j) = tmp
    movq    8(%r12), %rbp           # tmp = 8(bjni)
    movq    %rbp, (%r9, %r13)       # (b2in1, t8j) = tmp
    movq    16(%r12), %rbp          # tmp = 16(bjni)
    movq    %rbp, (%r10, %r13)      # (b2in2, t8j) = tmp
    movq    24(%r12), %rbp          # tmp = 24(bjni)
    movq    %rbp, (%r11, %r13)      # (b2in3, t8j) = tmp

    addq    %r15, %r12              # bjni += t8n
    addq    $8, %r13                # t8j += 8
    incq    %rdi                    # j++
    cmpq    %rdx, %rdi
    jl      L2                      # if j < n goto L2
    
    addq    %rcx, %r8               # b2in0 += t32n
    addq    %rcx, %r9               # b2in1 += t32n
    addq    %rcx, %r10              # b2in2 += t32n
    addq    %rcx, %r11              # b2in3 += t32n
    addq    $4, %rsi                # i += 4
    cmpq    %rdx, %rsi
    jl      L1                      # if i < n goto L1
    movq    %rax, 48(%rsp)          # b2


    # multiply matrixs #
    xorq    %rsi, %rsi              # i = 0
    movq    $4, %r13
    cmpq    %r13, %rdx
    jl      L10                     # if n < 4 goto L10

    movq    %rdx, %rax
    xorq    %rdx, %rdx
    movq    $2, %r13
    idiv    %r13
    testq   %rdx, %rdx
    jne     L10                     # if n / 2 != 0 goto L6

    movq    0(%rsp), %rax           # a
    movq    48(%rsp), %rbx          # b2
    movq    16(%rsp), %rcx          # c
    movq    24(%rsp), %rdx          # n
    xorq    %rsi, %rsi              # i = 0
L3:
    xorq    %rdi, %rdi              # j = 0
L4:
    xorpd   %xmm0, %xmm0            # xmm0 = 0
    xorpd   %xmm1, %xmm1            # xmm1 = 0
    xorpd   %xmm2, %xmm2            # xmm2 = 0
    xorpd   %xmm3, %xmm3            # xmm3 = 0

    movq    %r15, %r8               # ain0 = t8n
    imulq   %rsi, %r8               # ain0 *= i
    addq    %rax, %r8               # ain0 += a
    leaq    (%r8, %r15), %r9        # ain1 = ain0 + 8*n
    leaq    (%r9, %r15), %r10       # ain2 = ain1 + 8*n
    leaq    (%r10, %r15), %r11      # ain3 = ain2 + 8*n

    movq    %r15, %r12              # b2jn = t8n
    imulq   %rdi, %r12              # b2jn *= j
    addq    %rbx, %r12              # b2jn += b2

    xorq    %r13, %r13              # t8k = 0
    xorq    %rbp, %rbp              # k = 0
L5:
    movapd  (%r8, %r13), %xmm4      # xmm4 = (ain0, t8k)
    movapd  (%r9, %r13), %xmm5      # xmm5 = (ain1, t8k)
    movapd  (%r10, %r13), %xmm6     # xmm6 = (ain2, t8k)
    movapd  (%r11, %r13), %xmm7     # xmm7 = (ain3, t8k)

    movapd  (%r12, %r13), %xmm8     # xmm8 = (b2jn, t8k)

    mulpd   %xmm8, %xmm4            # xmm4 *= xmm8
    mulpd   %xmm8, %xmm5            # xmm5 *= xmm8
    mulpd   %xmm8, %xmm6            # xmm6 *= xmm8
    mulpd   %xmm8, %xmm7            # xmm7 *= xmm8

    addpd   %xmm4, %xmm0            # xmm0 += xmm4
    addpd   %xmm5, %xmm1            # xmm1 += xmm5
    addpd   %xmm6, %xmm2            # xmm2 += xmm6
    addpd   %xmm7, %xmm3            # xmm3 += xmm7

    addq    $16, %r13               # t8k += 16
    addq    $2, %rbp                # k += 2
    cmpq    %rdx, %rbp
    jl      L5                      # if k < n goto L5

    leaq    (%rcx, %rdi, 8), %r13   # cj = c + j * 8
    movq    %r15, %r8               # cin0j = t8n
    imulq   %rsi, %r8               # cin0j *= i
    addq    %r13, %r8               # cin0j += cj
    leaq    (%r8, %r15), %r9        # cin1j = cin0j + t8n
    leaq    (%r9, %r15), %r10       # cin2j = cin1j + t8n
    leaq    (%r10, %r15), %r11      # cin3j = cin2j + t8n
    
    movapd      %xmm0, %xmm4
    unpckhpd    %xmm4, %xmm4
    addsd       %xmm4, %xmm0        # xmm0.lo += xmm0.hi
    movapd      %xmm1, %xmm5
    unpckhpd    %xmm5, %xmm5
    addsd       %xmm5, %xmm1        # xmm1.lo += xmm1.hi
    movapd      %xmm2, %xmm6
    unpckhpd    %xmm6, %xmm6
    addsd       %xmm6, %xmm2        # xmm2.lo += xmm2.hi
    movapd      %xmm3, %xmm7
    unpckhpd    %xmm7, %xmm7
    addsd       %xmm7, %xmm3        # xmm3.lo += xmm3.hi

    movsd   %xmm0, (%r8)            # (cin0j) = xmm0.lo
    movsd   %xmm1, (%r9)            # (cin1j) = xmm1.lo
    movsd   %xmm2, (%r10)           # (cin2j) = xmm2.lo
    movsd   %xmm3, (%r11)           # (cin3j) = xmm3.lo

    incq    %rdi                    # j++
    cmpq    %rdx, %rdi
    jl      L4                      # if j < n goto L4

    addq    $4, %rsi                # i += 4
    leaq    4(%rsi), %r13           # tmp = i + 4
    cmpq    %rdx, %r13
    jle     L3                      # if tmp <= n goto L3

L10:
    movq    0(%rsp), %rax           # a
    movq    48(%rsp), %rbx          # b2
    movq    16(%rsp), %rcx          # c
    movq    24(%rsp), %rdx          # n
L6: # the rest part of mul #
    cmpq    %rdx, %rsi
    jge     L7                      # if i >= n goto L7

    xorq    %rdi, %rdi              # j = 0
L8:
    xorpd   %xmm2, %xmm2            # xmm2 = 0
    movq    %r15, %r9               # ain = t8n
    imulq   %rsi, %r9               # ain *= i
    addq    %rax, %r9               # ain += a
    movq    %r15, %r10              # b2jn = t8n
    imulq   %rdi, %r10              # b2jn *= j
    addq    %rbx, %r10              # b2jn += b
    xorq    %r11, %r11              # t8k = 0
    xorq    %rbp, %rbp              # k = 0
L9:
    movsd   (%r10, %r11), %xmm0     # xmm0.lo = (b2jn, t8k)
    movsd   (%r9, %r11), %xmm1      # xmm1.lo = (ain, t8k)
    mulsd   %xmm0, %xmm1            # xmm1.lo *= xmm0.lo
    addsd   %xmm1, %xmm2            # xmm2.lo += xmm1.lo
    addq    $8, %r11                # t8k += 8
    incq    %rbp                    # k++
    cmpq    %rdx, %rbp
    jl      L9                      # if k < n goto L9

    leaq    (%rcx, %rdi, 8), %r12   # cj = c + j * 8
    movq    %r15, %r13              # t8in = t8n
    imulq   %rsi, %r13              # t8in *= i
    movsd   %xmm2, (%r12, %r13)     # (cj, t8in) = xmm2.lo
    
    incq    %rdi                    # j++
    cmpq    %rdx, %rdi
    jl      L8                      # if j < n goto L8

    incq    %rsi                    # i++
    jmp     L6                      # goto L6

L7:
    movq    %rbx, %rdi
    call    free@PLT                # free(b2)

    addq    $512, %rsp
    popq    %r15            # pop callee-saved registers
    popq    %r14
    popq    %r13
    popq    %r12
    popq    %rbp
    popq    %rbx
EXIT:
    ret