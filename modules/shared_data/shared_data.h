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
    uint8_t     header;    //1 version and type and GPS connection
    float       latitude;  //4
    float       longitude; //4
    uint16_t    altitude;  //2
    int8_t     x_acc;      //2
    int8_t     y_acc;      //2
    int8_t     z_acc;      //2
    int16_t     temp;       //2
    int16_t     hum;        //2
    uint16_t    clear;      //2
    uint16_t    red;        //2
    uint16_t    green;      //2
    uint16_t    blue;       //2
    uint16_t    light;      //2
    uint16_t    moisture;   //2
} frame_data_t;

extern frame_data_t frame_data;

extern Mutex frame_data_mutex;

#endif


