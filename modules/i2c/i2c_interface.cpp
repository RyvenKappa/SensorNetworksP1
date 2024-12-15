#include "i2c_interface.h"
#include "../shared_data/shared_data.h"
#include "../temp_hum_sensor/temp_hum.h"
#include "../accelerometer_sensor/accelerometer.h"
#include "../color_sensor/color_sensor.h"
#include <cstdint>

Thread i2c_thread(osPriorityNormal,512,nullptr,"I2CThread");

Mutex i2c_mutex;
i2c_data_t i2c_data;

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
    frame_data_mutex.lock();
    frame_data.x_acc = 0.0;
    frame_data.y_acc = 0.0;
    frame_data.z_acc = 0.0;
    frame_data.temp = 0.0;
    frame_data.hum = 0.0;
    frame_data.clear = 0;
    frame_data.red = 0;
    frame_data.green = 0;
    frame_data.blue = 0;
    frame_data_mutex.unlock();
    i2c_mutex.lock();
    i2c_data.x_acc = 0.0;
    i2c_data.y_acc = 0.0;
    i2c_data.temp = 20.0;
    i2c_data.hum = 20.0;
    i2c_data.clear = 0;
    i2c_data.red = 0;
    i2c_data.green = 0;
    i2c_data.blue = 0;
    i2c_mutex.unlock();
    accelerometer_sensor_init();
    color_sensor_init();
    osStatus codigo = i2c_thread.start(&i2c_read_sensors);
    printf("Cosa de error: %d\n",codigo);
}