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

/**
* 
* TODO comentarlo
*
*/
typedef struct{
    float x_acc;
    float y_acc;
    float z_acc;
    float temp;
    float hum;
    uint16_t clear;
    uint16_t red;
    uint16_t green;
    uint16_t blue;
}i2c_data_t;

extern i2c_data_t i2c_data;

extern Mutex i2c_mutex;
#endif


