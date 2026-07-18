// 4-read 2-write register file using LVT (live value table).
// Same-cycle write to identical rd on both ports is forbidden (issue rule).
// Reads are write-first (bypass both write ports, port B younger).
module regfile_2w (
    input  wire        clk,
    input  wire [4:0]  rs1a, rs2a, rs1b, rs2b,
    output wire [31:0] rs1a_data, rs2a_data, rs1b_data, rs2b_data,
    input  wire        wena,
    input  wire [4:0]  rda,
    input  wire [31:0] wdataa,
    input  wire        wenb,
    input  wire [4:0]  rdb,
    input  wire [31:0] wdatab
);
    reg [31:0] rfa [0:31] /* verilator public_flat_rw */;
    reg [31:0] rfb [0:31] /* verilator public_flat_rw */;
    reg        lvt [0:31] /* verilator public_flat_rw */;

    integer i;
    initial begin
        for (i = 0; i < 32; i = i + 1) begin
            rfa[i] = 32'h0;
            rfb[i] = 32'h0;
            lvt[i] = 1'b0;
        end
    end

    always @(posedge clk) begin
        if (wena && rda != 5'd0) begin
            rfa[rda] <= wdataa;
            lvt[rda] <= 1'b0;
        end
        if (wenb && rdb != 5'd0) begin
            rfb[rdb] <= wdatab;
            lvt[rdb] <= 1'b1;
        end
    end

    function [31:0] rd_port;
        input [4:0] rs;
        begin
            rd_port = (rs == 5'd0) ? 32'h0 :
                      (wenb && rdb == rs) ? wdatab :
                      (wena && rda == rs) ? wdataa :
                      lvt[rs] ? rfb[rs] : rfa[rs];
        end
    endfunction

    assign rs1a_data = rd_port(rs1a);
    assign rs2a_data = rd_port(rs2a);
    assign rs1b_data = rd_port(rs1b);
    assign rs2b_data = rd_port(rs2b);
endmodule
