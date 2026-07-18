#!/usr/bin/env python3
"""coe2mem: convert a Xilinx .coe (radix 16) to a $readmemh .mem file.
Word content is preserved exactly; only the container format changes."""
import re
import sys


def coe_words(path):
    text = open(path).read()
    m = re.search(r"memory_initialization_radix\s*=\s*(\d+)\s*;", text)
    radix = int(m.group(1)) if m else 16
    m = re.search(r"memory_initialization_vector\s*=\s*(.*?);", text, re.S)
    if not m:
        sys.exit(f"{path}: no memory_initialization_vector")
    toks = [t.strip() for t in re.split(r"[,\s]+", m.group(1)) if t.strip()]
    return [int(t, radix) for t in toks]


def main():
    if len(sys.argv) != 4:
        sys.exit("usage: coe2mem.py <in.coe> <out.mem> <depth>")
    words = coe_words(sys.argv[1])
    depth = int(sys.argv[3])
    if len(words) > depth:
        sys.exit(f"{sys.argv[1]}: {len(words)} words > depth {depth}")
    with open(sys.argv[2], "w") as f:
        for w in words:
            f.write(f"{w:08x}\n")
        for _ in range(depth - len(words)):
            f.write("00000000\n")
    print(f"{sys.argv[2]}: {len(words)} words from coe, padded to {depth}")


if __name__ == "__main__":
    main()
