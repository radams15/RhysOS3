#include <x86/TTY.h>
#include <x86/serial.h>

#include <x86/GDT.h>
#include <x86/ISR.h>
#include <x86/IRQ.h>

#include <x86/multiboot.h>

void key(registers r){
    uint32 code = inb(0x60);

    TTY_print("KEY\n");

    outb(0x20, 0x20);
}

void early_init(multiboot_info* mb_info){
    serial_init();
    TTY_init(VGA_COLOUR_BLACK, VGA_COLOUR_WHITE);

    GDT_init();
    IDT_init();
    IRQ_init();

    IRQ_add_handler(IRQ1, key);

    IRQ_enable();
}

bool loop(){
    return TRUE;
}

int kmain(multiboot_info* mb_info){
    early_init(mb_info);

    serial_write("Boot Complete\n");
    TTY_print("Boot Complete!\n");

    asm volatile("int $49");

    while(loop());

    halt();
    return 0;
}
