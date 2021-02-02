#ifndef RHYSOS_KEYBOARD_H
#define RHYSOS_KEYBOARD_H

#include <x86/registers.h>

typedef void (*keyboard_t)(uint32 code);

void keyboard_init();

void keyboard_register(keyboard_t callback);

#endif //RHYSOS_KEYBOARD_H