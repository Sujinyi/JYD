# 简单的RISC-V测试程序
# 测试基本算术、内存访问和分支指令

.section .text
.globl _start

_start:
    # 测试立即数加法
    li x1, 10          # x1 = 10
    li x2, 20          # x2 = 20

    # 测试寄存器加法
    add x3, x1, x2     # x3 = 30

    # 测试减法
    sub x4, x2, x1     # x4 = 10

    # 测试逻辑运算
    and x5, x1, x2     # x5 = 0
    or  x6, x1, x2     # x6 = 30
    xor x7, x1, x2     # x7 = 30

    # 测试shift
    slli x8, x1, 2     # x8 = 40
    srli x9, x2, 1     # x9 = 10

    # 测试内存存储
    li x10, 0x00000000  # 数据存储基地址
    sw  x3, 0(x10)     # mem[0] = 30
    sw  x1, 4(x10)     # mem[4] = 10

    # 测试内存加载
    lw  x11, 0(x10)    # x11 = 30
    lw  x12, 4(x10)    # x12 = 10

    # 测试分支
    beq x1, x1, branch_target  # 应该跳转
    li  x13, 99        # 不应该执行

branch_target:
    li  x13, 100       # x13 = 100

    # 测试jal
    jal x14, func_call # 跳转到函数

    # 测试jalr返回
    li  x15, 200       # x15 = 200

    # 无限循环结束
end:
    j end

func_call:
    li  x16, 50        # x16 = 50
    jr  x14            # 返回
