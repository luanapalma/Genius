/*
 * LCDGenius.c
 *
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCDGenius.h"

void lcd_init(void)
{
	/* Configuração dos pinos do processador que o LCD utiliza como saída. */
	lcd_D7_ddr |= (1<<lcd_D7_bit);
	lcd_D6_ddr |= (1<<lcd_D6_bit);
	lcd_D5_ddr |= (1<<lcd_D5_bit);
	lcd_D4_ddr |= (1<<lcd_D4_bit);
	lcd_E_ddr |= (1<<lcd_E_bit);
	lcd_RS_ddr |= (1<<lcd_RS_bit);

	_delay_ms(100);									//Delay inicial de 100ms.

	lcd_RS_port &= ~(1<<lcd_RS_bit);				//Seleciona o Instruction Register.
	lcd_E_port &= ~(1<<lcd_E_bit);                  //Coloca E em nível baixo.

	/* Início da sequência de resets do LCD. */
	lcd_write(lcd_FunctionReset);
	_delay_ms(10);

	lcd_write(lcd_FunctionReset);
	_delay_us(200);

	lcd_write(lcd_FunctionReset);
	_delay_us(200);
	/* Fim da sequência de resets. */

	lcd_write(lcd_FunctionSet4bit);					//Configura modo de 4 bits.
	_delay_us(80);

	lcd_write_instruction(lcd_FunctionSet4bit);		//Configura modo, linhas e fonte.
	_delay_us(80);

	lcd_write_instruction(lcd_DisplayOff);			//Desliga o display.
	_delay_us(80);

	lcd_write_instruction(lcd_Clear);				//Limpa a RAM do display.
	_delay_ms(4);

	lcd_write_instruction(lcd_EntryMode);			//Configura o modo de deslocamento.
	_delay_us(80);
	
	lcd_write_instruction(lcd_DisplayOn);			//Liga o display.
	_delay_us(80);
}
/**
 * @param theString[] Array de caracteres a serem escritos no display.
 */
void lcd_write_string(uint8_t theString[])
{
	volatile int i = 0;
	while (theString[i] != 0)	//Loop que escreve a string caractere por caractere até que chegue ao fim desta.
	{
		lcd_write_character(theString[i]);
		i++;
		_delay_us(80);
	}
}
/**
 * @param theData Caractere a ser escrito no display.
 */
void lcd_write_character(uint8_t theData)
{
	lcd_RS_port |= (1<<lcd_RS_bit);					//Seleciona o Data Register.
	lcd_E_port &= ~(1<<lcd_E_bit);					//Coloca Enable em nível baixo.
	lcd_write(theData);								//Escreve a parte alta (4 bits) do caractere.
	lcd_write(theData << 4);						//Escreve a parte baixa (4 bits) do caractere.
}
/**
 * @param theInstruction Instrução a ser enviada para o LCD.
 */
void lcd_write_instruction(uint8_t theInstruction)
{
	lcd_RS_port &= ~(1<<lcd_RS_bit);				//Seleciona o Instruction Register.
	lcd_E_port &= ~(1<<lcd_E_bit);					//Coloca Enable em nível baixo.
	lcd_write(theInstruction);						//Escreve a parte alta (4 bits) da instrução.
	lcd_write(theInstruction << 4);					//Escreve a parte baixa (4 bits) da instrução.
}
/**
 * @param theByte Dado a ser escrito nas portas do LCD. Somente serão utilizados os 4 bits mais significativos.
 */
void lcd_write(uint8_t theByte)
{
	lcd_D7_port &= ~(1<<lcd_D7_bit);                        //Assume o dado é '0'.
	if (theByte & 1<<7) lcd_D7_port |= (1<<lcd_D7_bit);     //Em caso negativo, seta o bit para '1'.

	lcd_D6_port &= ~(1<<lcd_D6_bit);                        //Processo repetido para os outros bits.
	if (theByte & 1<<6) lcd_D6_port |= (1<<lcd_D6_bit);

	lcd_D5_port &= ~(1<<lcd_D5_bit);
	if (theByte & 1<<5) lcd_D5_port |= (1<<lcd_D5_bit);

	lcd_D4_port &= ~(1<<lcd_D4_bit);
	if (theByte & 1<<4) lcd_D4_port |= (1<<lcd_D4_bit);

	/* Este processo dá um pulso em Enable e escreve os 4 bits no LCD. */
	lcd_E_port &= ~(1<<lcd_E_bit);
	_delay_us(1);
	lcd_E_port |= (1<<lcd_E_bit);
	_delay_us(1);
	lcd_E_port &= ~(1<<lcd_E_bit);
	_delay_us(100);                         
}
