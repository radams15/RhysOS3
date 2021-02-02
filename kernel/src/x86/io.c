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


uint16 inw(uint16 port){
    uint16 out;

    asm volatile(
    "in %%dx, %%ax"
    : "=a"(out)
    : "d"(port)
    );

    return out;
}


void outl(uint16 port, int32 val){
    asm volatile(
    "outl %%eax,%%dx" : : "a"(val), "d"(port)
    );
}

uint32 inl(uint16 port){
    uint16 out;

    asm volatile(
    "inl %%dx,%%eax"
    : "=a"(out)
    : "d"(port)
    );

    return out;
}

void halt(){
    TTY_print("\nSystem Has Halted\n\n");
    asm("hlt");
}