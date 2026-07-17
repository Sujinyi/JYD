# withM48

这是严格对标分赛区要求生成的 48 秒级测试。RV32I、RV32M、zicsr/trap 都是真实执行测试，不再硬写通过数；性能测试部分为自定义 8 项。

## 当前文件

- `irom-new.coe`: RV32IM + zicsr/trap + 8 个大规模性能测试
- `dram.coe`: 复制官方 `withMext/dram.coe` 小模板，14 个 word
- `smoke8.dis`: 反汇编
- `smoke8.map`: 链接 map

## 规模

```text
GCC opt     = -O0
PERF_REPEAT = 39
```

单轮校准：

```text
repeat=1 -> 62,445,367 cycles
```

估算：

```text
62,445,367 * 39 = 2,435,369,313 cycles
about 48.7s at 50 MHz
```

## 8 个性能测试

- perf1: 80x80 int32 矩阵乘法
- perf2: CRC16-CCITT，4096-byte buffer
- perf3: 1000 元素 bubble sort
- perf4: 2..2000 质数计数
- perf5: 4096-byte 状态机 checksum
- perf6: 2048 元素数组 transform
- perf7: 512 节点链表遍历，4096 steps
- perf8: 4096 轮 bit-mix/hash

## 非性能测试

计时开始前会真实执行：

- RV32I 37 条指令测试
- RV32M 8 条指令测试
- zicsr + ecall/mret trap 测试

summary 中的 `37/0` 和 `8/0` 来自真实测试结果，不是固定写入。counter 只包下面这段：

```text
counter start
repeat 39:
  perf1..perf8
counter stop
```

全部通过时：

```text
status_bits = 0x03030303
LED = 0x078b7323
```

右侧两列 LED 映射：

```text
row1: perf8 perf7
row2: perf6 perf5
row3: perf4 perf3
row4: perf2 perf1
```

## SEG 显示

SEG 写入 BCD 格式：

```text
[31:24] RV32I 通过数，两位十进制
[23:20] M 扩展通过数，一位十进制
[19:0]  性能测试计时，五位十进制 ms
```

例如 RV32I 37 条通过、M 8 条通过、性能测试 12345ms：

```text
SEG = 0x37812345
```
