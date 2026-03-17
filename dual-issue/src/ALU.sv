`timescale 1ns / 1ps
`include "config.sv"

//////////////////////////////////////////////////////////////////////////////////
// Simplified Behavioral ALU for RV32I
//////////////////////////////////////////////////////////////////////////////////

module ALU(
    input  logic [31:0] sr1,
    input  logic [31:0] sr2,
    input  logic [ 3:0] alu_op,
    output logic [31:0] result
);

    always_comb begin
        case(alu_op) 
            `ADD:   result = sr1 + sr2;
            `SUB:   result = sr1 - sr2;
            `AND:   result = sr1 & sr2;
            `OR:    result = sr1 | sr2;
            `XOR:   result = sr1 ^ sr2;
            `SLT:   result = ($signed(sr1) < $signed(sr2)) ? 32'd1 : 32'd0;
            `SLTU:  result = (sr1 < sr2) ? 32'd1 : 32'd0;
            `SLL:   result = sr1 << sr2[4:0];
            `SRL:   result = sr1 >> sr2[4:0];
            `SRA:   result = $signed(sr1) >>> sr2[4:0];
            default: result = sr1; // Default to passing through sr1
        endcase
    end

endmodule
