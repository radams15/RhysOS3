#include <keyboard.h>

#include <x86/ISR.h>
#include <x86/TTY.h>
#include <x86/IRQ.h>

keyboard_t keyboard_callback = NULL;

void key_pressed(registers r){
    uint32 code = inb(0x60);

    if(keyboard_callback != NULL) {
        keyboard_callback(code);
    }

    outb(0x20, 0x20);
}

void keyboard_init(){
    IRQ_add_handler(IRQ1, key_pressed);
}

void keyboard_register(keyboard_t callback){
    keyboard_callback = callback;
    serial_write("Added keyboard handler\n");
}