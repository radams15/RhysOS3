#include <x86/io.h>

void outb(uint16 port, int8 val){
    asm volatile(
            "outb %0, %1" : : "a"(val), "Nd"(port)
    );
}

uint8 inb(uint16 port){
    uint8 out;

    asm volatile(
              "inb %1, %0"
            : "=a"(out)
            : "Nd"(port)
    );

    return out;
}

void halt(){
    asm("hlt");
}
