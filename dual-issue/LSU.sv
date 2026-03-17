`timescale 1ns / 1ps
`include "config.sv"

module LSU(
    input  logic        clk,
    input  logic        rst,
    
    // Control from Issue
    input  logic        lsu_valid, 
    input  logic [31:0] lsu_opcode_inst,
    input  logic [31:0] lsu_opcode_pc,
    input  logic [ 4:0] lsu_opcode_rd_idx,
    input  logic [31:0] lsu_opcode_ra_operand, // Base address
    input  logic [31:0] lsu_opcode_rb_operand, // Data to store
    
    // Interface to BRAM
    output logic [31:0] mem_addr,
    output logic [31:0] mem_data_wr,
    output logic [ 3:0] mem_wr, 
    input  logic [31:0] mem_data_rd, 
    
    // Output to Writeback
    output logic        writeback_valid,
    output logic [ 4:0] writeback_rd_idx,
    output logic [31:0] writeback_value  
);

    wire [2:0] funct3 = lsu_opcode_inst[14:12];
    wire [6:0] op     = lsu_opcode_inst[6:0];
    wire is_load      = (op == 7'h03);
    wire is_store     = (op == 7'h23);
    
    wire [31:0] offset = is_load ? {{20{lsu_opcode_inst[31]}}, lsu_opcode_inst[31:20]} :
                                   {{20{lsu_opcode_inst[31]}}, lsu_opcode_inst[31:25], lsu_opcode_inst[11:7]};
    wire [31:0] addr   = lsu_opcode_ra_operand + offset;
    
    assign mem_addr = addr;// dont consider misaligned access for now 

    always_comb begin
        mem_wr      = 4'b0000;
        mem_data_wr = lsu_opcode_rb_operand;
        
        if (lsu_valid && is_store) begin
            case (funct3)
                3'b000: begin // SB
                    mem_wr = (4'b0001 << addr[1:0]);
                    mem_data_wr = {4{lsu_opcode_rb_operand[7:0]}};
                end
                3'b001: begin // SH
                    mem_wr = (addr[1]) ? 4'b1100 : 4'b0011;
                    mem_data_wr = {2{lsu_opcode_rb_operand[15:0]}};
                end
                3'b010: begin // SW
                    mem_wr = 4'b1111;
                    mem_data_wr = lsu_opcode_rb_operand;
                end
            endcase
        end
    end

    logic [1:0] addr_lsb_q;
    logic [2:0] funct3_q;
    logic       is_load_q;
    logic [4:0] rd_idx_q;

    always_ff @(posedge clk) begin
        if (rst) begin
            is_load_q <= 1'b0;
            rd_idx_q <= 5'd0;
        end 
        else begin
            is_load_q  <= lsu_valid  && is_load;
            funct3_q   <= funct3;
            addr_lsb_q <= addr[1:0];
            rd_idx_q   <= lsu_opcode_rd_idx;
        end
    end

    always_comb begin
        writeback_valid = is_load_q;
        writeback_rd_idx = rd_idx_q;
        writeback_value = mem_data_rd;

        if (is_load_q) begin
            case (funct3_q)
                3'b000: begin // LB
                    case (addr_lsb_q)
                        2'b00: writeback_value = {{24{mem_data_rd[7]}},  mem_data_rd[7:0]};
                        2'b01: writeback_value = {{24{mem_data_rd[15]}}, mem_data_rd[15:8]};
                        2'b10: writeback_value = {{24{mem_data_rd[23]}}, mem_data_rd[23:16]};
                        2'b11: writeback_value = {{24{mem_data_rd[31]}}, mem_data_rd[31:24]};
                    endcase
                end
                3'b001: begin // LH
                    case (addr_lsb_q[1])
                        1'b0: writeback_value = {{16{mem_data_rd[15]}}, mem_data_rd[15:0]};
                        1'b1: writeback_value = {{16{mem_data_rd[31]}}, mem_data_rd[31:16]};
                    endcase
                end
                3'b100: begin // LBU
                    case (addr_lsb_q)
                        2'b00: writeback_value = {24'b0, mem_data_rd[7:0]};
                        2'b01: writeback_value = {24'b0, mem_data_rd[15:8]};
                        2'b10: writeback_value = {24'b0, mem_data_rd[23:16]};
                        2'b11: writeback_value = {24'b0, mem_data_rd[31:24]};
                    endcase
                end
                3'b101: begin // LHU
                    case (addr_lsb_q[1])
                        1'b0: writeback_value = {16'b0, mem_data_rd[15:0]};
                        1'b1: writeback_value = {16'b0, mem_data_rd[31:16]};
                    endcase
                end
                3'b010: writeback_value = mem_data_rd; // LW
                default: ;
            endcase
        end
    end

endmodule
