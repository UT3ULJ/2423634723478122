/*
 * Timer indikator.c
 *
 * Created: 14.10.2017 19:39:11
 * Author : Vega
 */ 

// 8   7   6   5   4   3   2   1
// A | B | C | D | E | F | G | DP | Ob


#define F_CPU 1000000UL

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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//-----------------------------------------//
unsigned int i;
unsigned char R1=0, R2=0, R3=0, R4=0;
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
	
	TCCR1B |= (1<<WGM12);        // Установка режима СТС - сброс по совпадению
	TIMSK |= (1<<OCIE1A);          // Установка бита прерывания 1 счетчика по свопадению с OCR1A (H L)
	//0000111101000010
	//111001001101111000
	OCR1AH = 0b00001111;       // - старшие биты - Записываем число для сравнения 16 бит + нижняя строчка
	OCR1AL = 0b01000010;       // - младшие биты - F_CPU/256=3906 , в бинарном формате - 00001111-01000010    11110100 0010010
	TCCR1B |= (1<<CS10);              //  Устанавливаем делитель 256    - 1 000 000 / 3906 = 256
	
	}
	
//-----------------------------------------//


//-----------------------------------------//

unsigned char n_count=0;


//-----------------------------------------//

ISR (TIMER1_COMPA_vect)
{
	if (n_count==0) {PORTB&=~(1<<PORTB0);PORTB&=~(1<<PORTB1);PORTB&=~(1<<PORTB2);PORTB|=(1<<PORTB4); segchar(R1);}
	if (n_count==1)	{PORTB&=~(1<<PORTB0);PORTB&=~(1<<PORTB1);PORTB&=~(1<<PORTB4);PORTB|=(1<<PORTB2); segchar(R2);}
	if (n_count==2)	{PORTB&=~(1<<PORTB0);PORTB&=~(1<<PORTB2);PORTB&=~(1<<PORTB4);PORTB|=(1<<PORTB1); segchar(R3);}
	if (n_count==3)	{PORTB&=~(1<<PORTB1);PORTB&=~(1<<PORTB2);PORTB&=~(1<<PORTB4);PORTB|=(1<<PORTB0); segchar(R4);}
	n_count++;
	if (n_count>4) n_count=0;
	
}

//-----------------------------------------//

void ledprint(unsigned int number)
{
	R1 = number%10;
	R2 = number%100/10;
	R3 = number%1000/100;
	R4 = number/1000;
}
//-----------------------------------------//

int main(void)
{

	
	unsigned char buttondeb=0, butstatus=0;
	
	timer_ini(); 
	
	DDRD=0xFF;
	DDRB=0b00001111;
	DDRC=0b10011111;
	PORTD=0b00000000;
	PORTB=0b01001111;
	PORTC=0b00011111;
	i=0;
	sei();
	
	while (1)
	{
		for (i=0;i<10000;i++)
		{
			while (butstatus==0)
			{
				
						if (!(PINB&0b01000000))
						{
							if (buttondeb<5)
							{
								buttondeb++;
							}
							else
							{
								
								i=0;
								butstatus=1;
								
							}
							
						}
						else
						{
							if (buttondeb>0)
							{
								buttondeb--;
							}
							else
							{
								
								butstatus=1;
								
							}
						}
				
			}
			ledprint(i);
			_delay_ms(1000);
			butstatus=0;
		}
		

	
	
	
	
 	}
}
