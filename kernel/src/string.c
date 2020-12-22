#include <string.h>

uint32 strlen(const char* c){
    uint32 len = 0;
	while(c[len]){
		len++;
    }
	return len;
}

char chr(uint32 code){
    return code^0b00110000;
}
