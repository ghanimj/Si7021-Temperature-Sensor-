#ifndef SI7021_H__
#define SI7021_H__

#define SI7021_ADDR 0x40
#define HUMIDITY_HMM 0xE5
#define HUMIDITY_NHMM 0xF5
#define TEMP_HMM 0xE3
#define TEMP_NHMM 0xF3
#define TEMP_AFTER_HUMIDITY 0xE0
#define RST 0xFE

#define PASS 1
#define FAIL 0

uint8_t si7021_get_firmware(void);
uint8_t si7021_read_temp(float* rx_buf);
uint8_t si7021_read_humidity(float* rx_buf);

#endif
