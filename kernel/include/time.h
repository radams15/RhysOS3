//
// Created by rhys on 24/12/2020.
//

#ifndef RHYSOS3_TIME_H
#define RHYSOS3_TIME_H

#include <Types.h>
#include <CMOS.h>

struct tm{
    time_t tm_sec;
    time_t tm_min;
    time_t tm_hour;
    time_t tm_mday;
    time_t tm_mon;
    time_t tm_year;
};

struct tm time_get();

#endif //RHYSOS3_TIME_H
