/**
 * @file gps.h
 * @brief Header file for GPS module integration.
 * This file defines the GPS data structure and functions for initializing,
 * deinitializing, and reading GPS data.
 * @version 1.0
 * @date 2025-01-01
 * @note This module uses the C++17 standard.
 */

#ifndef __GPS_H__
#define __GPS_H__

#include <stdint.h>
#include "driver/uart.h"
#include "driver/gpio.h"

#define GPS_UART_PORT_NUM      UART_NUM_1
#define GPS_UART_TX_PIN       17
#define GPS_UART_RX_PIN       16
#define GPS_UART_BAUD_RATE    9600
#define GPS_UART_BUFFER_SIZE  1024
#define GPS_UART_TIMEOUT_MS   1000
#define GPS_UART_PARITY       UART_PARITY_DISABLE
#define GPS_UART_STOP_BITS    UART_STOP_BITS_1
#define GPS_UART_DATA_BITS    UART_DATA_8_BITS

/**
 * @brief Structure to hold GPS data.
 * This structure contains fields for latitude, longitude,
 * altitude, speed, and timestamp.
 */

typedef struct {
    float latitude;
    float longitude;
    float altitude;
    float speed;
    uint32_t timestamp;
    int num_satellites;
    int fix_quality; // 0 = no fix, 1 = GPS fix, 2 = DGPS fix, etc.
    // Additional fields can be added as needed
} gps_data_t;

/**
 * @brief Initializes the GPS module.
 * This function configures the UART settings and prepares the GPS module for data reading.
 */
void gps_init(void);

/**
 * @brief Deinitializes the GPS module.
 * This function cleans up resources used by the GPS module.
 */
void gps_deinit(void);

/**
 * @brief Reads data from the GPS module.
 * This function reads GPS data and fills the provided gps_data_t structure.
 * @param data Pointer to a gps_data_t structure to fill with GPS data.
 * @return 0 on success, negative value on error.
 */
int gps_read_data(gps_data_t *data);

#endif // __GPS_H__