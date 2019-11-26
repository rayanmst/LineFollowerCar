/*
 * main.c
 *
 *  Created on: 12 de nov de 2019
 *      Author: rayan
 */

#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "sonar.h"
#include "avr_gpio.h"
#include "avr_usart.h"

int main(void) {
	FILE *debug = get_usart_stream();

	GPIO_B->DDR = 1<<PB5;


	USART_Init(B9600);
	sonar_init();
	sei();

	while(1)
	{
		fprintf(debug, "Dist: %u\n\r", get_dist());
		GPIO_SetBit(GPIO_B,PB5);
		_delay_us(10);
		GPIO_ClrBit(GPIO_B, PB5);
		_delay_ms(1000);
	}
	return 0;
}
