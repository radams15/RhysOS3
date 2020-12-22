#include <x86/serial.h>

void serial_init(){
    outb(SERIAL_PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(SERIAL_PORT + 0, 0x03);    // Set divisor to 3 (low byte) 38400 baud
    outb(SERIAL_PORT + 1, 0x00);    //                  (high byte)
    outb(SERIAL_PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(SERIAL_PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold

    serial_write("Serial Initialised!\n");
}

bool serial_send_buf_empty(){
    return inb(SERIAL_PORT + 5) & 0x20;
}

void serial_writec(unsigned char c){
    while(! serial_send_buf_empty()){
        // wait for serial buffer to empty
    }

    outb(SERIAL_PORT, c);
}

void serial_writei(uint32 num){
    uint32 num_temp = num;
    uint32 size = 0;
    uint32 power;

    while(TRUE) {
        num_temp = num_temp / 10;
        size++;
        if (num_temp == 0) {
            break;
        }
    }

    power = pow(10, size - 1);

    uint32 p, i;

    while(TRUE){
        p = num % power;

        if(power > 10) {
            i = p / (power / 10);
            serial_writec(chr(i));
        }else {
            serial_writec(chr(p));
            break;
        }

        power /= 10;

        if(power == 0){
            break;
        }
    }
}

void serial_write(const char* text, ...){

    bool skip_next = FALSE;

    va_list args;

    va_start(args, NULL);
    for (int i=0; text[i] != NULL; i++){
        if(skip_next){
            skip_next = FALSE;
            continue;
        }

        if(text[i] == '%'){
            char formatter = text[i+1];

            switch(formatter){
                case 'd':
                    serial_writei(va_arg(args, uint32));
                    break;
                    
                    
                case 'x':
                    serial_write(""); // must be expression before assignment
                    char buf[32];
                    hex_str(va_arg(args, uint32), buf);
                    serial_write(buf);
                    break;

                default:
                    break;
            }

            skip_next = TRUE;

        }else{
            serial_writec(text[i]);
        }
    }

    va_end(args);
}
