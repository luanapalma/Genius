/*
 * TimerAndADCGenius.c
 *
 */ 

#include <avr/io.h>
#include "TimerAndADCGenius.h"

void ADCInit(){
	ADMUX = 0x0F;							//Usa o canal em 0V.
	ADMUX |= (1 << REFS0);					//Usa AVcc como referencia.
	ADMUX &= ~(1 << ADLAR);					//Resolução de 10 bits, com alinhamento à direita.
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);	//Ajusta clock do ADC para 125 kHz (1MHz com prescala de 8).
}
void TimerInit(){
	/* Configuração dos três registradores com seus respectivos comandos. */
	TIMER_RAND_CTRL_A = NORMAL_MODE_OPERATION; 
	TIMER_RAND_CTRL_B = NO_PREESCALER;
	TIMER_RAND_MASK |= OVF_INT_ENABLE;
}
/**
 * @return Valor correspondente ao botão pressionado.
 */

uint16_t lerBotaoMenu()
{
	uint8_t canal = 0;
	uint16_t ADC_res;
	ADMUX |= (canal & 0x0F);			//Define o canal.
	ADCSRA |= (1 << ADEN);				//Habilita o ADC.
	ADCSRA |= (1 << ADSC);				//Inicia conversao do ADC
	while(ADCSRA && (1 << ADSC)==1);	//Aguarda fim da conversao.
	ADC_res = ADCL;
	ADC_res = (ADCH << 8) + ADC_res;	//Leitura do resultado.
	ADMUX &= ~0x0F;						//Retorna para o canal 0V.
	
	/*	A comparação precisa aqui precisa seguir 
		uma ordem crescente para que nenhum botão
		sombreado por outro.						*/
	
	if(ADC_res<RIGHT)					//Valor da porta menor que o limite superior de RIGHT.
		return RIGHT;
	if(ADC_res<UP)						//Valor da porta menor que o limite superior de UP.
		return UP;
	if(ADC_res<DOWN)					//Valor da porta menor que o limite superior de DOWN.
		return DOWN;
	if(ADC_res<LEFT)					//Valor da porta menor que o limite superior de LEFT.
		return LEFT;
	if(ADC_res<CANCEL)					//Valor da porta menor que o limite superior de CANCEL.
		return CANCEL;
	if(ADC_res>=CANCEL)					//Valor da porta maior que qualquer outro valor testado.
		return NONE;
	
	return 0;
}