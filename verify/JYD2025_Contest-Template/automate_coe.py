import sys
import os

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
        i_32 = i & 0xFFFFFFFF
        s1 = (13 * i_32) & 0xFFFFFFFF
        res1 = riscv_rem(i_32, 7) & 0xFFFFFFFF
        res2 = riscv_div(i_32, -3) & 0xFFFFFFFF
        val = (s1 + res1 + res2) & 0xFFFFFFFF
        total_sum = (total_sum + val) & 0xFFFFFFFF
    return total_sum & 0xFFFFFFFF

def get_imm_parts(val):
    # Standard RISC-V immediate generation for LUI + ADDI
    lower = val & 0xFFF
    if lower & 0x800:
        lower -= 0x1000
        upper = (val >> 12) + 1
    else:
        upper = (val >> 12)
    return upper & 0xFFFFF, lower & 0xFFF

def encode_lui(rd, imm):
    return (imm << 12) | (rd << 7) | 0x37

def encode_addi(rd, rs1, imm):
    return (imm << 20) | (rs1 << 15) | (0 << 12) | (rd << 7) | 0x13

def patch_coe(coe_path, N):
    if not os.path.exists(coe_path):
        print(f"Error: {coe_path} not found")
        return

    checksum = simulate_benchmark(N)
    print(f"Loop Count: {N}, Calculated Checksum: {hex(checksum)}")

    with open(coe_path, 'r') as f:
        lines = f.readlines()

    # Loop Count (N) at lines 345, 346 (offsets 344, 345 0-indexed)
    u_n, l_n = get_imm_parts(N)
    lines[344] = f"{encode_lui(15, u_n):08x},\n"
    lines[345] = f"{encode_addi(15, 15, l_n):08x},\n"

    # Checksum at lines 352, 353 (offsets 351, 352 0-indexed)
    u_c, l_c = get_imm_parts(checksum)
    lines[351] = f"{encode_lui(15, u_c):08x},\n"
    lines[352] = f"{encode_addi(15, 15, l_c):08x},\n"

    with open(coe_path, 'w') as f:
        f.writelines(lines)
    print(f"Successfully patched {coe_path}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python automate_coe.py <N> [coe_path]")
    else:
        n_val = int(sys.argv[1])
        path = sys.argv[2] if len(sys.argv) > 2 else "irom.coe"
        patch_coe(path, n_val)
