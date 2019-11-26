/*
 * sonar.c
 *
 *  Created on: 12 de nov de 2019
 *      Author: rayan
 */

#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "avr_timer.h"
#include "avr_gpio.h"
#include "sonar.h"
#include "bits.h"

volatile uint32_t dist = 0, inicio;
volatile uint8_t estouros = 0;

void sonar_init() {
	TIMER_1->TCCRA = 0;
	TIMER_1->TCCRB = SET(ICES1) | SET(CS11);
	TIMSK1 = SET(ICIE1) | SET(TOIE1);
}

uint32_t get_dist(){
	return dist/2;
}

ISR(TIMER1_CAPT_vect){
	CPL_BIT(TIMER_1->TCCRB, ICES1);
	if(!TST_BIT(TIMER_1->TCCRB, ICES1)){
		inicio = TIMER_1->ICR;
		estouros = 0;
	} else if(estouros == 0)
		dist = (TIMER_1->ICR - inicio);
	else if(estouros == 1){
		dist = (1<<16) + TIMER_1->ICR - inicio;
		estouros = 0;
	}
	else {
		estouros = 0;
		dist = 65000;
	}

}

ISR(TIMER1_OVF_vect){
	estouros ++;
}
