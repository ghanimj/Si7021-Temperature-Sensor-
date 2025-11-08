#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

#include <rcc.h>
#include <hal.h>
#include <uart.h>

#define LED_PIN(pin) (BIT(pin))
#define LED_PORT 'A'

int main(void) {
	/* Configure hal.h to hold pin bank and pins, 32bits can fit both */

	char buf[32];

	uart2_init();

	systick_init();
	lora_version = new_lora(&lora);
	for (;;) {
		delay(50);
	}
	return 0;
}
