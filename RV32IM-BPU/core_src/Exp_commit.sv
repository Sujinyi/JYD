`timescale 1ns/100ps
`include "./config.sv"
module Exp_Commit(
    input  logic [ 2:0] priv_vec,
    output logic [31:0] exp_code
);
    always_comb begin
        exp_code = 0;
        if(priv_vec[`ECALL]) begin
            exp_code = 32'hb;
        end
    end
endmodule
