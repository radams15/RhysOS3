
#include <VBE.h>

VBE_Screen* VBE_active = NULL;

void VBE_init(uint32* fb_addr, uint32 width, uint32 height, uint8 colour_depth){
    VBE_active = kmalloc(sizeof(VBE_Screen));

    VBE_active->fb_addr = fb_addr;
    VBE_active->width = width;
    VBE_active->height = height;
    VBE_active->colour_depth = colour_depth;

    serial_write("Initilised screen at addr: %x (%d x %d)\n", VBE_active->fb_addr, VBE_active->width, VBE_active->height);
    
    VBE_set_bg(0xFFFFFF);
}

void VBE_pix(uint32 x, uint32 y, uint32 colour){
    if(VBE_active != NULL){
        VBE_active->fb_addr[(y*VBE_active->width)+x] = colour;
    }else{
        serial_write("Pix FAIL!\n");
    }
}

void VBE_hline(uint32 x, uint32 y, uint32 w, uint32 colour){
    for(uint32 lx=x ; lx<x+w ; lx++){
        VBE_pix(lx, y, colour);
    }
}

void VBE_vline(uint32 x, uint32 y, uint32 h, uint32 colour){
    for(uint32 ly=y ; ly<x+h ; ly++){
        VBE_pix(x, ly, colour);
    }
}

void VBE_rect(uint32 x, uint32 y, uint32 w, uint32 h, uint32 colour){

	for(uint32 ly = y ; ly<h+y ; ly++){
        for(uint32 lx = x ; lx<x+w ; lx++){
            VBE_pix(lx, ly, colour);
        }
	}

}

void VBE_set_bg(uint32 colour){
        VBE_rect(0, 0, VBE_active->width, VBE_active->height, colour);
}