/*
 * lcd_i2c.c
 *
 * Created: 04/09/2017 07:37:47 p. m.
 * Author : falco
 */

// Yo asigne el pin 0x02 como el En de la LCD
// y el pin 0x01 como el pin RS de la LCD
// Los pines de los datos los m�s altos del modulo a los de la lcd P4-D4,P5-D5,P6-D6,P7-D7
// R/W va a tierra
#include <avr/io.h>
//-----Proto-Type-------//
void lcd_init();		  //----LCD Initializing Function
void toggle();			  //----Latching function of LCD
void lcd_cmd_hf(char v1); //----Function to send half byte command to LCD
void lcd_cmd(char v2);	  //----Function to send Command to LCD
void lcd_dwr(char v3);	  //----Function to send data to LCD
void lcd_msg(char *c);	  //----Function to Send String to LCD
void delay(int ms);		  //----Delay function
void lcd_lef_sh();		  //----Left Shifting Function
void lcd_rig_sh();		  //----Right Shifting Function
void lcd_x_y(uint8_t x_pos, uint8_t y_pos);
void twi_lcd_clear();
//----------------------//
