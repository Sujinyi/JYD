`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/04/24 10:51:04
// Design Name: 
// Module Name: myCPU
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module myCPU1#(
    parameter DATAWIDTH = 32,
    parameter RESET_VAL = 32'h8000_0000
)(
    input  logic         cpu_rst,
    input  logic         cpu_clk,

    // Interface to IROM, you need add some signals
    input logic [31:0]   irom_rdata,
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

    //IF阶段的信号
    logic [DATAWIDTH -1 : 0] pc_if;
    logic [DATAWIDTH -1 : 0] pcadd4_if;
    logic [DATAWIDTH - 1:0] npc;

    /*
    // 修改逻辑：加一个 MUX 或者逻辑与
    logic [31:0] real_npc;
    // 如果正在复位，强制下个 PC 也是 0。
    // 这样当复位撤销的那一瞬间，PC 采到的 D 端数据是 0，而不是 4。
    assign real_npc = cpu_rst ? 32'h0 : npc;
    */

    logic stall;
    PC #(
        .DATAWIDTH  (DATAWIDTH),
        .RESET_VAL  (RESET_VAL)
    ) pc_inst(
        .clk        (cpu_clk),
        .rst        (cpu_rst),
        .npc        (npc),
        .stall      (stall),
        .pc_out     (pc_if)
    );

    logic True;
    logic [DATAWIDTH - 1:0] npc_offset_ex;

    logic OffsetOrigin_ex;
    logic [DATAWIDTH - 1 : 0] imm_ex; 
    logic  [DATAWIDTH - 1 : 0] alu_out_ex;

    MUX2_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_npc_offset(
        .A          (imm_ex),//0
        .B          (alu_out_ex),//1
        .Control    (OffsetOrigin_ex),
        .Result     (npc_offset_ex)
    );

    logic branched;
    logic [1:0] npc_op_ex;
    NPC #(
        .DATAWIDTH  (DATAWIDTH)
    ) npc_inst(
        .isTrue     (True),
        .npc_op     (npc_op_ex),
        .pc         (pc_if),
        .offset     (npc_offset_ex),
        .npc        (npc),
        .pcadd4     (pcadd4_if),
        .branched    (branched)
    );

    //地址线32位 数据线32位
    //存储器是字寻址 pc也是字节寻址 所以pc>>2
    //assign irom_addr = pc_out >> 2; // 0x0,0x4,0x8 --> 0,1,2...
    assign irom_addr = pc_if;
    logic [DATAWIDTH - 1 : 0] instr_if;
    assign instr_if = irom_rdata;

    logic IF_ID_flush;
    logic [31:0] pcadd4_id;
    logic [31:0] instr_id;
    logic [31:0] pc_id;
    IF_ID #(
        .RESET_VAL  (RESET_VAL)
    ) if_id_inst(
        .clk        (cpu_clk),
        .rst        (cpu_rst),
        .pcadd4_if  (pcadd4_if),
        .instr_if   (instr_if),
        .pc_if      (pc_if),
        .stall      (stall),
        .flush      (IF_ID_flush),
        .pcadd4_id  (pcadd4_id),
        .instr_id   (instr_id),
        .pc_id      (pc_id)
    );

    //ID阶段的信号
    logic RegWrite_wb;
    logic [DATAWIDTH - 1 : 0] RF_wdata_wb;
    logic [DATAWIDTH - 1 : 0] rs1_data_id;
    logic [DATAWIDTH - 1 : 0] rs2_data_id;
    logic [4:0] rR1_id;
    logic [4:0] rR2_id;
    logic [4:0] rRd_id;
    assign rR1_id = instr_id[19:15];
    assign rR2_id = instr_id[24:20];
    assign rRd_id = instr_id[11:7];

    logic [4:0] rRd_wb;

    RF #(
        .ADDR_WIDTH (5),
        .DATAWIDTH  (DATAWIDTH)
    )reg_file_inst (
        .clk             (cpu_clk),
        .rst             (cpu_rst),
        .wen             (RegWrite_wb),
        .waddr           (rRd_wb),
        .wdata           (RF_wdata_wb),
        .rR1             (rR1_id),
        .rR2             (rR2_id),
        .rR1_data        (rs1_data_id),
        .rR2_data        (rs2_data_id)
    );

    logic [31:0] imm_id;
    IMMGEN #(
        .DATAWIDTH  (32)	
    )imm_gen_inst (
        .instr   (instr_id),
        .imm     (imm_id)  
    );

    logic RegWrite_id;
    logic [1:0] MemToReg_id;
    logic MemWrite_id;
    logic OffsetOrigin_id;
    logic alua_sel_id;
    logic alub_sel_id;
    logic [1:0] LdSrc_id;
    logic [1:0] StSrc_id;
    logic Sext_id;
    logic have_inst_id;
    logic [1:0] npc_op_id;
    logic isLUI_id;

    Control control_inst (
        .opcode      (instr_id[6:0]),
        .funct       ({instr_id[30],instr_id[14:12]}),
        .NpcOp       (npc_op_id),
        .RegWrite    (RegWrite_id),
        .MemToReg    (MemToReg_id),
        .MemWrite    (MemWrite_id),
        .OffsetOrigin(OffsetOrigin_id),
        .alua_sel    (alua_sel_id),
        .alub_sel    (alub_sel_id),
        .LdSrc       (LdSrc_id),//00:lw, 01:lb(u),10:lh(u)
        .StSrc       (StSrc_id),//00:sw, 01:sb, 10:sh
        .Sext        (Sext_id), //0:zero_ext, 1:sign_ext
        .isLUI       (isLUI_id),
        .have_inst    (have_inst_id)
    );

    logic [3:0] ALUControl_id;
    ACTL ALU_controller_inst(
        .opcode       (instr_id[6:0]),
        .funct        ({instr_id[30],instr_id[14:12]}),
        .ALUControl   (ALUControl_id) 
    );

    logic ID_EX_flush;
    logic RegWrite_ex;
    logic [1:0] MemToReg_ex;
    logic MemWrite_ex;
    //logic OffsetOrigin_ex;
    logic alua_sel_ex;
    logic alub_sel_ex;
    logic [1:0] LdSrc_ex;
    logic [1:0] StSrc_ex;
    logic Sext_ex;
    logic [3:0] ALUControl_ex;
    logic [31:0] pcadd4_ex;
    logic [31:0] rs1_data_ex;
    logic [31:0] rs2_data_ex;
    logic [31:0] pc_ex; 
    logic have_inst_ex;
    logic [4:0] rR1_ex;
    logic [4:0] rR2_ex;
    logic [4:0] rRd_ex;
    logic isLUI_ex;

    ID_EX #(
        .RESET_VAL  (RESET_VAL)
    ) id_ex_inst(
        .clk            (cpu_clk),
        .rst            (cpu_rst),
        .npc_op_id      (npc_op_id),
        .RegWrite_id    (RegWrite_id),
        .MemToReg_id    (MemToReg_id),
        .MemWrite_id    (MemWrite_id),
        .OffsetOrigin_id(OffsetOrigin_id),
        .alua_sel_id    (alua_sel_id),
        .alub_sel_id    (alub_sel_id),
        .LdSrc_id       (LdSrc_id),
        .StSrc_id       (StSrc_id),
        .Sext_id        (Sext_id),
        .ALUControl_id  (ALUControl_id),
        .pcadd4_id      (pcadd4_id),
        .rR1_data_id    (rs1_data_id),
        .rR2_data_id    (rs2_data_id),
        .imm_id         (imm_id),
        .rR1_id         (rR1_id),
        .rR2_id         (rR2_id),
        .rRd_id         (rRd_id),
        .isLUI_id       (isLUI_id),
        .isLUI_ex       (isLUI_ex),
        .rR1_ex         (rR1_ex),
        .rR2_ex         (rR2_ex),
        .rRd_ex         (rRd_ex),
        .pc_id          (pc_id),
        .flush          (ID_EX_flush),
        .npc_op_ex      (npc_op_ex),
        .RegWrite_ex    (RegWrite_ex),
        .MemToReg_ex    (MemToReg_ex),
        .MemWrite_ex    (MemWrite_ex),
        .OffsetOrigin_ex(OffsetOrigin_ex),
        .alua_sel_ex    (alua_sel_ex),
        .alub_sel_ex    (alub_sel_ex),
        .LdSrc_ex       (LdSrc_ex),
        .StSrc_ex       (StSrc_ex),
        .Sext_ex        (Sext_ex),
        .ALUControl_ex  (ALUControl_ex),
        .pcadd4_ex      (pcadd4_ex),
        .rR1_data_ex    (rs1_data_ex),
        .rR2_data_ex    (rs2_data_ex),
        .imm_ex         (imm_ex),
        .pc_ex          (pc_ex),
        .have_inst_id   (have_inst_id),
        .have_inst_ex   (have_inst_ex)
    );
    //EX阶段的信号
    logic [1:0] ForwardA;
    logic [31:0] aluout_mem;
    logic [31:0] mux_forwarda_out;
    logic [31:0] imm_mem;
    MUX4_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_forward_a(
        .A          (rs1_data_ex),//0
        .B          (RF_wdata_wb),//1
        .C          (aluout_mem),//2
        .D          (imm_mem),//3 上一条是LUI的话，这里要用imm_mem，而不是alu_mem
        .Control    (ForwardA),
        .Result     (mux_forwarda_out)
    );

    logic [1:0] ForwardB;
    logic [31:0] mux_forwardb_out;
    MUX4_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_forward_b(
        .A          (rs2_data_ex),//0
        .B          (RF_wdata_wb),//1
        .C          (aluout_mem),//2
        .D          (imm_mem),//3 上一条是LUI的话，这里要用imm_mem，而不是alu_mem
        .Control    (ForwardB),
        .Result     (mux_forwardb_out)
    );

    logic [31:0] alu_b;
    MUX2_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_alu_b(
        .A          (mux_forwardb_out),//0
        .B          (imm_ex),//1
        .Control    (alub_sel_ex),
        .Result     (alu_b)
    );

    logic [31:0] alu_a;
    MUX2_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_alu_a(
        .A          (mux_forwarda_out),//0
        .B          (pc_ex),//1
        .Control    (alua_sel_ex),
        .Result     (alu_a)
    );

    //logic [31:0] alu_out_ex;
    ALU# (
        .DATAWIDTH  (DATAWIDTH)	
    ) alu_inst (
        .A           (alu_a),
        .B           (alu_b),
        .ALUControl  (ALUControl_ex),
        .Result      (alu_out_ex),
        .isTrue      (True)
    );

    Hazard_Detection hazard_detection_inst(
        .rR1_id      (rR1_id),
        .rR2_id      (rR2_id),
        .rRd_ex      (rRd_ex),
        .MemToReg_ex (MemToReg_ex),
        .branched    (branched),
        .stall        (stall),
        .ID_EX_flush  (ID_EX_flush),
        .IF_ID_flush  (IF_ID_flush)
    );

    //logic [31:0] instr_mem;
    //logic [31:0] instr_wb; 
    logic RegWrite_mem;
    logic [4:0] rRd_mem;
    logic isLUI_mem;

    Forwarding forwarding_inst(
        .rR1_ex       (rR1_ex),
        .rR2_ex       (rR2_ex),
        .isLUI_mem    (isLUI_mem),
        .rRd_mem      (rRd_mem),
        .rRd_wb       (rRd_wb),
        .RegWrite_mem (RegWrite_mem),
        .RegWrite_wb  (RegWrite_wb),
        .ForwardA     (ForwardA),
        .ForwardB     (ForwardB)
    );

    //logic [31:0] aluout_mem;
    logic [31:0] rs2_data_mem;
    logic [31:0] pcadd4_mem;
    //logic [4:0] rRd_mem;
    logic MemWrite_mem;
    logic [1:0] MemToReg_mem;
    logic [1:0] LdSrc_mem;
    logic [1:0] StSrc_mem;
    logic Sext_mem;
    logic [31:0] pc_mem;
    //logic [31:0] instr_mem;
    logic have_inst_mem;
    EX_MEM #(
        .RESET_VAL  (RESET_VAL)
    ) ex_mem_inst(
        .clk            (cpu_clk),
        .rst            (cpu_rst),
        .LdSrc_ex       (LdSrc_ex),
        .StSrc_ex       (StSrc_ex),
        .Sext_ex        (Sext_ex),
        .imm_ex         (imm_ex),
        .rRd_ex         (rRd_ex),
        .RegWrite_ex    (RegWrite_ex),
        .MemWrite_ex    (MemWrite_ex),
        .MemToReg_ex    (MemToReg_ex),
        .aluout_ex      (alu_out_ex),
        .rR2_data_ex    (mux_forwardb_out),//注意这里是前递后的数据
        .pcadd4_ex      (pcadd4_ex),
        .pc_ex          (pc_ex),
        .isLUI_ex       (isLUI_ex),
        .isLUI_mem      (isLUI_mem),
        .aluout_mem     (aluout_mem),
        .rR2_data_mem   (rs2_data_mem),
        .pcadd4_mem     (pcadd4_mem),
        .rRd_mem         (rRd_mem),
        .RegWrite_mem    (RegWrite_mem),
        .MemWrite_mem    (MemWrite_mem),
        .MemToReg_mem    (MemToReg_mem),
        .LdSrc_mem       (LdSrc_mem),
        .StSrc_mem       (StSrc_mem),
        .Sext_mem        (Sext_mem),
        .imm_mem         (imm_mem),
        .pc_mem          (pc_mem),
        .have_inst_ex    (have_inst_ex),
        .have_inst_mem   (have_inst_mem)
    );

    logic [DATAWIDTH-1:0] dram_rdata_mem;
    MEM #( .DATAWIDTH(DATAWIDTH) ) MEM_inst(
        .alu_out    (aluout_mem),
        .rR2_data   (rs2_data_mem),
        .bus_rdata  (bus_rdata),
        .LdSrc      (LdSrc_mem),
        .StSrc      (StSrc_mem),
        .MemWrite   (MemWrite_mem),
        .Sext       (Sext_mem),
        .bus_addr   (bus_addr),
        .bus_wdata  (bus_wdata),
        .bus_wen    (bus_wen),
        .dram_rdata_mem(dram_rdata_mem)
    ); 
    
    //logic [31:0] instr_wb;
    //logic RegWrite_wb;
    logic [1:0] MemToReg_wb;
    logic [31:0] aluout_wb;
    logic [31:0] imm_wb;
    logic [31:0] pcadd4_wb;
    logic [31:0] d_rdata_wb;
    logic [31:0] pc_wb;
    logic have_inst_wb;

    MEM_WB #(
        .RESET_VAL  (RESET_VAL)
        )mem_wb_inst(
        .clk             (cpu_clk),
        .rst             (cpu_rst),
        .rRd_mem         (rRd_mem),
        //.instr_mem       (instr_mem),
        .RegWrite_mem    (RegWrite_mem),
        .MemToReg_mem    (MemToReg_mem),
        .aluout_mem      (aluout_mem),
        .imm_mem         (imm_mem),
        .pcadd4_mem      (pcadd4_mem),
        .d_rdata_mem     (dram_rdata_mem),
        .pc_mem          (pc_mem),
        .rRd_wb          (rRd_wb),
        .RegWrite_wb     (RegWrite_wb),
        .MemToReg_wb     (MemToReg_wb),
        .aluout_wb       (aluout_wb),
        .imm_wb          (imm_wb),
        .pcadd4_wb       (pcadd4_wb),
        .d_rdata_wb      (d_rdata_wb),
        .pc_wb           (pc_wb),
        .have_inst_mem   (have_inst_mem),
        .have_inst_wb    (have_inst_wb)
    );

    //logic [31:0] RF_wdata_wb;
     MUX4_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_rf_wdata(
        .A          (pcadd4_wb),//0
        .B          (aluout_wb),//1
        .C          (d_rdata_wb),//2
        .D          (imm_wb),//3 处理lui指令，直接将立即数写入寄存器
        .Control    (MemToReg_wb),
        .Result     (RF_wdata_wb)
    );

    // Debug Interface
    // ==========================================
    // 修复 Difftest 时序错位问题
    // ==========================================
    
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
            last_wen   <= RegWrite_wb;    // 锁存当前指令是否写寄存器
            last_reg   <= rRd_wb; 
            last_value <= RF_wdata_wb;    // 锁存计算出的写回值
        end
    end

    // 让 Debug 端口输出锁存后的值（即上一条指令）
    assign debug_wb_have_inst = last_have_inst; 
    assign debug_wb_pc        = last_pc;    // 现在这里会输出 0 了！
    assign debug_wb_ena       = last_wen;
    assign debug_wb_reg       = last_reg;
    assign debug_wb_value     = last_value;
endmodule

