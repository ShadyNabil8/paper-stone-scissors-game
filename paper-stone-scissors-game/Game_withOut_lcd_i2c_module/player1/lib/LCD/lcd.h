#ifndef _LCD_H
#define _LCD_H
#include<avr/io.h>
#include<math.h>
#include<util/delay.h>

extern uint8_t LCD_x_pos;
extern uint8_t LCD_y_pos;

#define DDR_LCD_data     DDRC
#define PORT_LCD_data    PORTC
#define DDR_LCD_control  DDRD
#define PORT_LCD_control PORTD
#define RS 2
#define RW 3
#define E  4



#define CLEAR                       0x01
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define TWO_LINE_LCD_FOUR_BIT_MODE  0x28  
#define CURSOR_OFF                  0x0C
#define CURSOR_ON                   0x0E
#define SET_CURSOR_LOCATION         0x80
#define DISPLAY_RIGHT_SHIFT         0x1C
#define DISPLAY_LEFT_SHIFT          0x18
#define CURSOR_OFF                  0x0C

void LCD_INIT();
void LCD_CMD(uint8_t cmd);
void LCD_WRITE_CHAR(uint8_t c);
void LCD_WRITE_STR(char * str);
void LCD_CLEAR_SCREEN(void);
void LCD_X_Y(uint8_t x , uint8_t y);
void LCD_DISPLAY_RIGHT_SHIFT(uint8_t r);
void LCD_DISPLAY_LEFT_SHIFT(uint8_t l);
void LCD_WRITE_NUM(uint16_t n);
void LCD_clrear_row(uint8_t x,uint8_t y,uint8_t until);



#endif