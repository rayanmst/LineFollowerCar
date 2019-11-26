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
	SONAR_PORT->DDR |= SET(SONAR_ENABLE_PIN);
	TIMER_1->TCCRA = 0;
	TIMER_1->TCCRB = SET(ICES1) | SET(CS11);
	TIMSK1 = SET(ICIE1) | SET(TOIE1);
}

uint64_t get_dist(){
	if(dist<811) {
		return dist;
	}
	else return 911;
}

ISR(TIMER1_CAPT_vect){
	CPL_BIT(TIMER_1->TCCRB, ICES1);
	if(TST_BIT(TIMER_1->TCCRB, ICES1)){
		inicio = TIMER_1->ICR;
	} else if(estouros == 0)
		dist = (TIMER_1->ICR - inicio)/58;
	else {
		dist = (1<<16)/58 + (TIMER_1->ICR - inicio)/58;
		estouros = 0;
	}

}

ISR(TIMER1_OVF_vect){
	estouros = 1;
}
