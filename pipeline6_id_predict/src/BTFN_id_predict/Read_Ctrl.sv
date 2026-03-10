`include "config.sv"
module Read_Ctrl(
    input  logic [31:0] mem_rdata,
    input  logic [ 1:0] mem_raddr,
    input  logic [ 4:0] mem_access,
    output logic [31:0] rdata
);
    wire is_load            = mem_access[`LOAD_BIT];
    wire [2:0] load_type    = mem_access[2:0];
    wire [31:0] load_data   = mem_rdata;

    always_comb begin
        case(load_type)
        `LOAD_B: begin
            case(mem_raddr[1:0])
            2'b00: rdata = {{24{load_data[7]}}, load_data[7:0]};
            2'b01: rdata = {{24{load_data[15]}}, load_data[15:8]};
            2'b10: rdata = {{24{load_data[23]}}, load_data[23:16]};
            2'b11: rdata = {{24{load_data[31]}}, load_data[31:24]};
            endcase
        end
        `LOAD_H: begin
            case(mem_raddr[1:0])
            2'b00: rdata = {{16{load_data[15]}}, load_data[15:0]};
            2'b10: rdata = {{16{load_data[31]}}, load_data[31:16]};
            default: rdata = 32'h0;
            endcase
        end
        `LOAD_W: begin
            rdata = load_data;
        end
        `LOAD_UB: begin
            case(mem_raddr[1:0])
            2'b00: rdata = {24'h0, load_data[7:0]};
            2'b01: rdata = {24'h0, load_data[15:8]};
            2'b10: rdata = {24'h0, load_data[23:16]};
            2'b11: rdata = {24'h0, load_data[31:24]};
            endcase
        end
        `LOAD_UH: begin
            case(mem_raddr[1:0])
            2'b00: rdata = {16'h0, load_data[15:0]};
            2'b10: rdata = {16'h0, load_data[31:16]};
            default: rdata = 32'h0;
            endcase
        end
        default: begin
            rdata = 32'h0;
        end
        endcase
    end
endmodule