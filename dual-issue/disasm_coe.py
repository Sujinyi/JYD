from __future__ import annotations

import argparse
from pathlib import Path

from capstone import CS_ARCH_RISCV, CS_MODE_RISCV32, Cs


RESET_PC = 0x8000_0000


def load_words_from_coe(path: Path) -> list[int]:
    text = path.read_text(encoding="ascii")
    raw_lines = [line.strip() for line in text.splitlines()]

    data_started = False
    words: list[int] = []
    for line in raw_lines:
        if not line:
            continue
        if line.startswith("memory_initialization_vector"):
            data_started = True
            continue
        if not data_started:
            continue

        token = line.rstrip(",;").strip()
        if not token:
            continue
        words.append(int(token, 16))

    return words


def disasm_inst(md: Cs, inst_word: int, pc: int) -> str:
    inst_bytes = inst_word.to_bytes(4, byteorder="little", signed=False)
    decoded = list(md.disasm(inst_bytes, pc))
    if not decoded:
        return ".word 0x%08x" % inst_word

    insn = decoded[0]
    if insn.op_str:
        return f"{insn.mnemonic}\t{insn.op_str}"
    return insn.mnemonic


def main() -> None:
    parser = argparse.ArgumentParser(description="Disassemble a 64-bit IROM COE file.")
    parser.add_argument("coe", type=Path, help="Path to COE file")
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=None,
        help="Optional output asm path",
    )
    parser.add_argument(
        "--base-pc",
        type=lambda value: int(value, 0),
        default=RESET_PC,
        help="Instruction memory base PC, default 0x80000000",
    )
    args = parser.parse_args()

    words64 = load_words_from_coe(args.coe)
    md = Cs(CS_ARCH_RISCV, CS_MODE_RISCV32)

    out_lines = [f"; source: {args.coe}"]
    for idx, word64 in enumerate(words64):
        base_pc = args.base_pc + idx * 8
        lo = word64 & 0xFFFF_FFFF
        hi = (word64 >> 32) & 0xFFFF_FFFF

        for offset, inst_word in ((0, lo), (4, hi)):
            pc = base_pc + offset
            rel = pc - args.base_pc
            asm = disasm_inst(md, inst_word, pc)
            out_lines.append(f"{rel:08x}: {inst_word:08x}    {asm}")

    output_text = "\n".join(out_lines) + "\n"
    if args.output is None:
        print(output_text, end="")
    else:
        args.output.write_text(output_text, encoding="utf-8")


if __name__ == "__main__":
    main()
