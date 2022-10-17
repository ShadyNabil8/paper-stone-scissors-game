#include <lcd_i2c.h>
void toggle()
{
    TWDR |= 0x02;                      //---PIN En de la LCD en = 1;  -----Latching data in to LCD data register using High to Low signal
    TWCR = (1 << TWINT) | (1 << TWEN); //---Enable I2C and clear interrupt- Esta linea y la siguiente simepre van despues de querer mandar un coamndo por TDWR
    while (!(TWCR & (1 << TWINT)))
        ; //---Simepre poner despues de la linea anterior al mandar datos por TWDR
    delay(1);
    TWDR &= ~0x02;                     //---PIN del Enable de la LCD en = 0;
    TWCR = (1 << TWINT) | (1 << TWEN); //---Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
}

void lcd_cmd_hf(char v1)
{
    TWDR &= ~0x01;                     // PIN RS de la LCD rs = 0; ----Selecting register as Command register
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    TWDR &= 0x0F;                      //----clearing the Higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    TWDR |= (v1 & 0xF0);               //----Masking higher 4 bits and sending to LCD
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    toggle();
}

void lcd_cmd(char v2)
{
    TWDR &= ~0x01;                     // rs = 0; ----Selecting register as command register
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    TWDR &= 0x0F;                      //----clearing the Higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    TWDR |= (v2 & 0xF0);               //----Masking higher 4 bits and sending to LCD
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    toggle();

    TWDR &= 0x0F;                      //----clearing the Higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    TWDR |= ((v2 & 0x0F) << 4);        //----Masking lower 4 bits and sending to LCD
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    toggle();
}

void lcd_dwr(char v3)
{
    TWDR |= 0x01;                      // rs = 1; ----Selecting register as command register
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    TWDR &= 0x0F;                      //----clearing the Higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    TWDR |= (v3 & 0xF0);               //----Masking higher 4 bits and sending to LCD
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    toggle();

    TWDR &= 0x0F;                      //----clearing the Higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    TWDR |= ((v3 & 0x0F) << 4);        //----Masking lower 4 bits and sending to LCD
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable I2C and clear interrupt
    while (!(TWCR & (1 << TWINT)))
        ;
    toggle();
}

void lcd_init()
{
    lcd_cmd_hf(0x30); //-----Sequence for initializing LCD
    lcd_cmd_hf(0x30); //-----     "            "              "               "
    lcd_cmd_hf(0x20); //-----     "            "              "               "
    lcd_cmd(0x28);    //-----Selecting 16 x 2 LCD in 4Bit mode
    lcd_cmd(0x0C);    //-----Display ON Cursor OFF
    lcd_cmd(0x01);    //-----Clear display
    lcd_cmd(0x06);    //-----Cursor Auto Increment
    lcd_cmd(0x80);    //-----1st line 1st location of LCD
}

void delay(int ms)
{
    int i, j;
    for (i = 0; i <= ms; i++)
        for (j = 0; j <= 120; j++)
            ;
}

void lcd_msg(char *c)
{
    while (*c != 0)    //----Wait till all String are passed to LCD
        lcd_dwr(*c++); //----Send the String to LCD
}

void lcd_rig_sh()
{
    lcd_cmd(0x1C); //----Command for right Shift
    delay(400);
}

void lcd_lef_sh()
{
    lcd_cmd(0x18); //----Command for Left Shift
    delay(200);
}
void lcd_x_y(uint8_t x_pos, uint8_t y_pos)
{
    uint8_t loc = 0;
    switch (y_pos)
    {
    case 0:
        loc = x_pos;
        break;
    case 1:
        loc = 0x40 + x_pos;
        break;
    }
    lcd_cmd(0x80 | loc);
}
void twi_lcd_clear()
{
    lcd_cmd(0x01);
}