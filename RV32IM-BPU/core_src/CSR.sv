`include "./config.sv"
module CSR(
    input  logic [ 0:0] clk,
    input  logic [ 0:0] rst,
    input  logic [11:0] raddr,
    input  logic [11:0] waddr,
    input  logic [ 0:0] we,
    input  logic [31:0] wdata,
    output logic [31:0] rdata,

    output logic [31:0] mepc_out,
    input  logic [31:0] pc_wb,

    output logic [31:0] mtvec_out,

    input  logic [31:0] mcause_in,

    input  logic [ 2:0] priv_vec_wb
);

    localparam MSTATUS_MIE  = 32'h0000_0008;
    localparam MSTATUS_MPIE = 32'h0000_0080;
    localparam MSTATUS_MASK = MSTATUS_MIE | MSTATUS_MPIE;

    wire has_exp = |mcause_in;
    reg [31:0] mstatus;

    logic [31:0] mstatus_next;
    always_comb begin
        if(has_exp) begin
            mstatus_next = {mstatus[31:8],mstatus[3],mstatus[6:4],1'b0,mstatus[2:0]};
        end
        else if(priv_vec_wb[`MRET]) begin
            mstatus_next = {mstatus[31:8],1'b1,mstatus[6:4],mstatus[7],mstatus[2:0]};
        end
        else if(waddr == `CSR_MSTATUS && we) begin
            mstatus_next = wdata & MSTATUS_MASK;
        end
        else begin
            mstatus_next = mstatus;
        end
    end

    always_ff @(posedge clk) begin
        if(rst) begin
            mstatus <= 32'h0;
        end
        else begin
            mstatus <= mstatus_next;
        end
    end

    reg [31:0] mtvec;

    assign mtvec_out = mtvec;
    
    always_ff @(posedge clk) begin
        if(rst) begin
            mtvec <= 32'h0;
        end
        else if(waddr == `CSR_MTVEC && we) begin
            mtvec <=  wdata;
        end
    end

    reg [31:0] mcause;
    always_ff @(posedge clk) begin
        if(rst) begin
            mcause <= 32'h0;
        end
        else if(has_exp) begin
            mcause <= mcause_in;
        end
        else if(waddr == `CSR_MCAUSE && we) begin
            mcause <= wdata;
        end
    end

    reg [31:0] mepc;
    assign mepc_out = mepc;
    always_ff @(posedge clk) begin
        if(rst) begin
            mepc <= 32'h0;
        end
        else if(has_exp) begin
            mepc <= pc_wb;
        end
        else if(waddr == `CSR_MEPC && we) begin
            mepc <= wdata;
        end
    end

    reg [31:0] mscratch;
    always_ff @(posedge clk) begin
        if(rst) begin
            mscratch <= 32'h0;
        end
        else if(waddr == `CSR_MSCRATCH && we) begin
            mscratch <= wdata;
        end
    end
    // read
    //always_comb begin
    always_comb begin 
        case(raddr)
            `CSR_MSTATUS:
                rdata = mstatus_next;
            `CSR_MTVEC  : begin
                if(we&&waddr==`CSR_MTVEC) 
                    rdata = wdata;
                else
                    rdata = mtvec;
            end
            `CSR_MCAUSE : begin
                if(we&&waddr==`CSR_MCAUSE) 
                    rdata = wdata;
                else
                    rdata = mcause;
            end
            `CSR_MEPC   : begin
                if(we&&waddr==`CSR_MEPC) 
                    rdata = wdata;
                else
                    rdata = mepc;
            end
            `CSR_MSCRATCH : begin
                if(we&&waddr==`CSR_MSCRATCH) 
                    rdata = wdata;
                else
                    rdata = mscratch;
            end
            default     : rdata = 32'h0;
        endcase
    end
    
endmodule
