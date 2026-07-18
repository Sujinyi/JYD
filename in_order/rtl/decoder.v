// RV32I decoder: control signals + immediate generation
module decoder (
    input  wire [31:0] instr,
    output wire [4:0]  rs1,
    output wire [4:0]  rs2,
    output wire [4:0]  rd,
    output reg  [31:0] imm,
    output reg  [3:0]  alu_op,
    output reg  [1:0]  alu_a_sel,   // 0=rs1, 1=pc, 2=zero
    output reg         alu_b_sel,   // 0=rs2, 1=imm
    output reg         is_branch,
    output reg  [2:0]  branch_op,   // funct3
    output reg         is_jal,
    output reg         is_jalr,
    output reg         is_fencei,
    output reg         mem_read,
    output reg         mem_write,
    output reg  [2:0]  mem_funct3,
    output reg         rd_wen,
    output reg  [1:0]  wb_sel,      // 0=alu, 1=mem, 2=pc+4
    output reg         uses_rs1,
    output reg         uses_rs2,
    output reg         is_muldiv,
    output reg         is_csr,      // Zicsr: csrrw/csrrs/csrrc[i]
    output reg         is_ecall,    // ecall / ebreak
    output reg         is_mret
);
    localparam ALU_ADD  = 4'd0;
    localparam ALU_SUB  = 4'd1;
    localparam ALU_AND  = 4'd2;
    localparam ALU_OR   = 4'd3;
    localparam ALU_XOR  = 4'd4;
    localparam ALU_SLL  = 4'd5;
    localparam ALU_SRL  = 4'd6;
    localparam ALU_SRA  = 4'd7;
    localparam ALU_SLT  = 4'd8;
    localparam ALU_SLTU = 4'd9;

    wire [6:0] opcode = instr[6:0];
    wire [2:0] funct3 = instr[14:12];
    wire [6:0] funct7 = instr[31:25];

    assign rs1 = instr[19:15];
    assign rs2 = instr[24:20];
    assign rd  = instr[11:7];

    wire [31:0] imm_i = {{20{instr[31]}}, instr[31:20]};
    wire [31:0] imm_s = {{20{instr[31]}}, instr[31:25], instr[11:7]};
    wire [31:0] imm_b = {{19{instr[31]}}, instr[31], instr[7], instr[30:25], instr[11:8], 1'b0};
    wire [31:0] imm_u = {instr[31:12], 12'b0};
    wire [31:0] imm_j = {{11{instr[31]}}, instr[31], instr[19:12], instr[20], instr[30:21], 1'b0};

    reg [3:0] op_alu;
    always @(*) begin
        case (funct3)
            3'b000: op_alu = (opcode == 7'b0110011 && funct7[5]) ? ALU_SUB : ALU_ADD;
            3'b001: op_alu = ALU_SLL;
            3'b010: op_alu = ALU_SLT;
            3'b011: op_alu = ALU_SLTU;
            3'b100: op_alu = ALU_XOR;
            3'b101: op_alu = funct7[5] ? ALU_SRA : ALU_SRL;
            3'b110: op_alu = ALU_OR;
            default: op_alu = ALU_AND;
        endcase
    end

    always @(*) begin
        imm        = 32'h0;
        alu_op     = ALU_ADD;
        alu_a_sel  = 2'd0;
        alu_b_sel  = 1'b0;
        is_branch  = 1'b0;
        branch_op  = funct3;
        is_jal     = 1'b0;
        is_jalr    = 1'b0;
        is_fencei  = 1'b0;
        mem_read   = 1'b0;
        mem_write  = 1'b0;
        mem_funct3 = funct3;
        rd_wen     = 1'b0;
        wb_sel     = 2'd0;
        uses_rs1   = 1'b0;
        uses_rs2   = 1'b0;
        is_muldiv  = 1'b0;
        is_csr     = 1'b0;
        is_ecall   = 1'b0;
        is_mret    = 1'b0;
        case (opcode)
            7'b0110111: begin // LUI
                imm = imm_u; alu_a_sel = 2'd2; alu_b_sel = 1'b1; rd_wen = 1'b1;
            end
            7'b0010111: begin // AUIPC
                imm = imm_u; alu_a_sel = 2'd1; alu_b_sel = 1'b1; rd_wen = 1'b1;
            end
            7'b1101111: begin // JAL
                imm = imm_j; is_jal = 1'b1; rd_wen = 1'b1; wb_sel = 2'd2;
            end
            7'b1100111: begin // JALR
                imm = imm_i; is_jalr = 1'b1; rd_wen = 1'b1; wb_sel = 2'd2; uses_rs1 = 1'b1;
            end
            7'b1100011: begin // BRANCH
                imm = imm_b; is_branch = 1'b1; uses_rs1 = 1'b1; uses_rs2 = 1'b1;
            end
            7'b0000011: begin // LOAD
                imm = imm_i; alu_b_sel = 1'b1; mem_read = 1'b1; rd_wen = 1'b1;
                wb_sel = 2'd1; uses_rs1 = 1'b1;
            end
            7'b0100011: begin // STORE
                imm = imm_s; alu_b_sel = 1'b1; mem_write = 1'b1;
                uses_rs1 = 1'b1; uses_rs2 = 1'b1;
            end
            7'b0010011: begin // OP-IMM
                imm = imm_i; alu_b_sel = 1'b1; rd_wen = 1'b1; uses_rs1 = 1'b1;
                alu_op = op_alu;
                if (funct3 == 3'b000) alu_op = ALU_ADD; // addi (ignore funct7)
            end
            7'b0110011: begin // OP
                rd_wen = 1'b1; uses_rs1 = 1'b1; uses_rs2 = 1'b1;
                alu_op = op_alu;
                if (funct7 == 7'b0000001) is_muldiv = 1'b1; // RV32M
            end
            7'b0001111: begin // FENCE / FENCE.I
                if (funct3 == 3'b001) is_fencei = 1'b1;
            end
            7'b1110011: begin // SYSTEM
                if (funct3 == 3'b000) begin
                    // ecall (imm=0) / ebreak (imm=1) -> trap; mret (imm=0x302)
                    if (instr[31:20] == 12'h302) is_mret  = 1'b1;
                    else                         is_ecall = 1'b1;
                end else begin
                    // csrrw/csrrs/csrrc (+i variants). rs1 value or zimm.
                    is_csr   = 1'b1;
                    rd_wen   = 1'b1;
                    uses_rs1 = !funct3[2];   // register variants read rs1
                    imm      = {27'b0, instr[19:15]}; // zimm for the i-forms
                end
            end
            default: ; // treat as nop
        endcase
        if (opcode == 7'b0010011 || opcode == 7'b0110011) begin
            case (funct3)
                3'b001: alu_op = ALU_SLL;
                3'b010: alu_op = ALU_SLT;
                3'b011: alu_op = ALU_SLTU;
                3'b100: alu_op = ALU_XOR;
                3'b101: alu_op = funct7[5] ? ALU_SRA : ALU_SRL;
                3'b110: alu_op = ALU_OR;
                3'b111: alu_op = ALU_AND;
                3'b000: alu_op = (opcode == 7'b0110011 && funct7[5]) ? ALU_SUB : ALU_ADD;
            endcase
        end
    end
endmodule
