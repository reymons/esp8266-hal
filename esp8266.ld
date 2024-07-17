ENTRY(__boot)

MEMORY
{
    flash : ORIGIN = 0x40100000, LENGTH = 0x1000
    sram : ORIGIN = 0x3ffe8000, LENGTH = 0x1000
}

SECTIONS
{
    .boot : { *(.boot*) } > flash
    
    .literal : { *(.literal*) } > flash
    
    .text :
    {
        *(.text*)
    } > flash

    .rodata :
    {
        *(.rodata*)
    } > sram

    .data :
    {
        *(.data*)
    } > sram

    .bss :
    {
        *(.bss*)
    } > sram
}

