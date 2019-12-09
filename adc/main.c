#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/avr_gpio.h"
#include "../lib/avr_adc.h"
#include "../lib/avr_timer.h"
#include "../lib/bits.h"
#include "../adc/adc.h"
#include "../uart/uart.h"


/**
  * @brief  Configura hardware do timer0 para IRQ em overflow.
  * @param	Nenhum
  *
  * @retval Nenhum.
  */
void timer1_hardware_init(){

	/* Acesso indireto por struct e bit field: com avr_timer.h */
	TIMER_1->TCCRA = 0;
	TIMER_1->TCCRB = SET(CS12) | SET(CS10);
	TIMER_IRQS->TC0.BITS.TOIE = 1;
}



int main(){

	GPIO_B->DDR = 0xFF;
	/* Obtem o stream de depuração */
	FILE *debug = get_usart_stream();

	/* Inicializa hardware da USART */
	USART_Init(B9600);

	/* Inicializa o converor AD */
	adc_init();

	timer1_hardware_init();

	/* Ativa todos IRQs */
	sei();

		while(1){
			uint8_t i =0;
			fprintf(debug, "ADC0=%d\n", valor_adc(i));
			_delay_ms(500);
			i++;
			fprintf(debug, "ADC1=%d\n", valor_adc(i));
		    _delay_ms(500);
		}
}

ISR(TIMER1_OVF_vect){

}
