#include <stdint.h>

#include <i2c.h>

uint8_t si7021_get_firmware(void) {
	uint8_t firmware = 0;
	static const reg_fw[2] = {0x84, 0xB8};
	static const reg_len = 2;

	i2c_reg_read(i2c1, SI7021_ADDR, reg_fw, reg_fwlen, firmware, 1);

	return firmware == 0xFF || firmware == 0x20 ? PASS : FAIL;
}

uint8_t si7021_read_temp(float* rx_buf) {
	static const uint8_t reg_len = 1;
	float temp_val = 0.0f;
	float tmp[2];
	/* Temp code is 16 bits, so split among 2 bytes */
	i2c_reg_read(i2c1, SI7021_ADDR, TEMP_HMM, reg_len, tmp, 2); 

	float temp_val = 0.0f;
	if (tmp) {
		uint16_t temp_code = (tmp[0] << 8) | (tmp[1]);
		temp_val = (((175.72f * ((float) temp_code)) / 65536.0f) - 46.85f);
	}
	else {
		return FAIL;
	}

	*rx_buf = temp_val;

	return PASS;
}

uint8_t si7021_read_humidity(float* rx_buf) {
	static const uint8_t reg_len = 1;
	float humidity_val = 0.0f;
	float tmp[2];
	
	i2c_reg_read(i2c1, SI7021_ADDR, HUMIDITY_HMM, reg_len, tmp, 2);
	
	float humid_val = 0.0f;
	if (tmp) {
		uint16_t humid_code = (tmp[0] << 8) | (tmp[1]);
		humid_val = (((125.0f * ((float) humid_code)) / 65536.0f) - 6.0f)
	}
	else {
		return FAIL;
	}

	*rx_buf = humid_val;
	
	return PASS;
}
		
