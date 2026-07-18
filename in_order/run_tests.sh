#!/bin/bash
# Run all rv32ui tests through the difftest simulator
PASS=0; FAIL=0; FAILED=""
for elf in build/tests/*.elf; do
    name=$(basename "$elf" .elf)
    bin="build/tests/$name.bin"
    tohost=$(riscv64-elf-nm "$elf" | awk '$3=="tohost"{print $1}')
    out=$(./obj_dir/Vtop +bin="$bin" +tohost="$tohost" +max=500000 2>&1)
    if echo "$out" | grep -q "^PASS"; then
        printf "%-12s %s\n" "$name" "$(echo "$out" | grep '^PASS')"
        PASS=$((PASS+1))
    else
        printf "%-12s FAIL\n" "$name"
        echo "$out" | sed 's/^/    /'
        FAIL=$((FAIL+1)); FAILED="$FAILED $name"
    fi
done
echo "=================================="
echo "PASS: $PASS  FAIL: $FAIL"
[ -n "$FAILED" ] && echo "Failed:$FAILED"
exit $FAIL
