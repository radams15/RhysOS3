//
// Created by rhys on 23/12/2020.
//

#include <CMOS.h>

uint8 CMOS_read(uint8 reg){
    IRQ_disable();
    outb(0x70, reg);

    uint8 out = inb(0x71);
    IRQ_enable();

    return out;
}

bool CMOS_updating(){
    outb(0x70, 0x0A);

    return (inb(0x71) & 0x80);
}