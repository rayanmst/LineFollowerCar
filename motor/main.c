#include "motor.h"
#include <avr/interrupt.h>

#include <stdint.h>
#include <avr/pgmspace.h>

int main(){
	/* Configura timer em modo PWM */
	while (1){
		front(200);
		_delay_ms(3000);
		rear(200);
		_delay_ms(3000);
		right(200);
		_delay_ms(3000);
		left(200);
		_delay_ms(3000);
		tank(200, 100);
	}
}
