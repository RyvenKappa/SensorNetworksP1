#include "mbed.h"
#include "temp_hum.h"
#include "../i2c/i2c_interface.h"
#include "../shared_data/shared_data.h"
#include <cstdint>
#include <stdint.h>

static char cmd;
static char buff[2];

/**
* Reading function with conversion
*/
static void converted_reading(){
    cmd = TH_SENSOR_MEASUREH_MASTER;
    i2c_bus.write(TH_SENSOR_SLAVE_ADDRESS<<1,&cmd,1,true);
    //Humidity
    i2c_bus.read(TH_SENSOR_SLAVE_ADDRESS<<1,buff,2);
    //conversion
    i2c_mutex.lock();
    i2c_data.hum = ((125.0*(buff[0]<<8 | buff[1]))/65536.0)-6;
    i2c_mutex.unlock();


    //Obtain last temperature measurement
    cmd = TH_SENSOR_MEASURET_PREVIOUS;
    i2c_bus.write(TH_SENSOR_SLAVE_ADDRESS<<1,&cmd,1);
    i2c_bus.read(TH_SENSOR_SLAVE_ADDRESS<<1,buff,2);
    //Conversion
    i2c_mutex.lock();
    i2c_data.temp = (175.72*(buff[0]<<8 | buff[1])/65536.0)-46.85;
    i2c_mutex.unlock();
}

/**
* Static function for the thread loop
*/
void temp_hum_sensor_read(){
    converted_reading();
}
