#include "gps.h"
#include <cstdint>
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
    if ((strncmp(buffer, "$GPGGA",6)==0) && (!found_gps_msg)){
        sscanf(buffer, "$GPGGA,%f,%f,%c,%f,%c,%hhu,%hhu,%f,%f,%c", &time_stamp,&latitude,&latitude_c,&longitude,&longitude_c,&quality,&sats,&hdop,&altitude,&altitude_c);
        frame_data_mutex.lock();
        frame_data.gps_conn = sats;
        frame_data.latitude = latitude;
        frame_data.longitude = longitude;
        frame_data_mutex.unlock();
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
                buffer[buffer_index] = '\0';
                buffer_index = 0;
                parse_gps_msg();
            }else{
                buffer[buffer_index++] = c;
            }
        }
        serial.enable_input(false);
        ThisThread::sleep_for(5s);
    }
}

void gps_init(){
    //TODO initialize the gps data
    frame_data_mutex.lock();
    frame_data.longitude = 45.122130;
    frame_data.latitude = -3.00022;
    frame_data.altitude = 700;
    frame_data_mutex.unlock();
    serial.enable_input(false);
    gps_thread.start(&gps_read_data);
}