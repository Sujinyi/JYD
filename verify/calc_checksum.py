def riscv_div(n, d):
    if d == 0: return -1
    return int(n / d)

def riscv_rem(n, d):
    if d == 0: return n
    q = riscv_div(n, d)
    return (n - q * d)

def simulate_benchmark(N):
    total_sum = 0
    for i in range(N):
        # From disassembly:
        # a5 = i
        # s1 = 13 * i (calculated via slli 1, add, slli 2, add)
        # res1 = i % 7 (func 0x800013ac is signed rem)
        # res2 = i // -3 (func 0x80001328 is signed div)
        
        i_32 = i & 0xFFFFFFFF
        s1 = (13 * i_32) & 0xFFFFFFFF
        res1 = riscv_rem(i_32, 7) & 0xFFFFFFFF
        res2 = riscv_div(i_32, -3) & 0xFFFFFFFF
        
        val = (s1 + res1 + res2) & 0xFFFFFFFF
        total_sum = (total_sum + val) & 0xFFFFFFFF
        
    return total_sum

if __name__ == '__main__':
    orig_n = 100000
    orig_sum = simulate_benchmark(orig_n)
    print(f"For N={orig_n}, sum = {hex(orig_sum)} (Expected: 0xbef16570)")
    
    new_n = 2
    new_sum = simulate_benchmark(new_n)
    print(f"For N={new_n}, sum = {hex(new_sum)}")
