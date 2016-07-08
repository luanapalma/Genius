/*
 * InterfaceGenius.h
 *
 */ 


#ifndef INTERFACEGENIUS_H_
#define INTERFACEGENIUS_H_

/**
	@brief Função que exibe a tela do menu principal no display.
*/
void ExibeMenuPrincipal();
/**
	@brief Função que exibe a tela de confirmação de jogo no display.
*/
void ExibeJogar();
/**
	@brief Função que exibe a tela de preparação de jogo no display.
*/
void ExibeGenius();
/**
	@brief Função que exibe a tela de fim de jogo no display.
*/
void ExibeGameOver(uint8_t  pontuacao);
/**
	@brief Função que exibe o layout inicial da tela de inserção de nome no display.
*/
void ExibeTelaName();
/**
	@brief Função que exibe layout inicial do Ranking no display.
*/
void ExibeTelaRanking();

#endif /* INTERFACEGENIUS_H_ */