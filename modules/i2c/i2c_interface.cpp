#include "i2c_interface.h"
#include "../shared_data/shared_data.h"
#include "../temp_hum_sensor/temp_hum.h"
#include "../accelerometer_sensor/accelerometer.h"
#include "../color_sensor/color_sensor.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

Thread i2c_thread(osPriorityNormal,512,nullptr,"I2CThread");

I2C i2c_bus(I2C_SDA_PIN,I2C_SCL_PIN);

/**
* Static function to call for the readings of the i2c sensors.
*/
static void i2c_read_sensors(){
    while (true) {
        accelerometer_sensor_read();//TODO Hacer que la interrupción de la orientación se tenga en cuenta secuencialmente
        color_sensor_read();
        temp_hum_sensor_read();
        ThisThread::sleep_for(5s);
    }
}


void i2c_thread_init(){
    // Initialize all the frame data related to acc, color, and temp&hum.
    frame_data_mutex.lock();
    frame_data.measurement_report.x_acc = 0;
    frame_data.measurement_report.y_acc = 0;
    frame_data.measurement_report.z_acc = 0;
    frame_data.measurement_report.temp = 20;
    frame_data.measurement_report.hum = 15;
    frame_data.measurement_report.clear = 0;
    frame_data.measurement_report.red = 0;
    frame_data.measurement_report.green = 0;
    frame_data.measurement_report.blue = 0;
    frame_data_mutex.unlock();
    // Configure sensors.
    accelerometer_sensor_init();
    color_sensor_init();
    // Start the thread.
    osStatus codigo = i2c_thread.start(&i2c_read_sensors);
    if (codigo != 0){
        fprintf(stderr, "Error on the start of the I2C Thread, code: %d. Exiting the app.\n", codigo);
        exit(0);
    }
}