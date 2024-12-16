#ifndef SHARED_DATA_H
#define SHARED_DATA_H
#include "mbed.h"
#include <cstdint>
/**
* @file shared_data.h
*
* @brief Shared data module to define the structures that are sent to the lorawan modules.
*
* @author Diego Aceituno Seoane
*
* @date 16-12-2024
*
*/

/**
* @brief Structure for the frame sent to the lorawan application
*/
typedef struct PACKED {
    uint8_t     header    : 8;    /*!< 1B version and type and flags */
    uint32_t    latitude  : 32;   /*!< 4B full float latitude */
    uint32_t    longitude : 32;   /*!< 4B full float longitude */
    uint16_t    altitude  : 16;   /*!< 2B full altitude from the gps */
    uint16_t    clear     : 16;   /*!< 2B full clear data from the color sensor */
    uint16_t    red       : 16;   /*!< 2B full red data from the color sensor */
    uint16_t    green     : 16;   /*!< 2B full green data from the color sensor */
    uint16_t    blue      : 16;   /*!< 2B full blue data from the color sensor */
    int16_t     temp      : 16;   /*!< 2B full temp data from the temperature sensor */
    uint16_t    hum       : 10;   /*!< 10b humidity as a percentage with 1 digit * 10 */
    int16_t     x_acc     : 14;   /*!< 14b acceleration in the x axis from the sensor */
    int16_t     y_acc     : 14;   /*!< 14b acceleration in the y axis from the sensor */
    int16_t     z_acc     : 14;   /*!< 14b acceleration in the z axis from the sensor */
    uint16_t    light     : 10;   /*!< 10b light as a percentage with 1 digit * 10 */
    uint16_t    moisture  : 10;   /*!< 10b moisture as a percentage with 1 digit * 10 */
} frame_data_t;

extern frame_data_t frame_data;   /*!< Frame data element */

extern Mutex frame_data_mutex;    /*!< Mutex to access the structure */

#endif


