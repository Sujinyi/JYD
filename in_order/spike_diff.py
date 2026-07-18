#!/usr/bin/env python3
"""Trace-based difftest: DUT commit log vs Spike --log-commits."""
import re
import subprocess
import sys
import glob
import os

SPIKE = "/home/zyp/Desktop/jichuangsai/use_riscv_tests/riscv-isa-sim/build/spike"
ISA = "rv32im"
BASE = 0x80000000
COMMIT_RE = re.compile(
    r"^core\s+\d+: \d 0x([0-9a-f]+) \(0x([0-9a-f]+)\)(?: x\s*(\d+)\s+0x([0-9a-f]+))?"
)


def spike_commits(elf, log):
    subprocess.run(
        [SPIKE, f"--isa={ISA}", "--priv=m", "-m0x80000000:0x400000",
         "--log-commits", "-l", f"--log={log}", elf],
        check=True, capture_output=True)
    out = []
    with open(log) as f:
        for line in f:
            m = COMMIT_RE.match(line)
            if not m:
                continue
            pc = int(m.group(1), 16)
            if pc < BASE:
                continue  # boot ROM
            instr = int(m.group(2), 16)
            rd = int(m.group(3)) if m.group(3) else None
            wdata = int(m.group(4), 16) if m.group(4) else None
            if rd == 0:
                rd, wdata = None, None
            out.append((pc, instr, rd, wdata))
    return out


def dut_commits(bin_path, tohost, log):
    r = subprocess.run(
        ["./obj_dir/Vtop", f"+bin={bin_path}", f"+tohost={tohost:x}",
         "+max=2000000", f"+commitlog={log}"],
        capture_output=True, text=True)
    if "PASS" not in r.stdout:
        print(r.stdout)
        sys.exit(f"DUT did not pass on {bin_path}")
    out = []
    with open(log) as f:
        for line in f:
            t = line.split()
            pc, instr = int(t[0], 16), int(t[1], 16)
            if instr in (0x00000073, 0x00100073):
                continue  # ecall/ebreak trap: spike does not log a commit
            if t[2] == "-":
                out.append((pc, instr, None, None))
            else:
                out.append((pc, instr, int(t[2][1:]), int(t[3], 16)))
    return out


def tohost_addr(elf):
    r = subprocess.run(["riscv64-elf-nm", elf], capture_output=True, text=True)
    for line in r.stdout.splitlines():
        p = line.split()
        if p[-1] == "tohost":
            return int(p[0], 16)
    sys.exit(f"no tohost in {elf}")


def main():
    global ISA
    args = sys.argv[1:]
    if "--isa" in args:
        i = args.index("--isa")
        ISA = args[i + 1]
        args = args[:i] + args[i + 2:]
    if args and args[0] == "--elf":
        elfs = args[1:]
    else:
        elfs = sorted(glob.glob("build/tests/*.elf")) + sorted(glob.glob("build/csrc/*.elf"))
        if args:
            elfs = []
            for nm in args:
                for d in ("build/tests", "build/csrc"):
                    if os.path.exists(f"{d}/{nm}.elf"):
                        elfs.append(f"{d}/{nm}.elf")
                        break
    npass = 0
    for elf in elfs:
        name = os.path.basename(elf)[:-4]
        binp = elf[:-4] + ".bin"
        s = spike_commits(elf, f"/tmp/opencode/spike_{name}.log")
        d = dut_commits(binp, tohost_addr(elf), f"/tmp/opencode/dut_{name}.log")
        n = min(len(s), len(d))
        ok = True
        for i in range(n):
            if s[i] != d[i]:
                print(f"{name}: MISMATCH at commit #{i}")
                for j in range(max(0, i - 3), min(n, i + 2)):
                    def fmt(c):
                        pc, instr, rd, wd = c
                        w = f"x{rd}={wd:08x}" if rd else "-"
                        return f"pc={pc:08x} instr={instr:08x} {w}"
                    print(f"  [{j}] spike: {fmt(s[j])}")
                    print(f"      dut:   {fmt(d[j])}")
                ok = False
                break
        if ok:
            print(f"{name:12s} OK ({n} commits compared)")
            npass += 1
    print("==================================")
    print(f"spike-difftest: {npass}/{len(elfs)} OK")
    sys.exit(0 if npass == len(elfs) else 1)


if __name__ == "__main__":
    main()
