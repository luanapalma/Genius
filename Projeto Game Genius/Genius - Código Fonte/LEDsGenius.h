/*
 * LEDsGenius.h
 *
 */ 


#ifndef LEDSGENIUS_H_
#define LEDSGENIUS_H_

/**
	@def PORTA_LEDS
	@brief Definição da porta do processador utilizada pelos LEDs.
*/
#define PORTA_LEDS PORTK
/**
	@def PORTA_LEDS_CONTROLE
	@brief Registrador de controle da porta utilizada pelos LEDs.
*/
#define PORTA_LEDS_CONTROLE DDRK
/**
	@def LED_Y_PIN
	@brief Definição do pino da porta utilizado pelo LED amarelo.
*/
#define LED_Y_PIN DDK7
/**
	@def LED_B_PIN
	@brief Definição do pino da porta utilizado pelo LED azul.
*/
#define LED_B_PIN DDK6
/**
	@def LED_G_PIN
	@brief Definição do pino da porta utilizado pelo LED verde.
*/
#define LED_G_PIN DDK5
/**
	@def LED_R_PIN
	@brief Definição do pino da porta utilizado pelo LED vermelho.
*/
#define LED_R_PIN DDK4
/**
	@def DELAY_BLINK 
	@brief Definição do tempo, em ms, que um LED deve piscar durante o jogo.
*/
#define DELAY_BLINK 700
/**
	@def DELAY_PISCA
	@brief Definição do tempo, em ms, que os LEDs devem piscar quando chamada a função PiscaLeds.
*/
#define DELAY_PISCA 500
/**
	@def QUANT_PISCA
	@brief Quantidade de vezes que os LEDs devem piscar quando chamada a função PiscaLeds.
*/
#define QUANT_PISCA 3
/**
	@brief Função que pisca os 4 LEDs ao mesmo tempo.
*/
void PiscaLeds();
/**
	@brief Função que pisca o LED amarelo.
*/
void YBlink();
/**
	@brief Função que pisca o LED azul.
*/
void BBlink();
/**
	@brief Função que pisca o LED verde.
*/
void GBlink();
/**
	@brief Função que pisca o LED vermelho.
*/
void RBlink();
/**
	@brief Função que configura os pinos utilizados pelos LEDs.
*/
void LEDsInit();

#endif /* LEDSGENIUS_H_ */