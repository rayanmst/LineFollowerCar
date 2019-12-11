#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/avr_gpio.h"
#include "../lib/avr_adc.h"
#include "../lib/avr_timer.h"
#include "../lib/bits.h"
#include "adc.h"

volatile uint16_t adc[2];
volatile uint8_t aux_adc=0;

void adc_init(){

	/* Ref externa no pino AVCC com capacitor de 100n em VREF.
	 * Habiltiação inicial no Canal 0 */
	ADCS->AD_MUX = SET(REFS0);
	/* Habilita AD:
	 * Conversão contínua
	 * IRQ ativo
	 * Prescaler de 128 */
	ADCS->ADC_SRA = SET(ADEN)  |	//ADC Enable
					SET(ADSC)  | 	// ADC Start conversion
					SET(ADATE) |	// ADC Auto Trigger borda subida
					SET(ADPS0) | SET(ADPS1) | SET(ADPS2) | //ADPS[0..2] AD Prescaler selection 64
					SET(ADIE); 		//AD IRQ ENABLE

	/* Auto trigger in timer1 overflow */
	ADCS->ADC_SRB = SET(ADTS2) | SET(ADTS1);

	/* Desabilita hardware Analógico de PC0,PC1 */
	DIDR0 = SET(ADC0D) | SET(ADC1D);

}


ISR(ADC_vect)
{
    ADMUX &= 0xF0;
    ADMUX |= aux_adc; //selecionando os canais
    adc[aux_adc] = ADC;  //lê canal
	aux_adc++;
    aux_adc = aux_adc & 0x1; // contar no máximo até 1
}

void test_bat() {
	if( adc[1] == 478 || adc[0] - adc[1] == 478 )
		itsTimeToStop();
}


uint16_t valor_adc(uint8_t i){
	return adc[i];
}
