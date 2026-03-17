`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/03/14 19:47:57
// Design Name: 
// Module Name: RF
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module RF(
    input logic clk,
    input logic rst,
    input logic we0,
    input logic we1,
    input logic [4:0] rd0,
    input logic [4:0] rd1,
    input logic [31:0] rd0_value,
    input logic [31:0] rd1_value,
    input logic [4:0] ra0,
    input logic [4:0] rb0,
    input logic [4:0] ra1,
    input logic [4:0] rb1,

    output logic [31:0] ra0_value,
    output logic [31:0] rb0_value,
    output logic [31:0] ra1_value,
    output logic [31:0] rb1_value
    );

    logic [31:0] rf[31:0];
    integer i;
    always_ff @(posedge clk) begin
        if (rst) begin
            for (i = 0; i < 32; i = i + 1) begin
                rf[i] <= 32'd0;
            end
        end else begin
            if (we0&&rd0 != 5'b0) begin
                rf[rd0] <= rd0_value;
            end
            if (we1&&rd1 != 5'b0) begin
                rf[rd1] <= rd1_value;
            end
        end
    end

    assign ra0_value = (ra0 == 5'd0) ? 32'd0 : 
                       (we1 && rd1 == ra0) ? rd1_value : 
                       (we0 && rd0 == ra0) ? rd0_value : rf[ra0];

    assign rb0_value = (rb0 == 5'd0) ? 32'd0 : 
                       (we1 && rd1 == rb0) ? rd1_value : 
                       (we0 && rd0 == rb0) ? rd0_value : rf[rb0];

    assign ra1_value = (ra1 == 5'd0) ? 32'd0 : 
                       (we1 && rd1 == ra1) ? rd1_value : 
                       (we0 && rd0 == ra1) ? rd0_value : rf[ra1];

    assign rb1_value = (rb1 == 5'd0) ? 32'd0 : 
                       (we1 && rd1 == rb1) ? rd1_value : 
                       (we0 && rd0 == rb1) ? rd0_value : rf[rb1];

endmodule
