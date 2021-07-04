/*
 * unit7-lesson2.c
 *
 * Created: 6/30/2021 8:56:08 PM
 * Author : Darsh
 */ 

#include <avr/io.h>
#define  F_CPU 1000000UL
#include <util/delay.h>
#include "LCD.h"

int main(void)
{
	s_LCD_Config_t MYLCD ={
		{
			(unsigned char *)&PORTC,
			(unsigned char *)&DDRC,
			(unsigned char *)&PINC,
			2,5,7
		},
		{
			(unsigned char *)&PORTD,
			(unsigned char *)&DDRD,
			(unsigned char *)&PIND,
			4,7
		},
		NOSHIFT_INCREMENT,
		ONDISP_BLINKCURSOR,
		FOURBIT_2LINE_10DOT
		
	};
	LCD_init(&MYLCD);
	_delay_ms(50);
	//int i;
	unsigned char mychar[11]={16,24,28,30,31,30,28,24,16,31,4};
	LCD_buildcustom(&MYLCD,0,mychar);
	LCD_buildcustom(&MYLCD,1,mychar);
	LCD_clearscreen(&MYLCD);
    /* Replace with your application code */
    while (1) 
	{
		_delay_ms(100);
    }
}

