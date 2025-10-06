MEMORY
{
    IRAM (rx) : ORIGIN = 0x40381000, LENGTH = 0x020000
    DRAM (rw) : ORIGIN = 0x3FC8A800, LENGTH = 0x010000
}

SECTIONS
{
    .iram0.text :
    {
        *(.text*)
    } > IRAM

    .iram0.rodata :
    {
        *(.rodata*)
    } > IRAM

    .dram0.data :
    {
        *(.data*)
    } > DRAM

    .dram0.bss :
    {
        *(.bss*)
    } > DRAM
}
