#include "moisture_sensor.h"

#define MOISTURE_READ_PIN PA_0
#define MOISTURE_POWER_PIN PA_13

static AnalogIn value_reader(MOISTURE_READ_PIN);
#ifdef DEBUG_MODE
static DigitalOut power_pin(MOISTURE_POWER_PIN);
#endif

/**
* Static function for the thread loop
*/
float read_moisture_sensor_data(){
    #ifdef DEBUG_MODE
    power_pin.write(1);
    ThisThread::sleep_for(1ms);
    #endif

    float return_value = ((float)value_reader.read_u16()*100)/0xFFFF;
    
    #ifdef DEBUG_MODE
    power_pin.write(0);
    #endif
    return return_value;
}