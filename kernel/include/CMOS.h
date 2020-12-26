//
// Created by rhys on 23/12/2020.
//

#ifndef RHYSOS3_CMOS_H
#define RHYSOS3_CMOS_H

#include <Types.h>
#include <x86/io.h>
#include <x86/IRQ.h>

uint8 CMOS_read(uint8 reg);
bool CMOS_updating();

#endif //RHYSOS3_CMOS_H
