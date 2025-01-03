#include "gps.h"
#include <cstdint>
#include <cstdio>
Thread gps_thread(osPriorityNormal,1024,nullptr,"GPSThread");

static char buffer[83];
static BufferedSerial serial(NC,GPS_RX,9600);
static bool wait_gps_msg = 0;


int buffer_index = 0;
char c;

static bool found_gps_msg = false;
static bool found_gps_date = false;

static float time_stamp = 240405.000;
static float latitude = 0.0;
static char latitude_c = 'N';
static float longitude = 0.0;
static char longitude_c = 'W';
static uint8_t quality = 0;
static uint8_t sats = 0;
static float altitude = 0.0;
static char altitude_c = 'm';
static float hdop = 0.0;
static uint32_t date = 0;

/**
* Static function to analyze the gps msg and find the specific one we need to fill a msg.
*/
static void parse_gps_msg(){
    // Strncmp to find specific NMEA sentences that need deeper parsing.
    if ((strncmp(buffer, "$GPGGA",6)==0) && (!found_gps_msg)){
        sscanf(buffer, "$GPGGA,%f,%f,%c,%f,%c,%hhu,%hhu,%f,%f,%c", &time_stamp,&latitude,&latitude_c,&longitude,&longitude_c,&quality,&sats,&hdop,&altitude,&altitude_c);
        // Process the data if there is any and put them in the frame data for the lora message procedure.
        if (sats>0){
            frame_data_mutex.lock();
            latitude = latitude/100.0;
            if (latitude_c=='S') {
                latitude = -1*latitude;
            }
            longitude = longitude/100.0;
            if (longitude_c=='W') {
                longitude = -1*longitude;
            }
            frame_data.measurement_report.latitude = *(uint32_t *)&latitude;
            frame_data.measurement_report.longitude = *(uint32_t *)&longitude;
            frame_data.measurement_report.altitude = (uint16_t)altitude;
            frame_data_mutex.unlock();
        }
        found_gps_msg = true;
    }else if ((strncmp(buffer, "$GPRMC",6)==0) && (!found_gps_date)) {
        sscanf(buffer, "%*[^\\,],%*[^\\,],%*[^\\,],%*[^\\,],%*[^\\,],%*[^\\,],%*[^\\,],%*[^\\,],%*[^\\,],%u",&date);
        found_gps_date = true;
    }
}

/**
* Static function to read the gps data
*/
static void gps_read_data(){
    while (true) {
        found_gps_msg = false;
        found_gps_date = false;
        serial.enable_input(true);
        while ((!found_gps_msg) || (!found_gps_date)) {
            serial.read(&c,1);
            if (c == '\n') {
                // When a complete NMEA sentence if found, parse it.
                buffer[buffer_index] = '\0';
                buffer_index = 0;
                parse_gps_msg();
            }else{
                // Otherwise, rewrite the buffer.
                buffer[buffer_index++] = c;
            }
        }
        serial.enable_input(false);
        ThisThread::sleep_for(5s);
    }
}

void gps_init(){

    // Set the frame data related to the GPS in madrid.
    frame_data_mutex.lock();
    float longitude = -3.609561;
    frame_data.measurement_report.longitude = *(uint32_t *)&longitude;
    float latitude = 40.386017;
    frame_data.measurement_report.latitude = *(uint32_t *)&latitude;
    frame_data.measurement_report.altitude = 700;
    frame_data_mutex.unlock();

    serial.enable_input(false);
    osStatus codigo = gps_thread.start(&gps_read_data);
    if (codigo != 0){
        fprintf(stderr, "Error on the start of the I2C Thread, code: %d. Exiting the app.\n", codigo);
        exit(0);
    }
}