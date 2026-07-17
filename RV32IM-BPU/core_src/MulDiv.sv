`include"./config.sv"
module MulDiv(
    input  logic        clk,
    input  logic        rst,
    input  logic        valid,
    input  logic        start,// a start pulse
    input  logic [2:0]  op,
    input  logic [31:0] a,
    input  logic [31:0] b,
    output logic        busy,
    output logic        done,
    output logic [31:0] result
);

    localparam IDLE     = 2'b00,
               MUL_EXEC = 2'b01,
               MUL_WAIT = 2'b10,
               DIV_RUN  = 2'b11;

    logic [1:0] cs,ns;
    always_ff @( posedge clk ) begin 
        if(rst) 
            cs <= 2'b00;
        else
            cs <= ns;
    end

    logic [2:0]  op_r;

    logic is_mul_op;
    logic is_div_op;
    logic is_rem_op;
    logic is_signed_div;

    assign is_mul_op = ((op == `MUL)  || (op == `MULH) ||
                       (op == `MULHSU) || (op == `MULHU))&&valid;

    assign is_div_op = ((op == `DIV)  || (op == `DIVU) ||
                        (op == `REM)  || (op == `REMU))&&valid;

    assign is_rem_op = ((op == `REM) || (op == `REMU))&&valid;

    assign is_signed_div = ((op == `DIV) || (op == `REM))&&valid;

    logic        mul_signed_a;
    logic        mul_signed_b;
    logic [32:0] mul_a_ext;
    logic [32:0] mul_b_ext;
    logic [32:0] mul_a_r;
    logic [32:0] mul_b_r;
    logic [65:0] mul_prod_r;

    always_comb begin
        mul_signed_a = (op == `MULH) || (op == `MULHSU);
        mul_signed_b = (op == `MULH);

        mul_a_ext = {mul_signed_a & a[31], a};
        mul_b_ext = {mul_signed_b & b[31], b};
    end

    logic [31:0] dividend_abs;
    logic [31:0] divisor_abs;
    logic        quotient_neg;
    logic        remainder_neg;

    logic [31:0] dividend_r;
    logic [31:0] divisor_r;
    logic [31:0] quotient_r;
    logic [32:0] rem_r;
    logic [5:0]  div_cnt;

    logic        quotient_neg_r;
    logic        remainder_neg_r;
    logic        div_is_rem_r;

    logic [32:0] rem_shift;
    logic        ge_divisor;
    logic [32:0] rem_step;
    logic [31:0] quotient_step;

    logic [31:0] quotient_final;
    logic [31:0] remainder_final;

    always_comb begin
        if (is_signed_div && a[31])
            dividend_abs = ~a + 32'd1;
        else
            dividend_abs = a;

        if (is_signed_div && b[31])
            divisor_abs = ~b + 32'd1;
        else
            divisor_abs = b;

        quotient_neg  = is_signed_div && (a[31] ^ b[31]);
        remainder_neg = is_signed_div && a[31];
    end

    // radix-2 compare-sub 一拍逻辑
    always_comb begin
        rem_shift = {rem_r[31:0], dividend_r[31]};

        ge_divisor = (rem_shift >= {1'b0, divisor_r});

        if (ge_divisor) begin
            rem_step      = rem_shift - {1'b0, divisor_r};
            quotient_step = {quotient_r[30:0], 1'b1};
        end else begin
            rem_step      = rem_shift;
            quotient_step = {quotient_r[30:0], 1'b0};
        end

        quotient_final = quotient_neg_r ? (~quotient_step + 32'd1) :
                                          quotient_step;

        remainder_final = remainder_neg_r ? (~rem_step[31:0] + 32'd1) :
                                            rem_step[31:0];
    end




    logic div_by_zero;
    logic div_overflow;
    logic div_special;

    assign div_by_zero = is_div_op && (b == 32'b0);

    assign div_overflow = is_signed_div &&
                        (a == 32'h8000_0000) &&
                        (b == 32'hFFFF_FFFF);

    assign div_special = div_by_zero || div_overflow;

    //Transfer logic
    always_comb begin
        ns = cs;

        case (cs)
            IDLE: begin
                if (start && is_mul_op)
                    ns = MUL_EXEC;
                else if (start && is_div_op && !div_special)
                    ns = DIV_RUN;
                else
                    ns = IDLE;
            end

            MUL_EXEC: begin
                ns = MUL_WAIT;
            end

            MUL_WAIT: begin
                ns = IDLE;
            end

            DIV_RUN: begin
                ns = (div_cnt == 6'd31) ? IDLE : DIV_RUN;
            end

            default: begin
                ns = IDLE;
            end
        endcase
    end
    //Output logic 
    always_ff @(posedge clk) begin
        if (rst) begin
            busy           <= 1'b0;
            done           <= 1'b0;
            result         <= 32'b0;

            op_r           <= 3'b0;

            mul_a_r        <= 33'b0;
            mul_b_r        <= 33'b0;
            mul_prod_r     <= 66'b0;

            dividend_r     <= 32'b0;
            divisor_r      <= 32'b0;
            quotient_r     <= 32'b0;
            rem_r          <= 33'b0;
            div_cnt        <= 6'b0;

            quotient_neg_r <= 1'b0;
            remainder_neg_r<= 1'b0;
            div_is_rem_r   <= 1'b0;
        end 
        else begin
            done <= 1'b0;
            case (cs)

                IDLE: begin
                    busy <= 1'b0;

                    if (start) begin
                        op_r <= op;
                        if (is_mul_op) begin
                            busy       <= 1'b1;
                            mul_a_r    <= mul_a_ext;
                            mul_b_r    <= mul_b_ext;
                        end
                        else if (is_div_op) begin
                            busy <= 1'b1;
                            // 除零：DIV/DIVU = -1，REM/REMU = dividend
                            if (b == 32'b0) begin
                                result <= is_rem_op ? a : 32'hFFFF_FFFF;
                                done   <= 1'b1;
                                busy   <= 1'b0;
                            end

                            // signed overflow: INT_MIN / -1
                            else if (is_signed_div &&
                                     (a == 32'h8000_0000) &&
                                     (b == 32'hFFFF_FFFF)) begin
                                result <= is_rem_op ? 32'h0000_0000 :
                                                    32'h8000_0000;
                                done   <= 1'b1;
                                busy   <= 1'b0;
                            end

                            // 普通除法：进入 32-cycle 迭代
                            else begin
                                dividend_r      <= dividend_abs;
                                divisor_r       <= divisor_abs;
                                quotient_r      <= 32'b0;
                                rem_r           <= 33'b0;
                                div_cnt         <= 6'd0;

                                quotient_neg_r  <= quotient_neg;
                                remainder_neg_r <= remainder_neg;
                                div_is_rem_r    <= is_rem_op;
                            end
                        end

                        else begin
                            // 非法 op，这里直接返回 0
                            result <= 32'b0;
                            done   <= 1'b1;
                            busy   <= 1'b0;
                        end
                    end
                end

                MUL_EXEC: begin
                    busy       <= 1'b1;
                    mul_prod_r <= $signed(mul_a_r) * $signed(mul_b_r);
                end

                MUL_WAIT: begin
                    unique case (op_r)
                        `MUL:    result <= mul_prod_r[31:0];
                        `MULH:   result <= mul_prod_r[63:32];
                        `MULHSU: result <= mul_prod_r[63:32];
                        `MULHU:  result <= mul_prod_r[63:32];
                        default: result <= 32'b0;
                    endcase

                    done  <= 1'b1;
                    busy  <= 1'b0;
                end

                DIV_RUN: begin
                    rem_r      <= rem_step;
                    quotient_r <= quotient_step;
                    dividend_r <= {dividend_r[30:0], 1'b0};

                    if (div_cnt == 6'd31) begin
                        result <= div_is_rem_r ? remainder_final : quotient_final;
                        done   <= 1'b1;
                        busy   <= 1'b0;
                    end else begin
                        div_cnt <= div_cnt + 6'd1;
                        busy    <= 1'b1;
                    end
                end

                default: begin
                    busy  <= 1'b0;
                    done  <= 1'b0;
                end
            endcase
        end
    end

endmodule
