asm(".asciz \"kernel start\\n\"");

#include "console.h"
#include "cpu/isr.h"
#include "cpu/gdt.h"
#include "drivers/keyboard.h"
#include "drivers/vga.h"
#include "drivers/ata.h"
#include "drivers/misc.h"
#include "drivers/sound.h"
#include "drivers/uart.h"
#include "drivers/PIT.h"
#include "fs/fs.h"
#include "lib/string.h"
#include "proc.h"



void _start() {
    load_gdt();
    init_keyboard();
    init_pit();
    uartinit();
    load_idt();
    sti();

    vga_clear_screen();
    printk("YABLOKO\n");

    printk("\n> ");

    grasshopper();
    qemu_shutdown();
}
