# Vivado-authoritative BPU and simulator synchronization design

## Decision

The Vivado project's `core_src` remains the canonical CPU implementation. First repair its BPU update wiring, then mirror the corrected core into both single-issue simulation environments. Do not touch any dual-issue source or build artifact.

## Scope

- Repair only the BPU update-side port bindings in `core_src/CPU.sv` by connecting the already-computed EX-stage signals.
- Copy the canonical common RTL into `cdp-tests/mySoC`, including the newer pipelined `MulDiv` and CSR implementation.
- Keep CECS's simulation-only `CPU.sv` wrapper, DPI IROM/DRAM, public performance-counter ports, shadow predictors, and all counter logic. Adapt only its core BPU/Decode/common RTL so its behavioral CPU core matches the corrected canonical design.
- Do not alter IROM/DRAM capacities, the CECS dual-issue directory, or performance-counter behavior.

## Verification

The user will perform board-level regression. Avoid a synthetic forced-internal-state test; use Vivado synthesis/implementation and bitstream generation as the automated integration gate.
