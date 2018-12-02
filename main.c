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

#define set_zero PORTB&=0b11110000
#define set_one set_zero; /
				PORTB|=0b00000001
#define set_two set_zero; /
				PORTB|=0b00000010
#define set_three set_zero; /
				PORTB|=0b00000011
#define set_four set_zero; /
				PORTB|=0b00000100
#define set_five set_zero; /
				PORTB|=0b00000101
#define set_six set_zero; /
				PORTB|=0b00000110
#define set_seven set_zero; /
				PORTB|=0b00000111
#define set_eight set_zero; /
				PORTB|=0b00001000
#define set_nine set_zero; /
				PORTB|=0b00001001

//-----------------------------------------//

#include <avr/io.h>
#include <stdio.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "Libraries/main_init.h"
#include "Libraries/i2c.h"
#include "Libraries/ds3231.h"
#include "libraries/bcd.h"


//-----------------------------------------//
unsigned long i;
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
		
		case 0: set_zero; break;
		case 1: set_one; break;
		case 2: set_two; break;
		case 3: set_three; break;
		case 4: set_four; break;
		case 5: set_five; break;
		case 6: set_six; break;
		case 7: set_nine; break;
		case 8: set_eight; break;
		case 9: set_nine; break;
		
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


void ledprint(unsigned long number)
{	
	cli();
	R1 = number%10;
	R2 = number%100/10;
	R3 = number%1000/100;
	R4 = number%10000/1000;
	R5 = number%100000/10000;
	R6 = number/100000;
	sei();
}
//-----------------------------------------//

int main(void)
{
	
	timer_ini(); 
	_delay_us(15);
	ds3231_init();
	_delay_us(15);
	
	DDRD=0xFF;
	DDRB=0b00001111;
	DDRC=0b00011111;
	PORTD=0b00000000;
	PORTB=0b00001111;
	PORTC=0b00001111;
	sei();
	


	
	
	while (1)
	{
/*		ds3231_read_time(time);*/
/*		ledprint();*/
		//for (i=0;i<1000000;i++)
		{
			ledprint(123456);
			//_delay_ms(100);
		}

 	}
}