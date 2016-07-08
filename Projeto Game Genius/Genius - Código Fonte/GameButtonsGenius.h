/*
 * GameButtonsGenius.h
 *
 */ 


#ifndef GAMEBUTTONSGENIUS_H_
#define GAMEBUTTONSGENIUS_H_


/**
	@def BOTOES_CONTROLE
	@brief Registrador utilizado no controle de interrupções externas.
*/
#define BOTOES_CONTROLE EICRA
/**
	@def BOTOES_SELECT
	@brief Registrador que seleciona quais interrupções externas serão ativadas.
*/
#define BOTOES_SELECT EIMSK
/**
	@def BOTAO_Y_PIN
	@brief Porta do processador utilizada na interrupção do botão amarelo.
*/
#define BOTAO_Y_PIN INT0
/**
	@def BOTAO_B_PIN
	@brief Porta do processador utilizada na interrupção do botão azul.
*/
#define BOTAO_B_PIN INT1
/**
	@def BOTAO_G_PIN
	@brief Porta do processador utilizada na interrupção do botão verde.
*/
#define BOTAO_G_PIN INT2
/**
	@def BOTAO_R_PIN
	@brief Porta do processador utilizada na interrupção do botão vermelho.
*/
#define BOTAO_R_PIN INT3
/**
	@def BOTAO_Y_FUNCT
	@brief Redefinição do nome da função de interrupção para a porta do botão amarelo.
*/
#define BOTAO_Y_FUNCT INT0_vect
/**
	@def BOTAO_B_FUNCT
	@brief Redefinição do nome da função de interrupção para a porta do botão azul.
*/
#define BOTAO_B_FUNCT INT1_vect
/**
	@def BOTAO_G_FUNCT
	@brief Redefinição do nome da função de interrupção para a porta do botão verde.
*/
#define BOTAO_G_FUNCT INT2_vect
/**
	@def BOTAO_R_FUNCT
	@brief Redefinição do nome da função de interrupção para a porta do botão vermelho.
*/
#define BOTAO_R_FUNCT INT3_vect

/**
	@brief Função que configura as interrupções ligadas ao botões e as portas as quais estes se ligam.
*/
void GameButtonsInit();


#endif /* GAMEBUTTONSGENIUS_H_ */