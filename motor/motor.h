#ifndef MOTOR_H
#define MOTOR_H

#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "lib/bits.h"
#include "lib/avr_timer.h"
#include "lib/avr_gpio.h"

void rear (uint8_t v);
void front (uint8_t v);
void tank (uint8_t v1, uint8_t v2);
void right (uint8_t v);
void left (uint8_t v);
void test (uint8_t v1, uint8_t v2);

#endif
