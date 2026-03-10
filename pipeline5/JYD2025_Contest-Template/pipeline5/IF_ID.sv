module IF_ID#(
    parameter RESET_VAL = 32'h8000_0000
)(
    input logic clk,
    input logic rst,
    input logic [31:0] pcadd4_if,
    input logic [31:0] instr_if,
    input logic [31:0] pc_if,
    input logic stall,
    input logic flush,
    output logic [31:0] pcadd4_id,
    output logic [31:0] instr_id,
    output logic [31:0] pc_id
    );
    always_ff @( posedge clk ) begin
        if(rst) begin
            pcadd4_id <= 32'b0;
            instr_id <= 32'b0;
            pc_id <= RESET_VAL;
        end
        else begin
            if(flush) begin
                pcadd4_id <= 32'b0;
                instr_id <= 32'b0;
                pc_id <= RESET_VAL;
            end
            else if(stall) begin
                pcadd4_id <= pcadd4_id;
                instr_id <= instr_id;
                pc_id <= pc_id;
            end
            else begin
                pcadd4_id <= pcadd4_if;
                instr_id <= instr_if;
                pc_id <= pc_if;
            end
        end
    end
        
endmodule