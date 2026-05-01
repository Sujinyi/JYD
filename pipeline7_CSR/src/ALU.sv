`include "config.sv"
module ALU(
    input  logic [31:0] sr1,
    input  logic [31:0] sr2,
    input  logic [ 4:0] alu_op,
    output logic [31:0] result
);

    always_comb begin
        case(alu_op) 
        `ADD:                   result = sr1 + sr2;
        // Lab3 TODO: finish the following cases

        `SUB:                   result = sr1 - sr2;
        `AND:                   result = sr1 & sr2;
        `SLT:                   result = $signed(sr1) < $signed(sr2);
        `SLTU:                  result = sr1 < sr2;
        `OR:                    result = sr1 | sr2;
        `XOR:                   result = sr1 ^ sr2;
        `SLL:                   result = sr1 << (sr2[4:0]);
        `SRL:                   result = sr1 >> (sr2[4:0]);
        `SRA:                   result = $signed(sr1) >>> (sr2[4:0]);

        default:                result = 0;
        endcase
    end
endmodule