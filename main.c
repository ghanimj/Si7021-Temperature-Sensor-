#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

#include <rcc.h>
#include <hal.h>
#include <uart.h>
#include <i2c.h>
#include <si7021.h>

int main(void) {
	/* Configure hal.h to hold pin bank and pins, 32bits can fit both */

	uart2_init();


	systick_init();

	volatile uint32_t* fpu = CPACR;
	*fpu |= 0xF << 20; /* Set FPU bits */


	for (;;) {

		double temp_val = 0.0f;

		/* 5kb worth operation wowee */
		/* Also float is unrepresented, would need implementation etc, so just gonna cast to int */

		printf("Hello\r\n");

		delay(500);
	}
	return 0;
}
