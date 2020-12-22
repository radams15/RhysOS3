#ifndef TTY_H_INCLUDED
#define TTY_H_INCLUDED

#include <Types.h>

#include "string.h"
#include "VGA.h"

void TTY_init(int fg, int bg);
void TTY_set_colour(int fg, int bg);

void TTY_charat(char c, uint8 colour, int x, int y);

void TTY_putc(char c);
void TTY_print(const char* c);

#endif // TTY_H_INCLUDED
