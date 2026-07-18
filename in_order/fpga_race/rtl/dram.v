// DRAM: 256KB (65536 x 32) data RAM, port-compatible drop-in for the JYD
// Vivado Block Memory Generator IP instanced inside perip_bridge.sv:
//   DRAM Mem_DRAM (.clka, .wea[3:0], .addra[15:0], .dina, .douta);
// Byte write enables, sync 1-cycle read, WRITE_FIRST not required by the
// core (no same-cycle read/write to the same address from a single port).
// Initialized from the official dram.coe content (converted to .mem).
module DRAM #(
    parameter MEM_FILE = "dram.mem"
) (
    input  wire        clka,
    input  wire [3:0]  wea,
    input  wire [15:0] addra,
    input  wire [31:0] dina,
    output reg  [31:0] douta,
    // port B: slot1 memory port (loads + word stores), same clock
    input  wire [15:0] addrb,
    input  wire [3:0]  web,
    input  wire [31:0] dinb,
    output reg  [31:0] doutb
);
    // cascade_height=1: forbid the BRAM hardware cascade chain (CASCADEIN/OUT
    // serial readout, ~2.2ns) and use parallel block reads + fabric output
    // mux instead (~0.5ns faster). Width/depth/ports/behaviour unchanged.
    (* cascade_height = 1 *) reg [31:0] mem [0:65535];
    initial $readmemh(MEM_FILE, mem);

    always @(posedge clka) begin
        douta <= mem[addra];
        if (wea[0]) mem[addra][7:0]   <= dina[7:0];
        if (wea[1]) mem[addra][15:8]  <= dina[15:8];
        if (wea[2]) mem[addra][23:16] <= dina[23:16];
        if (wea[3]) mem[addra][31:24] <= dina[31:24];
    end

    always @(posedge clka) begin
        doutb <= mem[addrb];
        if (web[0]) mem[addrb][7:0]   <= dinb[7:0];
        if (web[1]) mem[addrb][15:8]  <= dinb[15:8];
        if (web[2]) mem[addrb][23:16] <= dinb[23:16];
        if (web[3]) mem[addrb][31:24] <= dinb[31:24];
    end
endmodule
