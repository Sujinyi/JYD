# Genesys 2 比赛平台上板记录

**板卡**: Digilent Genesys 2 (Kintex-7 XC7K325T-2FFG900C)
**测试程序**: `jyd_rv32im/coe/withM48/`（官方 48 秒级比赛镜像，内容未改动）
**计时基准**: 50MHz 独立时钟域 ms 计数器（与 CPU 频率无关，纯拼墙钟时间）
**判定**: 数码管 SEG = `[RV32I 两位][M 一位][ms 五位]`，全过 LED = `0x078b7323`

## 上板记录表

| # | 日期 | git commit / tag | 测试程序 | CPU 频率 | WNS | I/M/trap | 实测用时 | 仿真预测 | 备注 |
|---|---|---|---|---|---|---|---|---|---|
| 1 | 2026-07-17 | `fa2b5ed` / `race-11947ms` | withM48 irom-new | 200 MHz | +0.068 | 37/37 · 8/8 · pass | **11.947s** | 11947ms（逐位一致） | 首次上板，平台移植基线 |
| 2 | 2026-07-17 | `e31007a` / `race-v2-2904ms` | withMext irom-v2 | 200 MHz | +0.068* | 37/37 · 8/8 · pass | **2.904s** | 2904ms（逐位一致） | 换官方 demo v2 镜像，仅换 mem 重编译（*时序未重查，同 RTL） |
| 3 | 2026-07-18 | 待上板 / `race-v2-1828ms-220mhz` | withMext irom-v2 | **220 MHz** | -0.249（Default） | 待测 | 待测 | **402.2M cyc ÷ 220MHz ≈ 1828ms** | sf+mul 流水+L0 D$+slot1 双口+8 把时序刀+div 二级捕获；pblock Y3Y4 窗口。WNS 为 Default 口径小幅违例，上板数据先作参考 |
| 4 | 2026-07-18 | 同 RTL，pll 240MHz 版 bit | withMext irom-v2 | **240 MHz** | -0.748（Default，超载 18%） | 37/37 · 8/8 | **1.675s** | 1676ms（402.2M cyc ÷ 240MHz，逐 ms 吻合） | **STA 大幅违例但硅上实测精确通过**——typical 硅+室温裕量远超 slow-corner 模型；上板实测 #3 |

## 参照系

| 设计 | 频率 | withM48 用时 | irom-v2 用时 | 来源 |
|---|---|---|---|---|
| JYD (7 级单发射) | 260 MHz | ~9.4s | 未测 | 推算（2.435G cycles 折算，非同板实测） |
| 本设计 (6 级双发射) | 200 MHz | 11.947s | 2.904s | 上板实测 #1 / #2 |
| 本设计（最终版 sf+mul+L0+双口+级联） | 220 MHz | **~7.05s**（仿真 1.552G cyc） | **~1.83s**（仿真 402.2M cyc） | 仿真换算，待上板；**vs JYD -25%** |
| 本设计（同 RTL，240MHz 实测） | **240 MHz** | **~6.47s**（1.552G cyc 换算） | **1.675s（上板实测）** | irom-v2 实测逐 ms 吻合预测；**vs JYD -31%** |

当前差距 ~27%，主要来自频率差（260 vs 200）。追频或 CPI 优化待做。

## 平台构成（与比赛一致）

- `fpga_race/rtl/`：`top.sv` / `perip_bridge.sv`(+2 行参数透传) / `twin_controller.sv` / `counter.sv` / `display_seg.sv` / `seg7.sv` / `uart.sv` —— JYD RV32IM 原版
- `student_top.sv` 重写：接双发射核；`irom3p.v`（取指对端口 + rodata 读口，16KB）+ `dram.v`（256KB，IP 端口兼容）替代 Vivado IP；`pll.v`（RTL MMCM：200MHz LVDS 差分入 → 50MHz 外设域 + CPU 域）
- 约束 `fpga_race/constrs/race.xdc`：引脚表与 `Genesys_riscv_10s.xdc` 逐脚一致，仅时钟定义适配 RTL MMCM
- 显示：物理数码管扩展板（PMOD JA/JB/JC/JD + XADC 口），无需上位机

## 复现命令

```bash
# mem 生成 + 平台仿真（ms 级精确，1:4 时钟比）
make race-sim && ./obj_dir_race/Vrace

# bitstream（~25 分钟）
vivado -mode batch -source fpga_race/vivado_race.tcl

# 烧录
vivado -mode batch -source fpga/program.tcl \
  -tclargs fpga_race/vivado/race.runs/impl_1/top.bit
```

## 核心规格（记录 #1 时点）

6 级双发射 in-order RV32IM + Zicsr/M-mode trap（mtvec/mepc/mcause/mscratch,
ecall/ebreak/mret），128 项 BTB + agree-gshare 256 + 8 深 RAS，32 位 AGU，
fib CPI 0.838 / crc32 0.81。验证基线：50 riscv-tests + 58 spike difftest +
30 random + 8 ctests 全绿。
