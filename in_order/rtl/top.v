// Simulation top: dual-issue core + banked 4MB memory @ 0x80000000
// Bank0 = even words, bank1 = odd words; sync read (BRAM model).
module top (
    input  wire        clk,
    input  wire        rst,
    output wire [31:0] mon_waddr,
    output wire [3:0]  mon_wen,
    output wire [31:0] mon_wdata,
    output wire        commit0_valid,
    output wire [31:0] commit0_pc,
    output wire [31:0] commit0_instr,
    output wire        commit0_rd_wen,
    output wire [4:0]  commit0_rd,
    output wire [31:0] commit0_rd_wdata,
    output wire        commit1_valid,
    output wire [31:0] commit1_pc,
    output wire [31:0] commit1_instr,
    output wire        commit1_rd_wen,
    output wire [4:0]  commit1_rd,
    output wire [31:0] commit1_rd_wdata
);
    localparam BANK_WORDS = 1 << 13; // 2 banks x 32KB = 64KB

    reg [31:0] mem0 [0:BANK_WORDS-1] /* verilator public_flat_rw */;
    reg [31:0] mem1 [0:BANK_WORDS-1] /* verilator public_flat_rw */;

    wire [31:0] imem_addr, dmem_addr, dmem_wdata;
    wire [31:0] dmem_rdata;
    wire        dmem_ren;
    wire [3:0]  dmem_wen;
    wire [31:0] imem_rdata0, imem_rdata1;
    wire [31:0] dmem1_addr, dmem1_rdata, dmem1_wdata;
    wire        dmem1_ren;
    wire [3:0]  dmem1_wen;

    core u_core (
        .clk(clk), .rst(rst),
        .imem_addr(imem_addr), .imem_rdata0(imem_rdata0), .imem_rdata1(imem_rdata1),
        .dmem_addr(dmem_addr), .dmem_ren(dmem_ren),
        .dmem_wen(dmem_wen), .dmem_wdata(dmem_wdata), .dmem_rdata(dmem_rdata),
        .dmem1_addr(dmem1_addr), .dmem1_ren(dmem1_ren),
        .dmem1_wen(dmem1_wen), .dmem1_wdata(dmem1_wdata), .dmem1_rdata(dmem1_rdata),
        .commit0_valid(commit0_valid), .commit0_pc(commit0_pc), .commit0_instr(commit0_instr),
        .commit0_rd_wen(commit0_rd_wen), .commit0_rd(commit0_rd),
        .commit0_rd_wdata(commit0_rd_wdata),
        .commit1_valid(commit1_valid), .commit1_pc(commit1_pc), .commit1_instr(commit1_instr),
        .commit1_rd_wen(commit1_rd_wen), .commit1_rd(commit1_rd),
        .commit1_rd_wdata(commit1_rd_wdata)
    );

    // instruction pair fetch: i0 @ addr, i1 @ addr+4
    wire        ib   = imem_addr[2];
    wire [12:0] iidx = imem_addr[15:3];
    reg  [31:0] i_r0, i_r1;
    reg         ib_r;
    always @(posedge clk) begin
        i_r0 <= mem0[ib ? iidx + 13'd1 : iidx];
        i_r1 <= mem1[iidx];
        ib_r <= ib;
    end
    assign imem_rdata0 = ib_r ? i_r1 : i_r0;
    assign imem_rdata1 = ib_r ? i_r0 : i_r1;

    // data port
    wire        db   = dmem_addr[2];
    wire [12:0] didx = dmem_addr[15:3];
    reg  [31:0] d_r0, d_r1;
    reg         db_r;
    always @(posedge clk) begin
        d_r0 <= mem0[didx];
        d_r1 <= mem1[didx];
        db_r <= db;
        if (!db) begin
            if (dmem_wen[0]) mem0[didx][7:0]   <= dmem_wdata[7:0];
            if (dmem_wen[1]) mem0[didx][15:8]  <= dmem_wdata[15:8];
            if (dmem_wen[2]) mem0[didx][23:16] <= dmem_wdata[23:16];
            if (dmem_wen[3]) mem0[didx][31:24] <= dmem_wdata[31:24];
        end else begin
            if (dmem_wen[0]) mem1[didx][7:0]   <= dmem_wdata[7:0];
            if (dmem_wen[1]) mem1[didx][15:8]  <= dmem_wdata[15:8];
            if (dmem_wen[2]) mem1[didx][23:16] <= dmem_wdata[23:16];
            if (dmem_wen[3]) mem1[didx][31:24] <= dmem_wdata[31:24];
        end
    end
    assign dmem_rdata = db_r ? d_r1 : d_r0;

    // slot1 port (second read + word-store write of the same banked memory)
    wire        db1   = dmem1_addr[2];
    wire [12:0] didx1 = dmem1_addr[15:3];
    reg  [31:0] d1_r0, d1_r1;
    reg         db1_r;
    always @(posedge clk) begin
        d1_r0 <= mem0[didx1];
        d1_r1 <= mem1[didx1];
        db1_r <= db1;
        if (dmem1_wen != 4'b0) begin
            if (!db1) mem0[didx1] <= dmem1_wdata;
            else      mem1[didx1] <= dmem1_wdata;
        end
    end
    assign dmem1_rdata = db1_r ? d1_r1 : d1_r0;

    // store monitor: the two write ports are mutually exclusive per cycle
    // (issue rule), so a simple mux covers tohost/putc writes on either port
    wire s1w = (dmem1_wen != 4'b0);
    assign mon_waddr = s1w ? dmem1_addr  : dmem_addr;
    assign mon_wen   = s1w ? dmem1_wen   : dmem_wen;
    assign mon_wdata = s1w ? dmem1_wdata : dmem_wdata;
endmodule
