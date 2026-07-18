#!/usr/bin/env python3
"""bin -> $readmemh word files: flat (.mem) + even/odd banks (.mem0/.mem1)"""
import sys

binf, memf = sys.argv[1], sys.argv[2]
data = open(binf, "rb").read()
data += b"\x00" * ((4 - len(data) % 4) % 4)
words = [int.from_bytes(data[i:i + 4], "little") for i in range(0, len(data), 4)]
if len(words) % 2:
    words.append(0)
with open(memf, "w") as f:
    f.write("".join(f"{w:08x}\n" for w in words))
with open(memf + "0", "w") as f:
    f.write("".join(f"{w:08x}\n" for w in words[0::2]))
with open(memf + "1", "w") as f:
    f.write("".join(f"{w:08x}\n" for w in words[1::2]))
