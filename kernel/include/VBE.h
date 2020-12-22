#ifndef VBE_H_INCLUDED
#define VBE_H_INCLUDED

#include <Types.h>

#include <memory.h>
#include <x86/serial.h>

typedef struct{
    uint32* fb_addr;
    uint32 width;
    uint32 height;
    uint8 colour_depth;
} VBE_Screen;

VBE_Screen* VBE_init(uint32* fb_addr, uint32 width, uint32 height, uint8 colour_depth);

void VBE_pix(uint32 x, uint32 y, uint32 colour);

void VBE_rect(uint32 x, uint32 y, uint32 w, uint32 h, uint32 colour);

void VBE_set_bg(uint32 colour);

#endif // VBE_H_INCLUDED
