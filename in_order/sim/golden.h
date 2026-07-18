// Golden RV32I ISS for difftest
#pragma once
#include <cstdint>
#include <cstdio>
#include <vector>

struct Golden {
    uint32_t pc = 0x80000000u;
    uint32_t x[32] = {0};
    uint32_t mtvec = 0, mepc = 0, mcause = 0, mscratch = 0;
    std::vector<uint32_t> mem; // word array, base 0x80000000
    static constexpr uint32_t BASE = 0x80000000u;
    uint32_t mask;

    uint32_t csr_read(uint32_t a) const {
        switch (a) {
        case 0x305: return mtvec;
        case 0x341: return mepc;
        case 0x342: return mcause;
        case 0x340: return mscratch;
        default: return 0;
        }
    }
    void csr_write(uint32_t a, uint32_t v) {
        switch (a) {
        case 0x305: mtvec = v; break;
        case 0x341: mepc = v; break;
        case 0x342: mcause = v; break;
        case 0x340: mscratch = v; break;
        default: break;
        }
    }

    explicit Golden(size_t words) : mem(words, 0), mask((uint32_t)words - 1) {}

    uint32_t rw(uint32_t addr) const { return mem[(addr >> 2) & mask]; }
    void ww(uint32_t addr, uint32_t data, uint32_t strb) {
        uint32_t &w = mem[(addr >> 2) & mask];
        for (int i = 0; i < 4; i++)
            if (strb & (1u << i)) {
                w = (w & ~(0xFFu << (8 * i))) | (data & (0xFFu << (8 * i)));
            }
    }

    static int32_t sext(uint32_t v, int bits) {
        return (int32_t)(v << (32 - bits)) >> (32 - bits);
    }

    // execute one instruction at pc
    void step() {
        uint32_t inst = rw(pc);
        uint32_t opcode = inst & 0x7F;
        uint32_t rd  = (inst >> 7) & 0x1F;
        uint32_t f3  = (inst >> 12) & 0x7;
        uint32_t rs1 = (inst >> 15) & 0x1F;
        uint32_t rs2 = (inst >> 20) & 0x1F;
        uint32_t f7  = inst >> 25;
        uint32_t a = x[rs1], b = x[rs2];
        uint32_t next = pc + 4;
        uint32_t wd = 0;
        bool wen = false;

        int32_t imm_i = sext(inst >> 20, 12);
        int32_t imm_s = sext(((inst >> 25) << 5) | ((inst >> 7) & 0x1F), 12);
        int32_t imm_b = sext((((inst >> 31) & 1) << 12) | (((inst >> 7) & 1) << 11) |
                             (((inst >> 25) & 0x3F) << 5) | (((inst >> 8) & 0xF) << 1), 13);
        uint32_t imm_u = inst & 0xFFFFF000u;
        int32_t imm_j = sext((((inst >> 31) & 1) << 20) | (((inst >> 12) & 0xFF) << 12) |
                             (((inst >> 20) & 1) << 11) | (((inst >> 21) & 0x3FF) << 1), 21);

        switch (opcode) {
        case 0x37: wen = true; wd = imm_u; break;                  // lui
        case 0x17: wen = true; wd = pc + imm_u; break;             // auipc
        case 0x6F: wen = true; wd = pc + 4; next = pc + imm_j; break; // jal
        case 0x67: wen = true; wd = pc + 4; next = (a + imm_i) & ~1u; break; // jalr
        case 0x63: { // branch
            bool t = false;
            switch (f3) {
            case 0: t = (a == b); break;
            case 1: t = (a != b); break;
            case 4: t = ((int32_t)a < (int32_t)b); break;
            case 5: t = ((int32_t)a >= (int32_t)b); break;
            case 6: t = (a < b); break;
            case 7: t = (a >= b); break;
            }
            if (t) next = pc + imm_b;
            break;
        }
        case 0x03: { // load
            uint32_t addr = a + imm_i;
            uint32_t w = rw(addr);
            uint32_t off = addr & 3;
            switch (f3) {
            case 0: wd = (uint32_t)(int32_t)(int8_t)(w >> (8 * off)); break;   // lb
            case 1: wd = (uint32_t)(int32_t)(int16_t)(w >> (8 * (off & 2))); break; // lh
            case 2: wd = w; break;                                             // lw
            case 4: wd = (w >> (8 * off)) & 0xFF; break;                       // lbu
            case 5: wd = (w >> (8 * (off & 2))) & 0xFFFF; break;               // lhu
            }
            wen = true;
            break;
        }
        case 0x23: { // store
            uint32_t addr = a + imm_s;
            uint32_t off = addr & 3;
            switch (f3) {
            case 0: ww(addr, b << (8 * off), 1u << off); break;                // sb
            case 1: ww(addr, (off & 2) ? (b << 16) : b, (off & 2) ? 0xC : 0x3); break; // sh
            case 2: ww(addr, b, 0xF); break;                                   // sw
            }
            break;
        }
        case 0x13: { // op-imm
            wen = true;
            uint32_t sh = imm_i & 0x1F;
            switch (f3) {
            case 0: wd = a + imm_i; break;
            case 1: wd = a << sh; break;
            case 2: wd = ((int32_t)a < imm_i) ? 1 : 0; break;
            case 3: wd = (a < (uint32_t)imm_i) ? 1 : 0; break;
            case 4: wd = a ^ imm_i; break;
            case 5: wd = (f7 & 0x20) ? (uint32_t)((int32_t)a >> sh) : (a >> sh); break;
            case 6: wd = a | imm_i; break;
            case 7: wd = a & imm_i; break;
            }
            break;
        }
        case 0x33: { // op
            wen = true;
            if (f7 == 1) { // RV32M
                int64_t sa = (int32_t)a, sb = (int32_t)b;
                uint64_t uua = a, uub = b;
                switch (f3) {
                case 0: wd = (uint32_t)(sa * sb); break;                      // mul
                case 1: wd = (uint32_t)(((int64_t)sa * sb) >> 32); break;     // mulh
                case 2: wd = (uint32_t)(((int64_t)sa * (int64_t)uub) >> 32); break; // mulhsu
                case 3: wd = (uint32_t)((uua * uub) >> 32); break;            // mulhu
                case 4: // div
                    wd = (b == 0) ? 0xFFFFFFFFu :
                         (a == 0x80000000u && b == 0xFFFFFFFFu) ? 0x80000000u :
                         (uint32_t)((int32_t)a / (int32_t)b);
                    break;
                case 5: wd = (b == 0) ? 0xFFFFFFFFu : (a / b); break;         // divu
                case 6: // rem
                    wd = (b == 0) ? a :
                         (a == 0x80000000u && b == 0xFFFFFFFFu) ? 0 :
                         (uint32_t)((int32_t)a % (int32_t)b);
                    break;
                case 7: wd = (b == 0) ? a : (a % b); break;                   // remu
                }
                break;
            }
            uint32_t sh = b & 0x1F;
            switch (f3) {
            case 0: wd = (f7 & 0x20) ? (a - b) : (a + b); break;
            case 1: wd = a << sh; break;
            case 2: wd = ((int32_t)a < (int32_t)b) ? 1 : 0; break;
            case 3: wd = (a < b) ? 1 : 0; break;
            case 4: wd = a ^ b; break;
            case 5: wd = (f7 & 0x20) ? (uint32_t)((int32_t)a >> sh) : (a >> sh); break;
            case 6: wd = a | b; break;
            case 7: wd = a & b; break;
            }
            break;
        }
        case 0x73: { // SYSTEM: Zicsr + ecall/ebreak/mret (machine-only)
            uint32_t csr = inst >> 20;
            if (f3 == 0) {
                if (csr == 0x302) {           // mret
                    next = mepc;
                } else if ((csr & ~1u) == 0) { // ecall (0) / ebreak (1)
                    mepc = pc;
                    mcause = (csr & 1) ? 3 : 11;
                    next = mtvec & ~3u;
                }
            } else {
                uint32_t src = (f3 & 4) ? rs1 : a; // zimm or rs1 value
                uint32_t old = csr_read(csr);
                wen = true; wd = old;
                bool wr = ((f3 & 3) == 1) || (rs1 != 0);
                if (wr) {
                    uint32_t nv = ((f3 & 3) == 1) ? src :
                                  ((f3 & 3) == 2) ? (old | src) : (old & ~src);
                    csr_write(csr, nv);
                }
            }
            break;
        }
        default: break; // fence, fence.i -> nop
        }

        if (wen && rd != 0) x[rd] = wd;
        pc = next;
    }
};
