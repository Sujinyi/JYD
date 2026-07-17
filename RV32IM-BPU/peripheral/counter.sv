`timescale 1ns / 1ps

module counter(
    input  logic         cpu_clk,
    input  logic         cnt_clk,
    input  logic         rst,

    input  logic         start_req,
    input  logic         stop_req,
    output logic [31:0]  perip_rdata
);

    logic        start_tgl_cpu;
    logic        stop_tgl_cpu;
    logic [1:0]  start_tgl_cnt_sync;
    logic [1:0]  stop_tgl_cnt_sync;
    logic        start_run;
    logic [15:0] cnt_1ms;
    //logic [18:0] cnt_1ms;
    logic [31:0] cnt_ms;
    logic [31:0] cnt_ms_gray;
    logic [31:0] cnt_ms_gray_cpu_sync1;
    logic [31:0] cnt_ms_gray_cpu_sync2;

    function automatic logic [31:0] gray_to_bin(input logic [31:0] gray);
        logic [31:0] bin;
        integer i;
        begin
            bin[31] = gray[31];
            for (i = 30; i >= 0; i = i - 1) begin
                bin[i] = bin[i + 1] ^ gray[i];
            end
            gray_to_bin = bin;
        end
    endfunction

    always_ff @(posedge cpu_clk) begin
        if (rst) begin
            start_tgl_cpu <= 1'b0;
            stop_tgl_cpu <= 1'b0;
        end else begin
            if (start_req) begin
                start_tgl_cpu <= ~start_tgl_cpu;
            end
            if (stop_req) begin
                stop_tgl_cpu <= ~stop_tgl_cpu;
            end
        end
    end

    always_ff @(posedge cnt_clk) begin
        if (rst) begin
            start_tgl_cnt_sync <= 2'b00;
            stop_tgl_cnt_sync <= 2'b00;
        end else begin
            start_tgl_cnt_sync <= {start_tgl_cnt_sync[0], start_tgl_cpu};
            stop_tgl_cnt_sync <= {stop_tgl_cnt_sync[0], stop_tgl_cpu};
        end
    end

    wire start_req_cnt = start_tgl_cnt_sync[1] ^ start_tgl_cnt_sync[0];
    wire stop_req_cnt = stop_tgl_cnt_sync[1] ^ stop_tgl_cnt_sync[0];

    always_ff @(posedge cnt_clk) begin
        if (rst) begin
            start_run <= 1'b0;
        end else if (start_req_cnt) begin
            start_run <= 1'b1;
        end else if (stop_req_cnt) begin
            start_run <= 1'b0;
        end
    end

    always_ff @(posedge cnt_clk) begin
        if (rst) begin
            cnt_1ms <= 19'd0;
        end else if (start_run) begin
            if (cnt_1ms == 16'd49999) begin
            //if (cnt_1ms == 19'd499999) begin
                cnt_1ms <= 19'd0;
            end else begin
                cnt_1ms <= cnt_1ms + 19'd1;
            end
        end else begin
            cnt_1ms <= 19'd0;
        end
    end

    always_ff @(posedge cnt_clk) begin
        if (rst) begin
            cnt_ms <= 32'd0;
        end else if (start_run && (cnt_1ms == 16'd49999)) begin
        //end else if (start_run && (cnt_1ms == 19'd499999)) begin
            cnt_ms <= cnt_ms + 32'd1;
        end
    end

    assign cnt_ms_gray = cnt_ms ^ (cnt_ms >> 1);

    always_ff @(posedge cpu_clk) begin
        if (rst) begin
            cnt_ms_gray_cpu_sync1 <= 32'd0;
            cnt_ms_gray_cpu_sync2 <= 32'd0;
        end else begin
            cnt_ms_gray_cpu_sync1 <= cnt_ms_gray;
            cnt_ms_gray_cpu_sync2 <= cnt_ms_gray_cpu_sync1;
        end
    end

    assign perip_rdata = gray_to_bin(cnt_ms_gray_cpu_sync2);

endmodule
