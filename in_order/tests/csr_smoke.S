# CSR/trap smoke test mirroring the withM48 competition sequence:
# csrw/csrr on mtvec/mepc/mcause/mscratch, ecall -> handler -> mret,
# ebreak, csrrs/csrrc/csrrwi/csrrsi/csrrci forms.
#include "riscv_test.h"

RVTEST_RV32U
RVTEST_CODE_BEGIN

        # ---- install trap handler ----
        la      t0, trap_handler
        csrw    mtvec, t0
        csrr    t1, mtvec
        li      TESTNUM, 2
        bne     t0, t1, fail

        # ---- ecall #1: handler bumps s1, returns to pc+4 ----
        li      s1, 0
        li      s2, 0
        ecall
        li      TESTNUM, 3
        li      t2, 1
        bne     s1, t2, fail            # handler ran once
        li      t2, 11
        bne     s2, t2, fail            # mcause == 11 (ecall M)

        # ---- ecall #2 ----
        ecall
second_ecall_ret:                       # = ecall pc + 4 (handler's mepc value)
        li      TESTNUM, 4
        li      t2, 2
        bne     s1, t2, fail

        # ---- mepc readback: handler wrote mepc = ecall_pc + 4 ----
        la      t3, second_ecall_ret
        csrr    t4, mepc
        li      TESTNUM, 5
        bne     t3, t4, fail

        # ---- ebreak: mcause == 3 ----
        ebreak
        li      TESTNUM, 6
        li      t2, 3
        bne     s2, t2, fail

        # ---- mscratch rw ----
        li      t0, 0xdeadbeef
        csrw    mscratch, t0
        csrr    t1, mscratch
        li      TESTNUM, 7
        bne     t0, t1, fail

        # ---- csrrs / csrrc ----
        li      t0, 0xf0f0f0f0
        csrw    mscratch, t0
        li      t1, 0x0f0f0f0f
        csrrs   t2, mscratch, t1        # t2 = old, mscratch |= t1
        li      TESTNUM, 8
        bne     t2, t0, fail
        csrr    t3, mscratch
        li      t4, 0xffffffff
        bne     t3, t4, fail
        li      t1, 0x000000ff
        csrrc   t2, mscratch, t1        # mscratch &= ~t1
        csrr    t3, mscratch
        li      t4, 0xffffff00
        li      TESTNUM, 9
        bne     t3, t4, fail

        # ---- immediate forms ----
        csrwi   mscratch, 21
        csrr    t0, mscratch
        li      TESTNUM, 10
        li      t1, 21
        bne     t0, t1, fail
        csrrsi  t2, mscratch, 10        # 21|10 = 31
        csrr    t0, mscratch
        li      t1, 31
        bne     t0, t1, fail
        csrrci  t2, mscratch, 3         # 31&~3 = 28
        csrr    t0, mscratch
        li      t1, 28
        li      TESTNUM, 11
        bne     t0, t1, fail

        # ---- csrrs x0 (pure read, no write) ----
        csrrs   t0, mscratch, x0
        li      t1, 28
        li      TESTNUM, 12
        bne     t0, t1, fail

        # ---- direct mepc/mcause csrw + mret round trip ----
        la      t0, mret_target
        csrw    mepc, t0
        mret
        li      TESTNUM, 13
        j       fail                    # mret must not fall through
mret_target:
        li      TESTNUM, 14
        csrr    t0, mcause              # still 3 from the ebreak trap
        li      t1, 3
        bne     t0, t1, fail

        RVTEST_PASS

fail:
        RVTEST_FAIL

        # trap handler: s1++, s2 = mcause, mepc += 4, mret
trap_handler:
        addi    s1, s1, 1
        csrr    s2, mcause
        csrr    t5, mepc
        addi    t5, t5, 4
        csrw    mepc, t5
        mret

RVTEST_CODE_END

RVTEST_DATA_BEGIN
RVTEST_DATA_END
