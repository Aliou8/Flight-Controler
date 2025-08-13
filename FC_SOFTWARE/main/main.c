#include <stdio.h>
#include "bmp390.h"
#include "icm42670.h"
#include "gps.h"
#include "esp_system.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void app_main(void)
{
    gps_data_t gps_data;
    // Initialize GPS module
    gps_init();
    ESP_LOGI("GPS", "GPS module initialized");
    while (1) {
        // Read GPS data
        int result = gps_read_data(&gps_data);
        if (result == 0) {
            ESP_LOGI("GPS", "Latitude: %.6f, Longitude: %.6f, Altitude: %.2f, Speed: %.2f, Timestamp: %u, Satellites: %d, Fix Quality: %d",
                     gps_data.latitude, gps_data.longitude, gps_data.altitude,
                     gps_data.speed, gps_data.timestamp, gps_data.num_satellites,
                     gps_data.fix_quality);
        } else {
            ESP_LOGE("GPS", "Error reading GPS data: %d", result);
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second before next read
    }

}