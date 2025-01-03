#include "mbed.h"
#include "color_sensor.h"
#include "../shared_data/shared_data.h"
#include "../i2c/i2c_interface.h"
#include <cstdint>
#include <stdint.h>

DigitalOut color_led(COLOR_SENSOR_LED);


static char cmd[2];
static char data[8];
/**
* Static function for measurement processing
*/
static void measurement_process(){
    // Original data is processed and inserted in the frame structure for lora
    frame_data_mutex.lock();
    frame_data.measurement_report.clear = data[1]<<8 | data[0];
    frame_data.measurement_report.red = data[3]<<8 | data[2];
    frame_data.measurement_report.green = (data[5]<<8 | data[4]) + frame_data.measurement_report.red*0.15; //Spectral compensation is added to the green.
    frame_data.measurement_report.blue = (data[7]<<8 | data[6]) + frame_data.measurement_report.red*0.25;  //Spectral compensation is added to the blue.
    frame_data_mutex.unlock();
}

void color_sensor_read(){
    color_led.write(1);
    //Activate sensor, AEN & PON
    cmd[0] = COLOR_SENSOR_CMD_MSK | COLOR_SENSOR_TYPE_AUTO_INCREMENT | COLOR_SENSOR_ENABLE;
    cmd[1] = 0x03;
    i2c_bus.write(COLOR_SENSOR_SLAVE_ADDRESS<<1,cmd,2);
    ThisThread::sleep_for(3ms); //PON stabilization time
    //Wait for integration and reading
    ThisThread::sleep_for(160ms); //Integration time and RGBC Init 2.4+154=157.4
    color_led.write(0);
    cmd[0] = COLOR_SENSOR_CMD_MSK | COLOR_SENSOR_TYPE_AUTO_INCREMENT | COLOR_SENSOR_CDATAL;
    i2c_bus.write(COLOR_SENSOR_SLAVE_ADDRESS<<1,cmd,1);
    i2c_bus.read(COLOR_SENSOR_SLAVE_ADDRESS<<1,data,8);
    //Deactivate sensor and disable RGBC ADCs
    cmd[0] = COLOR_SENSOR_CMD_MSK | COLOR_SENSOR_TYPE_AUTO_INCREMENT | COLOR_SENSOR_ENABLE;
    cmd[1] = 0x00;//!AEN & !PON
    i2c_bus.write(COLOR_SENSOR_SLAVE_ADDRESS<<1,cmd,2);
    //Process measurement into the ctrl_msg_t and put into queue
    measurement_process();
}


void color_sensor_init(){
    // Init configuration: Wait dissabled, interruptions dissabled and AEN deactivated.
    cmd[0] = COLOR_SENSOR_CMD_MSK | COLOR_SENSOR_TYPE_AUTO_INCREMENT | COLOR_SENSOR_ENABLE;
    cmd[1] = 0x02; 
    i2c_bus.write(COLOR_SENSOR_SLAVE_ADDRESS<<1,cmd,2);

    // Init configuration: 154ms of RGBC Integration
    cmd[0] = COLOR_SENSOR_CMD_MSK | COLOR_SENSOR_TYPE_AUTO_INCREMENT | COLOR_SENSOR_ATIME;
    cmd[1] = 0xC0;
    i2c_bus.write(COLOR_SENSOR_SLAVE_ADDRESS<<1,cmd,2);
}