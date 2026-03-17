
// opcode
`define ADD     4'b0000
`define SUB     4'b1000
`define AND     4'b0111
`define SLT     4'b0010
`define SLTU    4'b0011
`define OR      4'b0110
`define XOR     4'b0100
`define SLL     4'b0001
`define SRL     4'b0101
`define SRA     4'b1101


// branch
`define BEQ             3'b000
`define BNE             3'b001
`define BLT             3'b100
`define BGE             3'b101
`define BLTU            3'b110
`define BGEU            3'b111
`define JAL             5'b11111
`define JALR            5'b11011

// memory opcode
`define NO_ACCESS       5'b00000
`define LOAD_B          3'b000
`define LOAD_UB         3'b100
`define LOAD_H          3'b001
`define LOAD_UH         3'b101
`define LOAD_W          3'b010
`define STORE_B         3'b000
`define STORE_H         3'b001
`define STORE_W         3'b010
`define LOAD_BIT        3
`define STORE_BIT       4

// ALU SR
`define SRC1_REG1        2'h0
`define SRC1_PC          2'h1
`define SRC1_ZERO        2'h2
`define SRC2_REG2        2'h0
`define SRC2_IMM         2'h1
`define SRC2_FOUR        2'h2
//`define SRC2_CSR         2'h3

// Writeback
`define FROM_ALU         1'h0
`define FROM_MEM         1'h1
// `define FROM_CSR         2'h1

