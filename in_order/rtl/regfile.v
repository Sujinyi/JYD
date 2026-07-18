module regfile (
    input  wire        clk,
    input  wire [4:0]  rs1,
    input  wire [4:0]  rs2,
    output wire [31:0] rs1_data,
    output wire [31:0] rs2_data,
    input  wire        wen,
    input  wire [4:0]  rd,
    input  wire [31:0] rd_data
);
    reg [31:0] rf [0:31] /* verilator public_flat_rw */;

    integer i;
    initial begin
        for (i = 0; i < 32; i = i + 1) rf[i] = 32'h0;
    end

    always @(posedge clk) begin
        if (wen && rd != 5'd0) rf[rd] <= rd_data;
    end

    // write-first bypass (WB -> ID)
    assign rs1_data = (rs1 == 5'd0) ? 32'h0 :
                      (wen && rd == rs1) ? rd_data : rf[rs1];
    assign rs2_data = (rs2 == 5'd0) ? 32'h0 :
                      (wen && rd == rs2) ? rd_data : rf[rs2];
endmodule
