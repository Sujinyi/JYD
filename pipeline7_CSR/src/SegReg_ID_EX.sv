module SegReg_ID_EX#(
    parameter PC_RESET_VAL = 32'h0,
    parameter int TAGE_META_W = 1
)(
    input  logic [ 0:0] clk,
    input  logic [ 0:0] rst,
    input  logic [ 0:0] stall,
    input  logic [ 0:0] flush,

    input  logic [31:0] pc_id,
    input  logic [31:0] inst_id,
    input  logic [31:0] rdata1_id,
    input  logic [31:0] rdata2_id,
    input  logic [31:0] imm_id,
    input  logic [ 4:0] mem_access_id,
    input  logic [ 3:0] alu_op_id,
    input  logic [ 4:0] br_type_id,
    input  logic [ 0:0] wb_rf_sel_id,
    input  logic [ 1:0] alu_rs1_sel_id,
    input  logic [ 1:0] alu_rs2_sel_id,
    input  logic [ 0:0] rf_we_id,
    input  logic [ 0:0] have_inst_id,
    input  logic [ 0:0] predict_taken_id,
    input  logic [31:0] predict_target_id,
    //input  logic [TAGE_META_W-1:0] tage_meta_id,
    input  logic [ 2:0] priv_vec_id,
    input  logic [31:0] csr_rdata_id,

    output logic [31:0] csr_rdata_ex,
    output logic [ 2:0] priv_vec_ex,
    output logic [ 0:0] predict_taken_ex,
    output logic [31:0] predict_target_ex,
    //output logic [TAGE_META_W-1:0] tage_meta_ex,
    output logic [31:0] pc_ex,
    output logic [31:0] inst_ex,
    output logic [31:0] rdata1_ex,
    output logic [31:0] rdata2_ex,
    output logic [31:0] imm_ex,
    output logic [ 4:0] mem_access_ex,
    output logic [ 3:0] alu_op_ex,
    output logic [ 4:0] br_type_ex,
    output logic [ 0:0] wb_rf_sel_ex,
    output logic [ 1:0] alu_rs1_sel_ex,
    output logic [ 1:0] alu_rs2_sel_ex,
    output logic [ 0:0] rf_we_ex,
    output logic [ 0:0] have_inst_ex
);
    always_ff @(posedge clk) begin
        if(rst || flush) begin
            predict_taken_ex <= 1'b0;
            predict_target_ex<= 32'h0;
            //tage_meta_ex    <= '0;
            pc_ex           <= PC_RESET_VAL;
            inst_ex         <= 32'h0;
            rdata1_ex       <= 32'h0;
            rdata2_ex       <= 32'h0;
            imm_ex          <= 32'h0;
            mem_access_ex   <=  5'h0;
            alu_op_ex       <=  4'h0;
            br_type_ex      <=  5'h0;
            wb_rf_sel_ex    <=  1'h0;
            alu_rs1_sel_ex  <=  2'h0;
            alu_rs2_sel_ex  <=  2'h0;
            rf_we_ex        <=  1'h0;
            have_inst_ex    <=  1'h0;
            priv_vec_ex     <=  3'h0;
            csr_rdata_ex    <= 32'h0;
        end 
        else begin
            if(!stall) begin
                predict_taken_ex <= predict_taken_id;
                predict_target_ex<= predict_target_id;
                //tage_meta_ex    <= tage_meta_id;
                pc_ex           <= pc_id;
                inst_ex         <= inst_id;
                rdata1_ex       <= rdata1_id;
                rdata2_ex       <= rdata2_id;
                imm_ex          <= imm_id;
                mem_access_ex   <= mem_access_id;
                alu_op_ex       <= alu_op_id;
                br_type_ex      <= br_type_id;
                wb_rf_sel_ex    <= wb_rf_sel_id;
                alu_rs1_sel_ex  <= alu_rs1_sel_id;
                alu_rs2_sel_ex  <= alu_rs2_sel_id;
                rf_we_ex        <= rf_we_id;
                have_inst_ex    <= have_inst_id;
                priv_vec_ex     <= priv_vec_id;
                csr_rdata_ex    <= csr_rdata_id;
            end
        end
    end

endmodule
