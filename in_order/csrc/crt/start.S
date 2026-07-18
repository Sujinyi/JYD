.section .text.init
.globl _start
_start:
    la   sp, __stack_top
    la   a0, __bss_start
    la   a1, __bss_end
1:  bgeu a0, a1, 2f
    sw   zero, 0(a0)
    addi a0, a0, 4
    j    1b
2:  call main
    la   t0, tohost
    beqz a0, 3f
    slli a0, a0, 1
    ori  a0, a0, 1
    sw   a0, 0(t0)      # fail: (code<<1)|1
1:  j    1b
3:  li   t1, 1
    sw   t1, 0(t0)      # pass
1:  j    1b
