/*
 * Timer indikator.c
 *
 * Created: 14.10.2017 19:39:11
 * Author : Vega
 */ 

// 8   7   6   5   4   3   2   1
// A | B | C | D | E | F | G | DP | Ob

//-----------------------------------------//

#define F_CPU 8000000UL

#define Zero 0b00000000
#define One 0b00000001
#define Two 0b00000010
#define Three 0b00000011
#define Four 0b00000100
#define Five 0b00000101
#define Six 0b00000110
#define Seven 0b00000111
#define Eight 0b00001000
#define Nine 0b00001001

//-----------------------------------------//

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Libraries/main_init.h"
#include "Libraries/i2c.h"
#include "Libraries/ds3231.h"
#include "libraries/bcd.h"


//-----------------------------------------//
unsigned char R1=0, R2=0, R3=0, R4=0, R5=0, R6=0;
//????????? ??????? ?????????? ? ?????? ????? ??? ????? ? ?????? ??????
unsigned char time[3] = {0};
//char string[20] = {0};
unsigned char data[4] = {0};
unsigned char time_alarm1[2] = {0};
unsigned char time_alarm2[2] = {0};
//-----------------------------------------//

void segchar (unsigned char seg)
{
	switch(seg)
	{
		
		case 0: PORTD = Zero; break;
		case 1: PORTD = One; break;
		case 2: PORTD = Two; break;
		case 3: PORTD = Three; break;
		case 4: PORTD = Four; break;
		case 5: PORTD = Five; break;
		case 6: PORTD = Six; break;
		case 7: PORTD = Seven; break;
		case 8: PORTD = Eight; break;
		case 9: PORTD = Nine; break;
		
	}
}

//-----------------------------------------//

void timer_ini(void) 
	{
	
	TCCR1B |= (1<<WGM12);        // ????????? ?????? ??? - ????? ?? ??????????
	TIMSK |= (1<<OCIE1A);          // ????????? ???? ?????????? 1 ???????? ?? ?????????? ? OCR1A (H L)
	//0000111101000010
	//111001001101111000
	OCR1AH = 0b01111010;       // - ??????? ???? - ?????????? ????? ??? ????????? 16 ??? + ?????? ???????
	OCR1AL = 0b00010010;       // - ??????? ???? - F_CPU/256=3906 , ? ???????? ??????? - 00001111-01000010    11110100 0010010        01111010 00010010
	TCCR1B |= (1<<CS10);              //  ????????????? ???????? 256    - 1 000 000 / 3906 = 256
	
	}
	
//-----------------------------------------//

//?????????????? ???? ???? ???????? ?????
//-------------------------------------------------------------------------
unsigned char bcd (unsigned char data_bc)
{
	unsigned char bc;

	bc=((((data_bc&(1<<6))|(data_bc&(1<<5))|(data_bc&(1<<4)))*0x0A)>>4)+((data_bc&(1<<3))|(data_bc&(1<<2))|(data_bc&(1<<1))|(data_bc&0x01));

	return bc;
}

unsigned char bin(unsigned char dec)
{

	char bcd;

	char n1, dig1, num1, count1;

	num1 = dec;
	count1 = 0;
	bcd = 0;
	for (n1=0; n1<4; n1++)
	{
		dig1 = num1%10;
		num1 = num1/10;
		bcd = (dig1<<count1)|bcd;
		count1 += 4;
	}

	return bcd;
}

//-------------------------------------------------------------------------

//-----------------------------------------//

unsigned char n_count=0;


//-----------------------------------------//

ISR (TIMER1_COMPA_vect)
{
	if (n_count==0) {PORTC&=~(1<<PORTC0);PORTC&=~(1<<PORTC1);PORTC&=~(1<<PORTC2);PORTC&=~(1<<PORTC3);PORTB&=~(1<<PORTB0);PORTB|=(1<<PORTB1); segchar(R1);}
	if (n_count==1) {PORTC&=~(1<<PORTC0);PORTC&=~(1<<PORTC1);PORTC&=~(1<<PORTC2);PORTC&=~(1<<PORTC3);PORTB&=~(1<<PORTB1);PORTB|=(1<<PORTB0); segchar(R2);}
	if (n_count==2) {PORTC&=~(1<<PORTC0);PORTC&=~(1<<PORTC1);PORTC&=~(1<<PORTC2);PORTB&=~(1<<PORTB0);PORTB&=~(1<<PORTB1);PORTC|=(1<<PORTC3); segchar(R3);}
	if (n_count==3)	{PORTC&=~(1<<PORTC0);PORTC&=~(1<<PORTC1);PORTC&=~(1<<PORTC3);PORTB&=~(1<<PORTB0);PORTB&=~(1<<PORTB1);PORTC|=(1<<PORTC2); segchar(R4);}
	if (n_count==4)	{PORTC&=~(1<<PORTC0);PORTC&=~(1<<PORTC2);PORTC&=~(1<<PORTC3);PORTB&=~(1<<PORTB0);PORTB&=~(1<<PORTB1);PORTC|=(1<<PORTC1); segchar(R5);}
	if (n_count==5)	{PORTC&=~(1<<PORTC1);PORTC&=~(1<<PORTC2);PORTC&=~(1<<PORTC3);PORTB&=~(1<<PORTB0);PORTB&=~(1<<PORTB1);PORTC|=(1<<PORTC0); segchar(R6);}
	n_count++;
	if (n_count>5) n_count=0;
	
}


void ledprint(unsigned char *number)
{	
	cli();
	R5 = *number%10;
	R6 = *number/10;
	number++;
	R3 = *number%10;
	R4 = *number/10;
	number++;
	R1 = *number%10;
	R2 = *number/10;
	
	
	
	
	
	
	sei();
}


int main(void)
{
	
	
	
	DDRD=0b00001111;
	DDRB=0b00000011;
	DDRC=0b00001111;
	
	PORTD=0b10000000;
	PORTB=0b00000100;
	PORTC=0b00000000;
	
	timer_ini(); 
	_delay_us(15);
	ds3231_init();
	_delay_us(15);


	sei();
	


	//ds3231_write_time(DS3231_24, 15,02,00);
	
//-----------------------------------------//
	
//ебошим настройку часов
//-------------------------------------------------------------------------
// 				if (!(PINB&0b00000100))
// 				{
// 					ds3231_read_time(time);
// 					if (time[0]>=23)
// 					{
// 						time[0]=0;
// 					}
// 					else
// 					{
// 						time[0]++;
// 					}
// 					unsigned char time0_1 [1]= {0};
// 					time0_1 [0]=ds3231_byte(time [0]);
// 					ds3231_write_reg(0x02 ,time0_1[0]);
// 					_delay_ms(1000);
// 				}
// 				
				//-------------------------------------------------------------------------
// 				//ебашим настройку ебаных минут
// 				//-------------------------------------------------------------------------
// 				if (!(PIND&0b00000010))
// 				{
// 					ds3231_read_time(time);
// 					if (time[1]>=59)
// 					{
// 						time[1]=0;
// 					}
// 					else
// 					{
// 						time[1]++;
// 					}
// 					unsigned char time0_1 [1]= {0};
// 					time0_1 [0]=ds3231_byte(time [1]);
// 					ds3231_write_reg(0x01 ,time0_1[0]);
// 					_delay_ms(1000);
// 				}
// 				
// 				else
// 				{
// 					ds3231_read_time(time);
// 				}
// 				//-------------------------------------------------------------------------
// 				//ебашим настройку секунд
// 				
// 				if (!(PIND&0b00000100))
// 				{
// 					ds3231_read_time(time);
// 					if (time[2]>=59)
// 					{
// 						time[2]=0;
// 					}
// 					else
// 					{
// 						time[2]++;
// 					}
// 					unsigned char time0_1 [1]= {0};
// 					time0_1 [0]=ds3231_byte(time [2]);
// 					ds3231_write_reg(0x00 ,time0_1[0]);
// 					_delay_ms(100);
// 				}
// 				
// 				else
// 				{
// 					ds3231_read_time(time);
// 				}
//-------------------------------------------------------------------------
	while (1)
	{

		{
//------------------------------------------------------------------------------------------------	
//Индикация			
			ds3231_read_time(time);
			ledprint(time);
//------------------------------------------------------------------------------------------------	
			// Настройка часов
			if (!(PINB&0b00000100))
			 				{
			 					ds3231_read_time(time);
			 					if (time[0]>=23)
			 					{
			 						time[0]=0;
			 					}
			 					else
			 					{
			 						time[0]++;
			 					}
			 					unsigned char time0_1 [1]= {0};
			 					time0_1 [0]=ds3231_byte(time [0]);
			 					ds3231_write_reg(0x02 ,time0_1[0]);
			 					_delay_ms(500);
			 				}

//------------------------------------------------------------------------------------------------

// 				if (!(PIND&0b10000000))
// 				{
// 					ds3231_read_time(time);
// 					if (time[1]>=59)
// 					{
// 						time[1]=0;
// 					}
// 					else
// 					{
// 						time[1]++;
// 					}
// 					unsigned char time0_1 [1]= {0};
// 					time0_1 [0]=ds3231_byte(time [1]);
// 					ds3231_write_reg(0x01 ,time0_1[0]);
// 					_delay_ms(500);
// 				}							 
							 
			}
			
		}

 	
}





