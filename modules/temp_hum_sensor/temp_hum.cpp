#include "mbed.h"
#include "temp_hum.h"
#include "../i2c/i2c_interface.h"
#include "../shared_data/shared_data.h"
#include <cstdint>
#include <stdint.h>

static char cmd;
static char buff[2];

/**
* Static reading function for the values.
*/
static void converted_reading(){
    // Read sensor's humidity
    cmd = TH_SENSOR_MEASUREH_MASTER;
    i2c_bus.write(TH_SENSOR_SLAVE_ADDRESS<<1,&cmd,1,true);
    i2c_bus.read(TH_SENSOR_SLAVE_ADDRESS<<1,buff,2);

    // Perform the conversion of the value and store in the frame data for the next message.
    frame_data_mutex.lock();
    frame_data.hum = (uint16_t)(((125.0*(buff[0]<<8 | buff[1])/65536.0)-6)*10);
    frame_data_mutex.unlock();

    //Obtain last temperature measurement from the sensor
    cmd = TH_SENSOR_MEASURET_PREVIOUS;
    i2c_bus.write(TH_SENSOR_SLAVE_ADDRESS<<1,&cmd,1);
    i2c_bus.read(TH_SENSOR_SLAVE_ADDRESS<<1,buff,2);
    // Store the 16 bit value in the frame data for the next message without conversion.
    frame_data_mutex.lock();
    frame_data.temp = (buff[0]<<8 | buff[1]);
    frame_data_mutex.unlock();
}

void temp_hum_sensor_read(){
    converted_reading();
}
