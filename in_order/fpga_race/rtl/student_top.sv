`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// student_top: competition SoC wrapper (same ports as the reference version),
// CPU replaced with the 2-wide in-order dual-issue RV32IM+Zicsr core.
//
//   - IROM  16KB @ 0x8000_0000 : irom3p (fetch pair port + rodata read port)
//   - DRAM 256KB @ 0x8010_0000 : inside perip_bridge (port-compatible RTL DRAM)
//   - MMIO       @ 0x8020_00xx : SW/KEY/SEG/LED/CNT via perip_bridge (untouched)
//
// dmem timing matches the bridge/BRAM contract: address+wen registered by the
// core at EX/M1 (FF outputs), read data valid one cycle later (M2).
//////////////////////////////////////////////////////////////////////////////////

module student_top#(
    parameter                           P_SW_CNT            = 64,
    parameter                           P_LED_CNT           = 32,
    parameter                           P_SEG_CNT           = 40,
    parameter                           P_KEY_CNT           = 8,
    parameter                           IROM_MEM            = "irom.mem",
    parameter                           DRAM_MEM            = "dram.mem"
) (
    input                                       w_cpu_clk     ,
    input                                       w_clk_50Mhz   ,
    input                                       w_clk_rst     ,
    input  [P_KEY_CNT - 1:0]                    virtual_key   ,
    input  [P_SW_CNT  - 1:0]                    virtual_sw    ,

    output [P_LED_CNT - 1:0]                    virtual_led   ,
    output [P_SEG_CNT - 1:0]                    virtual_seg
);

    // ================= core =================
    wire [31:0] imem_addr, imem_rdata0, imem_rdata1;
    wire [31:0] dmem_addr, dmem_wdata, dmem_rdata;
    wire        dmem_ren;
    wire [3:0]  dmem_wen;
    wire [31:0] dmem1_addr, dmem1_rdata, dmem1_wdata;
    wire        dmem1_ren;
    wire [3:0]  dmem1_wen;

    core u_core (
        .clk(w_cpu_clk), .rst(w_clk_rst),
        .imem_addr(imem_addr), .imem_rdata0(imem_rdata0), .imem_rdata1(imem_rdata1),
        .dmem_addr(dmem_addr), .dmem_ren(dmem_ren),
        .dmem_wen(dmem_wen), .dmem_wdata(dmem_wdata), .dmem_rdata(dmem_rdata),
        .dmem1_addr(dmem1_addr), .dmem1_ren(dmem1_ren),
        .dmem1_wen(dmem1_wen), .dmem1_wdata(dmem1_wdata), .dmem1_rdata(dmem1_rdata),
        .commit0_valid(), .commit0_pc(), .commit0_instr(),
        .commit0_rd_wen(), .commit0_rd(), .commit0_rd_wdata(),
        .commit1_valid(), .commit1_pc(), .commit1_instr(),
        .commit1_rd_wen(), .commit1_rd(), .commit1_rd_wdata()
    );

    // ================= IROM (fetch pair + rodata reads) =================
    wire [31:0] irom_drdata, irom_drdata1;
    // 实例1：双发射取指
    IROM u_irom_fetch (
        .clka  (w_cpu_clk),
        .addra (imem_addr[13:2]),
        .douta (imem_rdata0),

        .clkb  (w_cpu_clk),
        .addrb (imem_addr[13:2] + 12'd1),
        .doutb (imem_rdata1)
    );

    // 实例2：两个数据读口
    IROM u_irom_data (
        .clka  (w_cpu_clk),
        .addra (dmem_addr[13:2]),
        .douta (irom_drdata),

        .clkb  (w_cpu_clk),
        .addrb (dmem1_addr[13:2]),
        .doutb (irom_drdata1)
    );

    // ================= data-side routing =================
    // IROM page (0x8000_xxxx) reads come from the ROM copy; everything else
    // (DRAM 0x8010_xxxx, MMIO 0x8020_xxxx) is served by perip_bridge.
    // dmem_addr is valid in M1; read data is consumed in M2 -> register select.
    wire dmem_is_irom = (dmem_addr[31:16] == 16'h8000);
    reg  dmem_is_irom_r;
    always @(posedge w_cpu_clk) begin
        if (w_clk_rst) dmem_is_irom_r <= 1'b0;
        else           dmem_is_irom_r <= dmem_is_irom;
    end

    wire [31:0] perip_rdata;
    assign dmem_rdata = dmem_is_irom_r ? irom_drdata : perip_rdata;

    // slot1 read-only port: statically DRAM or IROM (issue rule), so it never
    // needs the peripheral bridge. DRAM port B serves it; IROM likewise.
    wire dmem1_is_irom = (dmem1_addr[31:16] == 16'h8000);
    reg  dmem1_is_irom_r;
    always @(posedge w_cpu_clk) begin
        if (w_clk_rst) dmem1_is_irom_r <= 1'b0;
        else           dmem1_is_irom_r <= dmem1_is_irom;
    end
    wire [31:0] dram_doutb;
    assign dmem1_rdata = dmem1_is_irom_r ? irom_drdata1 : dram_doutb;

    // writes to the IROM page are architecturally impossible in the test
    // image (no self-modifying code); bridge address decode ignores them.
    perip_bridge #(.DRAM_MEM(DRAM_MEM)) bridge_inst (
        .clk                (w_cpu_clk),
        .cnt_clk            (w_clk_50Mhz),
        .rst                (w_clk_rst),
        .perip_addr         (dmem_addr),
        .perip_wdata        (dmem_wdata),
        .perip_wstrb        (dmem_wen),
        .perip_rdata        (perip_rdata),
        .dram_addrb         (dmem1_addr[17:2]),
        .dram_web           (dmem1_wen),
        .dram_dinb          (dmem1_wdata),
        .dram_doutb         (dram_doutb),
        .virtual_sw_input   (virtual_sw),
        .virtual_key_input  (virtual_key),
        .virtual_seg_output (virtual_seg),
        .virtual_led_output (virtual_led)
    );

endmodule
