/*
 * GameButtonsGenius.c
 *
 */ 

#include <avr/io.h>
#include "GameButtonsGenius.h"

void GameButtonsInit(){
	BOTOES_CONTROLE = 0x00;		//Configura as interrupções
	BOTOES_SELECT &= ~(0xFF);
	/* Seleciona as portas de interrupção */
	BOTOES_SELECT = (1<<BOTAO_Y_PIN)|(1<<BOTAO_B_PIN)|(1<<BOTAO_G_PIN)|(1<<BOTAO_R_PIN);
}