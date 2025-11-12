#include <stdint.h>

#include <i2c.h>
#include <hal.h>
#include <uart.h>

struct i2c* i2c1 = I2C1;

void i2c_init(struct i2c* i2c, uint32_t i2c_pins, uint8_t i2c_port) {
	uint8_t i2c_af = 4;

	if (i2c == I2C1) RCC->APB1ENR |= BIT(21);

	gpio_set_mode(i2c_pins, GPIO_MODE_AF_OD, i2c_port);
	gpio_set_speed(i2c_pins, HIGH_SPEED, i2c_port);
	gpio_set_af(i2c_pins, i2c_af, i2c_port);

	i2c->CR1 = 0, i2c->CR2 = 0;
	i2c->CR2 |= 0x10; /* 16 MHz frequency */

	i2c->OAR1 = 0, i2c->OAR2 = 0; 
	
	i2c->CCR = 80; /* 80 = 100KHz standard freq */
	i2c->TRISE = 17;/* 1000/(1/16MHz) + 1 */


	i2c->CR1 |= PE;
}

void i2c_transmit(struct i2c* i2c, uint8_t addr, uint8_t* tx_buf, size_t tx_len) {
	while(i2c->SR2 & I2C_BUS_BUSY);

	i2c->CR1 |= START; /* Generate start */
	while (!(i2c->SR1 & I2C_SB_FLAG));

	i2c->DR = (uint32_t) ((addr << 1) | 0);

	while (!(i2c->SR1 & I2C_ADDR_RX));

	(void)i2c->SR1;
	(void)i2c->SR2; /* Read both SR registers to set to 0 */
	
	size_t len = tx_len;
	while(len--) {
		while (!(i2c->SR1 & I2C_TXE_FLAG));
		i2c->DR = (uint32_t) *tx_buf++;
	}

	i2c->CR1 |= STOP;
}

void i2c_receive(struct i2c* i2c, uint8_t addr, uint8_t* rx_buf, size_t rx_bytes) {
	while(i2c->SR2 & I2C_BUS_BUSY);

	i2c->CR1 |= START;
	while (!(i2c->SR1 & I2C_SB_FLAG));

	i2c->DR = (uint32_t) ((addr << 1) | 1);
	i2c->CR1 &= ~(I2C_SET_ACK);

	while (!(i2c->SR1 & I2C_ADDR_RX));
	
	(void)i2c->SR1;
	(void)i2c->SR2; /* Read both SR registers to set to 0 */
	
	size_t len = rx_bytes;
	while(len--) {
		while(!(i2c->SR1 & I2C_RXNE_FLAG));
		rx_buf[len] = (uint8_t) i2c->DR;
	}

	i2c->CR1 |= STOP;
}

void i2c_reg_read(struct i2c* i2c, uint8_t addr, uint8_t* cmd, size_t cmd_len, uint8_t* rx_buf, size_t rx_bytes) {
	/* Set ACK, set START, send slave addr, send
	 * cmd addr, set (RE)START, send slave addr again,
	 * ready to read
	 */
	while(i2c->SR2 & I2C_BUS_BUSY); /* Bus busy? */

	i2c->CR1 |= START;
	while (!(i2c->SR1 & I2C_SB_FLAG));

	i2c->DR = (uint32_t) ((addr << 1) | 0);
	while (!(i2c->SR1 & I2C_ADDR_RX)); /* Send and wait for addr to be received */

	(void)i2c->SR1;
	(void)i2c->SR2; /* Read both SR registers to set to 0 */
	
	/* Write command to receiver */
	size_t len = cmd_len;
	while(len--) {
		while(!(i2c->SR1 & I2C_TXE_FLAG));
		i2c->DR = (uint32_t) *cmd++;
	}

	/* Restart, prepare a read */
	uart_write_buf(uart2, "stop\r\n", 6);
	i2c->CR1 |= START;
	while (!(i2c->SR1 & I2C_SB_FLAG));

	i2c->CR1 |= I2C_SET_ACK;	
	i2c->DR = (uint32_t) ((addr << 1) | 1);
	while (!(i2c->SR1 & I2C_ADDR_RX)); /* Send and wait for addr to be received */

	(void)i2c->SR1;
	(void)i2c->SR2; /* Read both SR registers to set to 0 */

	if (rx_bytes == 1) {
		i2c->CR1 &= ~(I2C_SET_ACK);	

		while(i2c->SR1 & I2C_RXNE_FLAG);
		*rx_buf = (uint8_t) i2c->DR;
	}
	/* We're just gonna handle 1 byte reception case for now */

	i2c->CR1 |= STOP;
}



void i2c1_init(void) {
	uint8_t i2c1_port = I2C1_PORT;
	uint32_t i2c1_pins = I2C1_SDA | I2C1_SCL;

	i2c_init(i2c1, i2c1_pins, i2c1_port);
}
