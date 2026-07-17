# IROMv2 BPU A/B Simulation Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Generate the RV32IM IROMv2+DRAM image, synchronize an isolated CECS single-issue core with Vivado's BPU behavior, and measure correct versus bad BPU wiring with all other variables fixed.

**Architecture:** Two isolated CECS source snapshots are derived from one instrumented baseline. Both retain CECS DPI/counters and use Vivado's functional BPU; the bad snapshot differs only by explicit zero ties on the historical bad update payload. Separate object directories and raw logs prevent stale-build or cross-run contamination.

**Tech Stack:** SystemVerilog, Verilator, GNU Make, Python 3, CECS-Lab simulator under Ubuntu-22.04, PowerShell/WSL orchestration.

---

The relevant directories are not Git repositories, so commit steps are unavailable. Preserve provenance with SHA-256 manifests, recursive diffs, isolated source/build directories, and raw run logs.

### Task 1: Freeze inputs and establish isolated paths

**Files:**
- Read: `D:/jyd20260525/jyd2026/withMext/demo/irom-v2.coe`
- Read: `D:/jyd20260525/jyd2026/withMext/demo/dram.coe`
- Read: `C:/Users/21186/Desktop/test/BTFN/RV32IM/core_src/*.sv`
- Read: `/home/kazusa/CECS-Lab/simulator/IP/mycpu/*`
- Create: `/home/kazusa/CECS-Lab/simulator/artifacts/iromv2_bpu_ab/manifest.txt`

**Step 1:** Record source/image hashes and confirm `DUAL_ISSUE=0` is the selected Makefile path.

**Step 2:** Assert that no stale `make run` or `VCPU` process is active before building.

**Step 3:** Reserve these isolated paths: `IP/mycpu_iromv2_bpu_ok`, `IP/mycpu_iromv2_bpu_bad`, `build_iromv2_bpu_ok`, and `build_iromv2_bpu_bad`.

### Task 2: Add and validate the COE-pair converter

**Files:**
- Create: `/home/kazusa/CECS-Lab/simulator/script/convert_coe_pair.py`
- Create: `/home/kazusa/CECS-Lab/simulator/testcases/app/iromv2_withMext.irom.bin`
- Create: `/home/kazusa/CECS-Lab/simulator/testcases/app/iromv2_withMext.dram.bin`
- Create: `/home/kazusa/CECS-Lab/simulator/testcases/app/iromv2_withMext.combined.bin`

**Step 1:** Before writing output, parse both COEs in memory and assert 32-bit word width, valid radix 16, and no malformed tokens.

**Step 2:** Emit each word with `int(token, 16).to_bytes(4, "little")`.

**Step 3:** Build the combined image as `irom + bytes(0x100000 - len(irom)) + dram`; fail if IROM exceeds the DRAM offset.

**Step 4:** Run the converter and verify expected sizes: IROM 8864 bytes, DRAM 56 bytes, combined 1,048,632 bytes.

**Step 5:** Compare the new bytes with the old reference images and require exact equality, then record new SHA-256 values. The old files remain read-only and are not used for simulation.

### Task 3: Create the Vivado-aligned CECS baseline

**Files:**
- Create from baseline: `/home/kazusa/CECS-Lab/simulator/IP/mycpu_iromv2_bpu_ok/*`
- Modify: `/home/kazusa/CECS-Lab/simulator/IP/mycpu_iromv2_bpu_ok/BPU.sv`
- Modify: `/home/kazusa/CECS-Lab/simulator/IP/mycpu_iromv2_bpu_ok/CPU.sv`

**Step 1:** Copy current `IP/mycpu` to the OK snapshot without touching the original.

**Step 2:** Replace the CECS BPU module with the active Vivado `core_src/BPU.sv` behavior.

**Step 3:** Adapt only the BPU instance/prediction bookkeeping in CECS `CPU.sv` to the Vivado interface. Keep CECS public counter ports, DPI memory wrappers, shadow predictors, and counter always blocks byte-for-byte where possible.

**Step 4:** Align `perf_pred_taken_cnt` and `perf_btb_hit_cnt` to valid IF1 predictions by registering the Vivado outputs for one stage; do not change EX-stage misprediction definitions.

**Step 5:** Diff the resulting CPU against the original and confirm all changes are confined to prediction declarations, BPU instantiation, and prediction-only counter alignment.

### Task 4: Create the deterministic bad-wiring variant

**Files:**
- Create from OK snapshot: `/home/kazusa/CECS-Lab/simulator/IP/mycpu_iromv2_bpu_bad/*`
- Modify: `/home/kazusa/CECS-Lab/simulator/IP/mycpu_iromv2_bpu_bad/CPU.sv`

**Step 1:** Copy the completed OK snapshot to the BAD snapshot.

**Step 2:** Keep `.update_en(bpu_update_en)` but replace only these instance inputs with constants: `update_pc`, `actual_taken`, `actual_target`, `update_is_ret`, `ras_push`, `ras_pop`, and `ras_push_addr`.

**Step 3:** Recursively diff OK against BAD and require that the diff contains only those explicit port bindings.

### Task 5: Lint and build both single-issue variants

**Files:**
- Create: `/home/kazusa/CECS-Lab/simulator/build_iromv2_bpu_ok/*`
- Create: `/home/kazusa/CECS-Lab/simulator/build_iromv2_bpu_bad/*`

**Step 1:** Run Verilator lint for each snapshot and inspect all warnings involving width, implicit nets, latches, and unused BPU ports.

**Step 2:** Build OK with command-line `VSRC_DIR` and `OBJ_DIR` overrides and `DUAL_ISSUE=0`.

**Step 3:** Build BAD with the corresponding isolated overrides.

**Step 4:** Verify executable timestamps and source manifests, and confirm neither command used `IP/dual_issue_cecs` or normal `build/VCPU`.

### Task 6: Execute the controlled A/B workload

**Files:**
- Create: `/home/kazusa/CECS-Lab/simulator/artifacts/iromv2_bpu_ab/bpu_ok.log`
- Create: `/home/kazusa/CECS-Lab/simulator/artifacts/iromv2_bpu_ab/bpu_bad.log`

**Step 1:** Run each isolated executable with the same new combined image and arguments `-b --no-diff --loop-halt-pc=0x80000014 --loop-halt-commits=32`.

**Step 2:** Save complete stdout/stderr separately and require one `SIM_RESULT` and one `PERF_RESULT` per run.

**Step 3:** If either run exceeds a bounded wall-clock limit, stop it and diagnose instead of leaving a stale process.

### Task 7: Validate and calculate the comparison

**Files:**
- Create: `/home/kazusa/CECS-Lab/simulator/artifacts/iromv2_bpu_ab/summary.txt`

**Step 1:** Parse both result lines and require identical stop PC, `a0`, `t6`, and commit count.

**Step 2:** Calculate IPC and overall/conditional/JALR/return prediction accuracy from raw counters, guarding zero denominators.

**Step 3:** Calculate absolute and percentage cycle reduction and IPC uplift.

**Step 4:** Record image/source hashes, exact commands, raw counters, derived metrics, and the OK-vs-BAD source diff proof in `summary.txt`.

**Step 5:** Report the comparison only if all invariants pass; otherwise report the failed invariant and do not present misleading IPC conclusions.

