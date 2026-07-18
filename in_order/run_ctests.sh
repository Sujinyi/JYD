#!/bin/bash
# Run all C tests: DUT execution (with console output) + spike commit-log difftest
PASS=0; FAIL=0; FAILED=""
for elf in build/csrc/*.elf; do
    name=$(basename "$elf" .elf)
    bin="build/csrc/$name.bin"
    tohost=$(riscv64-elf-nm "$elf" | awk '$3=="tohost"{print $1}')
    putc=$(riscv64-elf-nm "$elf" | awk '$3=="putchar_mmio"{print $1}')
    echo "=== $name ==="
    if ./obj_dir/Vtop +bin="$bin" +tohost="$tohost" +putc="$putc" +max=2000000; then
        PASS=$((PASS+1))
    else
        FAIL=$((FAIL+1)); FAILED="$FAILED $name"
    fi
done
echo "=================================="
echo "PASS: $PASS  FAIL: $FAIL"
[ -n "$FAILED" ] && echo "Failed:$FAILED"
exit $FAIL
