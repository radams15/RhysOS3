#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#include <stdarg.h>

#include "Types.h"
#include "io.h"
#include "string.h"
#include "math.h"

enum{
    SERIAL_PORT = 0x3f8
};

void serial_init();

bool serial_send_buf_empty();

void serial_writec(unsigned char a);

void serial_writei(uint32 num);

void serial_write(const char* text, ...);

#endif // SERIAL_H_INCLUDED
