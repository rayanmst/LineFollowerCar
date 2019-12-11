/*
 * pwm.c
 *
 *  Created on: 4 de out de 2019
 *      Author: Rayan Martins Steinbach
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "bits.h"
#include "avr_gpio.h"
#include "avr_timer.h"
#include "sonar.h"
#include "adc.h"

void carInit() {
	GPIO_B->DDR |= SET(PB3);
	GPIO_D->DDR |= SET(PD3) | SET(PD5) | SET(PD6);

	TIMER_0->TCCRB = SET(CS01)  | SET(CS00);
	TIMER_2->TCCRB = SET(CS22);

	sonar_init();
	adc_init();
}

void goBack(uint8_t imSpeed) {
	/* Timer0 configuration:
	 * 						COM0A0 and COM0A1 : Inverting mode
	 * 						COM0B1			  : Non-inverting mode
	 */

	TIMER_0->TCCRA = SET(WGM01) | SET(WGM00) | SET(COM0A1) | SET(COM0A0) | SET(COM0B1);

	/* Timer2 configuration:
	 * 						COM2A0 and COM2A1 : Inverting mode
	 * 						COM2B1            : Non-inverting mode
	 */
	TIMER_2->TCCRA = SET(WGM21) | SET(WGM20) | SET(COM2A1) | SET(COM2A0) | SET(COM2B1);

	TIMER_0->OCRA = imSpeed;
	TIMER_0->OCRB = imSpeed;
	TIMER_2->OCRA = imSpeed;
	TIMER_2->OCRB = imSpeed;

}

void goAhead(uint8_t imSpeed) {
	/* Timer0 configuration:
	 * 						COM0A1			  : Non-inverting mode
	 * 						COM0B1 and COM0B0 : Inverting mode
	 */
	TIMER_0->TCCRA =  SET(WGM01) | SET(WGM00) | SET(COM0A1) | CLEAR(COM0A0) | SET(COM0B1) | SET(COM0B0);

	/* Timer2 configuration:
	 * 						COM2A1			  : Non-inverting mode
	 * 						COM2B0 and COM2B1 : Inverting mode
	 */
	TIMER_2->TCCRA =  SET(WGM21) | SET(WGM20) | SET(COM2A1) | CLEAR(COM2A0) | SET(COM2B1) | SET(COM2B0);

	TIMER_0->OCRA = imSpeed;
	TIMER_0->OCRB = imSpeed;
	TIMER_2->OCRA = imSpeed;
	TIMER_2->OCRB = imSpeed;
}

void toLeft(uint8_t imSpeed) {
	/* Timer0 configuration:
	 * 						COM0A1			  : Non-inverting mode
	 * 						COM0B1 and COM0B0 : Inverting mode
	 */
	TIMER_0->TCCRA = SET(WGM01) | SET(WGM00) | SET(COM0A1) | CLEAR(COM0A0) | SET(COM0B1) | SET(COM0B0);

	/* Timer2 configuration:
	 * 						COM2A1 and COM2A0 : Inverting mode
	 * 						COM2B1            : Non-inverting mode
	 */
	TIMER_2->TCCRA = SET(WGM21) | SET(WGM20) | SET(COM2A1) | SET(COM2A0)| SET(COM2B1) | CLEAR(COM2B0);

	TIMER_0->OCRA = imSpeed + 20;
	TIMER_0->OCRB = imSpeed + 20;
	TIMER_2->OCRA = imSpeed;
	TIMER_2->OCRB = imSpeed;

}

void toRight(uint8_t imSpeed) {
	/* Timer0 configuration:
	 * 						COM0A1 and COM0A0 : Inverting mode
	 * 						COM0B1            : Non-Inverting mode
	 */
	TIMER_0->TCCRA = SET(WGM01) | SET(WGM00) | SET(COM0A1) | SET(COM0A0) | SET(COM0B1) | CLEAR(COM0B0);

	/* Timer2 configuration:
	 * 						COM2A1            : Non-inverting mode
	 * 						COM2B1 and COM2B0 : Inverting mode
	 */
	TIMER_2->TCCRA =SET(WGM21) | SET(WGM20) | SET(COM2A1) | CLEAR(COM2A0) | SET(COM2B0)| SET(COM2B1);

	TIMER_0->OCRA = imSpeed + 20;
	TIMER_0->OCRB = imSpeed + 20;
	TIMER_2->OCRA = imSpeed;
	TIMER_2->OCRB = imSpeed;
}

void itsTimeToStop(){
	TIMER_0->TCCRA = 0;
	TIMER_0->TCCRB = SET(CS01)  | SET(CS00);
	TIMER_2->TCCRA = 0;
	TIMER_2->TCCRB = SET(CS22);

}

void move(uint8_t imSpeed, uint8_t data) {
	GPIO_B->PORT |= SET(PB4);
	GPIO_D->PORT |= SET(PD7);

	if(get_dist()>2000) {
		if(GPIO_PinTstBit(GPIO_B, PB4) || data == 'L') {
			toLeft(imSpeed);
		}
		else if(GPIO_PinTstBit(GPIO_D, PD7) || data == 'R') {
			toRight(imSpeed);
		}
		else goAhead(imSpeed);
	}
	else {
		itsTimeToStop();
	}
	if(data == 'B') {
				goBack(imSpeed);
	}
}
