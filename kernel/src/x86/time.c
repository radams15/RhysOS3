//
// Created by rhys on 24/12/2020.
//

#include <time.h>

struct tm time_get(){
    uint8 second;
    uint8 minute;
    uint8 hour;
    uint8 day;
    uint8 month;
    uint16 year;
    uint8 century;
    uint8 registerB;

    while (CMOS_updating()); // Make sure an update isn't in progress
    second = CMOS_read(0x00);
    minute = CMOS_read(0x02);
    hour = CMOS_read(0x04);
    day = CMOS_read(0x07);
    month = CMOS_read(0x08);
    year = CMOS_read(0x09);
    century = CMOS_read(0x00);

    registerB = CMOS_read(0x0B);

    if (!(registerB & 0x04)) { // Convert BCD to binary values if necessary
        second = (second & 0x0F) + ((second / 16) * 10);
        minute = (minute & 0x0F) + ((minute / 16) * 10);
        hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
        day = (day & 0x0F) + ((day / 16) * 10);
        month = (month & 0x0F) + ((month / 16) * 10);
        year = (year & 0x0F) + ((year / 16) * 10);
        century = (century & 0x0F) + ((century / 16) * 10);
    }

    if (!(registerB & 0x02) && (hour & 0x80)) { // Convert 12 hour clock to 24 hour clock if necessary
        hour = ((hour & 0x7F) + 12) % 24;
    }

    year += 2000;

    struct tm out = {
            second,
            minute,
            hour,
            day,
            month,
            year
    };

    return out;
}