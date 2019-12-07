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

#include "pwm.h"
#include "avr_gpio.h"
#include "uart.h"

int main(void) {
	uint8_t data = 0;

	GPIO_B->DDR = 1<<PB5;

	USART_Init(B38400);
	pwmInit();
	sei();

	while(1)
	{
		GPIO_SetBit(GPIO_B,PB5);
		_delay_us(10);
		GPIO_ClrBit(GPIO_B, PB5);
		//data = USART_rx();
		move(200, data);
	}
	return 0;
}
