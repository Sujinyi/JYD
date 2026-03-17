import argparse
from pathlib import Path


LOOP_LUI_IDX = 342
LOOP_ADDI_IDX = 343
LOOP_STORE_IDX = 344
LOOP_LOAD_IDX = 345

ORIGINAL_LOOP_LUI = 0x000007B7
ORIGINAL_LOOP_STORE = 0xFEF42623
ORIGINAL_LOOP_LOAD = 0xFEC42503


def get_imm_parts(val):
    lower = val & 0xFFF
    if lower & 0x800:
        lower -= 0x1000
        upper = (val >> 12) + 1
    else:
        upper = val >> 12
    return upper & 0xFFFFF, lower & 0xFFF


def encode_lui(rd, imm):
    return (imm << 12) | (rd << 7) | 0x37


def encode_addi(rd, rs1, imm):
    return (imm << 20) | (rs1 << 15) | (0 << 12) | (rd << 7) | 0x13


def parse_coe_entries(text):
    lines = text.splitlines()
    start = None
    for idx, line in enumerate(lines):
        if "memory_initialization_vector" in line:
            start = idx + 1
            break

    if start is None:
        raise ValueError("Invalid COE: missing memory_initialization_vector")

    entries = []
    for line in lines[start:]:
        stripped = line.strip()
        if not stripped:
            continue
        stripped = stripped.rstrip(",;")
        if stripped:
            entries.append(stripped)
        if line.strip().endswith(";"):
            break

    if not entries:
        raise ValueError("Invalid COE: no initialization entries found")

    return entries


def unpack_instructions(entries):
    max_hex_len = max(len(entry) for entry in entries)
    word_width = 64 if max_hex_len > 8 else 32
    instructions = []

    for entry in entries:
        value = int(entry, 16)
        if word_width == 64:
            instructions.append(value & 0xFFFFFFFF)
            instructions.append((value >> 32) & 0xFFFFFFFF)
        else:
            instructions.append(value & 0xFFFFFFFF)

    return instructions, word_width


def pack_entries(instructions, word_width):
    if word_width == 32:
        return [f"{inst & 0xFFFFFFFF:08x}" for inst in instructions]

    if word_width != 64:
        raise ValueError(f"Unsupported word width: {word_width}")

    packed = []
    for idx in range(0, len(instructions), 2):
        low_inst = instructions[idx] & 0xFFFFFFFF
        high_inst = instructions[idx + 1] & 0xFFFFFFFF if idx + 1 < len(instructions) else 0
        packed.append(f"{((high_inst << 32) | low_inst):016x}")
    return packed


def write_coe(path, entries):
    lines = [
        "memory_initialization_radix=16;",
        "memory_initialization_vector=",
    ]

    for idx, entry in enumerate(entries):
        suffix = ";" if idx == len(entries) - 1 else ","
        lines.append(f"{entry}{suffix}")

    Path(path).write_text("\n".join(lines) + "\n")


def patch_coe(coe_path, loop_count, word_width):
    path = Path(coe_path)
    if not path.exists():
        raise FileNotFoundError(f"{coe_path} not found")

    print(f"Loop Count: {loop_count}")

    entries = parse_coe_entries(path.read_text())
    instructions, detected_width = unpack_instructions(entries)

    target_width = word_width if word_width is not None else detected_width

    # The current benchmark template materializes the loop bound with:
    #   0x558: lui  a5, upper(loop_count)
    #   0x55c: addi a5, a5, lower(loop_count)
    #   0x560: sw   a5, -0x14(s0)
    #   0x564: lw   a0, -0x14(s0)
    # Keep the surrounding store/load intact and only patch the bound.
    upper_n, lower_n = get_imm_parts(loop_count)
    instructions[LOOP_LUI_IDX] = encode_lui(15, upper_n)
    instructions[LOOP_ADDI_IDX] = encode_addi(15, 15, lower_n)
    instructions[LOOP_STORE_IDX] = ORIGINAL_LOOP_STORE
    instructions[LOOP_LOAD_IDX] = ORIGINAL_LOOP_LOAD

    packed_entries = pack_entries(instructions, target_width)
    write_coe(path, packed_entries)

    print(
        f"Patched {coe_path} using {target_width}-bit words "
        f"(detected source width: {detected_width}-bit)"
    )


def main():
    parser = argparse.ArgumentParser(
        description="Patch loop count/checksum in a RISC-V COE file and repack to 32/64-bit words."
    )
    parser.add_argument("loop_count", type=int, help="Benchmark loop count")
    parser.add_argument("coe_path", nargs="?", default="irom.coe", help="Path to target COE file")
    parser.add_argument(
        "--word-width",
        type=int,
        choices=(32, 64),
        default=64,
        help="Output COE word width. Defaults to 64 for the current dual-issue IROM.",
    )
    args = parser.parse_args()

    patch_coe(args.coe_path, args.loop_count, args.word_width)


if __name__ == "__main__":
    main()
