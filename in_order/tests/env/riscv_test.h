// Minimal test environment for a simple RV32I core (no traps/CSRs).
// PASS/FAIL are signalled by storing to `tohost`.
#ifndef _ENV_RISCV_TEST_H
#define _ENV_RISCV_TEST_H

#define RVTEST_RV32U
#define RVTEST_RV64U
#define TESTNUM gp

#define RVTEST_CODE_BEGIN \
        .section .text.init; \
        .globl _start; \
_start:

#define RVTEST_CODE_END

#define RVTEST_PASS \
        fence; \
        li TESTNUM, 1; \
        la t5, tohost; \
        li t6, 1; \
        sw t6, 0(t5); \
1:      j 1b;

#define RVTEST_FAIL \
        fence; \
        sll TESTNUM, TESTNUM, 1; \
        or TESTNUM, TESTNUM, 1; \
        la t5, tohost; \
        sw TESTNUM, 0(t5); \
1:      j 1b;

#define RVTEST_DATA_BEGIN \
        .pushsection .tohost,"aw",@progbits; \
        .align 6; .global tohost; tohost: .dword 0; \
        .align 6; .global fromhost; fromhost: .dword 0; \
        .popsection; \
        .align 4; .global begin_signature; begin_signature:

#define RVTEST_DATA_END \
        .align 4; .global end_signature; end_signature:

#endif
