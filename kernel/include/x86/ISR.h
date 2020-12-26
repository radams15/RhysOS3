//
// Created by rhys on 31/10/2020.
//

#ifndef RHYSOS_ISR_H
#define RHYSOS_ISR_H

#include <x86/TTY.h>
#include <x86/registers.h>
#include <x86/serial.h>
#include <x86/io.h>

void ISR_handle(registers regs);


#endif //RHYSOS_ISR_H
