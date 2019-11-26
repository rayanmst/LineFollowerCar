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
#include "avr_usart.h"

int main(void) {
	FILE *debug = get_usart_stream();

	USART_Init(B9600);
	sonar_init();
	sei();

	while(1)
	{
		fprintf(debug, "Dist: %d\n\r", get_dist());
		_delay_ms(1000);
	}
	return 0;
}
