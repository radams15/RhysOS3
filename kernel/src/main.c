#include <x86/TTY.h>
#include <x86/serial.h>

#include <x86/GDT.h>
#include <x86/ISR.h>
#include <x86/IRQ.h>

#include <VBE.h>

#include <x86/multiboot.h>

void key(registers r){
    TTY_print("KEY\n");
}

void early_init(multiboot_info* mb_info){
    serial_init();
    TTY_init(VGA_COLOUR_BLACK, VGA_COLOUR_WHITE);
    GDT_init();
    IDT_init();
    IRQ_init();
    
    IRQ_add_handler(IRQ1, key);
    
    //VBE_init((void*) mb_info->framebuffer_addr, mb_info->framebuffer_width, mb_info->framebuffer_height, mb_info->framebuffer_bpp);
    
    serial_write("Boot Complete\n");
    
    TTY_print("Boot Complete!\n");
}

int kmain(multiboot_info* mb_info){
    early_init(mb_info);
    
    return 0;
}
