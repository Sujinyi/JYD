// IROM: 16KB (4096 x 32) instruction ROM, initialized from the official
// competition .coe content (converted to .mem, word content identical).
// Four read ports for the dual-issue core:
//   - fetch pair port (addr0 = pc word index, addr1 = pc+4 word index)
//   - data read ports (rodata reads from either issue slot)
// Implemented as two identically-initialized BRAM arrays, each true-dual-port.
module irom3p (
    input  wire        clk,
    input  wire [11:0] addr0,
    input  wire [11:0] addr1,
    output reg  [31:0] rdata0,
    output reg  [31:0] rdata1,
    input  wire [11:0] daddr,
    output reg  [31:0] drdata,
    input  wire [11:0] daddr1,
    output reg  [31:0] drdata1
);
        // 实例1：双发射取指
    IROM u_irom_fetch (
        .clka  (clk),
        .addra (imem_addr[13:2]),
        .douta (imem_rdata0),

        .clkb  (clk),
        .addrb (imem_addr[13:2] + 12'd1),
        .doutb (imem_rdata1)
    );

    // 实例2：两个数据读口
    IROM u_irom_data (
        .clka  (clk),
        .addra (dmem_addr[13:2]),
        .douta (irom_drdata),

        .clkb  (clk),
        .addrb (dmem1_addr[13:2]),
        .doutb (irom_drdata1)
    );
endmodule
