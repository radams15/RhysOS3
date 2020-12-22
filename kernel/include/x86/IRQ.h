//
// Created by rhys on 31/10/2020.
//

#ifndef RHYSOS_IRQ_H
#define RHYSOS_IRQ_H

#include <x86/io.h>
#include <x86/registers.h>
#include <x86/IDT.h>
#include <x86/TTY.h>
#include <x86/serial.h>

enum irq_codes {
    IRQ0 = 32,
    IRQ1 = 33,
    IRQ2 = 34,
    IRQ3 = 35,
    IRQ4 = 36,
    IRQ5 = 37,
    IRQ6 = 38,
    IRQ7 = 39,
    IRQ8 = 40,
    IRQ9 = 41,
    IRQ10 = 42,
    IRQ11 = 43,
    IRQ12 = 44,
    IRQ13 = 45,
    IRQ14 = 46,
    IRQ15 = 47
};

typedef void (*irq_callback)(registers);

void enable();
void disable();

void init();

extern void handle_irq(registers regs);

void add_handler(uint8 n, irq_callback handler);

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif //RHYSOS_IRQ_H
