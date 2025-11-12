#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

#include <rcc.h>
#include <hal.h>
#include <uart.h>
#include <i2c.h>

int main(void) {
	/* Configure hal.h to hold pin bank and pins, 32bits can fit both */

	char buf[32] = "Done\r\n";
	static const size_t buff_len = 6;
	static const uint8_t si7021_addr = 0x40;
	uint8_t reg_version[2] = {0x84, 0xB8};
	uint8_t rx_buf[10];

	uart2_init();
	i2c1_init();

	systick_init();
	for (;;) {
		i2c_transmit(i2c1, si7021_addr, reg_version, 2); 
		i2c_receive(i2c1, si7021_addr, rx_buf, 1);
		uart_write_buf(uart2, (char*)rx_buf, 1);
		uart_write_buf(uart2, "\r\n", 2);
		delay(500);
	}
	return 0;
}
