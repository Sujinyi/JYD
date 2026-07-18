// RV32M divide unit, multi-cycle, registered done/result outputs.
// (Multiplies are fully pipelined inside the core since the mul-pipe rework;
//  this unit now only serves DIV/DIVU/REM/REMU.)
// start: 1-cycle pulse (instruction entered EX, operands valid).
// Operands are CAPTURED into a_r/b_r first (the only flops fed by the deep
// forward network -- placeable next to it), everything else runs off those
// flops one cycle later:
//   div/0, signed-overflow : start+2               (3-cycle EX occupancy)
//   DIV*/REM*              : start+33              (34-cycle EX occupancy)
module muldiv (
    input  wire        clk,
    input  wire        rst,
    input  wire        start,
    input  wire [2:0]  funct3,
    input  wire [31:0] a,
    input  wire [31:0] b,
    output wire        done,
    output wire [31:0] result
);
    // stage 1: operand capture (fwd net -> flops, nothing else on the arc)
    reg         start_r;
    reg  [2:0]  f3_r;
    reg  [31:0] a_r, b_r;

    // special div cases judged on the REGISTERED operands
    wire div0  = (b_r == 32'd0);
    wire dovf  = !f3_r[0] && (a_r == 32'h8000_0000) && (b_r == 32'hFFFF_FFFF);
    reg         spec_r;
    reg  [31:0] spec_res_r;

    // ---------------- divider: restoring, 32 iterations ----------------
    reg  [31:0] dividend, divisor, quot;
    reg  [32:0] rem;
    reg  [5:0]  div_cnt;
    reg         div_busy;
    reg         q_neg, r_neg, rem_sel;
    wire [32:0] sub = {rem[31:0], dividend[31]} - {1'b0, divisor};

    wire [31:0] quot_fin = {quot[30:0], ~sub[32]};
    wire [31:0] rem_fin  = sub[32] ? {rem[30:0], dividend[31]} : sub[31:0];
    wire [31:0] div_out  = rem_sel ? (r_neg ? (~rem_fin  + 1'b1) : rem_fin)
                                   : (q_neg ? (~quot_fin + 1'b1) : quot_fin);
    wire div_done = div_busy && (div_cnt == 6'd1);
    // registered one cycle ahead (cnt==2 -> next cycle cnt==1): `done` is a
    // pure flop output, keeping the cnt-compare out of the
    // mstall -> issue -> queue-CE cone.
    reg  done_r;

    always @(posedge clk) begin
        if (rst) begin
            start_r  <= 1'b0;
            div_busy <= 1'b0;
            spec_r   <= 1'b0;
            done_r   <= 1'b0;
        end else begin
            start_r <= start;
            a_r     <= a;
            b_r     <= b;
            f3_r    <= funct3;
            spec_r  <= 1'b0;
            done_r  <= div_busy && (div_cnt == 6'd2);
            if (start_r && (div0 || dovf)) begin
                spec_r     <= 1'b1;
                spec_res_r <= div0 ? (f3_r[1] ? a_r : 32'hFFFF_FFFF)
                                   : (f3_r[1] ? 32'd0 : 32'h8000_0000);
            end else if (start_r) begin
                q_neg    <= !f3_r[0] && (a_r[31] ^ b_r[31]);
                r_neg    <= !f3_r[0] && a_r[31];
                rem_sel  <= f3_r[1];
                dividend <= (!f3_r[0] && a_r[31]) ? (~a_r + 1'b1) : a_r;
                divisor  <= (!f3_r[0] && b_r[31]) ? (~b_r + 1'b1) : b_r;
                rem      <= 33'd0;
                quot     <= 32'd0;
                div_cnt  <= 6'd32;
                div_busy <= 1'b1;
            end else if (div_busy) begin
                if (sub[32]) begin
                    rem  <= {rem[31:0], dividend[31]};
                    quot <= {quot[30:0], 1'b0};
                end else begin
                    rem  <= sub;
                    quot <= {quot[30:0], 1'b1};
                end
                dividend <= {dividend[30:0], 1'b0};
                div_cnt  <= div_cnt - 1'b1;
                if (div_done) div_busy <= 1'b0;
            end
        end
    end

    assign done   = spec_r | done_r;
    assign result = spec_r ? spec_res_r : div_out;
endmodule
