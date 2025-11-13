#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

#include <rcc.h>
#include <hal.h>
#include <uart.h>
#include <i2c.h>

int main(void) {
	/* Configure hal.h to hold pin bank and pins, 32bits can fit both */

	char buf[8] = "Done\r\n";
	static const size_t buff_len = 6;

	uart2_init();
	i2c1_init();

	systick_init();

	for (;;) {
		printf("I print stuff %d\r\n", 45);
		delay(500);
	}
	return 0;
}
