
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "lib/bits.h"
#include "uart/uart.h"
#include "pwm/motor.h"


int main(){

	uint8_t data;

	FILE *debug = get_usart_stream();

	/* Inicializa hardware da USART */
	USART_Init(B9600);

	sei();

	while(1){
		data = USART_rx();
		if( data == 'F'){
			fprintf(debug, "%c\n", data);
			front(200);
		}
		if( data == 'B'){
			fprintf(debug, "%c\n", data);
			rear(200);
		}
		if( data == 'L'){
			fprintf(debug, "%c\n", data);
			left(200);
		}
		if( data == 'R'){
			fprintf(debug, "%c\n", data);
			right(200);
		}
	}

		return 0;
}
