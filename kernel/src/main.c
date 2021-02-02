#include <x86/TTY.h>
#include <x86/serial.h>

#include <x86/GDT.h>
#include <x86/IRQ.h>

#include <VBE.h>

#include <drivers/ata/ata.h>

#include <x86/multiboot.h>
#include <string.h>

#include <keyboard.h>
#include <kshell.h>

void early_init(multiboot_info* mb_info){
    serial_init();
    TTY_init(VGA_COLOUR_BLACK, VGA_COLOUR_WHITE);

    GDT_init();
    IDT_init();
    IRQ_init();

    keyboard_init();

    IRQ_enable();

    //VBE_init(mb_info->framebuffer_addr, 1024, 768, 8);
}

bool loop(){
    return TRUE;
}

int kmain(multiboot_info* mb_info){
    early_init(mb_info);

    serial_write("Boot Complete\n");

    TTY_print("Boot Complete!\n");

    uint16* data = ATA_PIO_read_sect(0x0, 1);
    for(int i=0 ; i<ATA_CHUNK ; i++){
        if(data[i] == 0) break;

        TTY_print("%c%c", data[i]&0xFF, (data[i]>>8)&0xFF);
    }

    kfree(data);

    kshell_run();


    while(loop());

    halt();
    return 0;
}
