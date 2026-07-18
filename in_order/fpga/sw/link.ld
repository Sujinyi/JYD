OUTPUT_ARCH("riscv")
ENTRY(_start)

SECTIONS
{
  . = 0x80000000;
  .text : {
    *(.text.init)
    *(.text)
    *(.text.*)
  }
  . = ALIGN(0x100);
  .tohost : {
    . = ALIGN(64); tohost = .;   LONG(0); LONG(0);
    . = ALIGN(64); fromhost = .; LONG(0); LONG(0);
    . = ALIGN(64); putchar_mmio = .; LONG(0);
  }
  . = ALIGN(0x100);
  .data : {
    *(.data) *(.data.*)
    *(.rodata) *(.rodata.*)
    *(.sdata) *(.sdata.*) *(.srodata*)
  }
  . = ALIGN(4);
  .bss : {
    __bss_start = .;
    *(.bss) *(.bss.*) *(.sbss) *(.sbss.*) *(COMMON)
    . = ALIGN(4);
    __bss_end = .;
  }
  _end = .;
  __stack_top = 0x80010000 - 16;   /* 64KB RAM */
}
