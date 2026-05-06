module Regfile(
    input  logic [ 0:0] clk,
    input  logic [ 0:0] rst,
    input  logic [ 4:0] raddr1,
    input  logic [ 4:0] raddr2,
    input  logic [ 4:0] waddr,
    input  logic [31:0] wdata,
    input  logic        we,
    output logic [31:0] rdata1,
    output logic [31:0] rdata2
);
    logic [31:0] rf [31:0];
    /*
    always_ff @(posedge clk) begin
        if (we) begin
            rf[waddr] <= wdata;
        end
    end*/
    always_ff @(posedge clk) begin
        if(rst)
            for(int i = 0; i < 32; i++)
                rf[i] <= 32'd0;
        else if(we && waddr != 5'd0)
                rf[waddr] <= wdata;
    end

    assign rdata1 = (raddr1 == 5'd0) ? 32'd0
    :(we && waddr == raddr1) ? wdata : rf[raddr1];
    assign rdata2 = (raddr2 == 5'd0) ? 32'd0
    :(we && waddr == raddr2) ? wdata : rf[raddr2];
endmodule