#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <Types.h>
#include <x86/TTY.h>

void outb(uint16 port, int8 val);
uint8 inb(uint16 port);

uint16 inw(uint16 port);

void outl(uint16 port, int32 val);
uint32 inl(uint16 port);

void halt();

#endif // IO_H_INCLUDED
