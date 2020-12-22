
#include <VBE.h>

VBE_Screen* VBE_active = NULL;

VBE_Screen* VBE_init(uint32* fb_addr, uint32 width, uint32 height, uint8 colour_depth){
    VBE_Screen* out = kmalloc(sizeof(VBE_Screen));
    
    out->fb_addr = fb_addr;
    out->width = width;
    out->height = height;
    out->colour_depth = colour_depth;
    
    VBE_active = out;
    
    serial_write("Initilised screen at addr: %x (%d x %d)\n", VBE_active->fb_addr, VBE_active->width, VBE_active->height);
    
    VBE_set_bg(0xFFFFFF);
    
    
    return out;
}

void VBE_pix(uint32 x, uint32 y, uint32 colour){
    if(VBE_active != NULL){
        VBE_active->fb_addr[(y*VBE_active->width)+x] = colour;
    }else{
        serial_write("Pix FAIL!\n");
    }
}

void VBE_rect(uint32 x, uint32 y, uint32 w, uint32 h, uint32 colour){
	for(uint32 ly = y ; ly<h+y ; ly++){
		for (uint32 lx = x ; lx<w+x ; lx++){
            VBE_pix(lx, ly, colour);
        }
    }
}

void VBE_set_bg(uint32 colour){
        VBE_rect(0, 0, VBE_active->width, VBE_active->height, colour);
}
