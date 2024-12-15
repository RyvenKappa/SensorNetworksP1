#ifndef SHARED_DATA_H
#define SHARED_DATA_H
#include "mbed.h"
#include <cstdint>
/**
* 
* TODO comentarlo
*
*/
typedef struct PACKED {
    uint8_t     header;     //1 version and type
    uint8_t     gps_conn;   //1, 0 or N sats
    float       latitude;     //4
    float       longitude;    //4
    uint16_t    altitude;  //2
    int16_t     x_acc;      //2
    int16_t     y_acc;      //2
    int16_t     z_acc;      //2
    int16_t     temp;       //2
    int16_t     hum;        //2
    uint16_t    clear;      //2
    uint16_t    red;        //2
    uint16_t    green;      //2
    uint16_t    blue;       //2
} frame_data_t;

extern frame_data_t frame_data;

extern Mutex frame_data_mutex;

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


