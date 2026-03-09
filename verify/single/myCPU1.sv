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
    output               debug_wb_ena,
    output logic [ 4:0]  debug_wb_reg,
    output logic [31:0]  debug_wb_value

);

    logic [DATAWIDTH -1 : 0] pc_out;
    logic [DATAWIDTH -1 : 0] pcadd4;
    logic [DATAWIDTH -1 : 0] npc_imm;

    //logic PcSrc;
    logic [1:0] LdSrc;
    logic [1:0] StSrc;
    logic Sext;

    //assign i_addr = pc_out; //这里直接输出32位地址，后面再做移位
    //logic [DATAWIDTH -1 :0] instruction;
    logic [DATAWIDTH - 1:0] npc;

    // 修改逻辑：加一个 MUX 或者逻辑与
    logic [31:0] real_npc;
    // 如果正在复位，强制下个 PC 也是 0。
    // 这样当复位撤销的那一瞬间，PC 采到的 D 端数据是 0，而不是 4。
    assign real_npc = cpu_rst ? 32'h0 : npc;

    PC #(
        .DATAWIDTH  (DATAWIDTH),
        .RESET_VAL  (RESET_VAL)
    ) pc_inst(
        .clk        (cpu_clk),
        .rst        (cpu_rst),
        .npc        (real_npc),
        .pc_out     (pc_out)
    );

    logic True;
    logic [DATAWIDTH - 1:0] npc_offset;
    logic [1:0] npc_op;

    NPC #(
        .DATAWIDTH  (DATAWIDTH)
    ) npc_inst(
        .isTrue     (True),
        .npc_op     (npc_op),
        .pc         (pc_out),
        .offset     (npc_offset),
        .npc        (npc),
        .pcadd4     (pcadd4)
    );

    logic OffsetOrigin;
    logic [DATAWIDTH - 1 : 0] imm; 
    logic  [DATAWIDTH - 1 : 0] alu_out;

    MUX2_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_npc_offset(
        .A          (imm),//0
        .B          (alu_out),//1
        .Control    (OffsetOrigin),
        .Result     (npc_offset)
    );

    //地址线32位 数据线32位
    //存储器是字寻址 pc也是字节寻址 所以pc>>2
    //assign irom_addr = pc_out >> 2; // 0x0,0x4,0x8 --> 0,1,2...
    assign irom_addr = pc_out;
    logic [DATAWIDTH - 1 : 0] instruction;
    assign instruction = irom_rdata;

/*
    instr_rom #(
    .DATAWIDTH   (DATAWIDTH)  ,
    .RAMWIDTH    (8 )         ,
    .RAMDEPTH    (8)  
    ) instr_rom_inst (
        .ena      (1'b1),
        .daddr    (i_addr),//输入32位地址 去取指令
        .dout     (instruction)//输出32位指令
    );
*/

    logic RegWrite;
    logic [DATAWIDTH - 1 : 0] RF_wdata;
    logic [DATAWIDTH - 1 : 0] rs1_data;
    logic [DATAWIDTH - 1 : 0] rs2_data;

    RF #(
        .ADDR_WIDTH (5),
        .DATAWIDTH  (DATAWIDTH)
    )reg_file_inst (
        .clk             (cpu_clk),
        .rst             (cpu_rst),
        .wen       (RegWrite),
        .waddr     (instruction[11:7]),
        .wdata        (RF_wdata),
        .rR1    (instruction[19:15]),
        .rR2    (instruction[24:20]),
        .rR1_data   (rs1_data),
        .rR2_data   (rs2_data)
    );

    IMMGEN #(
        .DATAWIDTH  (32)	
    )imm_gen_inst (
        .instr   (instruction),
        .imm     (imm)  
    );

    logic [1:0] MemToReg;
    logic MemWrite;
    logic alua_sel;
    logic alub_sel;

    Control control_inst (
        .opcode      (instruction[6:0]),
        .funct       ({instruction[30],instruction[14:12]}),
        .NpcOp       (npc_op),
        .RegWrite    (RegWrite),
        .MemToReg    (MemToReg),
        .MemWrite    (MemWrite),
        .OffsetOrigin(OffsetOrigin),
        //.ALUSrc      (ALUSrc),
        .alua_sel    (alua_sel),
        .alub_sel    (alub_sel),
        //.PcSrc       (PcSrc),//0:pcadd4, 1:pc_auipc
        .LdSrc       (LdSrc),//00:lw, 01:lb(u),10:lh(u)
        .StSrc       (StSrc),//00:sw, 01:sb, 10:sh
        .Sext        (Sext) //0:zero_ext, 1:sign_ext
    );

    logic [3:0] ALUControl;
    ACTL ALU_controller_inst(
        .opcode       (instruction[6:0]),
        //.ALUOP        (ALUOP),
        .funct        ({instruction[30],instruction[14:12]}),
        .ALUControl   (ALUControl) 
    );

    logic [DATAWIDTH - 1 : 0] alu_b;
    MUX2_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_alu_b(
        .A          (rs2_data),//0
        .B          (imm),//1
        .Control    (alub_sel),
        .Result     (alu_b)
    );

    logic [DATAWIDTH - 1 : 0] alu_a;
    MUX2_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_alu_a(
        .A          (rs1_data),//0
        .B          (pc_out),//1
        .Control    (alua_sel),
        .Result     (alu_a)
    );

    ALU# (
        .DATAWIDTH  (DATAWIDTH)	
    ) alu_inst (
        .A           (alu_a),
        .B           (alu_b),
        .ALUControl  (ALUControl),
        .Result      (alu_out),
        .isTrue      (True)
    );
/*  
    logic [7:0] byte_sel;
    assign byte_sel = 
        (alu_out[1:0] == 2'b00) ? bus_rdata[7:0] :
        (alu_out[1:0] == 2'b01) ? bus_rdata[15:8] :
        (alu_out[1:0] == 2'b10) ? bus_rdata[23:16] :
                                   bus_rdata[31:24];

    logic [DATAWIDTH - 1 : 0] lb_data;
    MUX2_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_lbdata(
        .A          ({24'd0,byte_sel}),//0 lbu
        .B          ({{24{byte_sel[7]}},byte_sel}),//1 lb
        .Control    (Sext),
        .Result     (lb_data)
    );

    logic [15: 0] halfword_sel;

    assign halfword_sel = alu_out[1] ? bus_rdata[31:16] : bus_rdata[15:0];

    logic [DATAWIDTH - 1 : 0] lh_data;
    MUX2_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_lhdata(
        .A          ({16'd0,halfword_sel}),//0 lhu
        .B          ({{16{halfword_sel[15]}},halfword_sel}),//1 lh
        .Control    (Sext),
        .Result     (lh_data)
    );


    logic [DATAWIDTH -1 : 0] dram_rdata_wb;
    MUX3_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_dram_rdata_wb(
        .A          (bus_rdata),//00 lw
        .B          (lb_data),//01 lb
        .C          (lh_data),//10 lh
        .Control    (LdSrc),
        .Result     (dram_rdata_wb)
    );


    //32位地址线 32位数据线（读写） 
    //lw/sw通过alu计算出的地址是按照字节寻址，但是存储器是字寻址
    //assign dram_addr  = alu_out >> 2; // 0x0,0x4,0x8 --> 0,1,2...
    assign bus_addr  = alu_out;
    //assign dram_wdata = rs2_data;
    //assign dram_wen   = MemWrite;
    always_comb begin
        case(StSrc)
            2'b00:   bus_wdata = rs2_data;              // sw: 完整写入
            2'b01:   bus_wdata = {4{rs2_data[7:0]}};    // sb: 复制4份 (AA_AA_AA_AA)
            2'b10:   bus_wdata = {2{rs2_data[15:0]}};   // sh: 复制2份 (BBBB_BBBB)
            default: bus_wdata = rs2_data;
        endcase
    end
  
    always_comb begin 
        if(!MemWrite) begin
            bus_wen = 4'b0000;
        end
        else begin
            case (StSrc)
                2'b00: bus_wen = 4'b1111; // sw
                2'b01: begin // sb
                    case (alu_out[1:0])
                        2'b00: bus_wen = 4'b0001;
                        2'b01: bus_wen = 4'b0010;
                        2'b10: bus_wen = 4'b0100;
                        2'b11: bus_wen = 4'b1000;
                        default: bus_wen = 4'b0000;
                    endcase
                end
                2'b10: begin // sh
                    case (alu_out[1])
                        1'b0: bus_wen = 4'b0011;
                        1'b1: bus_wen = 4'b1100;
                        default: bus_wen = 4'b0000;
                    endcase
                end 
                default: bus_wen = 4'b0000;
            endcase
        end
    end

    data_ram #(
        .DATAWIDTH   (DATAWIDTH)  ,
        .RAMWIDTH    (8)         ,
        .RAMDEPTH    (8)  
    )data_ram_inst(
        .clk      (clk),
        .rst      (rst),
        .ena      (1'b1),
        .wen      (MemWrite),
        .din      (rs2_data),//32位数据输入 sw rs2,offset(rs1)
        .daddr    (d_addr),
        .dout     (data_ram_out)//32位数据输出
    );
*/    

   
/*
    logic [DATAWIDTH - 1 : 0] pc_auipc;
    assign pc_auipc = pc_out + imm;
    logic [DATAWIDTH - 1 : 0] pc_wb;
    MUX2_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_pc_wb(
        .A          (pcadd4),//0
        .B          (pc_auipc),//1
        .Control    (PcSrc),
        .Result     (pc_wb)
    );
*/

    logic [DATAWIDTH-1:0] dram_rdata_wb;
    MEM #( .DATAWIDTH(DATAWIDTH) ) MEM_inst(
        .alu_out    (alu_out),
        .rR2_data   (rs2_data),
        .bus_rdata  (bus_rdata),
        .LdSrc      (LdSrc),
        .StSrc      (StSrc),
        .MemWrite   (MemWrite),
        .Sext       (Sext),
        .bus_addr   (bus_addr),
        .bus_wdata  (bus_wdata),
        .bus_wen    (bus_wen),
        .dram_rdata_wb(dram_rdata_wb)
    );  

    MUX4_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_dout(
        .A          (pcadd4),//0
        .B          (alu_out),//1
        .C          (dram_rdata_wb),//2
        .D          (imm),//3 处理lui指令，直接将立即数写入寄存器
        .Control    (MemToReg),
        .Result     (RF_wdata)
    );
   
    // Debug Interface
    // ==========================================
    // 修复 Difftest 时序错位问题
    // ==========================================
    
    // 定义一组寄存器，用于锁存“上一条”指令的执行结果
    logic [31:0] last_pc;
    logic        last_wen;
    logic [4:0]  last_reg;
    logic [31:0] last_value;

    always_ff @(posedge cpu_clk) begin
        if (cpu_rst) begin
            last_pc    <= 32'h0;
            last_wen   <= 1'b0;
            last_reg   <= 5'h0;
            last_value <= 32'h0;
        end
        else begin
            // 在时钟上升沿，锁存当前周期计算出的结果
            last_pc    <= pc_out;      // 锁存当前的 0
            last_wen   <= RegWrite;    // 锁存当前指令是否写寄存器
            last_reg   <= instruction[11:7]; 
            last_value <= RF_wdata;    // 锁存计算出的写回值
        end
    end

    // 让 Debug 端口输出锁存后的值（即上一条指令）
    assign debug_wb_have_inst = ~cpu_rst; 
    assign debug_wb_pc        = last_pc;    // 现在这里会输出 0 了！
    assign debug_wb_ena       = last_wen;
    assign debug_wb_reg       = last_reg;
    assign debug_wb_value     = last_value;
endmodule

