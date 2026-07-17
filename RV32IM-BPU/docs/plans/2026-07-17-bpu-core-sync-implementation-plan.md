# BPU Core Synchronization Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Repair the authoritative BPU update wiring, synchronize it into the two single-issue simulation cores, and regenerate the Vivado bitstream without touching CECS performance counters or dual-issue sources.

**Architecture:** `core_src` is canonical. The cdp core is source-compatible and receives a direct module sync. CECS retains its simulator wrapper and counter block; its BPU interface/instance is adapted to the canonical update behavior.

**Tech Stack:** SystemVerilog, Verilator in Ubuntu-22.04, Vivado project `pipeline7_RAS`.

---

### Task 1: Repair the canonical BPU bindings

**Files:**
- Modify: `core_src/CPU.sv:99-108`

**Step 1:** Bind BPU update inputs to `pc_ex`, `jump`, `jump_target`, `is_ret_ex`, `ras_push_ex`, `ras_pop_ex`, and `ras_push_addr_ex`.

**Step 2:** Use Vivado synthesis/implementation as the automated integration gate. Board-level regression is explicitly deferred to the user; do not add a synthetic forced-internal-state test.

### Task 2: Synchronize cdp single-issue RTL

**Files:**
- Modify: `/home/kazusa/cdp-tests/mySoC/CPU.sv`, `BPU.sv`, `MulDiv.sv`, `CSR.sv`, `config.sv`, and matching common core modules

**Step 1:** Copy canonical common `.sv` modules excluding simulation wrapper files.

**Step 2:** Run the existing cdp build only as a compilation check.

Expected: no undeclared BPU-update warnings.

### Task 3: Synchronize CECS single-issue core while retaining counters

**Files:**
- Modify: `/home/kazusa/CECS-Lab/simulator/IP/mycpu/BPU.sv`, `Decode.sv`, and common core modules as appropriate
- Preserve: `/home/kazusa/CECS-Lab/simulator/IP/mycpu/CPU.sv` counter declarations, counter always block, DPI memory wrappers, and public counter outputs

**Step 1:** Keep CECS's existing correct BPU update bindings and counter plumbing.

**Step 2:** Synchronize the canonical MulDiv/CSR/common pipeline modules, retaining CECS's DPI-only additions.

**Step 3:** Clean/rebuild only the CECS single-issue `build/VCPU` with `DUAL_ISSUE=0`.

Expected: build uses `IP/mycpu`, not the dual-issue tree, and counters remain present.

### Task 4: Regenerate the FPGA bitstream

**Files:**
- Modify generated Vivado run outputs only

**Step 1:** Start `impl_1` through bitstream generation for `pipeline7_RAS`.

**Step 2:** Check synthesis logs for the previous undeclared/undriven BPU-update warnings.

Expected: no BPU-update implicit-net or width-mismatch warnings; provide the generated `.bit` path for board regression.
