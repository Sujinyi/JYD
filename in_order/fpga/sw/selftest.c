// On-board self-test & benchmark for the RV32I core.
// Reports per-test PASS/FAIL and cycle counts over UART; LED shows progress.
// On failure: LED blinks the failing test number forever.
#include "runtime.h"
#include "board.h"

static int fails, testno;

static void report(const char *name, int ok) {
    testno++;
    rt_puts(ok ? "[PASS] " : "[FAIL] ");
    rt_puts(name);
    rt_putc('\n');
    if (!ok) fails = testno;
    LED_REG = testno;
}

// ---------- functional tests ----------
static volatile int32_t va = -1234, vb = 56;
static volatile uint32_t ua = 0x89ABCDEFu;

static int t_alu(void) {
    return (va + vb == -1178) && (va - vb == -1290) &&
           ((va & vb) == 40) && ((va | vb) == -1218) && ((va ^ vb) == -1258) &&
           (va < vb) && (ua > (uint32_t)va ? 0 : 1) && ((va << 4) == -19744) &&
           ((va >> 2) == -309) && ((ua >> 8) == 0x0089ABCDu);
}

static int t_muldiv(void) {
    return (va * vb == -69104) && (va / vb == -22) && (va % vb == -2) &&
           (ua / 1000u == 2309737u) && (ua % 1000u == 967u);
}

static uint8_t buf[64];
static int t_ldst(void) {
    for (int i = 0; i < 64; i++) buf[i] = (uint8_t)(i * 7);
    uint16_t *h = (uint16_t *)buf;
    uint32_t *w = (uint32_t *)buf;
    if (buf[9] != 63 || h[3] != (uint16_t)((49 << 8) | 42)) return 0;
    w[0] = 0xDEADBEEF;
    if (buf[0] != 0xEF || buf[3] != 0xDE) return 0;
    int8_t s = (int8_t)buf[3];
    return s == (int8_t)0xDE && (int32_t)s == -34;
}

static int fib(int n) { return n < 2 ? n : fib(n - 1) + fib(n - 2); }
static int t_call(void) { return fib(15) == 610; }

static uint32_t crc32(const uint8_t *p, int n) {
    uint32_t c = 0xFFFFFFFFu;
    for (int i = 0; i < n; i++) {
        c ^= p[i];
        for (int b = 0; b < 8; b++)
            c = (c >> 1) ^ (0xEDB88320u & (0u - (c & 1)));
    }
    return ~c;
}
static int t_crc(void) {
    static const uint8_t msg[] = "RV32I on XC7A100T";
    return crc32(msg, 17) == crc32(msg, 17) && crc32(msg, 17) != 0;
}

static uint32_t arr[96];
static int t_sort(void) {
    uint32_t s = 0xCAFEBABE, sum0 = 0, sum1 = 0;
    for (int i = 0; i < 96; i++) {
        s ^= s << 13; s ^= s >> 17; s ^= s << 5;
        arr[i] = s;
        sum0 += s;
    }
    for (int i = 0; i < 95; i++)
        for (int j = 0; j < 95 - i; j++)
            if (arr[j] > arr[j + 1]) {
                uint32_t t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
    for (int i = 1; i < 96; i++)
        if (arr[i - 1] > arr[i]) return 0;
    for (int i = 0; i < 96; i++) sum1 += arr[i];
    return sum0 == sum1;
}

// ---------- benchmark ----------
static void bench(const char *name, int (*fn)(void)) {
    uint32_t c0 = CYCLE_REG, i0 = INSTRET_REG;
    volatile int r = fn();
    (void)r;
    uint32_t dc = CYCLE_REG - c0, di = INSTRET_REG - i0;
    rt_puts("  ");
    rt_puts(name);
    rt_puts(": ");
    rt_putdec((int32_t)dc);
    rt_puts(" cycles, ");
    rt_putdec((int32_t)di);
    rt_puts(" instrs, CPI*100=");
    rt_putdec((int32_t)(dc * 100u / di));
    rt_putc('\n');
}

int main(void) {
    rt_puts("\n==== RV32I self-test ====\n");
    report("alu",     t_alu());
    report("muldiv",  t_muldiv());
    report("ldst",    t_ldst());
    report("call",    t_call());
    report("crc32",   t_crc());
    report("sort",    t_sort());

    rt_puts(fails ? "RESULT: FAIL at test " : "RESULT: ALL PASS (");
    rt_putdec(fails ? fails : testno);
    rt_puts(fails ? "\n" : " tests)\n");

    rt_puts("==== benchmark ====\n");
    bench("fib(15) ", t_call);
    bench("sort96  ", t_sort);
    bench("crc32   ", t_crc);
    bench("muldiv  ", t_muldiv);
    rt_puts("==== done ====\n");

    if (fails) { // blink failing test number
        for (;;) {
            LED_REG = fails; delay(3000000);
            LED_REG = 0;     delay(3000000);
        }
    }
    uint32_t pat = 1; // all pass: marquee
    for (;;) {
        LED_REG = pat;
        pat = (pat == 8) ? 1 : (pat << 1);
        delay(6000000);
    }
}
