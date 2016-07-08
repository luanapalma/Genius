/*
 * LCDGenius.h
 *
 */ 


#ifndef LCDGENIUS_H_
#define LCDGENIUS_H_

/**
	@def lcd_D7_port
	@brief Definição da porta utilizada pelo pino D7.
*/
#define lcd_D7_port     PORTH
/**
	@def lcd_D7_bit
	@brief Definição do bit que o pino D7 ocupa na porta declarada.
*/
#define lcd_D7_bit      DDH4
/**
	@def lcd_D7_ddr
	@brief Registrador de controle da porta do pino D7.
*/
#define lcd_D7_ddr      DDRH
/**
	@def lcd_D6_port
	@brief Definição da porta utilizada pelo pino D6.
*/
#define lcd_D6_port     PORTH
/**
	@def lcd_D6_bit
	@brief Definição do bit que o pino D6 ocupa na porta declarada.
*/
#define lcd_D6_bit      DDH3
/**
	@def lcd_D6_ddr
	@brief Registrador de controle da porta do pino D6.
*/
#define lcd_D6_ddr      DDRH
/**
	@def lcd_D5_port
	@brief Definição da porta utilizada pelo pino D5.
*/
#define lcd_D5_port     PORTE
/**
	@def lcd_D5_bit
	@brief Definição do bit que o pino D5 ocupa na porta declarada.
*/
#define lcd_D5_bit      DDE3
/**
	@def lcd_D5_ddr
	@brief Registrador de controle da porta do pino D5.
*/
#define lcd_D5_ddr      DDRE
/**
	@def lcd_D4_port
	@brief Definição da porta utilizada pelo pino D4.
*/
#define lcd_D4_port     PORTG
/**
	@def lcd_D4_bit
	@brief Definição do bit que o pino D4 ocupa na porta declarada.
*/
#define lcd_D4_bit      DDG5
/**
	@def lcd_D4_ddr
	@brief Registrador de controle da porta do pino D4.
*/
#define lcd_D4_ddr      DDRG
/**
	@def lcd_E_port
	@brief Definição da porta utilizada pelo pino Enable.
*/
#define lcd_E_port      PORTH
/**
	@def lcd_E_bit
	@brief Definição do bit que o pino Enable ocupa na porta declarada.
*/
#define lcd_E_bit       DDH6
/**
	@def lcd_E_ddr
	@brief Registrador de controle da porta do pino Enable.
*/
#define lcd_E_ddr       DDRH
/**
	@def lcd_D7_port
	@brief Definição da porta utilizada pelo pino Register Select.
*/
#define lcd_RS_port     PORTH
/**
	@def lcd_RS_bit
	@brief Definição do bit que o pino Register Select ocupa na porta declarada.
*/
#define lcd_RS_bit      DDH5
/**
	@def lcd_RS_ddr
	@brief Registrador de controle da porta do pino Register Select.
*/
#define lcd_RS_ddr      DDRH

/**
	@def lcd_LineOne
	@brief Definição do offset relativo ao início da primeira linha do display.
*/
#define lcd_LineOne     0x00
/**
	@def lcd_LineTwo
	@brief Definição do offset relativo ao início da segunda linha do display.
*/
#define lcd_LineTwo     0x40

/* Instruções do LCD */
/**
	@def lcd_Clear
	@brief Instrução que substitui todos os caracteres por 'espaços' ASCII.
*/
#define lcd_Clear           0b00000001
/**
	@def lcd_Home
	@brief Instrução que retorna o cursor para a primeira posição da primeira linha.
*/
#define lcd_Home            0b00000010
/**
	@def lcd_EntryMode
	@brief Instrução que move o cursor da esquerda para a direita quando há leitura/escrita.
*/
#define lcd_EntryMode       0b00000110
/**
	@def lcd_DisplayOff
	@brief Instrução que desliga o display.
*/
#define lcd_DisplayOff      0b00001000
/**
	@def lcd_DisplayOn
	@brief Instrução que configura o display ligado, cursor desligado e caractere estático.
*/
#define lcd_DisplayOn       0b00001100
/**
	@def lcd_FunctionReset
	@brief Instrução que reseta o LCD.
*/
#define lcd_FunctionReset   0b00110000
/**
	@def lcd_FunctionSet4bit
	@brief Instrução que configura o LCD para receber dados de 4 bits, exibir fonte 5x7 e saber que possui duas linhas.
*/
#define lcd_FunctionSet4bit 0b00101000
/**
	@def lcd_SetCursor
	@brief Instrução que seta a posição do cursor.
*/
#define lcd_SetCursor       0b10000000

/**
	@brief Função que escreve 4 bits nos pinos do LCD (D7,D6,D5 e D4).
*/
void lcd_write(uint8_t);
/**
	@brief Função que envia uma instrução para o LCD.
*/
void lcd_write_instruction(uint8_t);
/**
	@brief Função que escreve um caractere na tela do LCD.
*/
void lcd_write_character(uint8_t);
/**
	@brief Função que escreve uma string na tela do LCD.
*/
void lcd_write_string(uint8_t *);
/**
	@brief Função que faz a configuração inicial do LCD.
*/
void lcd_init(void);

#endif /* LCDGENIUS_H_ */