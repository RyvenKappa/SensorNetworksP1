#include "mbed.h"
#include "accelerometer.h"
#include "../shared_data/shared_data.h"
#include "../i2c/i2c_interface.h"
#include <cstdint>
#include "stdio.h"

static char cmd[2];
static char data[6];


/**
* Static function to read axis
* Acceleration is 14bits ->0b00DDDDDD DDDDDDDD
*/
static void read_acc_x_y_z(){
    cmd[0] = ACCELEROMETER_X_MSB;
    i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,1,true);
    i2c_bus.read(ACCELEROMETER_SLAVE_ADDRESS<<1,data,6);
    frame_data_mutex.lock();
    frame_data.measurement_report.x_acc = (int16_t(data[0]<<8 | data[1]))>>2;
    frame_data.measurement_report.y_acc = (int16_t(data[2]<<8 | data[3]))>>2;
    frame_data.measurement_report.z_acc = (int16_t(data[4]<<8 | data[5]))>>2;
    frame_data_mutex.unlock();
}

void clear_acc_interrupt(){
    cmd[0] = ACCELEROMETER_PL_STATUS;
    i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,1,true);
    i2c_bus.read(ACCELEROMETER_SLAVE_ADDRESS<<1,data,1);
}

/**
* Static function for the thread loop
*/
void accelerometer_sensor_read(){
    //Set Active mode into the sensor
    //cmd[0] = ACCELEROMETER_CTRL_REG1;
    //cmd[1] = 0x01;//Active
    //i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,2);
    //ThisThread::sleep_for(5ms); //Turn-on time from standby
    read_acc_x_y_z();
    //Set Standby mode into the sensor
    //cmd[0] = ACCELEROMETER_CTRL_REG1;
    //cmd[1] = 0x00;//Standby
    //i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,2);
}

void accelerometer_sensor_init(){
    //Reset of the sensor
    cmd[0] = ACCELEROMETER_CTRL_REG2;
    cmd[1] = 0x40;
    i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,2);
    //We wait for the software reset
    ThisThread::sleep_for(3ms);

    //To configure some things as Low noise, we need to be in standby
    //Standby
    cmd[0] = ACCELEROMETER_F_SETUP;
    cmd[1] = 0x00;
    i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,2);
    //Configure 8G dynamic range
    cmd[0] = ACCELEROMETER_XYZ_DATA_CFG;
    cmd[1] = 0x02;
    i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,2);
    //Low noise is only 4G, command:
    //cmd[1] = 0x05;
    //i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,2);

    //Configure interruptions on the orientation
    cmd[0] = ACCELEROMETER_PL_CFG;
    cmd[1] = 0x40;
    i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,2);
    //Activate Interruption, defaults to PIN INT2
    cmd[0] = ACCELEROMETER_CTRL_REG4;
    cmd[1] = 0x10;
    i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,2);
    //Debounce counter to 100ms
    cmd[0] = ACCELEROMETER_PL_COUNT;
    cmd[1] = 0x05;
    i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,2);
    cmd[0] = ACCELEROMETER_CTRL_REG1;
    cmd[1] = 0x31;//Active
    i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,2);
    //Clean the first interrupt
    cmd[0] = ACCELEROMETER_PL_STATUS;
    i2c_bus.write(ACCELEROMETER_SLAVE_ADDRESS<<1,cmd,1,true);
    i2c_bus.read(ACCELEROMETER_SLAVE_ADDRESS<<1,data,1);
    ThisThread::sleep_for(5ms);
}