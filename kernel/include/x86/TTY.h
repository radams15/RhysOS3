#ifndef TTY_H_INCLUDED
#define TTY_H_INCLUDED

#include <Types.h>
#include <stdarg.h>

#include "string.h"
#include "VGA.h"
#include "math.h"

#define FORMAT_MARK '%'

void TTY_init(int fg, int bg);
void TTY_set_colour(int fg, int bg);

void TTY_charat(char c, uint8 colour, int x, int y);

void TTY_putc(char c);
void TTY_puti(int num);

void TTY_print(const char* text, ...);
void TTY_print_args(const char* text, va_list args);

#endif // TTY_H_INCLUDED
