#include <stdint.h>

// Pseudo-C translation of RISC-V assembly

void program() {
    uint32_t zero = 0, ra = 0, sp = 0, gp = 0, tp = 0;
    uint32_t t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0;
    uint32_t s0 = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0, s7 = 0, s8 = 0, s9 = 0, s10 = 0, s11 = 0;
    uint32_t a0 = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0;
    uint32_t pc = 0;


LOC_0:
    /*     0 */  sp = 0x0 + 0x108;                        // auipc sp, 0x108
    /*     4 */  sp = sp + 0x30;                          // addi sp, sp, 0x30

LOC_8:
    /*     8 */  ra = 0xc; goto LOC_5a0; // Call          // jal 0x5a0

LOC_c:
    /*     c */  ra = 0x10; goto LOC_534; // Call         // jal 0x534

LOC_10:
    /*    10 */  goto LOC_0;                              // j 0

LOC_14:
    /*    14 */  sp = sp + -0x10;                         // addi sp, sp, -0x10

LOC_18:
    /*    18 */  *(uint32_t*)(sp + 0xc) = ra;             // sw ra, 0xc(sp)

LOC_1c:
    /*    1c */  *(uint32_t*)(sp + 8) = s0;               // sw s0, 8(sp)

LOC_20:
    /*    20 */  s0 = sp + 0x10;                          // addi s0, sp, 0x10
    /*    24 */  a5 = 0x80200 << 12;                      // lui a5, 0x80200

LOC_28:
    /*    28 */  a5 = *(int32_t*)(a5 + 0);                // lw a5, 0(a5)

LOC_2c:
    /*    2c */  a0 = a5;                                 // mv a0, a5

LOC_30:
    /*    30 */  ra = *(int32_t*)(sp + 0xc);              // lw ra, 0xc(sp)

LOC_34:
    /*    34 */  s0 = *(int32_t*)(sp + 8);                // lw s0, 8(sp)

LOC_38:
    /*    38 */  sp = sp + 0x10;                          // addi sp, sp, 0x10

LOC_3c:
    /*    3c */  goto *ra; // Return                      // ret 

LOC_40:
    /*    40 */  sp = sp + -0x10;                         // addi sp, sp, -0x10

LOC_44:
    /*    44 */  *(uint32_t*)(sp + 0xc) = ra;             // sw ra, 0xc(sp)
    /*    48 */  *(uint32_t*)(sp + 8) = s0;               // sw s0, 8(sp)

LOC_4c:
    /*    4c */  s0 = sp + 0x10;                          // addi s0, sp, 0x10
    /*    50 */  a5 = 0x80200 << 12;                      // lui a5, 0x80200
    /*    54 */  a5 = a5 + 4;                             // addi a5, a5, 4

LOC_58:
    /*    58 */  a5 = *(int32_t*)(a5 + 0);                // lw a5, 0(a5)

LOC_5c:
    /*    5c */  a0 = a5;                                 // mv a0, a5

LOC_60:
    /*    60 */  ra = *(int32_t*)(sp + 0xc);              // lw ra, 0xc(sp)

LOC_64:
    /*    64 */  s0 = *(int32_t*)(sp + 8);                // lw s0, 8(sp)
    /*    68 */  sp = sp + 0x10;                          // addi sp, sp, 0x10

LOC_6c:
    /*    6c */  goto *ra; // Return                      // ret 

LOC_70:
    /*    70 */  sp = sp + -0x30;                         // addi sp, sp, -0x30
    /*    74 */  *(uint32_t*)(sp + 0x2c) = ra;            // sw ra, 0x2c(sp)
    /*    78 */  *(uint32_t*)(sp + 0x28) = s0;            // sw s0, 0x28(sp)
    /*    7c */  s0 = sp + 0x30;                          // addi s0, sp, 0x30
    /*    80 */  *(uint32_t*)(s0 + -0x24) = a0;           // sw a0, -0x24(s0)
    /*    84 */  *(uint32_t*)(s0 + -0x14) = zero;         // sw zero, -0x14(s0)
    /*    88 */  *(uint32_t*)(s0 + -0x18) = zero;         // sw zero, -0x18(s0)
    /*    8c */  goto LOC_58;                             // j 0x58

LOC_90:
    /*    90 */  a5 = *(int32_t*)(s0 + -0x24);            // lw a5, -0x24(s0)
    /*    94 */  a1 = zero + 0xa;                         // addi a1, zero, 0xa
    /*    98 */  a0 = a5;                                 // mv a0, a5
    /*    9c */  ra = 0xa0; goto LOC_12dc; // Call        // jal 0x12dc
    /*    a0 */  a5 = a0;                                 // mv a5, a0

LOC_a4:
    /*    a4 */  *(uint32_t*)(s0 + -0x1c) = a5;           // sw a5, -0x1c(s0)
    /*    a8 */  a5 = *(int32_t*)(s0 + -0x18);            // lw a5, -0x18(s0)
    /*    ac */  a4 = *(int32_t*)(s0 + -0x1c);            // lw a4, -0x1c(s0)
    /*    b0 */  a5 = a4 << (a5 & 0x1F);                  // sll a5, a4, a5
    /*    b4 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*    b8 */  a5 = a4 | a5;                            // or a5, a4, a5
    /*    bc */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*    c0 */  a5 = *(int32_t*)(s0 + -0x24);            // lw a5, -0x24(s0)
    /*    c4 */  a1 = zero + 0xa;                         // addi a1, zero, 0xa
    /*    c8 */  a0 = a5;                                 // mv a0, a5
    /*    cc */  ra = 0xd0; goto LOC_1264; // Call        // jal 0x1264
    /*    d0 */  a5 = a0;                                 // mv a5, a0
    /*    d4 */  *(uint32_t*)(s0 + -0x24) = a5;           // sw a5, -0x24(s0)
    /*    d8 */  a5 = *(int32_t*)(s0 + -0x18);            // lw a5, -0x18(s0)
    /*    dc */  a5 = a5 + 4;                             // addi a5, a5, 4
    /*    e0 */  *(uint32_t*)(s0 + -0x18) = a5;           // sw a5, -0x18(s0)
    /*    e4 */  a5 = *(int32_t*)(s0 + -0x24);            // lw a5, -0x24(s0)
    /*    e8 */  if (a5 != 0) goto LOC_90;                // bnez a5, -0x58
    /*    ec */  a5 = *(int32_t*)(s0 + -0x14);            // lw a5, -0x14(s0)
    /*    f0 */  a0 = a5;                                 // mv a0, a5
    /*    f4 */  ra = *(int32_t*)(sp + 0x2c);             // lw ra, 0x2c(sp)
    /*    f8 */  s0 = *(int32_t*)(sp + 0x28);             // lw s0, 0x28(sp)
    /*    fc */  sp = sp + 0x30;                          // addi sp, sp, 0x30
    /*   100 */  goto *ra; // Return                      // ret 

LOC_104:
    /*   104 */  sp = sp + -0x20;                         // addi sp, sp, -0x20

LOC_108:
    /*   108 */  *(uint32_t*)(sp + 0x1c) = ra;            // sw ra, 0x1c(sp)
    /*   10c */  *(uint32_t*)(sp + 0x18) = s0;            // sw s0, 0x18(sp)
    /*   110 */  s0 = sp + 0x20;                          // addi s0, sp, 0x20
    /*   114 */  a5 = 0x80100 << 12;                      // lui a5, 0x80100
    /*   118 */  a5 = *(int32_t*)(a5 + 0);                // lw a5, 0(a5)
    /*   11c */  a0 = a5;                                 // mv a0, a5
    /*   120 */  ra = 0x124; goto LOC_70; // Call         // jal -0xb0
    /*   124 */  *(uint32_t*)(s0 + -0x14) = a0;           // sw a0, -0x14(s0)
    /*   128 */  a5 = 0x80200 << 12;                      // lui a5, 0x80200
    /*   12c */  a5 = a5 + 0x20;                          // addi a5, a5, 0x20
    /*   130 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   134 */  a4 = a4 << 0x18;                         // slli a4, a4, 0x18
    /*   138 */  *(uint32_t*)(a5 + 0) = a4;               // sw a4, 0(a5)
    /*   13c */  // nop                                   // nop 
    /*   140 */  ra = *(int32_t*)(sp + 0x1c);             // lw ra, 0x1c(sp)
    /*   144 */  s0 = *(int32_t*)(sp + 0x18);             // lw s0, 0x18(sp)
    /*   148 */  sp = sp + 0x20;                          // addi sp, sp, 0x20
    /*   14c */  goto *ra; // Return                      // ret 

LOC_150:
    /*   150 */  sp = sp + -0x30;                         // addi sp, sp, -0x30
    /*   154 */  *(uint32_t*)(sp + 0x2c) = ra;            // sw ra, 0x2c(sp)
    /*   158 */  *(uint32_t*)(sp + 0x28) = s0;            // sw s0, 0x28(sp)
    /*   15c */  s0 = sp + 0x30;                          // addi s0, sp, 0x30
    /*   160 */  *(uint32_t*)(s0 + -0x24) = a0;           // sw a0, -0x24(s0)
    /*   164 */  a0 = *(int32_t*)(s0 + -0x24);            // lw a0, -0x24(s0)
    /*   168 */  ra = 0x16c; goto LOC_70; // Call         // jal -0xf8
    /*   16c */  a4 = a0;                                 // mv a4, a0
    /*   170 */  a5 = 0x1000 << 12;                       // lui a5, 0x1000
    /*   174 */  a5 = a5 + -1;                            // addi a5, a5, -1
    /*   178 */  a5 = a4 & a5;                            // and a5, a4, a5
    /*   17c */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   180 */  a5 = 0x80200 << 12;                      // lui a5, 0x80200

LOC_184:
    /*   184 */  a5 = a5 + 0x20;                          // addi a5, a5, 0x20
    /*   188 */  a3 = *(int32_t*)(a5 + 0);                // lw a3, 0(a5)
    /*   18c */  a5 = 0x80200 << 12;                      // lui a5, 0x80200
    /*   190 */  a5 = a5 + 0x20;                          // addi a5, a5, 0x20
    /*   194 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   198 */  a4 = a3 | a4;                            // or a4, a3, a4
    /*   19c */  *(uint32_t*)(a5 + 0) = a4;               // sw a4, 0(a5)
    /*   1a0 */  // nop                                   // nop 
    /*   1a4 */  ra = *(int32_t*)(sp + 0x2c);             // lw ra, 0x2c(sp)
    /*   1a8 */  s0 = *(int32_t*)(sp + 0x28);             // lw s0, 0x28(sp)
    /*   1ac */  sp = sp + 0x30;                          // addi sp, sp, 0x30
    /*   1b0 */  goto *ra; // Return                      // ret 

LOC_1b4:
    /*   1b4 */  sp = sp + -0x20;                         // addi sp, sp, -0x20
    /*   1b8 */  *(uint32_t*)(sp + 0x1c) = ra;            // sw ra, 0x1c(sp)
    /*   1bc */  *(uint32_t*)(sp + 0x18) = s0;            // sw s0, 0x18(sp)
    /*   1c0 */  s0 = sp + 0x20;                          // addi s0, sp, 0x20
    /*   1c4 */  *(uint32_t*)(s0 + -0x14) = a0;           // sw a0, -0x14(s0)
    /*   1c8 */  a5 = 0x80200 << 12;                      // lui a5, 0x80200
    /*   1cc */  a5 = a5 + 0x40;                          // addi a5, a5, 0x40

LOC_1d0:
    /*   1d0 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   1d4 */  *(uint32_t*)(a5 + 0) = a4;               // sw a4, 0(a5)
    /*   1d8 */  // nop                                   // nop 
    /*   1dc */  ra = *(int32_t*)(sp + 0x1c);             // lw ra, 0x1c(sp)
    /*   1e0 */  s0 = *(int32_t*)(sp + 0x18);             // lw s0, 0x18(sp)
    /*   1e4 */  sp = sp + 0x20;                          // addi sp, sp, 0x20
    /*   1e8 */  goto *ra; // Return                      // ret 

LOC_1ec:
    /*   1ec */  sp = sp + -0x20;                         // addi sp, sp, -0x20
    /*   1f0 */  *(uint32_t*)(sp + 0x1c) = ra;            // sw ra, 0x1c(sp)
    /*   1f4 */  *(uint32_t*)(sp + 0x18) = s0;            // sw s0, 0x18(sp)
    /*   1f8 */  s0 = sp + 0x20;                          // addi s0, sp, 0x20
    /*   1fc */  *(uint32_t*)(s0 + -0x14) = zero;         // sw zero, -0x14(s0)
    /*   200 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   204 */  a5 = 0x1000 << 12;                       // lui a5, 0x1000
    /*   208 */  a5 = a4 | a5;                            // or a5, a4, a5
    /*   20c */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   210 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   214 */  a5 = 0x20 << 12;                         // lui a5, 0x20

LOC_218:
    /*   218 */  a5 = a4 | a5;                            // or a5, a4, a5
    /*   21c */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   220 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   224 */  a5 = 0x1 << 12;                          // lui a5, 1
    /*   228 */  a5 = a5 + -0x800;                        // addi a5, a5, -0x800
    /*   22c */  a5 = a4 | a5;                            // or a5, a4, a5
    /*   230 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   234 */  a5 = *(int32_t*)(s0 + -0x14);            // lw a5, -0x14(s0)
    /*   238 */  a5 = a5 | 0x400;                         // ori a5, a5, 0x400
    /*   23c */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   240 */  a5 = *(int32_t*)(s0 + -0x14);            // lw a5, -0x14(s0)
    /*   244 */  a5 = a5 | 8;                             // ori a5, a5, 8
    /*   248 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   24c */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   250 */  a5 = 0x1 << 12;                          // lui a5, 1
    /*   254 */  a5 = a4 | a5;                            // or a5, a4, a5
    /*   258 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   25c */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   260 */  a5 = 0x200 << 12;                        // lui a5, 0x200
    /*   264 */  a5 = a4 | a5;                            // or a5, a4, a5
    /*   268 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   26c */  a0 = *(int32_t*)(s0 + -0x14);            // lw a0, -0x14(s0)
    /*   270 */  ra = 0x274; goto LOC_1b4; // Call        // jal -0xbc
    /*   274 */  // nop                                   // nop 
    /*   278 */  ra = *(int32_t*)(sp + 0x1c);             // lw ra, 0x1c(sp)
    /*   27c */  s0 = *(int32_t*)(sp + 0x18);             // lw s0, 0x18(sp)
    /*   280 */  sp = sp + 0x20;                          // addi sp, sp, 0x20
    /*   284 */  goto *ra; // Return                      // ret 

LOC_288:
    /*   288 */  sp = sp + -0x20;                         // addi sp, sp, -0x20
    /*   28c */  *(uint32_t*)(sp + 0x1c) = ra;            // sw ra, 0x1c(sp)
    /*   290 */  *(uint32_t*)(sp + 0x18) = s0;            // sw s0, 0x18(sp)

LOC_294:
    /*   294 */  s0 = sp + 0x20;                          // addi s0, sp, 0x20
    /*   298 */  *(uint32_t*)(s0 + -0x14) = zero;         // sw zero, -0x14(s0)
    /*   29c */  a5 = *(int32_t*)(s0 + -0x14);            // lw a5, -0x14(s0)
    /*   2a0 */  a5 = a5 | 0x20;                          // ori a5, a5, 0x20
    /*   2a4 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   2a8 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   2ac */  a5 = 0x1 << 12;                          // lui a5, 1
    /*   2b0 */  a5 = a4 | a5;                            // or a5, a4, a5
    /*   2b4 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   2b8 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   2bc */  a5 = 0x80 << 12;                         // lui a5, 0x80
    /*   2c0 */  a5 = a4 | a5;                            // or a5, a4, a5

LOC_2c4:
    /*   2c4 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   2c8 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   2cc */  a5 = 0x4000 << 12;                       // lui a5, 0x4000
    /*   2d0 */  a5 = a4 | a5;                            // or a5, a4, a5
    /*   2d4 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   2d8 */  a5 = *(int32_t*)(s0 + -0x14);            // lw a5, -0x14(s0)
    /*   2dc */  a5 = a5 | 4;                             // ori a5, a5, 4
    /*   2e0 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   2e4 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   2e8 */  a5 = 0x1 << 12;                          // lui a5, 1
    /*   2ec */  a5 = a5 + -0x800;                        // addi a5, a5, -0x800
    /*   2f0 */  a5 = a4 | a5;                            // or a5, a4, a5
    /*   2f4 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   2f8 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   2fc */  a5 = 0x100 << 12;                        // lui a5, 0x100
    /*   300 */  a5 = a4 | a5;                            // or a5, a4, a5
    /*   304 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   308 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   30c */  a5 = 0x20000 << 12;                      // lui a5, 0x20000
    /*   310 */  a5 = a4 | a5;                            // or a5, a4, a5
    /*   314 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   318 */  a0 = *(int32_t*)(s0 + -0x14);            // lw a0, -0x14(s0)
    /*   31c */  ra = 0x320; goto LOC_1b4; // Call        // jal -0x168
    /*   320 */  // nop                                   // nop 
    /*   324 */  ra = *(int32_t*)(sp + 0x1c);             // lw ra, 0x1c(sp)
    /*   328 */  s0 = *(int32_t*)(sp + 0x18);             // lw s0, 0x18(sp)
    /*   32c */  sp = sp + 0x20;                          // addi sp, sp, 0x20
    /*   330 */  goto *ra; // Return                      // ret 

LOC_334:
    /*   334 */  sp = sp + -0x20;                         // addi sp, sp, -0x20
    /*   338 */  *(uint32_t*)(sp + 0x1c) = ra;            // sw ra, 0x1c(sp)
    /*   33c */  *(uint32_t*)(sp + 0x18) = s0;            // sw s0, 0x18(sp)
    /*   340 */  s0 = sp + 0x20;                          // addi s0, sp, 0x20
    /*   344 */  *(uint32_t*)(s0 + -0x14) = zero;         // sw zero, -0x14(s0)
    /*   348 */  goto LOC_20;                             // j 0x20

LOC_34c:
    /*   34c */  a5 = 0x80200 << 12;                      // lui a5, 0x80200
    /*   350 */  a5 = a5 + 0x50;                          // addi a5, a5, 0x50
    /*   354 */  a4 = 0x80000 << 12;                      // lui a4, 0x80000
    /*   358 */  *(uint32_t*)(a5 + 0) = a4;               // sw a4, 0(a5)
    /*   35c */  a5 = *(int32_t*)(s0 + -0x14);            // lw a5, -0x14(s0)
    /*   360 */  a5 = a5 + 1;                             // addi a5, a5, 1
    /*   364 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   368 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   36c */  a5 = zero + 9;                           // addi a5, zero, 9
    /*   370 */  if ((int32_t)a5 >= (int32_t)a4) goto LOC_34c; // bge a5, a4, -0x24
    /*   374 */  // nop                                   // nop 
    /*   378 */  // nop                                   // nop 
    /*   37c */  ra = *(int32_t*)(sp + 0x1c);             // lw ra, 0x1c(sp)
    /*   380 */  s0 = *(int32_t*)(sp + 0x18);             // lw s0, 0x18(sp)
    /*   384 */  sp = sp + 0x20;                          // addi sp, sp, 0x20
    /*   388 */  goto *ra; // Return                      // ret 

LOC_38c:
    /*   38c */  sp = sp + -0x20;                         // addi sp, sp, -0x20
    /*   390 */  *(uint32_t*)(sp + 0x1c) = ra;            // sw ra, 0x1c(sp)
    /*   394 */  *(uint32_t*)(sp + 0x18) = s0;            // sw s0, 0x18(sp)
    /*   398 */  s0 = sp + 0x20;                          // addi s0, sp, 0x20
    /*   39c */  *(uint32_t*)(s0 + -0x14) = zero;         // sw zero, -0x14(s0)
    /*   3a0 */  goto LOC_20;                             // j 0x20

LOC_3a4:
    /*   3a4 */  a5 = 0x80200 << 12;                      // lui a5, 0x80200
    /*   3a8 */  a5 = a5 + 0x50;                          // addi a5, a5, 0x50
    /*   3ac */  a4 = zero + -1;                          // addi a4, zero, -1
    /*   3b0 */  *(uint32_t*)(a5 + 0) = a4;               // sw a4, 0(a5)
    /*   3b4 */  a5 = *(int32_t*)(s0 + -0x14);            // lw a5, -0x14(s0)
    /*   3b8 */  a5 = a5 + 1;                             // addi a5, a5, 1
    /*   3bc */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   3c0 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   3c4 */  a5 = zero + 9;                           // addi a5, zero, 9
    /*   3c8 */  if ((int32_t)a5 >= (int32_t)a4) goto LOC_3a4; // bge a5, a4, -0x24
    /*   3cc */  // nop                                   // nop 
    /*   3d0 */  // nop                                   // nop 
    /*   3d4 */  ra = *(int32_t*)(sp + 0x1c);             // lw ra, 0x1c(sp)
    /*   3d8 */  s0 = *(int32_t*)(sp + 0x18);             // lw s0, 0x18(sp)
    /*   3dc */  sp = sp + 0x20;                          // addi sp, sp, 0x20
    /*   3e0 */  goto *ra; // Return                      // ret 

LOC_3e4:
    /*   3e4 */  sp = sp + -0x10;                         // addi sp, sp, -0x10

LOC_3e8:
    /*   3e8 */  *(uint32_t*)(sp + 0xc) = ra;             // sw ra, 0xc(sp)
    /*   3ec */  *(uint32_t*)(sp + 8) = s0;               // sw s0, 8(sp)
    /*   3f0 */  s0 = sp + 0x10;                          // addi s0, sp, 0x10
    /*   3f4 */  a5 = 0x80200 << 12;                      // lui a5, 0x80200
    /*   3f8 */  a5 = a5 + 0x50;                          // addi a5, a5, 0x50
    /*   3fc */  a5 = *(int32_t*)(a5 + 0);                // lw a5, 0(a5)
    /*   400 */  a0 = a5;                                 // mv a0, a5
    /*   404 */  ra = *(int32_t*)(sp + 0xc);              // lw ra, 0xc(sp)
    /*   408 */  s0 = *(int32_t*)(sp + 8);                // lw s0, 8(sp)
    /*   40c */  sp = sp + 0x10;                          // addi sp, sp, 0x10
    /*   410 */  goto *ra; // Return                      // ret 

LOC_414:
    /*   414 */  sp = sp + -0x10;                         // addi sp, sp, -0x10
    /*   418 */  *(uint32_t*)(sp + 0xc) = ra;             // sw ra, 0xc(sp)
    /*   41c */  *(uint32_t*)(sp + 8) = s0;               // sw s0, 8(sp)
    /*   420 */  s0 = sp + 0x10;                          // addi s0, sp, 0x10
    /*   424 */  ra = 0x428; goto LOC_38c; // Call        // jal -0x98
    /*   428 */  ra = 0x42c; goto LOC_3e4; // Call        // jal -0x44
    /*   42c */  a5 = a0;                                 // mv a5, a0
    /*   430 */  a0 = a5;                                 // mv a0, a5
    /*   434 */  ra = 0x438; goto LOC_150; // Call        // jal -0x2e4
    /*   438 */  ra = 0x43c; goto LOC_288; // Call        // jal -0x1b0
    /*   43c */  t6 = zero;                               // mv t6, zero
    /*   440 */  // nop                                   // nop 
    /*   444 */  ra = *(int32_t*)(sp + 0xc);              // lw ra, 0xc(sp)
    /*   448 */  s0 = *(int32_t*)(sp + 8);                // lw s0, 8(sp)
    /*   44c */  sp = sp + 0x10;                          // addi sp, sp, 0x10
    /*   450 */  goto *ra; // Return                      // ret 

LOC_454:
    /*   454 */  sp = sp + -0x10;                         // addi sp, sp, -0x10
    /*   458 */  *(uint32_t*)(sp + 0xc) = ra;             // sw ra, 0xc(sp)
    /*   45c */  *(uint32_t*)(sp + 8) = s0;               // sw s0, 8(sp)
    /*   460 */  s0 = sp + 0x10;                          // addi s0, sp, 0x10
    /*   464 */  ra = 0x468; goto LOC_38c; // Call        // jal -0xd8

LOC_468:
    /*   468 */  ra = 0x46c; goto LOC_3e4; // Call        // jal -0x84
    /*   46c */  a5 = a0;                                 // mv a5, a0
    /*   470 */  a0 = a5;                                 // mv a0, a5
    /*   474 */  ra = 0x478; goto LOC_150; // Call        // jal -0x324
    /*   478 */  ra = 0x47c; goto LOC_1ec; // Call        // jal -0x28c
    /*   47c */  t6 = zero + 1;                           // addi t6, zero, 1
    /*   480 */  // nop                                   // nop 
    /*   484 */  ra = *(int32_t*)(sp + 0xc);              // lw ra, 0xc(sp)
    /*   488 */  s0 = *(int32_t*)(sp + 8);                // lw s0, 8(sp)
    /*   48c */  sp = sp + 0x10;                          // addi sp, sp, 0x10
    /*   490 */  goto *ra; // Return                      // ret 

LOC_494:
    /*   494 */  sp = sp + -0x30;                         // addi sp, sp, -0x30
    /*   498 */  *(uint32_t*)(sp + 0x2c) = ra;            // sw ra, 0x2c(sp)
    /*   49c */  *(uint32_t*)(sp + 0x28) = s0;            // sw s0, 0x28(sp)
    /*   4a0 */  *(uint32_t*)(sp + 0x24) = s1;            // sw s1, 0x24(sp)
    /*   4a4 */  s0 = sp + 0x30;                          // addi s0, sp, 0x30
    /*   4a8 */  *(uint32_t*)(s0 + -0x24) = a0;           // sw a0, -0x24(s0)
    /*   4ac */  *(uint32_t*)(s0 + -0x14) = zero;         // sw zero, -0x14(s0)

LOC_4b0:
    /*   4b0 */  *(uint32_t*)(s0 + -0x18) = zero;         // sw zero, -0x18(s0)
    /*   4b4 */  goto LOC_64;                             // j 0x64

LOC_4b8:
    /*   4b8 */  a4 = *(int32_t*)(s0 + -0x18);            // lw a4, -0x18(s0)
    /*   4bc */  a5 = a4;                                 // mv a5, a4
    /*   4c0 */  a5 = a5 << 1;                            // slli a5, a5, 1
    /*   4c4 */  a5 = a5 + a4;                            // add a5, a5, a4
    /*   4c8 */  a5 = a5 << 2;                            // slli a5, a5, 2
    /*   4cc */  s1 = a5 + a4;                            // add s1, a5, a4
    /*   4d0 */  a5 = *(int32_t*)(s0 + -0x18);            // lw a5, -0x18(s0)
    /*   4d4 */  a1 = zero + 7;                           // addi a1, zero, 7
    /*   4d8 */  a0 = a5;                                 // mv a0, a5

LOC_4dc:
    /*   4dc */  ra = 0x4e0; goto LOC_ed0; // Call        // jal 0xed0
    /*   4e0 */  a5 = a0;                                 // mv a5, a0
    /*   4e4 */  s1 = s1 + a5;                            // add s1, s1, a5
    /*   4e8 */  a5 = *(int32_t*)(s0 + -0x18);            // lw a5, -0x18(s0)
    /*   4ec */  a1 = zero + -3;                          // addi a1, zero, -3
    /*   4f0 */  a0 = a5;                                 // mv a0, a5
    /*   4f4 */  ra = 0x4f8; goto LOC_e34; // Call        // jal 0xe34
    /*   4f8 */  a5 = a0;                                 // mv a5, a0
    /*   4fc */  a5 = s1 + a5;                            // add a5, s1, a5
    /*   500 */  a4 = *(int32_t*)(s0 + -0x14);            // lw a4, -0x14(s0)
    /*   504 */  a5 = a4 + a5;                            // add a5, a4, a5
    /*   508 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   50c */  a5 = *(int32_t*)(s0 + -0x18);            // lw a5, -0x18(s0)
    /*   510 */  a5 = a5 + 1;                             // addi a5, a5, 1
    /*   514 */  *(uint32_t*)(s0 + -0x18) = a5;           // sw a5, -0x18(s0)
    /*   518 */  a4 = *(int32_t*)(s0 + -0x18);            // lw a4, -0x18(s0)
    /*   51c */  a5 = *(int32_t*)(s0 + -0x24);            // lw a5, -0x24(s0)
    /*   520 */  if ((int32_t)a4 < (int32_t)a5) goto LOC_4b8; // blt a4, a5, -0x68
    /*   524 */  a5 = *(int32_t*)(s0 + -0x14);            // lw a5, -0x14(s0)
    /*   528 */  a0 = a5;                                 // mv a0, a5
    /*   52c */  ra = *(int32_t*)(sp + 0x2c);             // lw ra, 0x2c(sp)
    /*   530 */  s0 = *(int32_t*)(sp + 0x28);             // lw s0, 0x28(sp)

LOC_534:
    /*   534 */  s1 = *(int32_t*)(sp + 0x24);             // lw s1, 0x24(sp)
    /*   538 */  sp = sp + 0x30;                          // addi sp, sp, 0x30
    /*   53c */  goto *ra; // Return                      // ret 
    /*   540 */  sp = sp + -0x20;                         // addi sp, sp, -0x20
    /*   544 */  *(uint32_t*)(sp + 0x1c) = ra;            // sw ra, 0x1c(sp)
    /*   548 */  *(uint32_t*)(sp + 0x18) = s0;            // sw s0, 0x18(sp)
    /*   54c */  s0 = sp + 0x20;                          // addi s0, sp, 0x20
    /*   550 */  ra = 0x554; goto LOC_104; // Call        // jal -0x44c
    /*   554 */  ra = 0x558; goto LOC_334; // Call        // jal -0x220
    /*   558 */  a5 = 0x18 << 12;                         // lui a5, 0x18

LOC_55c:
    /*   55c */  a5 = a5 + 0x6a0;                         // addi a5, a5, 0x6a0
    /*   560 */  *(uint32_t*)(s0 + -0x14) = a5;           // sw a5, -0x14(s0)
    /*   564 */  a0 = *(int32_t*)(s0 + -0x14);            // lw a0, -0x14(s0)
    /*   568 */  ra = 0x56c; goto LOC_494; // Call        // jal -0xd4
    /*   56c */  *(uint32_t*)(s0 + -0x18) = a0;           // sw a0, -0x18(s0)
    /*   570 */  a4 = *(int32_t*)(s0 + -0x18);            // lw a4, -0x18(s0)
    /*   574 */  a5 = 0xbef16 << 12;                      // lui a5, 0xbef16
    /*   578 */  a5 = a5 + 0x570;                         // addi a5, a5, 0x570
    /*   57c */  if ((int32_t)a4 == (int32_t)a5) goto LOC_10; // beq a4, a5, 0x10
    /*   580 */  ra = 0x584; goto LOC_414; // Call        // jal -0x16c
    /*   584 */  a5 = zero;                               // mv a5, zero

LOC_588:
    /*   588 */  goto LOC_c;                              // j 0xc
    /*   58c */  ra = 0x590; goto LOC_454; // Call        // jal -0x138
    /*   590 */  a5 = zero;                               // mv a5, zero
    /*   594 */  a0 = a5;                                 // mv a0, a5
    /*   598 */  ra = *(int32_t*)(sp + 0x1c);             // lw ra, 0x1c(sp)
    /*   59c */  s0 = *(int32_t*)(sp + 0x18);             // lw s0, 0x18(sp)

LOC_5a0:
    /*   5a0 */  sp = sp + 0x20;                          // addi sp, sp, 0x20
    /*   5a4 */  goto *ra; // Return                      // ret 
    /*   5a8 */  t1 = 0x5a8 + 0x100;                      // auipc t1, 0x100
    /*   5ac */  t1 = t1 + -0x5a0;                        // addi t1, t1, -0x5a0
    /*   5b0 */  *(uint32_t*)(t1 + 0x18) = ra;            // sw ra, 0x18(t1)
    /*   5b4 */  ra = 0x5b8; goto LOC_a4; // Call         // jal 0xa4
    /*   5b8 */  ra = 0x5bc; goto LOC_184; // Call        // jal 0x184
    /*   5bc */  ra = 0x5c0; goto LOC_34c; // Call        // jal 0x34c
    /*   5c0 */  ra = 0x5c4; goto LOC_468; // Call        // jal 0x468
    /*   5c4 */  ra = 0x5c8; goto LOC_294; // Call        // jal 0x294
    /*   5c8 */  ra = 0x5cc; goto LOC_1d0; // Call        // jal 0x1d0
    /*   5cc */  ra = 0x5d0; goto LOC_4b0; // Call        // jal 0x4b0
    /*   5d0 */  ra = 0x5d4; goto LOC_55c; // Call        // jal 0x55c
    /*   5d4 */  ra = 0x5d8; goto LOC_600; // Call        // jal 0x600
    /*   5d8 */  ra = 0x5dc; goto LOC_6ac; // Call        // jal 0x6ac
    /*   5dc */  ra = 0x5e0; goto LOC_764; // Call        // jal 0x764
    /*   5e0 */  ra = 0x5e4; goto LOC_79c; // Call        // jal 0x79c
    /*   5e4 */  ra = 0x5e8; goto LOC_38c; // Call        // jal 0x38c
    /*   5e8 */  ra = 0x5ec; goto LOC_108; // Call        // jal 0x108
    /*   5ec */  ra = 0x5f0; goto LOC_218; // Call        // jal 0x218
    /*   5f0 */  ra = 0x5f4; goto LOC_2c4; // Call        // jal 0x2c4
    /*   5f4 */  ra = 0x5f8; goto LOC_3e8; // Call        // jal 0x3e8
    /*   5f8 */  ra = 0x5fc; goto LOC_4dc; // Call        // jal 0x4dc
    /*   5fc */  ra = 0x600; goto LOC_588; // Call        // jal 0x588

LOC_600:
    /*   600 */  ra = 0x604; goto LOC_630; // Call        // jal 0x630
    /*   604 */  ra = 0x608; goto LOC_6ec; // Call        // jal 0x6ec
    /*   608 */  ra = 0x60c; goto LOC_814; // Call        // jal 0x814
    /*   60c */  ra = 0x610; goto LOC_7bc; // Call        // jal 0x7bc
    /*   610 */  ra = 0x614; goto LOC_950; // Call        // jal 0x950
    /*   614 */  ra = 0x618; goto LOC_9d4; // Call        // jal 0x9d4
    /*   618 */  ra = 0x61c; goto LOC_858; // Call        // jal 0x858
    /*   61c */  ra = 0x620; goto LOC_8a4; // Call        // jal 0x8a4
    /*   620 */  ra = 0x624; goto LOC_8f8; // Call        // jal 0x8f8
    /*   624 */  ra = 0x628; goto LOC_a30; // Call        // jal 0xa30
    /*   628 */  ra = 0x62c; goto LOC_a7c; // Call        // jal 0xa7c
    /*   62c */  ra = 0x630; goto LOC_acc; // Call        // jal 0xacc

LOC_630:
    /*   630 */  ra = 0x634; goto LOC_b14; // Call        // jal 0xb14
    /*   634 */  ra = 0x638; goto LOC_b5c; // Call        // jal 0xb5c
    /*   638 */  ra = 0x63c; goto LOC_ba4; // Call        // jal 0xba4
    /*   63c */  ra = 0x640; goto LOC_bec; // Call        // jal 0xbec
    /*   640 */  ra = 0x644; goto LOC_c34; // Call        // jal 0xc34
    /*   644 */  ra = 0x648; goto LOC_c80; // Call        // jal 0xc80
    /*   648 */  t1 = 0x648 + 0x100;                      // auipc t1, 0x100
    /*   64c */  t1 = t1 + -0x640;                        // addi t1, t1, -0x640
    /*   650 */  ra = *(int32_t*)(t1 + 0x18);             // lw ra, 0x18(t1)
    /*   654 */  goto *ra; // Return                      // ret 
    /*   658 */  t0 = 0x80000 << 12;                      // lui t0, 0x80000
    /*   65c */  t0 = t0 + -1;                            // addi t0, t0, -1
    /*   660 */  t1 = zero + 1;                           // addi t1, zero, 1
    /*   664 */  t2 = t0 + t1;                            // add t2, t0, t1
    /*   668 */  t3 = 0x80000 << 12;                      // lui t3, 0x80000
    /*   66c */  if ((int32_t)t2 != (int32_t)t3) goto LOC_6c; // bne t2, t3, 0x6c
    /*   670 */  t0 = zero + -1;                          // addi t0, zero, -1
    /*   674 */  t1 = zero + 1;                           // addi t1, zero, 1
    /*   678 */  t2 = t0 + t1;                            // add t2, t0, t1
    /*   67c */  if (t2 != 0) goto LOC_5c;                // bnez t2, 0x5c
    /*   680 */  t0 = 0x12345 << 12;                      // lui t0, 0x12345
    /*   684 */  t0 = t0 + 0x678;                         // addi t0, t0, 0x678
    /*   688 */  t1 = 0x87654 << 12;                      // lui t1, 0x87654
    /*   68c */  t1 = t1 + 0x321;                         // addi t1, t1, 0x321
    /*   690 */  t2 = t0 + t1;                            // add t2, t0, t1
    /*   694 */  t3 = 0x9999a << 12;                      // lui t3, 0x9999a
    /*   698 */  t3 = t3 + -0x667;                        // addi t3, t3, -0x667
    /*   69c */  if ((int32_t)t2 != (int32_t)t3) goto LOC_3c; // bne t2, t3, 0x3c
    /*   6a0 */  t3 = 0x9999a << 12;                      // lui t3, 0x9999a
    /*   6a4 */  t3 = t3 + -0x667;                        // addi t3, t3, -0x667
    /*   6a8 */  t4 = 0x9999a << 12;                      // lui t4, 0x9999a

LOC_6ac:
    /*   6ac */  t4 = t4 + -0x667;                        // addi t4, t4, -0x667
    /*   6b0 */  t5 = t3 + t4;                            // add t5, t3, t4
    /*   6b4 */  t6 = 0x33333 << 12;                      // lui t6, 0x33333
    /*   6b8 */  t6 = t6 + 0x332;                         // addi t6, t6, 0x332
    /*   6bc */  if ((int32_t)t5 != (int32_t)t6) goto LOC_1c; // bne t5, t6, 0x1c
    /*   6c0 */  t0 = 0x6c0 + 0x100;                      // auipc t0, 0x100
    /*   6c4 */  t0 = t0 + -0x6c0;                        // addi t0, t0, -0x6c0
    /*   6c8 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   6cc */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   6d0 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   6d4 */  goto *ra; // Return                      // ret 
    /*   6d8 */  t0 = 0x6d8 + 0x100;                      // auipc t0, 0x100
    /*   6dc */  t0 = t0 + -0x6d4;                        // addi t0, t0, -0x6d4
    /*   6e0 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   6e4 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   6e8 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)

LOC_6ec:
    /*   6ec */  goto *ra; // Return                      // ret 
    /*   6f0 */  t0 = zero;                               // mv t0, zero
    /*   6f4 */  t1 = t0 + 0x7b;                          // addi t1, t0, 0x7b
    /*   6f8 */  t2 = zero + 0x7b;                        // addi t2, zero, 0x7b
    /*   6fc */  if ((int32_t)t1 != (int32_t)t2) goto LOC_28; // bne t1, t2, 0x28
    /*   700 */  t0 = zero + -1;                          // addi t0, zero, -1
    /*   704 */  t1 = t0 + 1;                             // addi t1, t0, 1
    /*   708 */  if (t1 != 0) goto LOC_1c;                // bnez t1, 0x1c
    /*   70c */  t0 = 0x70c + 0x100;                      // auipc t0, 0x100
    /*   710 */  t0 = t0 + -0x70c;                        // addi t0, t0, -0x70c
    /*   714 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   718 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   71c */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   720 */  goto *ra; // Return                      // ret 
    /*   724 */  t0 = 0x724 + 0x100;                      // auipc t0, 0x100
    /*   728 */  t0 = t0 + -0x720;                        // addi t0, t0, -0x720
    /*   72c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   730 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   734 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   738 */  goto *ra; // Return                      // ret 
    /*   73c */  t0 = 0x80000 << 12;                      // lui t0, 0x80000
    /*   740 */  t0 = t0 + -1;                            // addi t0, t0, -1
    /*   744 */  t1 = 0x80000 << 12;                      // lui t1, 0x80000
    /*   748 */  t1 = t1 + -1;                            // addi t1, t1, -1
    /*   74c */  t2 = t0 - t1;                            // sub t2, t0, t1
    /*   750 */  if (t2 != 0) goto LOC_30;                // bnez t2, 0x30
    /*   754 */  t0 = zero;                               // mv t0, zero
    /*   758 */  t1 = zero + -1;                          // addi t1, zero, -1
    /*   75c */  t2 = t0 - t1;                            // sub t2, t0, t1
    /*   760 */  t3 = zero + 1;                           // addi t3, zero, 1

LOC_764:
    /*   764 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_1c; // bne t2, t3, 0x1c
    /*   768 */  t0 = 0x768 + 0x100;                      // auipc t0, 0x100
    /*   76c */  t0 = t0 + -0x768;                        // addi t0, t0, -0x768
    /*   770 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   774 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   778 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   77c */  goto *ra; // Return                      // ret 
    /*   780 */  t0 = 0x780 + 0x100;                      // auipc t0, 0x100
    /*   784 */  t0 = t0 + -0x77c;                        // addi t0, t0, -0x77c
    /*   788 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   78c */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   790 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   794 */  goto *ra; // Return                      // ret 
    /*   798 */  t0 = 0xaaaab << 12;                      // lui t0, 0xaaaab

LOC_79c:
    /*   79c */  t0 = t0 + -0x556;                        // addi t0, t0, -0x556
    /*   7a0 */  t1 = 0x55555 << 12;                      // lui t1, 0x55555
    /*   7a4 */  t1 = t1 + 0x555;                         // addi t1, t1, 0x555
    /*   7a8 */  t2 = t0 & t1;                            // and t2, t0, t1
    /*   7ac */  if (t2 != 0) goto LOC_40;                // bnez t2, 0x40
    /*   7b0 */  t0 = zero + -1;                          // addi t0, zero, -1
    /*   7b4 */  t1 = zero;                               // mv t1, zero
    /*   7b8 */  t2 = t0 & t1;                            // and t2, t0, t1

LOC_7bc:
    /*   7bc */  if (t2 != 0) goto LOC_30;                // bnez t2, 0x30
    /*   7c0 */  t0 = 0x12345 << 12;                      // lui t0, 0x12345
    /*   7c4 */  t0 = t0 + 0x678;                         // addi t0, t0, 0x678
    /*   7c8 */  t1 = zero + -1;                          // addi t1, zero, -1
    /*   7cc */  t2 = t0 & t1;                            // and t2, t0, t1
    /*   7d0 */  if ((int32_t)t2 != (int32_t)t0) goto LOC_1c; // bne t2, t0, 0x1c
    /*   7d4 */  t0 = 0x7d4 + 0x100;                      // auipc t0, 0x100
    /*   7d8 */  t0 = t0 + -0x7d4;                        // addi t0, t0, -0x7d4
    /*   7dc */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   7e0 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   7e4 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   7e8 */  goto *ra; // Return                      // ret 
    /*   7ec */  t0 = 0x7ec + 0x100;                      // auipc t0, 0x100
    /*   7f0 */  t0 = t0 + -0x7e8;                        // addi t0, t0, -0x7e8
    /*   7f4 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   7f8 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   7fc */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   800 */  goto *ra; // Return                      // ret 
    /*   804 */  t0 = zero + -1;                          // addi t0, zero, -1
    /*   808 */  t1 = t0 & 0x70f;                         // andi t1, t0, 0x70f
    /*   80c */  t2 = zero + 0x70f;                       // addi t2, zero, 0x70f
    /*   810 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_30; // bne t1, t2, 0x30

LOC_814:
    /*   814 */  t0 = 0x1234b << 12;                      // lui t0, 0x1234b
    /*   818 */  t0 = t0 + -0x433;                        // addi t0, t0, -0x433
    /*   81c */  t1 = t0 & 0x5cb;                         // andi t1, t0, 0x5cb
    /*   820 */  t2 = zero + 0x1c9;                       // addi t2, zero, 0x1c9
    /*   824 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_1c; // bne t1, t2, 0x1c
    /*   828 */  t0 = 0x828 + 0xff;                       // auipc t0, 0xff
    /*   82c */  t0 = t0 + 0x7d8;                         // addi t0, t0, 0x7d8
    /*   830 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   834 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   838 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   83c */  goto *ra; // Return                      // ret 
    /*   840 */  t0 = 0x840 + 0xff;                       // auipc t0, 0xff
    /*   844 */  t0 = t0 + 0x7c4;                         // addi t0, t0, 0x7c4
    /*   848 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   84c */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   850 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   854 */  goto *ra; // Return                      // ret 

LOC_858:
    /*   858 */  t0 = 0xaaaab << 12;                      // lui t0, 0xaaaab
    /*   85c */  t0 = t0 + -0x556;                        // addi t0, t0, -0x556
    /*   860 */  t1 = 0x55555 << 12;                      // lui t1, 0x55555
    /*   864 */  t1 = t1 + 0x555;                         // addi t1, t1, 0x555
    /*   868 */  t2 = t0 | t1;                            // or t2, t0, t1
    /*   86c */  t3 = zero + -1;                          // addi t3, zero, -1
    /*   870 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_2c; // bne t2, t3, 0x2c
    /*   874 */  t0 = zero;                               // mv t0, zero
    /*   878 */  t1 = zero;                               // mv t1, zero
    /*   87c */  t2 = t0 | t1;                            // or t2, t0, t1
    /*   880 */  if (t2 != 0) goto LOC_1c;                // bnez t2, 0x1c
    /*   884 */  t0 = 0x884 + 0xff;                       // auipc t0, 0xff
    /*   888 */  t0 = t0 + 0x77c;                         // addi t0, t0, 0x77c
    /*   88c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   890 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   894 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   898 */  goto *ra; // Return                      // ret 
    /*   89c */  t0 = 0x89c + 0xff;                       // auipc t0, 0xff
    /*   8a0 */  t0 = t0 + 0x768;                         // addi t0, t0, 0x768

LOC_8a4:
    /*   8a4 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   8a8 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   8ac */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   8b0 */  goto *ra; // Return                      // ret 
    /*   8b4 */  t0 = zero;                               // mv t0, zero
    /*   8b8 */  t1 = t0 | 0x7f0;                         // ori t1, t0, 0x7f0
    /*   8bc */  t2 = zero + 0x7f0;                       // addi t2, zero, 0x7f0
    /*   8c0 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_30; // bne t1, t2, 0x30
    /*   8c4 */  t0 = 0xaaaa0 << 12;                      // lui t0, 0xaaaa0
    /*   8c8 */  t1 = t0 | 0x7ff;                         // ori t1, t0, 0x7ff
    /*   8cc */  t2 = 0xaaaa0 << 12;                      // lui t2, 0xaaaa0
    /*   8d0 */  t2 = t2 + 0x7ff;                         // addi t2, t2, 0x7ff
    /*   8d4 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_1c; // bne t1, t2, 0x1c
    /*   8d8 */  t0 = 0x8d8 + 0xff;                       // auipc t0, 0xff
    /*   8dc */  t0 = t0 + 0x728;                         // addi t0, t0, 0x728
    /*   8e0 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   8e4 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   8e8 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   8ec */  goto *ra; // Return                      // ret 
    /*   8f0 */  t0 = 0x8f0 + 0xff;                       // auipc t0, 0xff
    /*   8f4 */  t0 = t0 + 0x714;                         // addi t0, t0, 0x714

LOC_8f8:
    /*   8f8 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   8fc */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   900 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   904 */  goto *ra; // Return                      // ret 
    /*   908 */  t0 = zero + -1;                          // addi t0, zero, -1
    /*   90c */  t1 = zero;                               // mv t1, zero
    /*   910 */  t2 = ((int32_t)t0 < (int32_t)t1) ? 1 : 0; // slt t2, t0, t1
    /*   914 */  t3 = zero + 1;                           // addi t3, zero, 1
    /*   918 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_40; // bne t2, t3, 0x40
    /*   91c */  t0 = zero + 0x7b;                        // addi t0, zero, 0x7b
    /*   920 */  t1 = zero + 0x7b;                        // addi t1, zero, 0x7b
    /*   924 */  t2 = ((int32_t)t0 < (int32_t)t1) ? 1 : 0; // slt t2, t0, t1
    /*   928 */  if (t2 != 0) goto LOC_30;                // bnez t2, 0x30
    /*   92c */  t0 = 0x80000 << 12;                      // lui t0, 0x80000
    /*   930 */  t0 = t0 + -1;                            // addi t0, t0, -1
    /*   934 */  t1 = zero + -1;                          // addi t1, zero, -1
    /*   938 */  t2 = ((int32_t)t0 < (int32_t)t1) ? 1 : 0; // slt t2, t0, t1
    /*   93c */  if (t2 != 0) goto LOC_1c;                // bnez t2, 0x1c
    /*   940 */  t0 = 0x940 + 0xff;                       // auipc t0, 0xff
    /*   944 */  t0 = t0 + 0x6c0;                         // addi t0, t0, 0x6c0
    /*   948 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   94c */  t1 = t1 + 1;                             // addi t1, t1, 1

LOC_950:
    /*   950 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   954 */  goto *ra; // Return                      // ret 
    /*   958 */  t0 = 0x958 + 0xff;                       // auipc t0, 0xff
    /*   95c */  t0 = t0 + 0x6ac;                         // addi t0, t0, 0x6ac
    /*   960 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   964 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   968 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   96c */  goto *ra; // Return                      // ret 
    /*   970 */  t0 = zero + -1;                          // addi t0, zero, -1
    /*   974 */  t1 = ((int32_t)t0 < (int32_t)0) ? 1 : 0; // slti t1, t0, 0
    /*   978 */  t2 = zero + 1;                           // addi t2, zero, 1
    /*   97c */  if ((int32_t)t1 != (int32_t)t2) goto LOC_4c; // bne t1, t2, 0x4c
    /*   980 */  t0 = zero + 5;                           // addi t0, zero, 5
    /*   984 */  t1 = ((int32_t)t0 < (int32_t)0xa) ? 1 : 0; // slti t1, t0, 0xa
    /*   988 */  t2 = zero + 1;                           // addi t2, zero, 1
    /*   98c */  if ((int32_t)t1 != (int32_t)t2) goto LOC_3c; // bne t1, t2, 0x3c
    /*   990 */  t0 = zero + 5;                           // addi t0, zero, 5
    /*   994 */  t1 = ((int32_t)t0 < (int32_t)5) ? 1 : 0; // slti t1, t0, 5
    /*   998 */  t2 = zero;                               // mv t2, zero
    /*   99c */  if ((int32_t)t1 != (int32_t)t2) goto LOC_2c; // bne t1, t2, 0x2c
    /*   9a0 */  t0 = zero + 0xa;                         // addi t0, zero, 0xa
    /*   9a4 */  t1 = ((int32_t)t0 < (int32_t)5) ? 1 : 0; // slti t1, t0, 5
    /*   9a8 */  t2 = zero;                               // mv t2, zero
    /*   9ac */  if ((int32_t)t1 != (int32_t)t2) goto LOC_1c; // bne t1, t2, 0x1c
    /*   9b0 */  t0 = 0x9b0 + 0xff;                       // auipc t0, 0xff
    /*   9b4 */  t0 = t0 + 0x650;                         // addi t0, t0, 0x650
    /*   9b8 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   9bc */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   9c0 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   9c4 */  goto *ra; // Return                      // ret 
    /*   9c8 */  t0 = 0x9c8 + 0xff;                       // auipc t0, 0xff
    /*   9cc */  t0 = t0 + 0x63c;                         // addi t0, t0, 0x63c
    /*   9d0 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)

LOC_9d4:
    /*   9d4 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   9d8 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   9dc */  t0 = zero;                               // mv t0, zero
    /*   9e0 */  t1 = (t0 == 0) ? 1 : 0;                  // seqz t1, t0
    /*   9e4 */  t2 = zero + 1;                           // addi t2, zero, 1
    /*   9e8 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_28; // bne t1, t2, 0x28
    /*   9ec */  t0 = zero + -1;                          // addi t0, zero, -1
    /*   9f0 */  t1 = ((uint32_t)t0 < (uint32_t)-1) ? 1 : 0; // sltiu t1, t0, -1
    /*   9f4 */  if (t1 != 0) goto LOC_1c;                // bnez t1, 0x1c
    /*   9f8 */  t0 = 0x9f8 + 0xff;                       // auipc t0, 0xff
    /*   9fc */  t0 = t0 + 0x608;                         // addi t0, t0, 0x608
    /*   a00 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   a04 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   a08 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   a0c */  goto *ra; // Return                      // ret 
    /*   a10 */  t0 = 0xa10 + 0xff;                       // auipc t0, 0xff
    /*   a14 */  t0 = t0 + 0x5f4;                         // addi t0, t0, 0x5f4
    /*   a18 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   a1c */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   a20 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   a24 */  goto *ra; // Return                      // ret 
    /*   a28 */  t0 = zero + -1;                          // addi t0, zero, -1
    /*   a2c */  t1 = zero;                               // mv t1, zero

LOC_a30:
    /*   a30 */  t2 = ((uint32_t)t0 < (uint32_t)t1) ? 1 : 0; // sltu t2, t0, t1
    /*   a34 */  if (t2 != 0) goto LOC_30;                // bnez t2, 0x30
    /*   a38 */  t0 = zero;                               // mv t0, zero
    /*   a3c */  t1 = zero + 1;                           // addi t1, zero, 1
    /*   a40 */  t2 = ((uint32_t)t0 < (uint32_t)t1) ? 1 : 0; // sltu t2, t0, t1
    /*   a44 */  t3 = zero + 1;                           // addi t3, zero, 1
    /*   a48 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_1c; // bne t2, t3, 0x1c
    /*   a4c */  t0 = 0xa4c + 0xff;                       // auipc t0, 0xff
    /*   a50 */  t0 = t0 + 0x5b4;                         // addi t0, t0, 0x5b4
    /*   a54 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   a58 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   a5c */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   a60 */  goto *ra; // Return                      // ret 
    /*   a64 */  t0 = 0xa64 + 0xff;                       // auipc t0, 0xff
    /*   a68 */  t0 = t0 + 0x5a0;                         // addi t0, t0, 0x5a0
    /*   a6c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   a70 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   a74 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   a78 */  goto *ra; // Return                      // ret 

LOC_a7c:
    /*   a7c */  t0 = 0xffff0 << 12;                      // lui t0, 0xffff0
    /*   a80 */  t1 = 0x10 << 12;                         // lui t1, 0x10
    /*   a84 */  t1 = t1 + -1;                            // addi t1, t1, -1
    /*   a88 */  t2 = t0 ^ t1;                            // xor t2, t0, t1
    /*   a8c */  t3 = zero + -1;                          // addi t3, zero, -1
    /*   a90 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_2c; // bne t2, t3, 0x2c
    /*   a94 */  t0 = 0xaaaab << 12;                      // lui t0, 0xaaaab
    /*   a98 */  t0 = t0 + -0x556;                        // addi t0, t0, -0x556
    /*   a9c */  t2 = t0 ^ t0;                            // xor t2, t0, t0
    /*   aa0 */  if (t2 != 0) goto LOC_1c;                // bnez t2, 0x1c
    /*   aa4 */  t0 = 0xaa4 + 0xff;                       // auipc t0, 0xff
    /*   aa8 */  t0 = t0 + 0x55c;                         // addi t0, t0, 0x55c
    /*   aac */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   ab0 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   ab4 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   ab8 */  goto *ra; // Return                      // ret 
    /*   abc */  t0 = 0xabc + 0xff;                       // auipc t0, 0xff
    /*   ac0 */  t0 = t0 + 0x548;                         // addi t0, t0, 0x548
    /*   ac4 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   ac8 */  t1 = t1 + 1;                             // addi t1, t1, 1

LOC_acc:
    /*   acc */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   ad0 */  goto *ra; // Return                      // ret 
    /*   ad4 */  t0 = 0xb << 12;                          // lui t0, 0xb
    /*   ad8 */  t0 = t0 + -0x556;                        // addi t0, t0, -0x556
    /*   adc */  t1 = t0 ^ 0x555;                         // xori t1, t0, 0x555
    /*   ae0 */  t2 = 0xb << 12;                          // lui t2, 0xb
    /*   ae4 */  t2 = t2 + -1;                            // addi t2, t2, -1
    /*   ae8 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_2c; // bne t1, t2, 0x2c
    /*   aec */  t0 = zero + 4;                           // addi t0, zero, 4
    /*   af0 */  t1 = t0 ^ 0x234;                         // xori t1, t0, 0x234
    /*   af4 */  t2 = zero + 0x230;                       // addi t2, zero, 0x230
    /*   af8 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_1c; // bne t1, t2, 0x1c
    /*   afc */  t0 = 0xafc + 0xff;                       // auipc t0, 0xff
    /*   b00 */  t0 = t0 + 0x504;                         // addi t0, t0, 0x504
    /*   b04 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   b08 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   b0c */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   b10 */  goto *ra; // Return                      // ret 

LOC_b14:
    /*   b14 */  t0 = 0xb14 + 0xff;                       // auipc t0, 0xff
    /*   b18 */  t0 = t0 + 0x4f0;                         // addi t0, t0, 0x4f0
    /*   b1c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   b20 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   b24 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   b28 */  goto *ra; // Return                      // ret 
    /*   b2c */  t0 = zero + 1;                           // addi t0, zero, 1
    /*   b30 */  t1 = zero + 3;                           // addi t1, zero, 3
    /*   b34 */  t2 = t0 << (t1 & 0x1F);                  // sll t2, t0, t1
    /*   b38 */  t3 = zero + 8;                           // addi t3, zero, 8
    /*   b3c */  if ((int32_t)t2 != (int32_t)t3) goto LOC_30; // bne t2, t3, 0x30
    /*   b40 */  t0 = zero + 1;                           // addi t0, zero, 1
    /*   b44 */  t1 = zero + 0x1f;                        // addi t1, zero, 0x1f
    /*   b48 */  t2 = t0 << (t1 & 0x1F);                  // sll t2, t0, t1
    /*   b4c */  t3 = 0x80000 << 12;                      // lui t3, 0x80000
    /*   b50 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_1c; // bne t2, t3, 0x1c
    /*   b54 */  t0 = 0xb54 + 0xff;                       // auipc t0, 0xff
    /*   b58 */  t0 = t0 + 0x4ac;                         // addi t0, t0, 0x4ac

LOC_b5c:
    /*   b5c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   b60 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   b64 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   b68 */  goto *ra; // Return                      // ret 
    /*   b6c */  t0 = 0xb6c + 0xff;                       // auipc t0, 0xff
    /*   b70 */  t0 = t0 + 0x498;                         // addi t0, t0, 0x498
    /*   b74 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   b78 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   b7c */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   b80 */  goto *ra; // Return                      // ret 
    /*   b84 */  t0 = zero + 1;                           // addi t0, zero, 1
    /*   b88 */  t1 = t0 << 4;                            // slli t1, t0, 4
    /*   b8c */  t2 = zero + 0x10;                        // addi t2, zero, 0x10
    /*   b90 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_2c; // bne t1, t2, 0x2c
    /*   b94 */  t0 = zero + 1;                           // addi t0, zero, 1
    /*   b98 */  t1 = t0 << 0x1f;                         // slli t1, t0, 0x1f
    /*   b9c */  t2 = 0x80000 << 12;                      // lui t2, 0x80000
    /*   ba0 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_1c; // bne t1, t2, 0x1c

LOC_ba4:
    /*   ba4 */  t0 = 0xba4 + 0xff;                       // auipc t0, 0xff
    /*   ba8 */  t0 = t0 + 0x45c;                         // addi t0, t0, 0x45c
    /*   bac */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   bb0 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   bb4 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   bb8 */  goto *ra; // Return                      // ret 
    /*   bbc */  t0 = 0xbbc + 0xff;                       // auipc t0, 0xff
    /*   bc0 */  t0 = t0 + 0x448;                         // addi t0, t0, 0x448
    /*   bc4 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   bc8 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   bcc */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   bd0 */  goto *ra; // Return                      // ret 
    /*   bd4 */  t0 = 0x80000 << 12;                      // lui t0, 0x80000
    /*   bd8 */  t1 = zero + 0x1f;                        // addi t1, zero, 0x1f
    /*   bdc */  t2 = (uint32_t)t0 >> (t1 & 0x1F);        // srl t2, t0, t1
    /*   be0 */  t3 = zero + 1;                           // addi t3, zero, 1
    /*   be4 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_34; // bne t2, t3, 0x34
    /*   be8 */  t0 = zero + -1;                          // addi t0, zero, -1

LOC_bec:
    /*   bec */  t1 = zero + 4;                           // addi t1, zero, 4
    /*   bf0 */  t2 = (uint32_t)t0 >> (t1 & 0x1F);        // srl t2, t0, t1
    /*   bf4 */  t3 = 0x10000 << 12;                      // lui t3, 0x10000
    /*   bf8 */  t3 = t3 + -1;                            // addi t3, t3, -1
    /*   bfc */  if ((int32_t)t2 != (int32_t)t3) goto LOC_1c; // bne t2, t3, 0x1c
    /*   c00 */  t0 = 0xc00 + 0xff;                       // auipc t0, 0xff
    /*   c04 */  t0 = t0 + 0x400;                         // addi t0, t0, 0x400
    /*   c08 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   c0c */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   c10 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   c14 */  goto *ra; // Return                      // ret 
    /*   c18 */  t0 = 0xc18 + 0xff;                       // auipc t0, 0xff
    /*   c1c */  t0 = t0 + 0x3ec;                         // addi t0, t0, 0x3ec
    /*   c20 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   c24 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   c28 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   c2c */  goto *ra; // Return                      // ret 
    /*   c30 */  t0 = 0x80000 << 12;                      // lui t0, 0x80000

LOC_c34:
    /*   c34 */  t1 = (uint32_t)t0 >> 0x1f;               // srli t1, t0, 0x1f
    /*   c38 */  t2 = zero + 1;                           // addi t2, zero, 1
    /*   c3c */  if ((int32_t)t1 != (int32_t)t2) goto LOC_30; // bne t1, t2, 0x30
    /*   c40 */  t0 = zero + -1;                          // addi t0, zero, -1
    /*   c44 */  t1 = (uint32_t)t0 >> 4;                  // srli t1, t0, 4
    /*   c48 */  t2 = 0x10000 << 12;                      // lui t2, 0x10000
    /*   c4c */  t2 = t2 + -1;                            // addi t2, t2, -1
    /*   c50 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_1c; // bne t1, t2, 0x1c
    /*   c54 */  t0 = 0xc54 + 0xff;                       // auipc t0, 0xff
    /*   c58 */  t0 = t0 + 0x3ac;                         // addi t0, t0, 0x3ac
    /*   c5c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   c60 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   c64 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   c68 */  goto *ra; // Return                      // ret 
    /*   c6c */  t0 = 0xc6c + 0xff;                       // auipc t0, 0xff
    /*   c70 */  t0 = t0 + 0x398;                         // addi t0, t0, 0x398
    /*   c74 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   c78 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   c7c */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)

LOC_c80:
    /*   c80 */  goto *ra; // Return                      // ret 
    /*   c84 */  t0 = zero + -1;                          // addi t0, zero, -1
    /*   c88 */  t1 = zero + 0x1f;                        // addi t1, zero, 0x1f
    /*   c8c */  t2 = (int32_t)t0 >> (t1 & 0x1F);         // sra t2, t0, t1
    /*   c90 */  t3 = zero + -1;                          // addi t3, zero, -1
    /*   c94 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_44; // bne t2, t3, 0x44
    /*   c98 */  t0 = 0x80000 << 12;                      // lui t0, 0x80000
    /*   c9c */  t1 = zero + 0x1f;                        // addi t1, zero, 0x1f
    /*   ca0 */  t2 = (int32_t)t0 >> (t1 & 0x1F);         // sra t2, t0, t1
    /*   ca4 */  t3 = zero + -1;                          // addi t3, zero, -1
    /*   ca8 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_30; // bne t2, t3, 0x30
    /*   cac */  t0 = 0x1000 << 12;                       // lui t0, 0x1000
    /*   cb0 */  t1 = zero + 4;                           // addi t1, zero, 4
    /*   cb4 */  t2 = (int32_t)t0 >> (t1 & 0x1F);         // sra t2, t0, t1
    /*   cb8 */  t3 = 0x100 << 12;                        // lui t3, 0x100
    /*   cbc */  if ((int32_t)t2 != (int32_t)t3) goto LOC_1c; // bne t2, t3, 0x1c
    /*   cc0 */  t0 = 0xcc0 + 0xff;                       // auipc t0, 0xff
    /*   cc4 */  t0 = t0 + 0x340;                         // addi t0, t0, 0x340
    /*   cc8 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   ccc */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   cd0 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   cd4 */  goto *ra; // Return                      // ret 
    /*   cd8 */  t0 = 0xcd8 + 0xff;                       // auipc t0, 0xff
    /*   cdc */  t0 = t0 + 0x32c;                         // addi t0, t0, 0x32c
    /*   ce0 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   ce4 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   ce8 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   cec */  goto *ra; // Return                      // ret 
    /*   cf0 */  t0 = zero + -1;                          // addi t0, zero, -1
    /*   cf4 */  t1 = (int32_t)t0 >> 0x1f;                // srai t1, t0, 0x1f
    /*   cf8 */  t2 = zero + -1;                          // addi t2, zero, -1
    /*   cfc */  if ((int32_t)t1 != (int32_t)t2) goto LOC_2c; // bne t1, t2, 0x2c
    /*   d00 */  t0 = 0x80000 << 12;                      // lui t0, 0x80000
    /*   d04 */  t1 = (int32_t)t0 >> 0x1f;                // srai t1, t0, 0x1f
    /*   d08 */  t2 = zero + -1;                          // addi t2, zero, -1
    /*   d0c */  if ((int32_t)t1 != (int32_t)t2) goto LOC_1c; // bne t1, t2, 0x1c
    /*   d10 */  t0 = 0xd10 + 0xff;                       // auipc t0, 0xff
    /*   d14 */  t0 = t0 + 0x2f0;                         // addi t0, t0, 0x2f0
    /*   d18 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   d1c */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   d20 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   d24 */  goto *ra; // Return                      // ret 
    /*   d28 */  t0 = 0xd28 + 0xff;                       // auipc t0, 0xff
    /*   d2c */  t0 = t0 + 0x2dc;                         // addi t0, t0, 0x2dc
    /*   d30 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   d34 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   d38 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   d3c */  goto *ra; // Return                      // ret 
    /*   d40 */  t0 = 0x12345 << 12;                      // lui t0, 0x12345
    /*   d44 */  t1 = 0x12345 << 12;                      // lui t1, 0x12345
    /*   d48 */  if ((int32_t)t0 != (int32_t)t1) goto LOC_1c; // bne t0, t1, 0x1c
    /*   d4c */  t0 = 0xd4c + 0xff;                       // auipc t0, 0xff
    /*   d50 */  t0 = t0 + 0x2b4;                         // addi t0, t0, 0x2b4
    /*   d54 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   d58 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   d5c */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   d60 */  goto *ra; // Return                      // ret 
    /*   d64 */  t0 = 0xd64 + 0xff;                       // auipc t0, 0xff
    /*   d68 */  t0 = t0 + 0x2a0;                         // addi t0, t0, 0x2a0
    /*   d6c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   d70 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   d74 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   d78 */  goto *ra; // Return                      // ret 
    /*   d7c */  t0 = 0xd7c + 0;                          // auipc t0, 0
    /*   d80 */  t0 = t0;                                 // mv t0, t0
    /*   d84 */  // nop                                   // nop 
    /*   d88 */  // nop                                   // nop 
    /*   d8c */  t1 = 0xd8c + 0;                          // auipc t1, 0
    /*   d90 */  t1 = t1 + -0x10;                         // addi t1, t1, -0x10
    /*   d94 */  if ((int32_t)t0 != (int32_t)t1) goto LOC_1c; // bne t0, t1, 0x1c
    /*   d98 */  t0 = 0xd98 + 0xff;                       // auipc t0, 0xff
    /*   d9c */  t0 = t0 + 0x268;                         // addi t0, t0, 0x268
    /*   da0 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   da4 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   da8 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   dac */  goto *ra; // Return                      // ret 
    /*   db0 */  t0 = 0xdb0 + 0xff;                       // auipc t0, 0xff
    /*   db4 */  t0 = t0 + 0x254;                         // addi t0, t0, 0x254
    /*   db8 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   dbc */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   dc0 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   dc4 */  goto *ra; // Return                      // ret 
    /*   dc8 */  t0 = 0x12345 << 12;                      // lui t0, 0x12345
    /*   dcc */  t0 = t0 + 0x688;                         // addi t0, t0, 0x688
    /*   dd0 */  t1 = 0xdd0 + 0xff;                       // auipc t1, 0xff
    /*   dd4 */  t1 = t1 + 0x238;                         // addi t1, t1, 0x238
    /*   dd8 */  *(uint32_t*)(t1 + 0) = t0;               // sw t0, 0(t1)
    /*   ddc */  t2 = *(int32_t*)(t1 + 0);                // lw t2, 0(t1)
    /*   de0 */  t3 = 0x12345 << 12;                      // lui t3, 0x12345
    /*   de4 */  t3 = t3 + 0x688;                         // addi t3, t3, 0x688
    /*   de8 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_1c; // bne t2, t3, 0x1c
    /*   dec */  t0 = 0xdec + 0xff;                       // auipc t0, 0xff
    /*   df0 */  t0 = t0 + 0x214;                         // addi t0, t0, 0x214
    /*   df4 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   df8 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   dfc */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   e00 */  goto *ra; // Return                      // ret 
    /*   e04 */  t0 = 0xe04 + 0xff;                       // auipc t0, 0xff
    /*   e08 */  t0 = t0 + 0x200;                         // addi t0, t0, 0x200
    /*   e0c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   e10 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   e14 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   e18 */  goto *ra; // Return                      // ret 
    /*   e1c */  s0 = ra;                                 // mv s0, ra
    /*   e20 */  ra = 0xe24; goto LOC_10; // Call         // jal 0x10
    /*   e24 */  t0 = 0xe24 + 0;                          // auipc t0, 0
    /*   e28 */  if ((int32_t)ra != (int32_t)t0) goto LOC_10; // bne ra, t0, 0x10
    /*   e2c */  goto LOC_28;                             // j 0x28
    /*   e30 */  t1 = zero + 4;                           // addi t1, zero, 4

LOC_e34:
    /*   e34 */  goto *ra; // Return                      // ret 
    /*   e38 */  t0 = 0xe38 + 0xff;                       // auipc t0, 0xff
    /*   e3c */  t0 = t0 + 0x1cc;                         // addi t0, t0, 0x1cc
    /*   e40 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   e44 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   e48 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   e4c */  ra = s0;                                 // mv ra, s0
    /*   e50 */  goto *ra; // Return                      // ret 
    /*   e54 */  t0 = 0xe54 + 0xff;                       // auipc t0, 0xff
    /*   e58 */  t0 = t0 + 0x1ac;                         // addi t0, t0, 0x1ac
    /*   e5c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   e60 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   e64 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   e68 */  ra = s0;                                 // mv ra, s0
    /*   e6c */  goto *ra; // Return                      // ret 
    /*   e70 */  t0 = 0xe70 + 0xff;                       // auipc t0, 0xff
    /*   e74 */  t0 = t0 + 0x198;                         // addi t0, t0, 0x198
    /*   e78 */  t1 = *(int8_t*)(t0 + 2);                 // lb t1, 2(t0)
    /*   e7c */  t2 = zero + 0x34;                        // addi t2, zero, 0x34
    /*   e80 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_28; // bne t1, t2, 0x28
    /*   e84 */  t1 = *(int8_t*)(t0 + 0);                 // lb t1, 0(t0)
    /*   e88 */  t2 = zero + -0x78;                       // addi t2, zero, -0x78
    /*   e8c */  if ((int32_t)t1 != (int32_t)t2) goto LOC_1c; // bne t1, t2, 0x1c
    /*   e90 */  t0 = 0xe90 + 0xff;                       // auipc t0, 0xff
    /*   e94 */  t0 = t0 + 0x170;                         // addi t0, t0, 0x170
    /*   e98 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   e9c */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   ea0 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   ea4 */  goto *ra; // Return                      // ret 
    /*   ea8 */  t0 = 0xea8 + 0xff;                       // auipc t0, 0xff
    /*   eac */  t0 = t0 + 0x15c;                         // addi t0, t0, 0x15c
    /*   eb0 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   eb4 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   eb8 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   ebc */  goto *ra; // Return                      // ret 
    /*   ec0 */  t0 = 0xec0 + 0xff;                       // auipc t0, 0xff
    /*   ec4 */  t0 = t0 + 0x148;                         // addi t0, t0, 0x148
    /*   ec8 */  t1 = *(int16_t*)(t0 + 4);                // lh t1, 4(t0)
    /*   ecc */  t2 = 0xffffb << 12;                      // lui t2, 0xffffb

LOC_ed0:
    /*   ed0 */  t2 = t2 + -0x433;                        // addi t2, t2, -0x433
    /*   ed4 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_2c; // bne t1, t2, 0x2c
    /*   ed8 */  t1 = *(int16_t*)(t0 + 6);                // lh t1, 6(t0)
    /*   edc */  t2 = 0x1 << 12;                          // lui t2, 1
    /*   ee0 */  t2 = t2 + 0x234;                         // addi t2, t2, 0x234
    /*   ee4 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_1c; // bne t1, t2, 0x1c
    /*   ee8 */  t0 = 0xee8 + 0xff;                       // auipc t0, 0xff
    /*   eec */  t0 = t0 + 0x118;                         // addi t0, t0, 0x118
    /*   ef0 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   ef4 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   ef8 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   efc */  goto *ra; // Return                      // ret 
    /*   f00 */  t0 = 0xf00 + 0xff;                       // auipc t0, 0xff
    /*   f04 */  t0 = t0 + 0x104;                         // addi t0, t0, 0x104
    /*   f08 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   f0c */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   f10 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   f14 */  goto *ra; // Return                      // ret 
    /*   f18 */  t0 = 0xf18 + 0xff;                       // auipc t0, 0xff
    /*   f1c */  t0 = t0 + 0xf0;                          // addi t0, t0, 0xf0
    /*   f20 */  t1 = *(int32_t*)(t0 + 8);                // lw t1, 8(t0)
    /*   f24 */  t2 = 0x55667 << 12;                      // lui t2, 0x55667
    /*   f28 */  t2 = t2 + 0x788;                         // addi t2, t2, 0x788
    /*   f2c */  if ((int32_t)t1 != (int32_t)t2) goto LOC_1c; // bne t1, t2, 0x1c
    /*   f30 */  t0 = 0xf30 + 0xff;                       // auipc t0, 0xff
    /*   f34 */  t0 = t0 + 0xd0;                          // addi t0, t0, 0xd0
    /*   f38 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   f3c */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   f40 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   f44 */  goto *ra; // Return                      // ret 
    /*   f48 */  t0 = 0xf48 + 0xff;                       // auipc t0, 0xff
    /*   f4c */  t0 = t0 + 0xbc;                          // addi t0, t0, 0xbc
    /*   f50 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   f54 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   f58 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   f5c */  goto *ra; // Return                      // ret 
    /*   f60 */  t0 = 0xf60 + 0xff;                       // auipc t0, 0xff
    /*   f64 */  t0 = t0 + 0xa8;                          // addi t0, t0, 0xa8
    /*   f68 */  t1 = zero + 0x7f;                        // addi t1, zero, 0x7f
    /*   f6c */  *(uint8_t*)(t0 + 0xc) = t1;              // sb t1, 0xc(t0)
    /*   f70 */  t2 = *(int8_t*)(t0 + 0xc);               // lb t2, 0xc(t0)
    /*   f74 */  t3 = zero + 0x7f;                        // addi t3, zero, 0x7f
    /*   f78 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_58; // bne t2, t3, 0x58
    /*   f7c */  t1 = zero + 0x7f;                        // addi t1, zero, 0x7f
    /*   f80 */  *(uint8_t*)(t0 + 0xd) = t1;              // sb t1, 0xd(t0)
    /*   f84 */  t2 = *(int8_t*)(t0 + 0xd);               // lb t2, 0xd(t0)
    /*   f88 */  t3 = zero + 0x7f;                        // addi t3, zero, 0x7f
    /*   f8c */  if ((int32_t)t2 != (int32_t)t3) goto LOC_44; // bne t2, t3, 0x44
    /*   f90 */  t1 = zero + 0x7f;                        // addi t1, zero, 0x7f
    /*   f94 */  *(uint8_t*)(t0 + 0xe) = t1;              // sb t1, 0xe(t0)
    /*   f98 */  t2 = *(int8_t*)(t0 + 0xe);               // lb t2, 0xe(t0)
    /*   f9c */  t3 = zero + 0x7f;                        // addi t3, zero, 0x7f
    /*   fa0 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_30; // bne t2, t3, 0x30
    /*   fa4 */  t1 = zero + 0x7f;                        // addi t1, zero, 0x7f
    /*   fa8 */  *(uint8_t*)(t0 + 0xf) = t1;              // sb t1, 0xf(t0)
    /*   fac */  t2 = *(int8_t*)(t0 + 0xf);               // lb t2, 0xf(t0)
    /*   fb0 */  t3 = zero + 0x7f;                        // addi t3, zero, 0x7f
    /*   fb4 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_1c; // bne t2, t3, 0x1c
    /*   fb8 */  t0 = 0xfb8 + 0xff;                       // auipc t0, 0xff
    /*   fbc */  t0 = t0 + 0x48;                          // addi t0, t0, 0x48
    /*   fc0 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   fc4 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   fc8 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   fcc */  goto *ra; // Return                      // ret 
    /*   fd0 */  t0 = 0xfd0 + 0xff;                       // auipc t0, 0xff
    /*   fd4 */  t0 = t0 + 0x34;                          // addi t0, t0, 0x34
    /*   fd8 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*   fdc */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   fe0 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*   fe4 */  goto *ra; // Return                      // ret 
    /*   fe8 */  t0 = 0xfe8 + 0xff;                       // auipc t0, 0xff
    /*   fec */  t0 = t0 + 0x20;                          // addi t0, t0, 0x20
    /*   ff0 */  t1 = 0x8 << 12;                          // lui t1, 8
    /*   ff4 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*   ff8 */  *(uint16_t*)(t0 + 0x10) = t1;            // sh t1, 0x10(t0)
    /*   ffc */  t2 = *(int16_t*)(t0 + 0x10);             // lh t2, 0x10(t0)
    /*  1000 */  t3 = 0xffff8 << 12;                      // lui t3, 0xffff8
    /*  1004 */  t3 = t3 + 1;                             // addi t3, t3, 1
    /*  1008 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_34; // bne t2, t3, 0x34
    /*  100c */  t1 = zero + 0x101;                       // addi t1, zero, 0x101
    /*  1010 */  *(uint16_t*)(t0 + 0x12) = t1;            // sh t1, 0x12(t0)
    /*  1014 */  t2 = *(int32_t*)(t0 + 0x10);             // lw t2, 0x10(t0)
    /*  1018 */  t3 = 0x1018 << 12;                       // lui t3, 0x1018
    /*  101c */  t3 = t3 + 1;                             // addi t3, t3, 1
    /*  1020 */  if ((int32_t)t2 != (int32_t)t3) goto LOC_1c; // bne t2, t3, 0x1c
    /*  1024 */  t0 = 0x1024 + 0xff;                      // auipc t0, 0xff
    /*  1028 */  t0 = t0 + -0x24;                         // addi t0, t0, -0x24
    /*  102c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  1030 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  1034 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  1038 */  goto *ra; // Return                      // ret 
    /*  103c */  t0 = 0x103c + 0xff;                      // auipc t0, 0xff
    /*  1040 */  t0 = t0 + -0x38;                         // addi t0, t0, -0x38
    /*  1044 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  1048 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  104c */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  1050 */  goto *ra; // Return                      // ret 
    /*  1054 */  t0 = 0x1054 + 0xff;                      // auipc t0, 0xff
    /*  1058 */  t0 = t0 + -0x4c;                         // addi t0, t0, -0x4c
    /*  105c */  t1 = *(uint8_t*)(t0 + 0x14);             // lbu t1, 0x14(t0)
    /*  1060 */  t2 = zero + 0xff;                        // addi t2, zero, 0xff
    /*  1064 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_28; // bne t1, t2, 0x28
    /*  1068 */  t1 = *(uint8_t*)(t0 + 0x15);             // lbu t1, 0x15(t0)
    /*  106c */  t2 = zero;                               // mv t2, zero
    /*  1070 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_1c; // bne t1, t2, 0x1c
    /*  1074 */  t0 = 0x1074 + 0xff;                      // auipc t0, 0xff
    /*  1078 */  t0 = t0 + -0x74;                         // addi t0, t0, -0x74
    /*  107c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  1080 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  1084 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  1088 */  goto *ra; // Return                      // ret 
    /*  108c */  t0 = 0x108c + 0xff;                      // auipc t0, 0xff
    /*  1090 */  t0 = t0 + -0x88;                         // addi t0, t0, -0x88
    /*  1094 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  1098 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  109c */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  10a0 */  goto *ra; // Return                      // ret 
    /*  10a4 */  t0 = 0x10a4 + 0xff;                      // auipc t0, 0xff
    /*  10a8 */  t0 = t0 + -0x9c;                         // addi t0, t0, -0x9c
    /*  10ac */  t1 = *(uint16_t*)(t0 + 0x14);            // lhu t1, 0x14(t0)
    /*  10b0 */  t2 = zero + 0xff;                        // addi t2, zero, 0xff
    /*  10b4 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_2c; // bne t1, t2, 0x2c
    /*  10b8 */  t1 = *(uint16_t*)(t0 + 0x16);            // lhu t1, 0x16(t0)
    /*  10bc */  t2 = 0x10 << 12;                         // lui t2, 0x10
    /*  10c0 */  t2 = t2 + -0x100;                        // addi t2, t2, -0x100
    /*  10c4 */  if ((int32_t)t1 != (int32_t)t2) goto LOC_1c; // bne t1, t2, 0x1c
    /*  10c8 */  t0 = 0x10c8 + 0xff;                      // auipc t0, 0xff
    /*  10cc */  t0 = t0 + -0xc8;                         // addi t0, t0, -0xc8
    /*  10d0 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  10d4 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  10d8 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  10dc */  goto *ra; // Return                      // ret 
    /*  10e0 */  t0 = 0x10e0 + 0xff;                      // auipc t0, 0xff
    /*  10e4 */  t0 = t0 + -0xdc;                         // addi t0, t0, -0xdc
    /*  10e8 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  10ec */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  10f0 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  10f4 */  goto *ra; // Return                      // ret 
    /*  10f8 */  t0 = zero + 5;                           // addi t0, zero, 5
    /*  10fc */  t1 = zero + 5;                           // addi t1, zero, 5
    /*  1100 */  if ((int32_t)t0 == (int32_t)t1) goto LOC_8; // beq t0, t1, 8
    /*  1104 */  goto LOC_28;                             // j 0x28
    /*  1108 */  t0 = zero + 1;                           // addi t0, zero, 1
    /*  110c */  t1 = zero + 2;                           // addi t1, zero, 2
    /*  1110 */  if ((int32_t)t0 == (int32_t)t1) goto LOC_1c; // beq t0, t1, 0x1c
    /*  1114 */  t0 = 0x1114 + 0xff;                      // auipc t0, 0xff
    /*  1118 */  t0 = t0 + -0x114;                        // addi t0, t0, -0x114
    /*  111c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  1120 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  1124 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  1128 */  goto *ra; // Return                      // ret 
    /*  112c */  t0 = 0x112c + 0xff;                      // auipc t0, 0xff
    /*  1130 */  t0 = t0 + -0x128;                        // addi t0, t0, -0x128
    /*  1134 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  1138 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  113c */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  1140 */  goto *ra; // Return                      // ret 
    /*  1144 */  t0 = zero + 1;                           // addi t0, zero, 1
    /*  1148 */  t1 = zero + 2;                           // addi t1, zero, 2
    /*  114c */  if ((int32_t)t0 != (int32_t)t1) goto LOC_8; // bne t0, t1, 8
    /*  1150 */  goto LOC_28;                             // j 0x28
    /*  1154 */  t0 = zero + 5;                           // addi t0, zero, 5
    /*  1158 */  t1 = zero + 5;                           // addi t1, zero, 5
    /*  115c */  if ((int32_t)t0 != (int32_t)t1) goto LOC_1c; // bne t0, t1, 0x1c
    /*  1160 */  t0 = 0x1160 + 0xff;                      // auipc t0, 0xff
    /*  1164 */  t0 = t0 + -0x160;                        // addi t0, t0, -0x160
    /*  1168 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  116c */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  1170 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  1174 */  goto *ra; // Return                      // ret 
    /*  1178 */  t0 = 0x1178 + 0xff;                      // auipc t0, 0xff
    /*  117c */  t0 = t0 + -0x174;                        // addi t0, t0, -0x174
    /*  1180 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  1184 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  1188 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  118c */  goto *ra; // Return                      // ret 
    /*  1190 */  t0 = zero + -1;                          // addi t0, zero, -1
    /*  1194 */  t1 = zero;                               // mv t1, zero
    /*  1198 */  if ((int32_t)t0 < (int32_t)t1) goto LOC_8; // blt t0, t1, 8
    /*  119c */  goto LOC_28;                             // j 0x28
    /*  11a0 */  t0 = zero + 5;                           // addi t0, zero, 5
    /*  11a4 */  t1 = zero + 5;                           // addi t1, zero, 5
    /*  11a8 */  if ((int32_t)t0 < (int32_t)t1) goto LOC_1c; // blt t0, t1, 0x1c
    /*  11ac */  t0 = 0x11ac + 0xff;                      // auipc t0, 0xff
    /*  11b0 */  t0 = t0 + -0x1ac;                        // addi t0, t0, -0x1ac
    /*  11b4 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  11b8 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  11bc */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  11c0 */  goto *ra; // Return                      // ret 
    /*  11c4 */  t0 = 0x11c4 + 0xff;                      // auipc t0, 0xff
    /*  11c8 */  t0 = t0 + -0x1c0;                        // addi t0, t0, -0x1c0
    /*  11cc */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  11d0 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  11d4 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  11d8 */  goto *ra; // Return                      // ret 
    /*  11dc */  t0 = zero + 1;                           // addi t0, zero, 1
    /*  11e0 */  t1 = zero + -1;                          // addi t1, zero, -1
    /*  11e4 */  if ((int32_t)t0 >= (int32_t)t1) goto LOC_8; // bge t0, t1, 8
    /*  11e8 */  goto LOC_28;                             // j 0x28
    /*  11ec */  t0 = zero + 1;                           // addi t0, zero, 1
    /*  11f0 */  t1 = zero + 5;                           // addi t1, zero, 5
    /*  11f4 */  if ((int32_t)t0 >= (int32_t)t1) goto LOC_1c; // bge t0, t1, 0x1c
    /*  11f8 */  t0 = 0x11f8 + 0xff;                      // auipc t0, 0xff
    /*  11fc */  t0 = t0 + -0x1f8;                        // addi t0, t0, -0x1f8
    /*  1200 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  1204 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  1208 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  120c */  goto *ra; // Return                      // ret 
    /*  1210 */  t0 = 0x1210 + 0xff;                      // auipc t0, 0xff
    /*  1214 */  t0 = t0 + -0x20c;                        // addi t0, t0, -0x20c
    /*  1218 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  121c */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  1220 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  1224 */  goto *ra; // Return                      // ret 
    /*  1228 */  t0 = zero + -1;                          // addi t0, zero, -1
    /*  122c */  t1 = zero + 5;                           // addi t1, zero, 5
    /*  1230 */  if ((uint32_t)t1 < (uint32_t)t0) goto LOC_8; // bltu t1, t0, 8
    /*  1234 */  goto LOC_28;                             // j 0x28
    /*  1238 */  t0 = zero + 5;                           // addi t0, zero, 5
    /*  123c */  t1 = zero + 5;                           // addi t1, zero, 5
    /*  1240 */  if ((uint32_t)t0 < (uint32_t)t1) goto LOC_1c; // bltu t0, t1, 0x1c
    /*  1244 */  t0 = 0x1244 + 0xff;                      // auipc t0, 0xff
    /*  1248 */  t0 = t0 + -0x244;                        // addi t0, t0, -0x244
    /*  124c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  1250 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  1254 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  1258 */  goto *ra; // Return                      // ret 
    /*  125c */  t0 = 0x125c + 0xff;                      // auipc t0, 0xff
    /*  1260 */  t0 = t0 + -0x258;                        // addi t0, t0, -0x258

LOC_1264:
    /*  1264 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  1268 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  126c */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  1270 */  goto *ra; // Return                      // ret 
    /*  1274 */  t0 = zero + 5;                           // addi t0, zero, 5
    /*  1278 */  t1 = zero + -1;                          // addi t1, zero, -1
    /*  127c */  if ((uint32_t)t1 >= (uint32_t)t0) goto LOC_18; // bgeu t1, t0, 0x18
    /*  1280 */  goto LOC_2c;                             // j 0x2c
    /*  1284 */  t0 = zero + 5;                           // addi t0, zero, 5
    /*  1288 */  t1 = zero + 5;                           // addi t1, zero, 5
    /*  128c */  if ((uint32_t)t0 >= (uint32_t)t1) goto LOC_8; // bgeu t0, t1, 8
    /*  1290 */  goto LOC_1c;                             // j 0x1c
    /*  1294 */  t0 = 0x1294 + 0xff;                      // auipc t0, 0xff
    /*  1298 */  t0 = t0 + -0x294;                        // addi t0, t0, -0x294
    /*  129c */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  12a0 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  12a4 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  12a8 */  goto *ra; // Return                      // ret 
    /*  12ac */  t0 = 0x12ac + 0xff;                      // auipc t0, 0xff
    /*  12b0 */  t0 = t0 + -0x2a8;                        // addi t0, t0, -0x2a8
    /*  12b4 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  12b8 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  12bc */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  12c0 */  goto *ra; // Return                      // ret 
    /*  12c4 */  s0 = ra;                                 // mv s0, ra
    /*  12c8 */  t0 = 0x12c8 + 0;                         // auipc t0, 0
    /*  12cc */  t0 = t0 + 0x20;                          // addi t0, t0, 0x20
    /*  12d0 */  pc = t0; ra = 0x12d4; // Return or Indirect Call // jalr t0
    /*  12d4 */  t3 = 0x12d4 + 0;                         // auipc t3, 0
    /*  12d8 */  t1 = zero + 8;                           // addi t1, zero, 8

LOC_12dc:
    /*  12dc */  if ((int32_t)t2 != (int32_t)t1) goto LOC_14; // bne t2, t1, 0x14
    /*  12e0 */  if ((int32_t)ra != (int32_t)t3) goto LOC_10; // bne ra, t3, 0x10
    /*  12e4 */  goto LOC_28;                             // j 0x28
    /*  12e8 */  t2 = zero + 8;                           // addi t2, zero, 8
    /*  12ec */  goto *ra; // Return                      // ret 
    /*  12f0 */  t0 = 0x12f0 + 0xff;                      // auipc t0, 0xff
    /*  12f4 */  t0 = t0 + -0x2ec;                        // addi t0, t0, -0x2ec
    /*  12f8 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  12fc */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  1300 */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  1304 */  ra = s0;                                 // mv ra, s0
    /*  1308 */  goto *ra; // Return                      // ret 
    /*  130c */  t0 = 0x130c + 0xff;                      // auipc t0, 0xff
    /*  1310 */  t0 = t0 + -0x30c;                        // addi t0, t0, -0x30c
    /*  1314 */  t1 = *(int32_t*)(t0 + 0);                // lw t1, 0(t0)
    /*  1318 */  t1 = t1 + 1;                             // addi t1, t1, 1
    /*  131c */  *(uint32_t*)(t0 + 0) = t1;               // sw t1, 0(t0)
    /*  1320 */  ra = s0;                                 // mv ra, s0
    /*  1324 */  goto *ra; // Return                      // ret 
    /*  1328 */  // Unhandled: bltz a0, 0x60              // bltz a0, 0x60
    /*  132c */  // Unhandled: bltz a1, 0x6c              // bltz a1, 0x6c

LOC_1330:
    /*  1330 */  a2 = a1;                                 // mv a2, a1
    /*  1334 */  a1 = a0;                                 // mv a1, a0
    /*  1338 */  a0 = zero + -1;                          // addi a0, zero, -1
    /*  133c */  if (a2 == 0) goto LOC_38;                // beqz a2, 0x38
    /*  1340 */  a3 = zero + 1;                           // addi a3, zero, 1
    /*  1344 */  if ((uint32_t)a2 >= (uint32_t)a1) goto LOC_14; // bgeu a2, a1, 0x14

LOC_1348:
    /*  1348 */  // Unhandled: blez a2, 0x10              // blez a2, 0x10
    /*  134c */  a2 = a2 << 1;                            // slli a2, a2, 1
    /*  1350 */  a3 = a3 << 1;                            // slli a3, a3, 1
    /*  1354 */  if ((uint32_t)a2 < (uint32_t)a1) goto LOC_1348; // bltu a2, a1, -0xc
    /*  1358 */  a0 = zero;                               // mv a0, zero

LOC_135c:
    /*  135c */  if ((uint32_t)a1 < (uint32_t)a2) goto LOC_c; // bltu a1, a2, 0xc
    /*  1360 */  a1 = a1 - a2;                            // sub a1, a1, a2
    /*  1364 */  a0 = a0 | a3;                            // or a0, a0, a3
    /*  1368 */  a3 = (uint32_t)a3 >> 1;                  // srli a3, a3, 1
    /*  136c */  a2 = (uint32_t)a2 >> 1;                  // srli a2, a2, 1
    /*  1370 */  if (a3 != 0) goto LOC_135c;              // bnez a3, -0x14
    /*  1374 */  goto *ra; // Return                      // ret 
    /*  1378 */  t0 = ra;                                 // mv t0, ra
    /*  137c */  ra = 0x1380; goto LOC_1330; // Call      // jal -0x4c
    /*  1380 */  a0 = a1;                                 // mv a0, a1
    /*  1384 */  // Unhandled: jr t0                      // jr t0
    /*  1388 */  a0 = -a0;                                // neg a0, a0
    /*  138c */  // Unhandled: bgtz a1, 0x10              // bgtz a1, 0x10
    /*  1390 */  a1 = -a1;                                // neg a1, a1
    /*  1394 */  goto LOC_1330;                           // j -0x64
    /*  1398 */  a1 = -a1;                                // neg a1, a1
    /*  139c */  t0 = ra;                                 // mv t0, ra
    /*  13a0 */  ra = 0x13a4; goto LOC_1330; // Call      // jal -0x70
    /*  13a4 */  a0 = -a0;                                // neg a0, a0
    /*  13a8 */  // Unhandled: jr t0                      // jr t0
    /*  13ac */  t0 = ra;                                 // mv t0, ra
    /*  13b0 */  // Unhandled: bltz a1, 0x14              // bltz a1, 0x14
    /*  13b4 */  // Unhandled: bltz a0, 0x18              // bltz a0, 0x18

LOC_13b8:
    /*  13b8 */  ra = 0x13bc; goto LOC_1330; // Call      // jal -0x88
    /*  13bc */  a0 = a1;                                 // mv a0, a1
    /*  13c0 */  // Unhandled: jr t0                      // jr t0
    /*  13c4 */  a1 = -a1;                                // neg a1, a1
    /*  13c8 */  // Unhandled: bgez a0, -0x10             // bgez a0, -0x10
    /*  13cc */  a0 = -a0;                                // neg a0, a0
    /*  13d0 */  ra = 0x13d4; goto LOC_1330; // Call      // jal -0xa0
    /*  13d4 */  a0 = -a1;                                // neg a0, a1
    /*  13d8 */  // Unhandled: jr t0                      // jr t0
}
