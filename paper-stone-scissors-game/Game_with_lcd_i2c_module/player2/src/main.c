#include<avr/io.h>
#include<util/delay.h>
#include"../lib/UART/UART.h"
#include<stdlib.h>
#include <time.h>

//#define F_CPU 8000000UL /* CPU Frequendy 8MHZ */

#define getBin(reg,bin)  ((reg>>bin)&1)

#define my_time '1'

typedef enum
{
  paper = 0,
  scissor= 1,
  stone = 2,

}actions;
int main(void)
{
  UART_init(UART_polling,TXandRX,baud_9600); /* initialize the UART communication protocol
    *
    * Select pooling (pooling in a flag)...
    * Select the ATmega32 to be transmetter and reviever...
    * Select 9600 baod rate...
  */

  DDRA = 0x00; /* configue PORTA as INPUT */
  PORTA |= 7; /* confugue the first 3 pins as input pull up */

  while(1)
  {
    while(UART_recieveByte() != my_time); /* pooling untill my game */
    while(getBin(PINA,paper) && getBin(PINA,scissor) && getBin(PINA,stone))
      ; /* loop until player chose */

    if(!getBin(PINA,paper))
    {
      _delay_ms(200);
      UART_sendByte(paper);
    }
      
    else if(!getBin(PINA,scissor))
    {
      _delay_ms(200);
      UART_sendByte(scissor);
    }
    else
    {
      _delay_ms(200);
      UART_sendByte(stone);
    }
  }
}