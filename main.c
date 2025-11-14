#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

#include <rcc.h>
#include <hal.h>
#include <uart.h>
#include <i2c.h>
#include <si7021.h>

int main(void) {
	/* Configure hal.h to hold pin bank and pins, 32bits can fit both */

	uart2_init();
	i2c1_init();


	systick_init();

	for (;;) {


		si7021_get_firmware();
		delay(500);
	}
	return 0;
}
