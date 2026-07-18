// FPGA top for Digilent Genesys 2 (XC7K325T-2FFG900C)
// 100MHz core clock (MMCM), 64KB banked BRAM, dual-issue core,
// UART TX @115200, 4 LEDs.
// MMIO map (addr bit30):
//   0x40000000  W: UART TX data   R: bit0 = UART busy
//   0x40000008  W/R: LED[3:0]
//   0x40000010  R: cycle counter    0x40000014  R: instret counter
module fpga_top #(
    parameter MEM_FILE0 = "prog.mem0",   // even words
    parameter MEM_FILE1 = "prog.mem1",   // odd words
    parameter BANK_WORDS = 8192,         // 2 banks x 32KB = 64KB
    parameter CORE_HZ   = 200_000_000
) (
    input  wire       sys_clk_p,         // 200MHz LVDS, pin AD12
    input  wire       sys_clk_n,         // pin AD11
    input  wire       sys_rst_n,         // CPU RESET button, active low, pin R19
    output wire       uart_txd,          // pin Y23 (FT232R RXD, to PC)
    output wire [3:0] led                // LD0-3: T28 V19 U30 U29
);
    // ---- core clock: 200MHz diff -> 200MHz via MMCM (bypassed in Verilator) ----
    wire clk_core, locked;
`ifdef VERILATOR
    assign clk_core = sys_clk_p;
    assign locked   = 1'b1;
`else
    wire sys_clk_ibuf, clk_fb, clk_out0;
    IBUFDS u_ibufds (.I(sys_clk_p), .IB(sys_clk_n), .O(sys_clk_ibuf));
    MMCME2_BASE #(
        .CLKIN1_PERIOD   (5.000),
        .CLKFBOUT_MULT_F (7.000),    // VCO = 200M * 7 = 1400MHz
        .CLKOUT0_DIVIDE_F(7.000),    // 1400 / 7 = 200MHz
        .DIVCLK_DIVIDE   (1)
    ) u_mmcm (
        .CLKIN1  (sys_clk_ibuf),
        .CLKFBIN (clk_fb),
        .CLKFBOUT(clk_fb),
        .CLKOUT0 (clk_out0),
        .CLKOUT0B(), .CLKOUT1(), .CLKOUT1B(), .CLKOUT2(), .CLKOUT2B(),
        .CLKOUT3(), .CLKOUT3B(), .CLKOUT4(), .CLKOUT5(), .CLKOUT6(),
        .CLKFBOUTB(),
        .LOCKED  (locked),
        .PWRDWN  (1'b0),
        .RST     (1'b0)
    );
    BUFG u_bufg (.I(clk_out0), .O(clk_core));
`endif

    reg [1:0] rst_sync;
    always @(posedge clk_core or negedge sys_rst_n) begin
        if (!sys_rst_n) rst_sync <= 2'b11;
        else            rst_sync <= {rst_sync[0], ~locked};
    end
    wire rst = rst_sync[1];

    // ================= core =================
    wire [31:0] imem_addr, imem_rdata0, imem_rdata1;
    wire [31:0] dmem_addr, dmem_wdata, dmem_rdata;
    wire        dmem_ren;
    wire [3:0]  dmem_wen;
    wire [31:0] dmem1_addr, dmem1_rdata, dmem1_wdata;
    wire        dmem1_ren;
    wire [3:0]  dmem1_wen;
    wire        commit0_valid, commit1_valid;

    core u_core (
        .clk(clk_core), .rst(rst),
        .imem_addr(imem_addr), .imem_rdata0(imem_rdata0), .imem_rdata1(imem_rdata1),
        .dmem_addr(dmem_addr), .dmem_ren(dmem_ren),
        .dmem_wen(dmem_wen), .dmem_wdata(dmem_wdata), .dmem_rdata(dmem_rdata),
        .dmem1_addr(dmem1_addr), .dmem1_ren(dmem1_ren),
        .dmem1_wen(dmem1_wen), .dmem1_wdata(dmem1_wdata), .dmem1_rdata(dmem1_rdata),
        .commit0_valid(commit0_valid), .commit0_pc(), .commit0_instr(),
        .commit0_rd_wen(), .commit0_rd(), .commit0_rd_wdata(),
        .commit1_valid(commit1_valid), .commit1_pc(), .commit1_instr(),
        .commit1_rd_wen(), .commit1_rd(), .commit1_rd_wdata()
    );

    // ================= banked BRAM (even/odd words) =================
    reg [31:0] mem0 [0:BANK_WORDS-1];
    reg [31:0] mem1 [0:BANK_WORDS-1];
    initial begin : mem_init
`ifndef SYNTHESIS
        reg [1023:0] memfile0, memfile1;
        if ($value$plusargs("mem0=%s", memfile0)) $readmemh(memfile0, mem0);
        else
`endif
        $readmemh(MEM_FILE0, mem0);
`ifndef SYNTHESIS
        if ($value$plusargs("mem1=%s", memfile1)) $readmemh(memfile1, mem1);
        else
`endif
        $readmemh(MEM_FILE1, mem1);
    end

    // instruction pair port
    wire        ib   = imem_addr[2];
    wire [12:0] iidx = imem_addr[15:3];
    reg  [31:0] i_r0, i_r1;
    reg         ib_r;
    always @(posedge clk_core) begin
        i_r0 <= mem0[ib ? iidx + 13'd1 : iidx];
        i_r1 <= mem1[iidx];
        ib_r <= ib;
    end
    assign imem_rdata0 = ib_r ? i_r1 : i_r0;
    assign imem_rdata1 = ib_r ? i_r0 : i_r1;

    // data port with MMIO decode
    wire        mmio_sel = dmem_addr[30];
    wire        db   = dmem_addr[2];
    wire [12:0] didx = dmem_addr[15:3];
    wire [3:0]  ram_we = mmio_sel ? 4'b0 : dmem_wen;
    reg  [31:0] d_r0, d_r1;
    reg         db_r;
    always @(posedge clk_core) begin
        d_r0 <= mem0[didx];
        db_r <= db;
        if (!db) begin
            if (ram_we[0]) mem0[didx][7:0]   <= dmem_wdata[7:0];
            if (ram_we[1]) mem0[didx][15:8]  <= dmem_wdata[15:8];
            if (ram_we[2]) mem0[didx][23:16] <= dmem_wdata[23:16];
            if (ram_we[3]) mem0[didx][31:24] <= dmem_wdata[31:24];
        end
    end
    always @(posedge clk_core) begin
        d_r1 <= mem1[didx];
        if (db) begin
            if (ram_we[0]) mem1[didx][7:0]   <= dmem_wdata[7:0];
            if (ram_we[1]) mem1[didx][15:8]  <= dmem_wdata[15:8];
            if (ram_we[2]) mem1[didx][23:16] <= dmem_wdata[23:16];
            if (ram_we[3]) mem1[didx][31:24] <= dmem_wdata[31:24];
        end
    end

    // ================= MMIO =================
    wire mmio_wr = mmio_sel && (dmem_wen != 4'b0);
    wire uart_busy;
    wire uart_start = mmio_wr && (dmem_addr[4:2] == 3'b000);

    uart_tx #(.CLK_FREQ(CORE_HZ), .BAUD(115200)) u_uart (
        .clk(clk_core), .rst(rst),
        .start(uart_start), .data(dmem_wdata[7:0]),
        .txd(uart_txd), .busy(uart_busy)
    );

    reg [3:0] led_r;
    always @(posedge clk_core) begin
        if (rst) led_r <= 4'b0;
        else if (mmio_wr && (dmem_addr[4:2] == 3'b010)) led_r <= dmem_wdata[3:0];
    end
    assign led = led_r;

    reg [31:0] cycle_cnt, instret_cnt;
    always @(posedge clk_core) begin
        if (rst) begin
            cycle_cnt   <= 32'd0;
            instret_cnt <= 32'd0;
        end else begin
            cycle_cnt   <= cycle_cnt + 1'b1;
            instret_cnt <= instret_cnt + {31'b0, commit0_valid} + {31'b0, commit1_valid};
        end
    end

    reg        mmio_sel_r;
    reg [31:0] mmio_r;
    always @(posedge clk_core) begin
        mmio_sel_r <= mmio_sel && dmem_ren;
        case (dmem_addr[4:2])
            3'b000:  mmio_r <= {31'b0, uart_busy};
            3'b010:  mmio_r <= {28'b0, led_r};
            3'b100:  mmio_r <= cycle_cnt;
            3'b101:  mmio_r <= instret_cnt;
            default: mmio_r <= 32'h0;
        endcase
    end
    assign dmem_rdata = mmio_sel_r ? mmio_r : (db_r ? d_r1 : d_r0);

    // slot1 port (second read + word-store write of the banks)
    wire        db1   = dmem1_addr[2];
    wire [12:0] didx1 = dmem1_addr[15:3];
    reg  [31:0] d1_r0, d1_r1;
    reg         db1_r;
    always @(posedge clk_core) begin
        d1_r0 <= mem0[didx1];
        d1_r1 <= mem1[didx1];
        db1_r <= db1;
        if (dmem1_wen != 4'b0) begin
            if (!db1) mem0[didx1] <= dmem1_wdata;
            else      mem1[didx1] <= dmem1_wdata;
        end
    end
    assign dmem1_rdata = db1_r ? d1_r1 : d1_r0;
endmodule
