import sys

def emulate_loop(N):
    # s0_minus_14 = 0
    # s0_minus_18 = 0
    # The actual code sets:
    # 0x800004ac:   sw zero, -0x14(s0)
    # 0x800004b0:   sw zero, -0x18(s0)
    var_14 = 0
    var_18 = 0

    # s0_minus_24 receives N
    var_24 = N

    # The loop starts at 0x800004b4
    # j 0x64 -> jumps to 0x80000518
    # 0x80000518:   lw a4, -0x18(s0)
    # 0x8000051c:   lw a5, -0x24(s0)
    # 0x80000520:   blt a4, a5, -0x68 (jumps to 0x800004b8)
    
    # 0x800004b8:
    for i in range(N):
        a4 = var_18
        a5 = a4
        a5 = (a5 << 1) & 0xFFFFFFFF
        a5 = (a5 + a4) & 0xFFFFFFFF
        a5 = (a5 << 2) & 0xFFFFFFFF
        s1 = (a5 + a4) & 0xFFFFFFFF
        
        a5 = var_18
        # a0 = a5
        # jal 0xed0 (func 2) -> at 0x800013ac
        # let's assume it multiplies or something, we need to inspect 0xed0 from 0x4dc which is 0x800013ac
        
        # wait, the jal offsets might be complex. Let me find what 0x800013ac does
        pass

if __name__ == "__main__":
    emulate_loop(2)
