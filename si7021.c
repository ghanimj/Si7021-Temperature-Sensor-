#include <stdint.h>

#include <i2c.h>
#include <si7021.h>

uint8_t si7021_get_firmware(void) {
	uint8_t firmware = 0;
	static uint8_t reg_fw[2] = {0x84, 0xB8};
	static size_t reg_len = 2;

	i2c_reg_read(i2c1, SI7021_ADDR, reg_fw, reg_len, &firmware, 1);

	return firmware;
}

uint8_t si7021_read_temp(float* rx_buf) {
	static uint8_t reg_temp = TEMP_HMM;
	static uint8_t reg_len = 1;
	float temp_val = 0.0f;
	uint8_t tmp[2];
	/* Temp code is 16 bits, so split among 2 bytes */
	i2c_reg_read(i2c1, SI7021_ADDR, &reg_temp, reg_len, tmp, 2); 
	if ((tmp[1] & 0x3) != 0) {
		uint16_t temp_code = (uint16_t)(((uint16_t)tmp[0] << 8) | (uint16_t)(tmp[1]));
		temp_val = (((175.72f * ((float) temp_code)) / 65536.0f) - 46.85f);
	}
	else {
		return FAIL;
	}

	*rx_buf = temp_val;

	return PASS;
}

uint8_t si7021_read_humidity(float* rx_buf) {
	static uint8_t reg_humid = HUMIDITY_HMM;
	static uint8_t reg_len = 1;
	float humid_val = 0.0f;
	uint8_t tmp[2];
	
	i2c_reg_read(i2c1, SI7021_ADDR, &reg_humid, reg_len, tmp, 2);
	
	if ((tmp[1] & 0x3) != 0) {
		uint16_t humid_code = (uint16_t)(((uint16_t)tmp[0] << 8U) | (uint16_t)(tmp[1]));
		humid_val = (((125.0f * ((float) humid_code)) / 65536.0f) - 6.0f);
	}
	else {
		return FAIL;
	}

	*rx_buf = humid_val;
	
	return PASS;
}
		
