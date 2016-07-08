/*
 * InterfaceGenius.c
 *
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCDGenius.h"

/**
	@brief Função auxiliar que limpa a tela do display e posiciona o cursor na primeira posição da primeira linha.
*/
void LimpaTela(){
	lcd_write_instruction(lcd_Clear);
	_delay_us(2000);
	lcd_write_instruction(lcd_SetCursor|lcd_LineOne);
	_delay_us(80);
}

void ExibeMenuPrincipal(){
	uint8_t menu[] = "      Menu";
	uint8_t playRanking[] = "<-Play Ranking->";
	LimpaTela();
	lcd_write_string(menu);
	lcd_write_instruction(lcd_SetCursor|lcd_LineTwo);
	_delay_us(80);
	lcd_write_string(playRanking);
}


void ExibeJogar(){
	uint8_t play[] = "     Play?";
	uint8_t yesNo[] = "<-Yes       No->";
	LimpaTela();
	lcd_write_string(play);
	lcd_write_instruction(lcd_SetCursor|lcd_LineTwo);
	_delay_us(80);
	lcd_write_string(yesNo);
}
/**
 * @param pontuacao Pontuação final do jogador a ser exibida na tela.
*/
void ExibeGameOver(uint8_t pontuacao){
	uint8_t gameOver[] = "   Game Over";
	uint8_t strScore[] = "  Score - ";
	uint8_t dig1Score = (pontuacao/100);							//Separa o algarismo de centena da pontuação.
	uint8_t dig2Score = ((pontuacao-(dig1Score*100))/10);			//Separa o algarismo de dezena da pontuação.
	uint8_t dig3Score = (pontuacao-(dig1Score*100)-(dig2Score*10));	//Separa o algarismo de unidade da pontuação.
	dig1Score+=48;													//O offset de um número em relação ao valor do seu
	dig2Score+=48;													//caractere em ASCII é 48.
	dig3Score+=48;
	LimpaTela();
	lcd_write_string(gameOver);
	lcd_write_instruction(lcd_SetCursor|lcd_LineTwo);
	_delay_us(80);
	lcd_write_string(strScore);
	lcd_write_character(dig1Score);
	lcd_write_character(dig2Score);
	lcd_write_character(dig3Score);
}

void ExibeGenius(){
	uint8_t genius[] = "     Genius";
	uint8_t tres[] = " 3"; //1
	uint8_t dois[] = "   2";//3
	uint8_t um[] = "   1";//3
	uint8_t go[] = "   GO!";//2
	LimpaTela();
	lcd_write_string(genius);
	lcd_write_instruction(lcd_SetCursor|lcd_LineTwo);	//Os delays entre escritas servem 
	_delay_ms(800);										//para o jogador ter a sensação
	lcd_write_string(tres);								//de uma contagem regressiva.
	_delay_ms(800);
	lcd_write_string(dois);
	_delay_ms(800);
	lcd_write_string(um);
	_delay_ms(800);
	lcd_write_string(go);
}

void ExibeTelaName(){
	uint8_t nameMenu[] = "      Name";
	uint8_t endName[] = "        [end]";
	LimpaTela();
	lcd_write_string(nameMenu);
	lcd_write_instruction(lcd_SetCursor|lcd_LineTwo);
	_delay_us(80);
	lcd_write_string(endName);
	lcd_write_instruction(lcd_SetCursor|lcd_LineTwo+2);
	_delay_us(80);
}

void ExibeTelaRanking(){
	uint8_t rankNameScore[] = "Rank Name Score";
	LimpaTela();
	lcd_write_string(rankNameScore);
}