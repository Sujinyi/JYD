#!/bin/bash
# Random-difftest stress: generate N random tests, run DUT vs spike comparison
# Usage: run_random.sh [count] [--m]
COUNT=${1:-20}
MFLAG=""
[ "$2" = "--m" ] && MFLAG="--m"
MARCH=rv32i_zifencei
[ -n "$MFLAG" ] && MARCH=rv32im_zifencei
mkdir -p build/random
FAIL=0
for seed in $(seq 1 "$COUNT"); do
    s=build/random/rand_$seed.S
    elf=build/random/rand_$seed.elf
    python3 tests/gen_random.py "$seed" 400 $MFLAG > "$s"
    riscv64-elf-gcc -march=$MARCH -mabi=ilp32 -static -nostdlib -nostartfiles \
      -mcmodel=medany -Itests/env -Iriscv-tests/isa/macros/scalar \
      -Ttests/env/link.ld "$s" -o "$elf" || { echo "rand_$seed BUILD FAIL"; FAIL=1; continue; }
    riscv64-elf-objcopy -O binary "$elf" "${elf%.elf}.bin"
    if ! python3 spike_diff.py --elf "$elf" > /dev/null 2>&1; then
        echo "rand_$seed DIFF FAIL"
        python3 spike_diff.py --elf "$elf" 2>&1 | tail -12
        FAIL=1
    fi
done
[ $FAIL -eq 0 ] && echo "random stress: $COUNT/$COUNT OK" || echo "random stress: FAILURES"
exit $FAIL
