# IROMv2 BPU Correct-vs-Bad Wiring Design

## Decision

Use the `withMext` IROMv2/DRAM pair because the target core is RV32IM. Treat the active Vivado `core_src` as the functional reference, retain all CECS DPI and performance-counter logic, and run two isolated CECS single-issue builds whose only functional difference is the BPU update wiring.

## Image layout

- Parse each 32-bit hexadecimal COE word and emit its four bytes little-endian.
- Place IROM at combined-image offset `0x0000_0000` (CPU address `0x8000_0000`).
- Zero-fill to offset `0x0010_0000`.
- Place DRAM at offset `0x0010_0000` (CPU address `0x8010_0000`).
- Verify the generated separate and combined images by size, SHA-256, and byte comparison against the previously generated reference only as a conversion oracle. The simulator run must use the newly generated file.

## CECS/Vivado synchronization boundary

- Start both test variants from the same current CECS `IP/mycpu` snapshot.
- Replace the CECS-specific prediction implementation with the active Vivado `BPU.sv` behavior and reproduce the Vivado IF1 prediction/update connections inside the CECS instrumented `CPU.sv`.
- Keep CECS-only top-level performance outputs, DPI IROM/DRAM wrappers, CSR/GPR DPI hooks, shadow predictors, and counter update blocks.
- Keep all non-BPU pipeline, hazard, MulDiv, memory, and decode behavior identical between A and B.
- Do not modify `IP/mycpu`, dual-issue RTL, or the normal `build/VCPU` artifact.

## Controlled A/B variable

`BPU_OK` connects the Vivado EX-stage update payload normally:

- `update_en = is_ctrl_ex`
- `update_pc = pc_ex`
- `actual_taken = jump`
- `actual_target = jump_target`
- RAS update inputs use `is_ret_ex`, `ras_push_ex`, `ras_pop_ex`, and `ras_push_addr_ex`.

`BPU_BAD` preserves the same `update_en` but explicitly ties the old incorrectly connected payload/RAS inputs to zero. This deterministically reproduces the old undriven wiring without simulator X-state dependence. No other source difference is allowed.

## Run and acceptance criteria

- Build both variants fresh with `DUAL_ISSUE=0` into separate object directories.
- Run the same newly generated combined image with `--no-diff` and stop after PC `0x8000_0014` commits 32 consecutive times.
- Require equal terminal PC, architectural register result fields, and committed-instruction count. If these differ, the A/B comparison is invalid.
- Report raw counters plus:
  - IPC = `commit / cycle`
  - overall control accuracy = `1 - mispred / ctrl`
  - conditional accuracy = `1 - cond_mispred / cond`
  - JALR accuracy = `1 - jalr_mispred / jalr`
  - return accuracy = `1 - ret_mispred / ret`
- Report cycle reduction and IPC uplift of `BPU_OK` relative to `BPU_BAD`.

