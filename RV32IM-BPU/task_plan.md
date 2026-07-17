# DCache throughput-technique analysis plan

## 2026-07-17 fresh task: repair EX-valid BPU recovery and generate bitstream

### Goal
Apply the Verilator-proven EX-valid misprediction fix to this Vivado project, verify that all BPU update inputs are explicitly connected, then run synthesis, implementation, and bitstream generation.

### Phases
- [complete] Inventory active RTL, project source selection, existing runs, and bitstream state
- [complete] Compare CPU/BPU/Hazard against the verified `CICC2026/RV32IM/core_src` source
- [complete] Apply only the BPU wiring and EX-valid Hazard changes required by the verified fix
- [complete] Run source/static checks and Vivado synthesis
- [complete] Run implementation and bitstream generation
- [complete] Verify artifact timestamp/size, DRC status, and routed timing

### Constraints
- Modify the specified Vivado project in place; preserve IP, constraints, COE contents, and unrelated RTL.
- Do not reset or delete the project/runs manually.
- Treat `core_src` files referenced by `pipeline7_RAS.xpr` as authoritative.
- A bitstream may be generated even if timing is not closed, but timing violations must be reported explicitly.

### Errors encountered
- The first PowerShell hash-comparison command piped directly from a `foreach` statement and failed to parse with `An empty pipe element is not allowed`. No files were changed; collect rows before formatting on the retry.
- A diagnostic `rg` call used a Windows wildcard path (`vivado*.log`) that `rg` rejected. The required run logs were still read explicitly; future searches use resolved filenames or directory globs.
- The foreground synthesis launcher exceeded the shell tool's short timeout and returned code 124, but Vivado PID 47032 remained active and continued synthesis normally. Do not relaunch; monitor that exact PID and `synth_1/runme.log` instead.

## 2026-07-17 fresh task: IROMv2 BPU A/B simulation

### Goal
Regenerate a CECS-loadable image from the selected IROMv2 COE and its matching DRAM COE, align the CECS single-issue functional core with the active Vivado core while preserving CECS performance counters/DPI memory wrappers, then compare correct versus intentionally disconnected BPU update wiring with the image and all other variables held identical.

### Phases
- [in_progress] Read-only inventory of COE format, memory map, active Vivado RTL, CECS build selection, counters, and existing run scripts
- [pending] Confirm the selected withMext/withoutMext image and exact stopping condition
- [pending] Present A/B design alternatives and obtain user approval
- [pending] Record approved design and implementation plan
- [pending] Convert and verify IROMv2 + DRAM image
- [pending] Align CECS single-issue functional core without deleting counters/DPI hooks
- [pending] Build and run correct/disconnected BPU variants
- [pending] Verify identical committed workload and report IPC/prediction accuracy

### Invariants
- Vivado `core_src` is the functional source of truth.
- CECS performance counters, DPI hooks, and single-issue simulator interface remain intact.
- Correct and incorrect runs differ only in BPU update wiring; same image, build flags, stopping rule, and counter definitions.
- No dual-issue source or stale dual-issue executable may enter the comparison.

### Errors encountered
- A broad Windows/WSL recursive memory-map and source comparison timed out after 24 seconds with no output. Split subsequent inspection into targeted local and WSL commands.
- The first read-only PowerShell COE parsing command used an invalid pipeline placement. It was rerun by collecting objects before formatting; no files were written.
- A WSL audit command lost its nested shell quoting around regular expressions. It was rerun through standard input (`bash -s`) and completed; no files were written.

## Goal
Reverse-engineer the core techniques by which the group member's cache increased throughput, using the chat evidence, supplied course material, local references, and the current CPU as a timing comparison. Ordinary Lab-5 cache integration is only a baseline. No RTL implementation before the design is reviewed and approved.

## Phases
- [completed] Inspect current CPU/memory interfaces, hazards, and repository state
- [completed] Review chat clues, both supplied lab pages, and local DCache materials for throughput mechanisms
- [completed] Distinguish ordinary blocking-cache effects from early lookup, banking/hash, prefetch, and non-blocking mechanisms
- [in_progress] Present the most likely reconstructed timing, confidence levels, and evidence
- [pending] Record the approved design and prepare an implementation plan

## Constraints and open questions
- Preserve correctness for loads, stores, byte enables, MMIO, flushes, and cache misses.
- Prefer a design that can close timing near the current 250 MHz target.
- User clarified that the immediate goal is understanding the other designer's throughput-increasing core technique, not a generic cache implementation tutorial.
- User prioritizes high program IPC while requiring that Fmax not degrade.

## Errors encountered
- `session-catchup.py` returned exit code 1 without output; no existing planning files were found, so initialized fresh planning files.
- `git status` / `git log` failed because this Vivado workspace has no `.git` directory; continued with direct source inspection.
- Bundled `pdftoppm.cmd` resolved to a nonexistent Poppler path. Used the actual bundled `native/poppler/Library/bin/pdftoppm.exe` and successfully rendered the PDF.

## Current audit: CPU core version consistency

### Goal
Compare the active CPU-core RTL in the Windows Vivado project against the copies actually used by `/home/kazusa/cdp-tests` and `/home/kazusa/CECS-Lab`, with special attention to manual fanout changes versus synthesis/implementation-time register replication.

### Phases
- [completed] Locate the authoritative/compiled RTL and Git state in all three environments
- [completed] Compare core source hashes and semantic diffs (CPU, Hazard, pipeline registers, BPU, register file, memory interface)
- [completed] Audit RTL/XDC/Tcl/Vivado reports for fanout attributes, duplicated registers, and high-fanout nets
- [completed] Determine whether both WSL simulations exercise the exact current Windows core
- [completed] Report every meaningful discrepancy and a safe synchronization workflow

### Constraints
- Read-only audit: do not modify RTL, project settings, or either simulation environment.
- IROM and DRAM capacities are fixed and are not design variables in this audit.
- The Windows Vivado `core_src` is authoritative. Ignore CECS performance counters/DPI-only instrumentation and ignore synthesis-generated register replicas when deciding whether RTL core logic matches.
