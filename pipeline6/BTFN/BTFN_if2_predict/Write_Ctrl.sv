`include "config.sv"
module Write_Ctrl(
    input  logic [31:0] mem_wdata,
    input  logic [ 1:0] alu_result,
    input  logic [ 4:0] mem_access,
    output logic [31:0] wdata,
    output logic [ 3:0] d_wstrb
);
    wire is_store = mem_access[`STORE_BIT];
    wire [2:0] store_type = mem_access[2:0];

    always_comb begin
        wdata = 32'h0;
        d_wstrb = 4'b0;
        
        if (is_store) begin
            case(store_type)
            `STORE_B: begin
                wdata = {4{mem_wdata[7:0]}};
                case(alu_result)
                2'b00: d_wstrb = 4'b0001;
                2'b01: d_wstrb = 4'b0010;
                2'b10: d_wstrb = 4'b0100;
                2'b11: d_wstrb = 4'b1000;
                endcase
            end
            `STORE_H: begin
                wdata = {2{mem_wdata[15:0]}};
                case(alu_result[1])
                1'b0: d_wstrb = 4'b0011;
                1'b1: d_wstrb = 4'b1100;
                endcase
            end
            `STORE_W: begin
                wdata = mem_wdata;
                d_wstrb = 4'b1111;
            end
            default: begin
                wdata = 32'h0;
                d_wstrb = 4'b0000;
            end
            endcase
        end
    end

endmodule