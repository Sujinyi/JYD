# DCache research findings

## 2026-07-17 EX-valid BPU bitstream task findings

- The project already contains an older repaired BPU update wiring and an older generated bitstream, according to the existing progress log.
- The newly verified regression fix additionally requires gating `Hazard.mispredicted` with `have_inst_ex`; the older project record predates that discovery.
- The existing planning files and project runs are preserved and will be updated in place.
- `pipeline7_RAS.xpr` actively references `core_src/BPU.sv`, `core_src/CPU.sv`, and `core_src/Hazard.sv`.
- Target `BPU.sv` already byte-matches the verified source, and target `CPU.sv` already has all seven real EX-stage BPU update connections.
- The complete semantic delta from the verified source is only two edits: connect `have_inst_ex` at the CPU's Hazard instance, and add/gate that input in `Hazard.sv`.
- No Vivado process is active. Existing `top.bit` is from 16:07:06 and will be replaced only by the normal implementation flow.
- The matching tool is available at `E:\Vivado25\2025.2.1\Vivado\bin\vivado.bat`.
- After the edit, target `CPU.sv`, `Hazard.sv`, and `BPU.sv` byte-match the Verilator-verified source. Static search finds no obsolete implicit `bpu_*` update nets.
- Existing generated run Tcl files are present. Prior run logs show `synth_design completed successfully` and `write_bitstream completed successfully`; direct generated Tcl remains the fallback if project-run orchestration crashes.
- The generated `synth_1/top.tcl` reads the active project RTL, constraints, IP checkpoints, runs `synth_design`, and writes `synth_1/top.dcp`. The generated `impl_1/top.tcl` consumes that DCP and runs through `write_bitstream -force top.bit`.
- Use the generated Tcl scripts directly from their run directories to avoid the previously observed project-controller crash after a valid synthesis DCP was produced.
- Direct synthesis is active as Vivado PID 47032. A separate pre-existing Vivado PID 50080 started at 16:56:44; it is not owned by this task and will not be stopped or controlled.
- Fresh synthesis completed at 17:18:46 with 0 errors and 0 critical warnings. Vivado generated a new `synth_1/top.dcp`; no project-controller crash occurred in the direct Tcl flow.
- Fresh synthesis log contains no BPU implicit-net, undriven-net, or 1-bit-to-32-bit BPU update-port warnings.
- Implementation/bitstream generation is active as task-owned Vivado PID 32288, launched hidden through cmd PID 12344. The unrelated pre-existing PID 50080 remains untouched.
- Implementation progressed through placement into post-placement physical optimization. Current estimated timing is not closed (`WNS=-1.198 ns`, `TNS=-862.892 ns`), but the flow remains healthy with no fatal errors.
- Routing completed with estimated setup `WNS=-0.867 ns`, `TNS=-713.588 ns`; hold timing is clean (`WHS=+0.077 ns`, `THS=0`). Vivado issued the expected timing critical warning.
- Pre-bitstream DRC completed with 0 errors. `write_bitstream` is actively creating the bitmap.
- `write_bitstream` completed successfully at 17:22:46. Fresh artifact is `pipeline7_RAS.runs/impl_1/top.bit`, 11,443,730 bytes.
- Final verification: synthesis errors 0, implementation errors 0, pre-bitstream DRC errors 0. The single implementation critical warning is the setup timing failure.
- Final routed timing at the active 200 MHz CPU clock is WNS -0.861 ns / TNS -706.221 ns across 1396 failing endpoints. Hold is clean at WHS +0.078 ns / THS 0.

Findings will be recorded here as the supplied documentation, local references, and current RTL are inspected.

## 2026-07-17 fresh IROMv2 BPU A/B findings

- `D:\jyd20260525\jyd2026` contains both `withMext` and `withoutMext` IROMv2/DRAM COE pairs.
- Verified the COE conversion method in memory against the existing BIN files: parse 32-bit hexadecimal words, serialize each word little-endian, put IROM at offset `0`, zero-fill to `0x0010_0000`, then put DRAM at `0x0010_0000`.
- Reconstructed bytes exactly match every existing separate and combined BIN: `withMext` is 8864 B IROM + 56 B DRAM; `withoutMext` is 7688 B IROM + 48 B DRAM.
- CECS defaults to single issue (`DUAL_ISSUE ?= 0`) from `IP/mycpu`; its DPI hooks and all performance counters must remain.
- Most pipeline-register/basic-datapath modules already match Vivado semantically. Material differences are concentrated in `CPU.sv`, `BPU.sv`, and CECS-only instrumentation.
- Vivado BPU exposes the IF1 prediction directly. CECS adds an IF2 response interface and update-kind inputs. Functional prediction/update behavior should follow Vivado while retaining CECS-only instrumentation.
- The old bad Vivado wiring left BPU update payload/RAS inputs effectively undriven while `update_en` stayed connected. Reproduce that deterministically by explicitly tying only those payload inputs low, rather than depending on implicit nets/X behavior.
- A stale CECS run using `withMext.irom-v2.combined.bin` was found and terminated. Its result is invalid and will not be reused.
- CECS maps the image from `CONFIG_MBASE = 0x8000_0000`; therefore combined-file offset `0x0010_0000` maps to DRAM address `0x8010_0000`, matching the Vivado map.
- IROMv2 ends in the self-loop instruction `jal zero, 0` at image offset `0x14`, i.e. PC `0x8000_0014`. The old script default `0x8000_0010` cannot stop this workload and explains the stale long-running simulation.
- Use `--loop-halt-pc=0x80000014 --loop-halt-commits=32` for both A/B runs, then require identical architectural terminal state and commit count before comparing IPC/accuracy.

## Current CPU context

- Repository has no `.git` metadata; design history/commits cannot be inspected.
- Pipeline is `IF1 -> IF2 -> ID -> EX -> LS1 -> LS2 -> WB`.
- CPU data interface is a fixed-latency, non-handshaked bundle: `bus_addr`, `bus_wdata`, `bus_wen[3:0]`, `bus_rdata`.
- `bus_addr` and stores are issued from LS1. Read data is consumed combinationally in LS2 and registered into WB.
- Hazard logic imposes two load-use stall cycles using `stall_by_load_use` plus the registered `stall_by_load_use_r`.
- A real blocking cache will need request-valid/ready or an equivalent `cache_stall/cache_done` contract; the existing interface cannot represent a variable-length miss safely.
- MMIO is decoded in the bridge at `0xFFFF_Fxxx`; it must bypass the cache and remain strongly ordered.
- Source hierarchy is `peripheral/student_top.sv -> CPU + memory/peripheral interconnect`; this is the likely integration point.

## Repository observations/errors

- `git status` and `git log` failed because the workspace is not a Git repository.

## Memory map and timing target

- Active hierarchy instantiates the DRAM BRAM inside `peripheral/perip_bridge.sv`; therefore a cache can be inserted either between CPU and bridge (preferred for clean MMIO bypass) or inside the bridge only on the DRAM branch.
- DRAM range is `0x8010_0000..0x8013_FFFF` (256 KiB). MMIO starts at `0x8020_0000` and includes switches, keys, seven-segment display, LEDs, and a counter.
- The current DRAM is a single-port 32-bit byte-write BRAM with read latency 1. The bridge registers the address for return-data selection.
- The Vivado project references the `pll_1` IP, whose CPU clock request is 260 MHz (about 3.846 ns), while another unused/local PLL variant is 100 MHz. Cache timing must be evaluated against the active 260 MHz clock.
- Existing trace testbench observes only WB architectural writes. It is useful for regression but insufficient for cache verification; directed cache hit/miss/write/eviction tests are needed.

## Evidence from the chat screenshots

High-confidence facts:

- The other design originally had seven pipeline stages and deliberately pipelined memory/BRAM by two cycles for timing; the author reports 250 MHz and about 0.75 IPC in that version.
- The author explicitly states the uncached load-use penalty was three stalls while a DCache hit cost one stall. Thus the throughput gain is primarily bypassing a slow/pipelined backing-memory path on hits.
- The later five-stage redesign moved request launch forward to EX and accepted the synchronous BRAM response in MEM. That alone explains a conventional one-bubble load-use timing.
- The author first wanted zero-stall load-use but abandoned it because timing failed.

Lower-confidence/future ideas, not proven as the already-working core mechanism:

- Storing operands and immediate values in a small buffer and returning data on a match was described as a newly conceived experiment ("刚刚想到，去做做看"). Another participant called it a prefetcher. It should not be treated as evidence of the measured implementation.
- "I already have two DCache" and "add a hash in front of DCache" appear later as brief statements with no diagram or timing. They could mean an L0/L1 hierarchy, two banks/ways, or a hashed/skewed lookup. Hashing cannot itself reduce hit latency; it can reduce conflict misses or select a small hot-data structure.
- Because the core is single-issue, two DCache banks do not by themselves raise requests per cycle. Their likely benefit is hit rate, capacity, or hiding miss latency, unless the implementation also supports non-blocking accesses.

Most defensible reconstruction:

- Fast path: a small cache close to the core returns a hit in one pipeline lookup and bypasses the two-cycle backing BRAM/DRAM route.
- Slow path: a miss freezes/replays the memory instruction, reads backing DRAM, refills the cache, and resumes; chat estimates indicate at least five cycles.
- The IPC improvement comes from `high hit rate x (slow-path cycles avoided)`, not from the word "cache" or hashing alone.

## Current timing reality

- The routed 260 MHz report does not meet timing: WNS is -1.646 ns, TNS is -1246.901 ns, with 1702 failing endpoints.
- The worst path is not DRAM; it is a 14-level control/forwarding/flush path from WB state into ID/EX clock-enable logic, with 5.218 ns data delay against a 3.846 ns period. Route delay dominates (4.147 ns).
- Adding an unregistered hash/tag/LUT lookup into existing global hazard/control cones would worsen Fmax. A fast L0 cache needs a local registered hit path and a simple stall response; existing global control timing should be fixed separately.

## Course documentation baseline and likely match to the group design

- The CECS DCache is explicitly a **two-stage, BRAM-based, two-way cache**: stage 1 computes the effective address and directly drives Tag/Valid/Data BRAM; stage 2 receives BRAM outputs, checks hit, aligns data, or launches miss handling.
- Its configuration is 16 sets, 16-byte lines, two ways. It has a Request Buffer, Return Buffer, write-back buffer, miss-address buffer, main miss/refill FSM, and a separate dirty write-back FSM.
- This directly matches the chat statement that the later design moved memory-request launch to EX and let MEM accept the synchronous BRAM return. It is stronger evidence than the LUT-L0 hypothesis.
- The CODH design also uses parallel Tag BRAM and Data BRAM. A cache hit returns in one cache access cycle; associativity may increase mux delay, but parallel lookup avoids a second tag-then-data cycle.
- Both course designs use write-back + write-allocate. Store hits modify only the cache and dirty bit, keeping slow backing-memory writes off the common path; dirty data is written back only on eviction.
- Line refill exploits spatial locality: the CODH example line is 4 words (128 bits), while the CECS DCache line is 16 bytes (also 4 words).
- Blocking miss handling stalls the pipeline until optional dirty eviction, line fetch, refill, and replay complete. This explains the chat's five-or-more-cycle miss while preserving one-cycle hit handling.
- The important throughput distinction: independent cache hits can be accepted every cycle without globally stalling the pipeline; only an immediate load-use dependency needs its one bubble. This is the likely source of the reported high IPC.
- The CECS AXI page explains why caches matter there: backing DRAM/AXI is variable and slow, while the cache presents a simple BRAM-like one-cycle hit path and only invokes the handshake bridge on misses.

## Assessment of the LUT-L0 hypothesis

- A tiny LUT/FF L0 is plausible as a later optimization, but the supplied course material and chat timing more directly support a BRAM Tag/Data DCache with early EX launch.
- In the current project, backing "DRAM" is already a read-latency-1 on-chip BRAM. Adding another ordinary BRAM cache in front will not inherently improve IPC; it helps only if it bypasses the current late LS/WB path, physically shortens routing, or the backing memory is changed to a slower interface.
- A tiny LUT L0 would be justified only after profiling shows high temporal locality and after the basic cache/retiming path is working. It must not be conflated with the already-demonstrated mechanism.

## Local DCache source inventory — first pass

- `CECS-pipeline-AXI-main/DCache.sv` is a completed/integrated version of the CECS two-way, two-stage BRAM DCache. `CPU.sv` drives its address directly with `alu_result_ex`; load/store request bits also come directly from EX.
- The corresponding CPU has one LS stage and WB. Its Hazard module uses one conventional load-use bubble, while `dcache_miss` stalls PC and every pipeline register during miss handling.
- Data and tag storage are two arrays/ways (`mem_rdata[2]`, two tag BRAMs). This likely explains at least some references to "two DCache": there are two ways/data banks, not necessarily a separate LUT L0 hierarchy.
- Common hit path in the completed source is: EX address -> parallel two-way Data/Tag BRAM -> valid+tag compare -> way/data select -> read alignment in LS -> WB.
- `cache/dcache.v` is a teaching/TODO variant with an explicit IDLE/LOOKUP/MISS/REFILL/WAIT_WRITE state organization and hit counters. It is less useful for direct reuse than the completed CECS integrated source.
- The course implementation broadcasts a combinational `dcache_miss` into global pipeline stall controls. That is functionally simple but should be treated as a timing risk at 260 MHz, especially given the current design's already-failing high-fanout control paths.

## Completed CECS DCache details relevant to IPC/Fmax

- Default size is 512 B: 16 sets x 2 ways x 16 B/line. Each line contains four 32-bit words.
- A Request Buffer pipelines the current address/control while the next EX address is already driving both ways' Tag/Data read addresses. On a hit, `req_buf_we=1` accepts the next request, so hit throughput is one request per cycle.
- Tag and Data reads are parallel across both ways. Valid bits are read in a matching registered stage. Hit comparison, way selection, word selection, and load alignment occur after BRAM output.
- The RAM wrappers have independent registered read address and write address/enable paths, allowing the lookup read stream to continue while a prior store-hit/refill writes a way. This is important for one-request-per-cycle throughput.
- Stores use write-back: a store hit updates the selected cache line and dirty table, not backing memory. A separate write-back buffer/FSM sends dirty victims only during replacement.
- The local source tree contains no implementation of `hash`, L0, prefetch, victim cache, MSHR, hit-under-miss, or load-value prediction. Those chat remarks were not part of the supplied working baseline.
- `Cache.md` is a broad integration note rather than an authoritative implementation; the primary files remain `CECS-pipeline-AXI-main/DCache.sv`, its RAM wrappers, CPU integration, and Hazard logic.

## PDF findings — the actual throughput tricks

- The 10-page PDF visually confirms the central trick: cache RAM **read address comes directly from the current pipeline/EX request**, while its **write address comes from the one-cycle-delayed Request Buffer**. This exploits separate BRAM read/write address paths so the cache can read the next request while finishing the previous hit/store.
- The PDF explicitly says the read address is supplied one cycle early so BRAM data appears next cycle without stalling the pipeline. This is exactly the group's later "request launch moved to EX; MEM receives synchronous BRAM response" statement.
- On a miss, returned words are assembled in a Return Buffer. The requested word is forwarded directly from that buffer to the pipeline instead of refilling the cache and then rereading it; this saves a post-refill cycle (critical-word/return-buffer bypass).
- The two-way design reads both Data and Tag ways in parallel, then compares/selects after BRAM. This trades some compare/mux logic for a lower miss rate while preserving a single BRAM lookup stage.
- Main miss/refill and dirty write-back are separate FSMs. With independent AXI read/write channels, dirty victim write-back can overlap the new line read, reducing dirty-miss service time.
- The PDF highlights integration hazards: cache must observe pipeline stall so return data is not lost; flush during outstanding requests must be handled; and multiple stall/flush priorities must be defined.

Most useful PDF pages:

- Pages 2-3: two-way datapath, Request Buffer, separate read/write addresses, early BRAM lookup, Return Buffer bypass.
- Pages 5-7: DCache write masks, dirty table, write-back buffer, miss address, and write-back FSM.
- Page 8: pipeline stall/flush integration hazards and testing guidance.

## Reference ranking for the high-IPC goal

1. `CECS-pipeline-AXI-main/CPU.sv` around the DCache instance: best proof of direct EX launch and pipeline alignment.
2. `CECS-pipeline-AXI-main/DCache.sv`: best working reference for pipelined hits, two ways, dirty/write-back, refill bypass, and separate FSMs.
3. `CECS-pipeline-AXI-main/BRAM_bytewrite.sv` and `BRAM_common.sv`: understand the independent read/write address behavior that enables one lookup per cycle.
4. PDF pages 2-3 and 5-8: clearest architecture diagrams and explanation of why the request buffer and early BRAM read improve throughput.
5. `CECS-pipeline-AXI-main/Hazard.sv`: useful for functional stall wiring, but its combinational global miss fanout is an anti-pattern to reassess for 260 MHz.
6. `lab7/src/simple_cache.v`: good educational baseline for address split and direct-mapped miss/refill, but not the preferred high-Fmax datapath because it uses wide-line mux/merge logic and a simplified memory model.
7. `cache/dcache.v`: incomplete/TODO teaching source; not worth prioritizing over the completed DCache.
8. AXI arbiter and simulated `mem.v`: only important when the backing store becomes an AXI/slow-memory interface; they do not explain hit-path IPC.

## PDF tooling note

- Bundled `pdftoppm.cmd` pointed to a missing path. Resolved by invoking the bundled Poppler executable under `native/poppler/Library/bin` directly; rendered pages 2-8 and visually checked pages 2, 3, 5, and 8.

## CPU-core consistency audit — initial inventory

- The Windows Vivado project has no Git metadata. `pipeline7_RAS.xpr` explicitly compiles the files in `core_src/`, including `CPU.sv`, `Hazard.sv`, `Regfile.sv`, `BPU.sv`, and all six pipeline-register modules. Generated copies under `.runs/.gen/.srcs` are not the authoritative RTL unless separately referenced.
- `cdp-tests` is a Git repository but its current CPU files under `mySoC/` are untracked. Its modified Makefile selects `mySoC/*.sv`, so source identity must be checked against the working tree rather than Git HEAD.
- `CECS-Lab` contains several parallel CPU snapshots (`mycpu`, `CSR`, `TAGE`, `pipeline7-RAS`, `pipeline6_if2`, etc.) and a heavily modified working tree. The active simulator selection must be derived from the Makefile/build scripts; merely comparing every `CPU.sv` would be misleading.
- Both WSL repositories contain substantial unrelated modifications and generated test/build files, so this audit will report only core-source and build-selection discrepancies.

## Audit tooling issue

- A first WSL command was mangled by PowerShell/Bash nested quoting and redirected Makefile text into an accidental workspace file named `%ln && printf n--`. The file was immediately identified and removed with `apply_patch`; no RTL or test environment file was changed.

## Build-selection and hash results

- `cdp-tests/Makefile` compiles all `mySoC/*.sv` except `config.sv/config_inst.sv`. After normalizing CRLF/LF, 22 of the 26 Windows core files match exactly. `CPU.sv` and `SegReg_LS1_LS2.sv` appeared byte-different only because of line endings and are semantically identical.
- The only real `cdp-tests` source differences are `config.sv`, `CSR.sv`, and `MulDiv.sv`. They concern optional bit-manipulation parameters, missing `mscratch`, and a shorter multiply latency/reset-style change; they are not register-fanout changes. The Makefile excludes `config.sv`, but modules include it textually, so its definitions still affect compilation.
- CECS-Lab defaults to `simulator/IP/mycpu`, but the existing `simulator/build/VCPU` was most recently built with `DUAL_ISSUE=1` from `IP/dual_issue_cecs` plus an external biriscv tree. Therefore the binary presently on disk is not the seven-stage Windows core.
- CECS-Lab reuses the same output name (`build/VCPU`) for single- and dual-issue builds. Because build dependencies do not encode the mode and the current binary is newer than the `mycpu` sources, switching back to default mode without cleaning can incorrectly run the stale dual-issue executable.
- Against CECS-Lab's default `IP/mycpu`, several core files differ semantically; this copy requires a focused diff. Files identical after line-ending normalization include Branch, MulDiv, muxes, NPC/PC, Read/Write control, EX/LS pipeline registers, and some other stage registers.

## Fanout search — preliminary conclusion

- No core RTL in Windows, `cdp-tests/mySoC`, or CECS-Lab's single-issue snapshots contains `max_fanout`, `fanout_limit`, `KEEP`, `DONT_TOUCH`, explicit `_dup/_copy/replica` signals, or a register-duplication directive. Thus there is currently no evidence of a hand-authored fanout attribute or replicated core register.
- Windows implementation did run ordinary `phys_opt_design`. Its log reports only two one-time replications, both under the peripheral counter (`bridge_inst/counter_inst`), not inside the CPU core. The earlier placement fanout pass identified candidates but made no very-high-fanout optimization.
- Generated `dont_touch.xdc` files only preserve PLL/BRAM IP hierarchy; they do not constrain or duplicate CPU registers.
- The Windows timing report's high-fanout problem therefore remains a structural control cone (especially the global pipeline-enable path), not a confirmed missing copy of a manually duplicated register.

## CECS-Lab `IP/mycpu` difference classification

- Much of `CPU.sv`'s size increase is simulator-only instrumentation: 30+ 64-bit performance counters, shadow bimodal/gshare tables, load/store hazard statistics, DPI-visible commit data, and integrated DPI IROM/DRAM wrappers. This code should not be copied into synthesis RTL and is unrelated to Fmax.
- `Hazard.sv` has formatting-only differences; its two-cycle load-use stall and global stall/flush topology match the Windows core.
- `Regfile.sv` differs only by the DPI `set_gpr_ptr()` hook and formatting. The RF array, synchronous write, two asynchronous reads, and WB read-after-write bypass are structurally the same; no RF-bank/register replication or fanout split is present.
- Pipeline-register modules are identical except comments/line endings. In particular, no duplicated enable/flush register was found.
- Minor non-fanout functional differences include stricter M-extension decode in CECS (`funct7 == 7'b0000001` versus Windows `funct7[0]`), explicit 32-bit zero extension for SLT results, and simulation DPI hooks. The major real architectural divergence is in BPU/CPU prediction plumbing, which is being examined separately.

## User-selected comparison boundary

- Treat Windows Vivado `core_src` as the source of truth.
- Exclude CECS performance counters, shadow-predictor statistics, DPI hooks, and integrated simulation memories from the core-logic comparison.
- Exclude Vivado-generated `_rep` cells from the RTL-change conclusion. Although synthesis replicated several IF2/ID instruction bits automatically, there is no corresponding RTL edit.

## Confirmed RTL register-stage change

- Windows `MulDiv.sv` adds `mul_a_r`, `mul_b_r`, and a `MUL_EXEC` state. It captures multiply operands first and evaluates the multiplier one cycle later. The main register block also uses synchronous rather than asynchronous reset.
- `cdp-tests` still has the older direct `mul_prod_r <= a*b` implementation, so its multiply latency/timing partition does not match Vivado.
- CECS-Lab `IP/mycpu/MulDiv.sv` matches the Vivado version after line-ending normalization. This is the strongest match for the user's recollection of a real source-level register/timing change.

## BPU integration discrepancy

- In the authoritative Windows `CPU.sv`, BPU update inputs at lines 102-108 are connected to implicit, undriven `bpu_*` nets instead of the already-computed `pc_ex`, `jump`, `jump_target`, `is_ret_ex`, `ras_push_ex`, `ras_pop_ex`, and `ras_push_addr_ex` signals.
- Vivado synthesis explicitly reports each symbol as undeclared, the 32-bit ports as receiving 1-bit nets, and all update-side nets as undriven. This is a real core-logic discrepancy, not CECS instrumentation.
- CECS `mycpu` wires these BPU inputs to the computed EX-stage signals. `cdp-tests` is identical to Windows and therefore retains the Windows behavior.

## Final source-level consistency conclusion

- There is no source-level Regfile fanout modification. The remembered real register/timing edit is almost certainly the pipelined multiply change in `MulDiv.sv`.
- `cdp-tests` matches the authoritative Vivado pipeline/control RTL but is stale in MulDiv and CSR. It also shares Vivado's current BPU update-wiring problem.
- CECS `IP/mycpu` matches the authoritative MulDiv and most pipeline/control logic after ignoring instrumentation, but intentionally/correctly differs in BPU wiring and has minor Decode/width cleanups.
- Consequently neither WSL environment is an exact behavioral mirror of the authoritative Windows core today.
- CECS's current `build/VCPU` was built in dual-issue mode; a default run can reuse it without rebuilding. Source comparison and executable-under-test must therefore be treated separately.

## BPU repair and synchronization status

- `core_src/CPU.sv` now declares `btb_hit_if1` and connects the BPU update inputs to the EX-stage `pc_ex`, `jump`, `jump_target`, return classification, and RAS push/pop signals already computed by the CPU.
- `cdp-tests/mySoC/{CPU,MulDiv,CSR,config}.sv` now byte-match the corresponding Vivado files. The cdp Verilator build completed successfully after synchronization.
- CECS source was deliberately not overwritten: its single-issue BPU bindings already match the repaired behavior, its MulDiv/CSR behavior already matches, and overwriting its wrapper would damage the user-requested counter/DPI interface.
- The matching tool is installed at `E:\Vivado25\2025.2.1\Vivado\bin\vivado.bat`. A project-driven run hit `EXCEPTION_ACCESS_VIOLATION` only after `synth_design` had completed with 0 errors and emitted `synth_1/top.dcp`. Running the generated implementation Tcl directly from that DCP completed bit generation successfully.
- Fresh artifact: `pipeline7_RAS.runs/impl_1/top.bit`, 11,443,730 bytes, timestamp 2026-07-17 14:53:18. It is a valid produced bitstream, but it is not timing-closed: routed WNS -2.143 ns, TNS -3249.380 ns; hold WNS +0.067 ns.

## Fresh IROMv2 A/B task inventory

- Input root `D:\jyd20260525\jyd2026` contains matching `withMext` and `withoutMext` IROMv2/DRAM COE pairs. The withMext COEs are `withMext/demo/irom-v2.coe` and `withMext/demo/dram.coe`.
- Old generated binaries exist, including `withMext.irom-v2.bin` (8864 bytes), `withMext.dram.bin` (56 bytes), and a combined image of 1,048,632 bytes. They are references only; the fresh task will regenerate from COE and verify byte order/content.
- No COE-to-BIN conversion tool was found by the first targeted filename search, so the conversion behavior must be reconstructed and checked against the old binaries rather than assumed.
- An aborted earlier CECS run remained active as WSL PIDs 1625/1631 for 27 minutes. Both exact processes were terminated before this fresh task; no CECS source was changed by that cleanup.
