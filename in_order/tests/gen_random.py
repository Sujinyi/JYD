#!/usr/bin/env python3
"""Random RV32I(M) instruction sequence generator for difftest stress.
Generates a .S file compatible with tests/env/riscv_test.h flow.
Control flow: only bounded forward branches/jumps -> guaranteed termination.
Usage: gen_random.py <seed> [n_instr] [--m] > out.S
"""
import random
import sys

seed = int(sys.argv[1])
n = int(sys.argv[2]) if len(sys.argv) > 2 and not sys.argv[2].startswith("-") else 300
use_m = "--m" in sys.argv
rng = random.Random(seed)

# x1..x15 general pool; x28 data base; x29 scratch; x30 link reg pool member
REGS = list(range(1, 16))
LINKS = [1, 5, 30]

R_OPS = ["add", "sub", "sll", "srl", "sra", "slt", "sltu", "xor", "or", "and"]
M_OPS = ["mul", "mulh", "mulhsu", "mulhu", "div", "divu", "rem", "remu"]
I_OPS = ["addi", "slti", "sltiu", "xori", "ori", "andi"]
SH_OPS = ["slli", "srli", "srai"]
LOADS = [("lw", 4), ("lh", 2), ("lhu", 2), ("lb", 1), ("lbu", 1)]
STORES = [("sw", 4), ("sh", 2), ("sb", 1)]
BR_OPS = ["beq", "bne", "blt", "bge", "bltu", "bgeu"]

DATA_WORDS = 64
lines = []
label_cnt = 0


def r(): return f"x{rng.choice(REGS)}"


def emit(s): lines.append(f"    {s}")


def rand_imm12(): return rng.randint(-2048, 2047)


def mem_off(size):
    o = rng.randrange(0, DATA_WORDS * 4 - size + 1)
    return o - o % size


ops = (["r"] * 22 + ["i"] * 22 + ["sh"] * 8 + ["lui"] * 4 + ["auipc"] * 2 +
       ["load"] * 12 + ["store"] * 10 + ["br"] * 12 + ["jal"] * 3 + ["jalr"] * 3)
if use_m:
    ops += ["m"] * 18

i = 0
while i < n:
    k = rng.choice(ops)
    if k == "r":
        emit(f"{rng.choice(R_OPS)} {r()}, {r()}, {r()}")
    elif k == "m":
        emit(f"{rng.choice(M_OPS)} {r()}, {r()}, {r()}")
    elif k == "i":
        emit(f"{rng.choice(I_OPS)} {r()}, {r()}, {rand_imm12()}")
    elif k == "sh":
        emit(f"{rng.choice(SH_OPS)} {r()}, {r()}, {rng.randint(0, 31)}")
    elif k == "lui":
        emit(f"lui {r()}, {rng.randint(0, 0xFFFFF)}")
    elif k == "auipc":
        emit(f"auipc {r()}, {rng.randint(0, 0xFFFFF)}")
    elif k == "load":
        op, sz = rng.choice(LOADS)
        emit(f"{op} {r()}, {mem_off(sz)}(x28)")
    elif k == "store":
        op, sz = rng.choice(STORES)
        emit(f"{op} {r()}, {mem_off(sz)}(x28)")
    elif k == "br":
        label_cnt += 1
        # forward branch over 1-4 simple instructions
        skip = rng.randint(1, 4)
        emit(f"{rng.choice(BR_OPS)} {r()}, {r()}, 1000{label_cnt}f")
        for _ in range(skip):
            emit(f"{rng.choice(I_OPS)} {r()}, {r()}, {rand_imm12()}")
            i += 1
        lines.append(f"1000{label_cnt}:")
    elif k == "jal":
        label_cnt += 1
        emit(f"jal x{rng.choice(LINKS)}, 1000{label_cnt}f")
        for _ in range(rng.randint(1, 2)):
            emit(f"{rng.choice(R_OPS)} {r()}, {r()}, {r()}")
            i += 1
        lines.append(f"1000{label_cnt}:")
    elif k == "jalr":
        # jalr to a computed forward address: la scratch, label; jalr
        label_cnt += 1
        emit(f"la x29, 1000{label_cnt}f")
        emit(f"jalr x{rng.choice(LINKS)}, x29, 0")
        lines.append(f"1000{label_cnt}:")
        i += 1
    i += 1

body = "\n".join(lines)

print(f"""// auto-generated random test, seed={seed} n={n} m={use_m}
#include "riscv_test.h"
#include "test_macros.h"

RVTEST_RV32U
RVTEST_CODE_BEGIN

    la x28, rand_data
{chr(10).join('    li x' + str(j) + ', ' + str(rng.randint(-2**31, 2**31 - 1)) for j in range(1, 16))}

{body}

    // fold all registers into x1 so the final state matters
{chr(10).join('    add x1, x1, x' + str(j) for j in range(2, 16))}
    li TESTNUM, 1
    RVTEST_PASS

RVTEST_CODE_END

    .data
RVTEST_DATA_BEGIN
    .align 4
rand_data:
{chr(10).join('    .word ' + str(rng.randint(-2**31, 2**31 - 1)) for _ in range(DATA_WORDS))}
RVTEST_DATA_END
""")
