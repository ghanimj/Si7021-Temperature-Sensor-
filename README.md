# Si7021
Communicating with Si7021 Temperature Sensor using i2C through STM32F411RE.
This project is built on top of the Bare Metal Programming Guide for STM32
(https://github.com/cpq/bare-metal-programming-guide)

by Ghanim

This project's design purpose was to mainly further understanding of bare-metal embedded programming,
and to get a sense of understanding of how I2C works under the hood. A temperature sensor module Si7021 is used
to communicate with our master Nucleo F411RE board using I2C.

The most difficult aspect of this project was definitely understanding
I2C. Coming from SPI with my previous LoRa project, I believed I2C would
be simpler now that I knew how to code one communication protocol. Unfortunately I was very wrong as most of my hours were spent debugging I2C bus glitches being stuck, slave being stuck and holding SDA hostage, carefully following 1-byte 2-byte reception protocols from STM32's reference sheet, but in the end the learning material definitely made it worth. Thankfully, I decided to invest into an oscilloscope before starting this project and it was a MASSIVE help, with this bug alone
I would have spent days and days more trying to debug what exactly was happening with my SDA lines. The Rigol DS1102 was a big help, and this project
alone made me learn about how to function an oscilloscopes as a great side-effect.

The nice part was that actually programming my Si7021 temp sensor module
was way easier than LoRa due to the fact that we simply just have to read a ready made temp code value from our sensor. No writing to change register settings, nothing like what made LoRa complicated. This was all handled simply with i2c_reg_read(). As for my I2C driver, it makes sure to not getitself stuck accidently on a new flash/user reset by sending dummy clock signals on init to slave. 

To make use of this, simply make sure our sensor is connected to the correct I2C pins on port B, using pin 9 for SCL and pin 8 for SDA. Use "git clone" to clone this project on your directory.

# Features:
Reading temp/humidity values, reading firmware values on our sensor.

# Future TO-DOs
If I was inclined I could finish making this a working library by setting implentation for rest of Si7021's registers, but the main purpose of a temp sensor is to get a temperature reading, and I have left it at that.
