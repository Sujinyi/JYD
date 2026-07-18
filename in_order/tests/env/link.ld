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
  .tohost : { *(.tohost) }
  . = ALIGN(0x100);
  .data : {
    *(.data)
    *(.data.*)
    *(.rodata)
    *(.rodata.*)
    *(.sdata)
    *(.sdata.*)
  }
  .bss : {
    *(.bss)
    *(.sbss)
  }
  _end = .;
}
