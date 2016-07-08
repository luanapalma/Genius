/*
 * TimerAndADCGenius.h
 *
 */ 


#ifndef TIMERANDADCGENIUS_H_
#define TIMERANDADCGENIUS_H_

/**
	@def TIMER_RAND
	@brief Redefine o nome do registrador onde pode ser lido o valor do timer.
*/
#define TIMER_RAND TCNT0
/**
	@def TIMER_RAND_CTRL_A
	@brief Registrador de controle A do timer do processador.
*/
#define TIMER_RAND_CTRL_A TCCR0A
/**
	@def TIMER_RAND_CTRL_B
	@brief Registrador de controle B do timer do processador.
*/
#define TIMER_RAND_CTRL_B TCCR0B
/**
	@def TIMER_RAND_MASK
	@brief Registrador máscara do timer.
*/
#define TIMER_RAND_MASK TIMSK0
/**
	@def OVF_INT_ENABLE
	@brief Comando a ser dado ao controle para que o timer funcione como uma interrupção dada por overflow.
*/
#define OVF_INT_ENABLE 0x01
/**
	@def NO_PREESCALER
	@brief Comando que define que o clock base não receberá divisão para o timer.
*/
#define NO_PREESCALER 0x01
/**
	@def NORMAL_MODE_OPERATION
	@brief Comando que define o modo normal de operação do timer.
*/
#define NORMAL_MODE_OPERATION 0x00
/**
	@def TIMER_RAND_FUNCT
	@brief Redefinição do nome da função de interrupção por overflow do timer.
*/
#define TIMER_RAND_FUNCT TIMER0_OVF_vect

/**
	@def RIGHT
	@brief Limite superior do valor analógico que representa botão direito do menu.
*/
#define RIGHT 50
/**
	@def UP
	@brief Limite superior do valor analógico que representa botão superior do menu.
*/
#define UP 195
/**
	@def DOWN
	@brief Limite superior do valor analógico que representa botão inferior do menu.
*/
#define DOWN 380
/**
	@def LEFT
	@brief Limite superior do valor analógico que representa botão esquerdo do menu.
*/
#define LEFT 555
/**
	@def CANCEL
	@brief Limite superior do valor analógico que representa botão select do menu.
*/
#define CANCEL 790
/**
	@def NONE
	@brief Valor analógico representativo para nenhum botão pressionado.
*/
#define NONE 1000
/**
	@brief Função que inicializa o conversor A/D
*/
void ADCInit();
/**
	@brief Função que configura o timer.
*/
void TimerInit();
/**
	@brief Função que lê o valor analógico da porta dos botões de menu e retorna o valor correspondente a UP, DOWN, LEFT, RIGHT, CANCEL ou NONE.
*/
uint16_t lerBotaoMenu();

#endif /* TIMERANDADCGENIUS_H_ */