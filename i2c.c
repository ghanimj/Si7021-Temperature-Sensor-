#include <stdint.h>

#include <hal.h>


void i2c_init(struct i2c* i2c, uint32_t i2c_pins, uint8_t i2c_port) {
	uint8_t i2c_af = 4;

	if (i2c == I2C1) RCC->APB1ENR |= BIT(21);

	gpio_set_mode(i2c_pins, GPIO_MODE_AF, i2c_port);
	gpio_set_af(i2c_pins, i2c_af, i2c_port);

	i2c->CR1 = 0, i2c->CR2 = 0;

	i2c->OAR1 = 0, i2c->OAR2 = 0; 


	i2c->CR2 |= 0x10 /* 16 MHz frequency */
	i2c->CR1 |= (BIT(0));

}

void i2c_transmit(struct i2c* i2c, uint8_t addr, uint8_t val)

void i2c1_init(void) {
	struct i2c* i2c1 = I2C1;
	uint8_t i2c1_port = I2C1_PORT;
	uint32_t i2c1_pins = I2C1_SDA | I2C1_SCL;

	i2c_init(i2c1, i2c1_pins, i2c1_port);
}
