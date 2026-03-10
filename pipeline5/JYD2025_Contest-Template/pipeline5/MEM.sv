module MEM#(
    parameter DATAWIDTH = 32
)(
    input logic [DATAWIDTH - 1 : 0] alu_out,
    input logic [DATAWIDTH - 1 : 0] rR2_data,
    input logic [DATAWIDTH - 1 : 0] bus_rdata,
    input logic [1 : 0] LdSrc,
    input logic [1 : 0] StSrc,
    input logic MemWrite,
    input logic Sext,
    output logic [DATAWIDTH - 1 : 0] bus_addr,
    output logic [DATAWIDTH - 1 : 0] bus_wdata,
    output logic [3 : 0] bus_wen,
    output logic [DATAWIDTH - 1 : 0] dram_rdata_mem

);
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

    // logic [DATAWIDTH -1 : 0] dram_rdata_wb; // removed duplicate declaration
    MUX3_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_dram_rdata_wb(
        .A          (bus_rdata),//00 lw
        .B          (lb_data),//01 lb
        .C          (lh_data),//10 lh
        .Control    (LdSrc),
        .Result     (dram_rdata_mem)
    );


    //32位地址线 32位数据线（读写） 
    //lw/sw通过alu计算出的地址是按照字节寻址，但是存储器是字寻址
    //assign dram_addr  = alu_out >> 2; // 0x0,0x4,0x8 --> 0,1,2...
    assign bus_addr  = alu_out;
    //assign dram_wdata = rR2_data;
    //assign dram_wen   = MemWrite;
    always_comb begin
        case(StSrc)
            2'b00:   bus_wdata = rR2_data;              // sw: 完整写入
            2'b01:   bus_wdata = {4{rR2_data[7:0]}};    // sb: 复制4份 (AA_AA_AA_AA)
            2'b10:   bus_wdata = {2{rR2_data[15:0]}};   // sh: 复制2份 (BBBB_BBBB)
            default: bus_wdata = rR2_data;
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
endmodule
