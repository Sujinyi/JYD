`include "config.sv"
module Decoder(
    input logic [6:0] opcode,
    output logic exec,
    output logic lsu,
    output logic branch,
    output logic rd_valid
);
    always_comb begin
            exec = 1'b0;
            lsu = 1'b0;
            branch = 1'b0;
            rd_valid = 1'b0;
        case(opcode)
        'h37: begin
            // lui, U_TYPE
            exec = 1'b1;
            lsu = 1'b0;
            branch = 1'b0;
            rd_valid = 1'b1;
        end
        'h17: begin
            // auipc, U_TYPE
            exec = 1'b1;
            lsu = 1'b0;
            branch = 1'b0;
            rd_valid = 1'b1;
        end
        'h6f: begin
            // jal, J_TYPE
            exec = 1'b0;
            lsu = 1'b0;
            branch = 1'b1;
            rd_valid = 1'b1;
        end
        'h67: begin
            // jalr, I_TYPE
            exec = 1'b0;
            lsu = 1'b0;
            branch = 1'b1;
            rd_valid = 1'b1;
        end
        'h63: begin
            // branch, B_TYPE
            exec = 1'b0;
            lsu = 1'b0;
            branch = 1'b1;
            rd_valid = 1'b0;
        end
        'h03: begin
            // load, I_TYPE
            exec = 1'b0;
            lsu = 1'b1;
            branch = 1'b0;
            rd_valid = 1'b1;
        end
        'h23: begin
            // store, S_TYPE
            exec = 1'b0;
            lsu = 1'b1;
            branch = 1'b0;
            rd_valid = 1'b0;
        end
        'h13: begin
            // imm, I_TYPE
            exec = 1'b1;
            lsu = 1'b0;
            branch = 1'b0;
            rd_valid = 1'b1;
        end
        'h33: begin
            // R_TYPE
            exec = 1'b1;
            lsu = 1'b0;
            branch = 1'b0;
            rd_valid = 1'b1;
        end
        endcase
    end

endmodule
