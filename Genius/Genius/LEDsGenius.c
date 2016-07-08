/*
 * LEDsGenius.c
 *
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "LEDsGenius.h"

void YBlink()
{
	PORTA_LEDS |=(1<<LED_Y_PIN);	//Acende
	_delay_ms(DELAY_BLINK);
	PORTA_LEDS &=~(1<<LED_Y_PIN);	//Apaga
}

void BBlink()
{
	PORTA_LEDS |=(1<<LED_B_PIN);	//Acende
	_delay_ms(DELAY_BLINK);
	PORTA_LEDS &=~(1<<LED_B_PIN);	//Apaga
}
void GBlink()
{
	PORTA_LEDS |=(1<<LED_G_PIN);	//Acende
	_delay_ms(DELAY_BLINK);
	PORTA_LEDS &=~(1<<LED_G_PIN);	//Apaga
}
void RBlink()
{
	PORTA_LEDS |=(1<<LED_R_PIN);	//Acende
	_delay_ms(DELAY_BLINK);
	PORTA_LEDS &=~(1<<LED_R_PIN);	//Apaga
}
void LEDsInit()
{
	/* Configura como saída os pinos utilizados pelos LEDs. */
	PORTA_LEDS_CONTROLE = (1<<LED_Y_PIN)|(1<<LED_B_PIN)|(1<<LED_G_PIN)|(1<<LED_R_PIN);
}
void PiscaLeds()
{
	uint8_t i;
	for(i = 0; i < QUANT_PISCA; i++){
		/* Acende todos os LEDs. */
		PORTA_LEDS |=(1<<LED_Y_PIN);
		PORTA_LEDS |=(1<<LED_B_PIN);
		PORTA_LEDS |=(1<<LED_G_PIN);
		PORTA_LEDS |=(1<<LED_R_PIN);
		_delay_ms(DELAY_PISCA);
		/* Apaga todos os LEDs. */
		PORTA_LEDS &=~(1<<LED_Y_PIN);
		PORTA_LEDS &=~(1<<LED_B_PIN);
		PORTA_LEDS &=~(1<<LED_G_PIN);
		PORTA_LEDS &=~(1<<LED_R_PIN);
		_delay_ms(DELAY_PISCA);
	}
}