#include <avr/io.h>
void i2c_init();

// Start condition
void i2c_start();

// I2C stop condition
void i2c_write(char x);

char i2c_read();
