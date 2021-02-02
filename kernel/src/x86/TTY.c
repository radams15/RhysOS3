
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

        case '\t':
            TTY_print("    ");
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

void TTY_puti(int num){
    uint32 power;
    uint32 size = num_size(num);

    power = pow(10, size - 1);

    uint32 p, i;

    while(TRUE){
        p = num % power;

        if(power > 10) {
            i = p / (power / 10);
            TTY_putc(chr(i));
        }else {
            TTY_putc(chr(p));
            break;
        }

        power /= 10;

        if(power == 0){
            break;
        }
    }
}

void TTY_print(const char* text, ...){
    va_list args;

    va_start(args, NULL);

    TTY_print_args(text, args);

    va_end(args);
}


void TTY_print_args(const char* text, va_list args){
    bool skip_next = FALSE;

    for (int i=0; text[i] != NULL; i++){
        if(skip_next){
            skip_next = FALSE;
            continue;
        }

        if(text[i] == FORMAT_MARK){
            char formatter = text[i+1];

            switch(formatter){
                case 'd': // int
                    TTY_puti(va_arg(args, uint32));
                    break;

                case 'c': // char
                    TTY_putc(va_arg(args, uint32));
                    break;

                case 's': // string
                    TTY_print(va_arg(args, char*));
                    break;

                case 'x': // hex int
                    TTY_print("");
                    char buf[32];
                    hex_str(va_arg(args, uint32), buf);
                    TTY_print(buf);
                    break;

                case FORMAT_MARK:
                    TTY_putc(FORMAT_MARK);
                    break;

                default:
                    break;
            }

            skip_next = TRUE;

        }else{
            TTY_putc(text[i]);
        }
    }
}


void TTY_clear(){
    TTY_col = 0;
    TTY_row = 0;
    for(uint32 i=0 ; i<(VGA_HEIGHT*VGA_WIDTH) ; i++){
        TTY_putc(NULL);
    }
    TTY_col = 0;
    TTY_row = 0;
}