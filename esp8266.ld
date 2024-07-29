ENTRY(__boot_startup)

MEMORY
{
    iram : ORIGIN = 0x40100000, LENGTH = 0x08000
    dram : ORIGIN = 0x3ffe8000, LENGTH = 0x14000
}

SECTIONS
{
    .text :
    {
        *(.vectors*)
        *(.boot.startup)
        *(.boot)
        . = ALIGN(4);
        *(.text*)
        __etext = .;
    } > iram

    .data :
    {
        *(.data*)
    } > dram

    .bss :
    {
        __sbss = .;
        *(.bss)
        *(COMMON)
        __ebss = .;
    } > dram

    .rodata :
    {
        *(.rodata*)
    } > dram
}

