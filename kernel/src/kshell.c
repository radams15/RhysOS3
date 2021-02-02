#include <kshell.h>

#include <x86/registers.h>
#include <keyboard.h>
#include <x86/TTY.h>

#include <keymap.h>
#include <memory.h>

#define KSH_BUF 1024

char kshell_buf[KSH_BUF];
uint32 kshell_buf_pos = 0;

char kshell_prompt[32] = "=> ";

int kshell_exec(const char* prog, const char** args){
    return 1;
}

const char** kshell_split(const char* input, int* len){
    int input_len = strlen(input);

    const char* command = kcalloc(input_len+1, sizeof(char));
    strcpy(command, input);


    (*len) = 1;
    for(int i=0 ; i<input_len ; i++){
        if(command[i] == ' '){
            (*len)++;
        }
    }

    const char* tok = strtok(command, " ");

    for(int i=0 ; i<(*len) ; i++){ // 2d arrays don't work because of my memory management
        TTY_print("\tTOK (%d): %s\n", i, tok);

        tok = strtok(NULL, " ");
    }

    kfree(command);

    return NULL;
}

void kshell_command(const char* command, uint32 size){
    int argc;
    const char** argv = kshell_split(command, &argc);

    if(argc == 0){
        TTY_print("\n");
    }else if(strcmp(argv[0], "echo") == 0){
        TTY_print("%s\n", command+strlen(argv[0])+1);
    }else if(strcmp(argv[0], "clear") == 0){
        TTY_clear();
    }else if(strcmp(argv[0], "halt") == 0){
        halt();
    }else{
        TTY_print("Error! Unknown command \"%s\"\n", argv[0]);
    }
}

char kshell_translate(uint32 code_in){
    uint32 code;
    uint8 chr;
    for(int i=0; keymap[i][0] != 0 ; i++){
        code = keymap[i][0];
        chr = keymap[i][1];

        if(code == code_in){
            return chr;
        }
    }

    return NULL;
}

void kshell_callback(uint32 code){
    if(kshell_buf_pos == KSH_BUF-1){
        return;
    }

    char c = kshell_translate(code);

    if(c == NULL){
        return;
    }if(c == '\n') {
        TTY_print("\n");

        char* to_give = kcalloc(kshell_buf_pos+1, sizeof(char));
        strcpy(to_give, kshell_buf);

        kshell_command(to_give, kshell_buf_pos+1);

        bzero(kshell_buf, KSH_BUF);
        kshell_buf_pos = 0;
        TTY_print("%s", kshell_prompt);

    }else{
        kshell_buf[kshell_buf_pos] = kshell_translate(code);

        TTY_print("%c", kshell_buf[kshell_buf_pos]);

        kshell_buf_pos++;
    }
}

void kshell_run(){
    keyboard_register(kshell_callback);
    TTY_print("\n%s", kshell_prompt);
}