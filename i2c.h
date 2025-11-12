#ifndef I2C_H__
#define I2C_H__

#include <hal.h>

/* I2C peripherals */
#define I2C1 ((struct i2c*) (0x40005400))
#define I2C2 ((struct i2c*) (0x40005800))
#define I2C3 ((struct i2c*) (0x40005C00)) 

/* I2C Pins */
#define I2C1_PORT 'B'
#define I2C1_SDA (PIN_NUM(9))
#define I2C1_SCL (PIN_NUM(8))

/* CR1 Registers */
#define SWRST (BIT(15))
#define ALERT (BIT(13))
#define POS (BIT(11))
#define I2C_SET_ACK (BIT(10))
#define STOP (BIT(9))
#define START (BIT(8))
#define NOSTRETCH (BIT(7))
#define ENGC (BIT(6))
#define ENPEC (BIT(5))
#define ENARP (BIT(4))
#define SMBTYPE (BIT(3))
#define SMBUS (BIT(1))
#define PE (BIT(0))

/* CRC2 Registers */
#define ITBUFEN (BIT(10))
#define ITEVTEN (BIT(9))
#define ITERREN (BIT(8))

/* OAR1 Registers */
#define ADDMODE10BIT (BIT(15))
#define ADDMODE7BIT 0

/* OAR2 Registers */
#define ENDUAL (BIT(0))

/* SR1 Registers */
#define I2C_TXE_FLAG (BIT(7))
#define I2C_RXNE_FLAG (BIT(6))
#define STOPF (BIT(4))
#define ADD10 (BIT(3))
#define BTF (BIT(2))
#define I2C_ADDR_RX (BIT(1))
#define I2C_SB_FLAG (BIT(0))

/* SR2 Registers */
#define DUALF (BIT(7))
#define I2C_TRA_FLAG (BIT(2))
#define I2C_BUS_BUSY (BIT(1))
#define MSL (BIT(0))

/* CCR Registers */
#define F_S (BIT(15))
#define DUTY (BIT(14))

/* FLTR Registers */
#define ANOFF (BIT(4))

extern struct i2c* i2c1;

struct i2c {
	volatile uint32_t CR1, CR2, OAR1, OAR2, DR, SR1, SR2,
		 CCR, TRISE, FLTR;
};


void i2c_init(struct i2c* i2c, uint32_t i2c_pins, uint8_t i2c_port);
void i2c_transmit(struct i2c* i2c, uint8_t addr, uint8_t* val, size_t tx_len);
void i2c_receive(struct i2c* i2c, uint8_t addr, uint8_t* rx_buf, size_t rx_bytes);
void i2c_reg_read(struct i2c* i2c, uint8_t addr, uint8_t* cmd, size_t cmd_len, uint8_t* rx_buf, size_t rx_bytes);
void i2c1_init(void);


#endif
