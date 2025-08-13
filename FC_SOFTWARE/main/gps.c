#include "gps.h"
#include <string.h>

void gps_init(void) {
    // Configure UART for GPS
    uart_config_t uart_config = {
        .baud_rate = GPS_UART_BAUD_RATE,
        .data_bits = GPS_UART_DATA_BITS,
        .parity = GPS_UART_PARITY,
        .stop_bits = GPS_UART_STOP_BITS,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT
    };
    
    // Install UART driver
    uart_driver_install(GPS_UART_PORT_NUM, GPS_UART_BUFFER_SIZE, 0, 0, NULL, 0);
    
    // Set UART parameters
    uart_param_config(GPS_UART_PORT_NUM, &uart_config);
    
    // Set pins for GPS UART
    uart_set_pin(GPS_UART_PORT_NUM, GPS_UART_TX_PIN, GPS_UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

void gps_deinit(void) {
    // Deinitialize UART for GPS
    uart_driver_delete(GPS_UART_PORT_NUM);
}

int gps_read_data(gps_data_t *data) {
    if (data == NULL) {
        return -1; // Error: null pointer
    }
    char buffer[GPS_UART_BUFFER_SIZE] = {0};
    int bytes_read = uart_read_bytes(GPS_UART_PORT_NUM, (uint8_t *)buffer, GPS_UART_BUFFER_SIZE - 1, GPS_UART_TIMEOUT_MS / portTICK_PERIOD_MS);
    if (bytes_read <= 0) {
        return -2; // Error: no data read
    }
    buffer[bytes_read] = '\0';

    // Find $GPGGA sentence
    char *gpgga = strstr(buffer, "$GPGGA,");
    if (!gpgga) {
        return -3; // Error: GPGGA sentence not found
    }

    // Example: $GPGGA,110827.00,41XX.32485,N,008XX.XXXXX,W,1,07,0.99,123.1,M,50.1,M,,*48
    char time[16], lat[16], ns, lon[16], ew, fix[4], sats[4], hdop[8], alt[8], alt_unit, geo_sep[8], geo_unit;
    int parsed = sscanf(gpgga,
        "$GPGGA,%15[^,],%15[^,],%c,%15[^,],%c,%3[^,],%3[^,],%7[^,],%7[^,],%c,%7[^,],%c",
        time, lat, &ns, lon, &ew, fix, sats, hdop, alt, &alt_unit, geo_sep, &geo_unit);

    if (parsed < 11) {
        return -4; // Error: failed to parse GPGGA
    }

    // Convert latitude
    double lat_deg = 0.0, lon_deg = 0.0;
    if (strlen(lat) >= 4) {
        double deg = atof(lat) / 100.0;
        int d = (int)deg;
        double m = (deg - d) * 100.0;
        lat_deg = d + m / 60.0;
        if (ns == 'S') lat_deg = -lat_deg;
    }
    // Convert longitude
    if (strlen(lon) >= 5) {
        double deg = atof(lon) / 100.0;
        int d = (int)deg;
        double m = (deg - d) * 100.0;
        lon_deg = d + m / 60.0;
        if (ew == 'W') lon_deg = -lon_deg;
    }

    data->latitude = lat_deg;
    data->longitude = lon_deg;
    data->altitude = atof(alt);
    data->num_satellites = atoi(sats);
    data->fix_quality = atoi(fix);
    // Optionally parse time, hdop, geo_sep, etc.

    return 0; // Success
}