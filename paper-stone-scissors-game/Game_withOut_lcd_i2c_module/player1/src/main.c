/*
 *
 *
 * **************** Stone/Paper/scissors Game *******************
 * Created by : Shady
 * Date 8/31/2022
 * 
 * I prefared not to use interrupts in this game, you can do it with intertupts :)
*/

#include<avr/io.h>
#include<util/delay.h>
#include <time.h>
#include<stdlib.h>
#include"../lib/UART/UART.h"
#include"../lib/LCD/lcd.h"

#define F_CPU 8000000UL /* CPU Frequendy 8MHZ */

#define getBin(reg,bin)  ((reg>>bin)&1)

#define player_time '1'

typedef struct
{
  char name[8];
  short int choise; /* it depends on Stone/Paper/scissors */
}player;


typedef enum
{
  paper = 0,
  scissor= 1,
  stone = 2,

}actions;

int main(void)
{

  LCD_INIT(); /* initialize the LCD module */

  UART_init(UART_polling,TXandRX,baud_9600); /* initialize the UART communication protocol
    *
    * Select pooling (pooling in a flag)...
    * Select the ATmega32 to be transmetter and reviever...
    * Select 9600 baod rate...
  */
  player player1 = {"Essam ",0}; /* player 1 info */
  player player2 = {"Shehata ",0}; /* player 2 info */
  DDRA = 0x00; /* configue PORTA as INPUT */
  PORTA |= 7; /* confugue the first 3 pins as input pull up */
  char game [3][10] = {"paper" , "scissor" , "stone"};
  
  while(1)
  {
    LCD_X_Y(0,0); /* Set the LCD sursor at the beginning */
    LCD_WRITE_STR(player1.name);
    LCD_X_Y(8,0);
    while(getBin(PINA,paper) && getBin(PINA,scissor) && getBin(PINA,stone))
      ; /* loop until shady chose */

    if(!getBin(PINA,paper))
    {
      LCD_WRITE_STR("paper");
      player1.choise = paper;
    }
      
    else if(!getBin(PINA,scissor))
    {
      LCD_WRITE_STR("scissor");
      player1.choise = scissor;
    }
    else
    {
      LCD_WRITE_STR("stone");
      player1.choise = stone;
    }
      
    _delay_ms(200);
    LCD_X_Y(0,1);
    LCD_WRITE_STR(player2.name);
    LCD_X_Y(8,1);
    UART_sendByte(player_time); /* This means " PLAY!!, It is your Game " */
    player2.choise = UART_recieveByte();
    LCD_WRITE_STR(game[player2.choise]);
    _delay_ms(200);
    LCD_CLEAR_SCREEN();

    /* The game logic
    *
    * i know it is confusing, but think
    * Stone     Scisor      Paper
    *   2         1           0
    * if the difference is +1, then the (first) player in the relation
      playerx.choise - playerx.choise wins

    * if the difference is -1, then the (second) player in the relation
    * But it is the opposite in case of the difference = 2 or -2
     
    */
    if(player1.choise == player2.choise)
      LCD_WRITE_STR("No winner");
    switch (player1.choise - player2.choise)
    {
    case 1:
      LCD_WRITE_STR(player1.name);
      LCD_WRITE_STR("Wins");
      break;

    case -1:
      LCD_WRITE_STR(player2.name);
      LCD_WRITE_STR("Wins");
      break;

    case 2:
      LCD_WRITE_STR(player2.name);
      LCD_WRITE_STR("Wins");
      break;

    case -2:
      LCD_WRITE_STR(player1.name);
      LCD_WRITE_STR("Wins");
      break;
    }
    _delay_ms(200);
    LCD_CLEAR_SCREEN();  
  }
  return 0;
}