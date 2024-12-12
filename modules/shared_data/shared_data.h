#ifndef SHARED_DATA_H
#define SHARED_DATA_H
#include "mbed.h"

/**
* 
* TODO comentarlo
*
*/
typedef struct{
    uint8_t sats;
    uint8_t time_h;
    uint8_t time_m;
    uint8_t time_s;
    uint8_t time_day;
    uint8_t time_month;
    uint16_t time_year;
    uint16_t altitude;
    char altitude_c;
    char lat_n;
    char lng_w;
    float lat;
    float lng;
}gps_data_t;

extern gps_data_t gps_data;

extern Mutex gps_mutex;
#endif


