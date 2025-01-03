#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H
#include "mbed.h"
/**
* @file accelerometer.h
*
* @brief Accelerometer control module.
*
* @author Diego Aceituno Seoane
*
* Controls a MMA8451Q 3-Axis sensor
*
*/

#define ACCELEROMETER_SLAVE_ADDRESS 0x1D
#define ACCELEROMETER_STATUS 0x00
#define ACCELEROMETER_X_MSB 0x01
#define ACCELEROMETER_X_LSB 0x02
#define ACCELEROMETER_Y_MSB 0x03
#define ACCELEROMETER_Y_LSB 0x04
#define ACCELEROMETER_Z_MSB 0x05
#define ACCELEROMETER_Z_LSB 0x06
#define ACCELEROMETER_F_SETUP 0x09
#define ACCELEROMETER_TRIG_CFG 0x0A
#define ACCELEROMETER_SYSMOD 0x0B
#define ACCELEROMETER_INT_SOURCE 0x0C
#define ACCELEROMETER_WHO_AM_I 0X0D
#define ACCELEROMETER_XYZ_DATA_CFG 0x0E
#define ACCELEROMETER_FILTER_CUTOFF 0x0F
#define ACCELEROMETER_PL_STATUS 0x10
#define ACCELEROMETER_PL_CFG 0x11
#define ACCELEROMETER_PL_COUNT 0x12
#define ACCELEROMETER_BF_ZCOMP 0x13
#define ACCELEROMETER_THS_REG 0x14
#define ACCELEROMETER_MT_CFG 0x15
#define ACCELEROMETER_MT_SRC 0x16
#define ACCELEROMETER_MT_THS 0x17
#define ACCELEROMETER_MT_COUNT 0x18
#define ACCELEROMETER_TRANSIENT_CFG 0x1D
#define ACCELEROMETER_TRANSIENT_SCR 0x1E
#define ACCELEROMETER_TRANSIENT_THS 0x1F
#define ACCELEROMETER_TRANSIENT_COUNT 0x20
#define ACCELEROMETER_PULSE_CFG 0x21
#define ACCELEROMETER_PULSE_SRC 0x22
#define ACCELEROMETER_PULSE_THSX 0x23
#define ACCELEROMETER_PULSE_THSY 0x24
#define ACCELEROMETER_PULSE_THSZ 0x25
#define ACCELEROMETER_PULSE_TMLT 0x26
#define ACCELEROMETER_PULSE_LTCY 0x27
#define ACCELEROMETER_PULSE_WIND 0x28
#define ACCELEROMETER_ASLP_COUNT 0x29
#define ACCELEROMETER_CTRL_REG1 0x2A
#define ACCELEROMETER_CTRL_REG2 0x2B
#define ACCELEROMETER_CTRL_REG3 0x2C
#define ACCELEROMETER_CTRL_REG4 0x2D
#define ACCELEROMETER_CTRL_REG5 0x2E
#define ACCELEROMETER_OFF_X 0x2F
#define ACCELEROMETER_OFF_Y 0x30
#define ACCELEROMETER_OFF_Z 0x31

#define ACCELEROMETER_8G 1024.0
#define ACCELEROMETER_4G 2048.0
#define ACCELEROMETER_2G 4096.0


extern void clear_acc_interrupt();

/**
* @brief Reading of the accelerometer data
*/
extern void accelerometer_sensor_read();

/**
* @brief Inicialization of the accelerometer sensor
*/
extern void accelerometer_sensor_init();
#endif