#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include "Types.h"

void outb(uint16 port, int8 val);
uint8 inb(uint16 port);

void halt();

#endif // IO_H_INCLUDED
