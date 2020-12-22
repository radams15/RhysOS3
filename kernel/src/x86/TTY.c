
#include <x86/TTY.h>

uint8 TTY_colour;

uint16 TTY_col;
uint16 TTY_row;
uint16* TTY_buf;

void TTY_init(int fg, int bg){
    TTY_row = 0;
    TTY_col = 0;
    
    TTY_set_colour(fg, bg);
    
    TTY_buf = (uint16*) VGA_MEM_START;
    
    for(int y=0 ; y<VGA_HEIGHT ; y++){
        for(int x=0 ; x<VGA_WIDTH ; x++){
            TTY_charat(' ', TTY_colour, x, y);
        }
    }
}

void TTY_set_colour(int fg, int bg){
    TTY_colour = VGA_colour(fg, bg);
}

void TTY_charat(char c, uint8 colour, int x, int y){
    uint16 index = y * VGA_WIDTH + x;
    TTY_buf[index] = VGA_chr(c, colour);
}

void TTY_putc(char c) {
    switch(c){
        case '\n':
            TTY_row++;
            TTY_col = 0;
            break;
        
        default:
            TTY_charat(c, TTY_colour, TTY_col, TTY_row);
            TTY_col++;
            break;
    }
    if (TTY_row >= VGA_WIDTH-1) {
        TTY_putc('\n');
    }
}

void TTY_print(const char* c){
    for(uint32 i=0 ; i<strlen(c) ; i++){
        TTY_putc(c[i]);
    }
}
