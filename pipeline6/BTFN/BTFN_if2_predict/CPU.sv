`include "config.sv"
module CPU#(
    parameter PC_RESET_VALUE = 32'h80000000,
    parameter I_CACHE_DEPTH = 8,
    parameter D_CACHE_DEPTH = 8
)(
    input  logic         cpu_rst,
    input  logic         cpu_clk,

    // Interface to IROM, you need add some signals
    input logic [31:0]   irom_rdata,
    output logic         irom_en,
    output logic         irom_rst,
    output logic [31:0]  irom_addr,//输出内部的pc作为地址
    
    // Interface to DRAM, you need add some signals
    input  logic [31:0]  bus_rdata,
    output logic [31:0]  bus_addr,
    output logic [31:0]  bus_wdata,
    output logic [ 3:0]  bus_wen,

    output logic         debug_wb_have_inst,
    output logic [31:0]  debug_wb_pc,
    output logic         debug_wb_ena,
    output logic [ 4:0]  debug_wb_reg,
    output logic [31:0]  debug_wb_value
);
    /* IF1 stage */
    logic [0:0]     branch_taken_if2,branch_taken_id,branch_taken_ex;
    logic [31:0]    pc_if1, pc_if2, pc_id, pc_ex, pc_ls, pc_wb;
    logic [31:0]    inst_if2, inst_id, inst_ex, inst_ls, inst_wb;
    logic [31:0]    pc_target, next_pc;
    logic [31:0]    imm_if2,imm_id, imm_ex;
    logic [31:0]    rf_wdata_wb;
    logic [31:0]    rf_rdata1_id, rf_rdata1_ex;
    logic [31:0]    rf_rdata2_id, rf_rdata2_ex;
    logic [31:0]    forward1_data, forward2_data;
    logic [31:0]    alu_rf_data1, alu_rf_data2;
    logic [31:0]    alu_rs1, alu_rs2;
    logic [31:0]    alu_result_ex, alu_result_ls, alu_result_wb;
    logic [31:0]    jump_target;
    logic [31:0]    mem_wdata_ex;
    logic [31:0]    mem_rdata_ls, mem_rdata_wb; 
    logic [31:0]    dcache_rdata_ls;
    logic [ 4:0]    alu_op_id, alu_op_ex;
    logic [ 4:0]    mem_access_id, mem_access_ex, mem_access_ls;
    logic [ 4:0]    br_type_id, br_type_ex;
    //logic [ 3:0]    wstrb_ex;
    logic [ 1:0]    alu_rs1_sel_id, alu_rs1_sel_ex;
    logic [ 1:0]    alu_rs2_sel_id, alu_rs2_sel_ex;
    logic [ 0:0]    wb_rf_sel_id, wb_rf_sel_ex, wb_rf_sel_ls, wb_rf_sel_wb;
    logic [ 0:0]    rf_we_id, rf_we_ex, rf_we_ls, rf_we_wb;

    logic [ 0:0]    forward1_en, forward2_en;
    logic [ 0:0]    jump;
    logic [ 0:0]    pc_set, pc_stall;
    logic [ 0:0]    IF1_IF2_stall, IF1_IF2_flush;
    logic [ 0:0]    IF2_ID_stall, IF2_ID_flush;
    logic [ 0:0]    ID_EX_flush;

    logic [ 0:0]    have_inst_id, have_inst_ex, have_inst_ls,have_inst_wb;

    //wire [31:0] predict_target = pc_id + imm_id;
    wire is_b_type_if2 = (inst_if2[6:0] == 7'b1100011);
    wire is_jal_if2    = (inst_if2[6:0] == 7'b1101111);
    assign branch_taken_if2 = (is_b_type_if2 && inst_if2[31])|| is_jal_if2;
    wire [31:0] predict_target_if2 = pc_if2 + imm_if2;

    wire [31:0] b_imm_if2 = {{20{inst_if2[31]}}, inst_if2[7], inst_if2[30:25], inst_if2[11:8], 1'b0};
    // J-type (JAL) 立即数
    wire [31:0] j_imm_if2 = {{12{inst_if2[31]}}, inst_if2[19:12], inst_if2[20], inst_if2[30:21], 1'b0};

    assign imm_if2 = is_jal_if2 ? j_imm_if2 : b_imm_if2;
    

    NPC_Mux  NPC_Mux_inst (
        .pc         (pc_if1),
        .pc_set     (pc_set),
        .branch_taken  (branch_taken_if2),
        .predict_target  (predict_target_if2),
        .pc_target  (pc_target),
        .next_pc    (next_pc)
    );

    PC#(
        .RESET_VALUE(PC_RESET_VALUE)
    ) PC_inst (
        .clk        (cpu_clk),
        .rst        (cpu_rst),
        .stall      (pc_stall),
        .next_pc    (next_pc),
        .pc         (pc_if1)
    );


    /* IF1-IF2 segreg */
    SegReg_IF1_IF2 # (
        .PC_RESET_VAL(PC_RESET_VALUE)
    ) SegReg_IF1_IF2_inst (
        .clk        (cpu_clk),
        .rst        (cpu_rst),
        .stall      (IF1_IF2_stall),
        .flush      (IF1_IF2_flush),
        .pc_if1     (pc_if1),
        .pc_if2     (pc_if2)
    );

    assign irom_addr = pc_if1;
    assign inst_if2  = irom_rdata;
    assign irom_en   = ~IF1_IF2_stall;
    assign irom_rst  = IF1_IF2_flush;

    /*
    ICache # (
        .DEPTH(I_CACHE_DEPTH)
    ) ICache_inst (
        .clk        (clk),
        .raddr      (pc_if1),
        .rdata      (inst_if2),
        .flush      (IF1_IF2_flush),
        .stall      (IF1_IF2_stall)
    );*/

    /* IF2 stage */

    // B-type 立即数
    
    /* IF2-ID segreg */
    SegReg_IF2_ID # (
        .PC_RESET_VAL(PC_RESET_VALUE)
    ) SegReg_IF2_ID_inst (
        .clk            (cpu_clk),
        .rst            (cpu_rst),
        .stall          (IF2_ID_stall),
        .flush          (IF2_ID_flush),
        .pc_if2         (pc_if2),
        .inst_if2       (inst_if2),
        .branch_taken_if2(branch_taken_if2),
        .pc_id          (pc_id),
        .inst_id        (inst_id),
        .branch_taken_id(branch_taken_id)
    );

    /* ID stage */
    Decode  Decode_inst (
        .inst           (inst_id),
        .have_inst      (have_inst_id),
        .alu_op         (alu_op_id),
        .mem_access     (mem_access_id),
        .imm            (imm_id),
        .rf_we          (rf_we_id),
        .alu_rs1_sel    (alu_rs1_sel_id),
        .alu_rs2_sel    (alu_rs2_sel_id),
        .wb_rf_sel      (wb_rf_sel_id),
        .br_type        (br_type_id)
    );
    Regfile  Regfile_inst (
        .clk            (cpu_clk),
        .raddr1         (inst_id[19:15]),
        .raddr2         (inst_id[24:20]),
        .waddr          (inst_wb[11:7]),
        .wdata          (rf_wdata_wb),
        .we             (rf_we_wb),
        .rdata1         (rf_rdata1_id),
        .rdata2         (rf_rdata2_id)
    );

    /* ID-EX segreg */
    SegReg_ID_EX # (
        .PC_RESET_VAL(PC_RESET_VALUE)
    ) SegReg_ID_EX_inst (
        .clk            (cpu_clk),
        .rst            (cpu_rst),
        .flush          (ID_EX_flush),
        .pc_id          (pc_id),
        .inst_id        (inst_id),
        .rdata1_id      (rf_rdata1_id),
        .rdata2_id      (rf_rdata2_id),
        .imm_id         (imm_id),
        .mem_access_id  (mem_access_id),
        .alu_op_id          (alu_op_id),
        .br_type_id     (br_type_id),
        .wb_rf_sel_id   (wb_rf_sel_id),
        .alu_rs1_sel_id (alu_rs1_sel_id),
        .alu_rs2_sel_id (alu_rs2_sel_id),
        .rf_we_id       (rf_we_id),
        .branch_taken_id(branch_taken_id),
        .branch_taken_ex(branch_taken_ex),
        .pc_ex          (pc_ex),
        .inst_ex        (inst_ex),
        .rdata1_ex      (rf_rdata1_ex),
        .rdata2_ex      (rf_rdata2_ex),
        .imm_ex         (imm_ex),
        .mem_access_ex  (mem_access_ex),
        .alu_op_ex          (alu_op_ex),
        .br_type_ex     (br_type_ex),
        .wb_rf_sel_ex   (wb_rf_sel_ex),
        .alu_rs1_sel_ex (alu_rs1_sel_ex),
        .alu_rs2_sel_ex (alu_rs2_sel_ex),
        .rf_we_ex       (rf_we_ex),
        .have_inst_id   (have_inst_id),
        .have_inst_ex   (have_inst_ex)

    );

    /* EX stage */
    Mux2_1 # (
        .WIDTH(32)
    )   ALU_rf_data1_mux (
        .din1           (rf_rdata1_ex),//0
        .din2           (forward1_data),//1
        .sel            (forward1_en),
        .dout           (alu_rf_data1)
    );
    Mux2_1 # (
        .WIDTH(32)
    )   ALU_rf_data2_mux (
        .din1           (rf_rdata2_ex),//0
        .din2           (forward2_data),//1
        .sel            (forward2_en),
        .dout           (alu_rf_data2)
    );
    Mux4_1 # (
        .WIDTH(32)
    )   ALU_rs1_mux (
        .din1           (alu_rf_data1),
        .din2           (pc_ex),
        .din3           (32'h0),
        .din4           (32'h0),
        .sel            (alu_rs1_sel_ex),
        .dout           (alu_rs1)
    );
    Mux4_1 # (
        .WIDTH(32)
    )   ALU_rs2_mux (
        .din1           (alu_rf_data2),
        .din2           (imm_ex),
        .din3           (32'h4),
        .din4           (32'h0),
        .sel            (alu_rs2_sel_ex),
        .dout           (alu_rs2)
    );

    ALU  ALU_inst (
        .sr1            (alu_rs1),
        .sr2            (alu_rs2),
        .alu_op         (alu_op_ex),
        .result         (alu_result_ex)
    );

    Branch  Branch_inst (
        .br_type        (br_type_ex),
        .sr1            (alu_rf_data1),
        .sr2            (alu_rf_data2),
        .pc             (pc_ex),
        .imm            (imm_ex),
        .jump           (jump),
        .jump_target    (jump_target)
    );

    /* EX-LS segreg */
    SegReg_EX_LS # (
        .PC_RESET_VAL(PC_RESET_VALUE)
    ) SegReg_EX_LS_inst (
        .clk            (cpu_clk),
        .rst            (cpu_rst),
        .pc_ex          (pc_ex),
        .inst_ex        (inst_ex),
        .alu_result_ex  (alu_result_ex),
        .mem_access_ex  (mem_access_ex),
        .wb_rf_sel_ex   (wb_rf_sel_ex),
        .rf_we_ex       (rf_we_ex),
        .pc_ls          (pc_ls),
        .inst_ls        (inst_ls),
        .alu_result_ls  (alu_result_ls),
        .mem_access_ls  (mem_access_ls),
        .wb_rf_sel_ls   (wb_rf_sel_ls),
        .rf_we_ls       (rf_we_ls),
        .have_inst_ex   (have_inst_ex),
        .have_inst_ls   (have_inst_ls)
    );

    logic [31:0] d_wdata;
    logic [3:0] d_wstrb;

    Write_Ctrl  Write_Ctrl_inst (
        .mem_wdata      (alu_rf_data2),
        .alu_result     (alu_result_ex[1:0]),
        .mem_access     (mem_access_ex),
        .wdata          (d_wdata),
        .d_wstrb        (d_wstrb)
    );

    assign bus_addr = alu_result_ex;
    assign bus_wdata = d_wdata;
    assign bus_wen = d_wstrb;

    /*
    DCache # (
        .DEPTH(D_CACHE_DEPTH)
    ) DCache_inst (
        .clk            (clk),
        .raddr          (alu_result_ex),
        .rdata          (dcache_rdata_ls),
        .waddr          (alu_result_ex),
        .wdata          (alu_rf_data2),
        .mem_access     (mem_access_ex),
        .flush          (EX_LS_flush),
        .stall          (EX_LS_stall)
    );
    */
    /* LS stage */
    Read_Ctrl  Read_Ctrl_inst (
        .mem_rdata      (bus_rdata),
        .mem_raddr      (alu_result_ls[1:0]),
        .mem_access     (mem_access_ls),
        .rdata          (mem_rdata_ls)
    );

    /* LS-WB segreg */
    SegReg_LS_WB # (
        .PC_RESET_VAL(PC_RESET_VALUE)
    ) SegReg_LS_WB_inst (
        .clk                (cpu_clk),
        .rst                (cpu_rst),
        .pc_ls              (pc_ls),
        .inst_ls            (inst_ls),
        .alu_result_ls      (alu_result_ls),
        .mem_rdata_ls       (mem_rdata_ls),
        .wb_rf_sel_ls       (wb_rf_sel_ls),
        .rf_we_ls           (rf_we_ls),
        .pc_wb              (pc_wb),
        .inst_wb            (inst_wb),
        .alu_result_wb      (alu_result_wb),
        .mem_rdata_wb       (mem_rdata_wb),
        .wb_rf_sel_wb       (wb_rf_sel_wb),
        .rf_we_wb           (rf_we_wb),
        .have_inst_ls       (have_inst_ls),
        .have_inst_wb       (have_inst_wb)
    );

    /* WB stage */
    Mux2_1 # (
        .WIDTH(32)
    )   WB_rf_wdata_mux (
        .din1           (alu_result_wb),//0
        .din2           (mem_rdata_wb),//1
        .sel            (wb_rf_sel_wb),
        .dout           (rf_wdata_wb)
    );


    /* Hazard */
    Hazard  Hazard_inst (
        .rf_rd_ls           (inst_ls[11:7]),
        .rf_rd_wb           (inst_wb[11:7]),
        .rf_we_ls           (rf_we_ls),
        .rf_we_wb           (rf_we_wb),
        .rf_rs1_ex          (inst_ex[19:15]),
        .rf_rs2_ex          (inst_ex[24:20]),
        .rf_wdata_tmp_ls    (alu_result_ls),
        .rf_wdata_wb        (rf_wdata_wb),
        .forward1_en        (forward1_en),
        .forward2_en        (forward2_en),
        .forward1_data      (forward1_data),
        .forward2_data      (forward2_data),

        .mem_access_ex      (mem_access_ex),
        .rf_rd_ex           (inst_ex[11:7]),
        .rf_rs1_id          (inst_id[19:15]),
        .rf_rs2_id          (inst_id[24:20]),
        .jump               (jump),
        .jump_target        (jump_target),

        .branch_taken_if2    (branch_taken_if2),
        .branch_taken_ex    (branch_taken_ex),
        .pc_ex              (pc_ex),
        .pc_set             (pc_set),
        .IF1_IF2_flush      (IF1_IF2_flush),
        .IF2_ID_flush       (IF2_ID_flush),
        .ID_EX_flush        (ID_EX_flush),
        .pc_stall           (pc_stall),
        .IF1_IF2_stall      (IF1_IF2_stall),
        .IF2_ID_stall       (IF2_ID_stall),
        .pc_set_target      (pc_target)
    ); 
/*
    // 定义一组寄存器，用于锁存“上一条”指令的执行结果
    logic last_have_inst;
    logic [31:0] last_pc;
    logic        last_wen;
    logic [4:0]  last_reg;
    logic [31:0] last_value;

    always_ff @(posedge cpu_clk) begin
        if (cpu_rst) begin
            last_have_inst <= 1'b0;
            last_pc    <= 32'h0;
            last_wen   <= 1'b0;
            last_reg   <= 5'h0;
            last_value <= 32'h0;
        end
        else begin
            // 在时钟上升沿，锁存当前周期计算出的结果
            last_have_inst <= have_inst_wb;
            last_pc    <= pc_wb;      // 锁存当前的 0
            last_wen   <= rf_we_wb;    // 锁存当前指令是否写寄存器
            last_reg   <= inst_wb[11:7]; 
            last_value <= rf_wdata_wb;    // 锁存计算出的写回值
        end
    end
*/
    // 让 Debug 端口输出锁存后的值（即上一条指令）
    assign debug_wb_have_inst = have_inst_wb; 
    assign debug_wb_pc        = pc_wb;    // 现在这里会输出 0 了！
    assign debug_wb_ena       = rf_we_wb;
    assign debug_wb_reg       = inst_wb[11:7];
    assign debug_wb_value     = rf_wdata_wb;
endmodule