//
// Created by rhys on 31/10/2020.
//

#include <x86/ISR.h>

extern void isr_handler(registers regs){
    TTY_print("recieved interrupt: %d\n");
}
