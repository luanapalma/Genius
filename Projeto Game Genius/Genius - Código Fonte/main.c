/**
  \mainpage Game Genius
  \author Luana Palma & Deivis Strieder
  \version 1.0
  \date Julho de 2016
 */

/**
	@def F_CPU
	@brief Definição da frequência da CPU para utilização da biblioteca delay.h
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>

#include "LCDGenius.h"
#include "LEDsGenius.h"
#include "InterfaceGenius.h"
#include "GameButtonsGenius.h"
#include "TimerAndADCGenius.h"
#include "MemoriaGenius.h"

/**
	@def MAX_SEQ
	@brief Tamanho máximo de elementos na sequência de luzes.
*/
#define MAX_SEQ 100

/**
	@def Y_NUM
	@brief Definição do número correspondente à cor amarela.
*/
#define Y_NUM 1

/**
	@def B_NUM
	@brief Definição do número correspondente à cor azul.
*/
#define B_NUM 2

/**
	@def G_NUM
	@brief Definição do número correspondente à cor verde.
*/
#define G_NUM 3

/**
	@def R_NUM
	@brief Definição do número correspondente à cor vermelha.
*/
#define R_NUM 4

/**
	@def POSICOES_RANKING
	@brief Definição do número total de posições no ranking.
*/
#define POSICOES_RANKING 10

/**
	@def TAM_LINHA
	@brief Definição da quantidade de posições da memória ocupadas por uma linha do ranking.
*/
#define TAM_LINHA 4

/**
	@def ULTIMA_LINHA
	@brief Definição do endereço inicial na memória da última linha de ranking.
*/
#define ULTIMA_LINHA (POSICOES_RANKING-1)*TAM_LINHA

/**
	@def A
	@brief Definição do valor da letra A referente à tabela ASCII.
*/
#define A 65 

/**
	@def Z
	@brief Definição do valor da letra Z referente à tabela ASCII.
*/
#define Z 90 

/**
	@def PRIM_CARACT_NOME
	@brief Definição do espaçamento inicial do nome no estado Insere Nome.
*/
#define PRIM_CARACT_NOME 3 

/**
	@brief Tipo utilizado para definir o nome dos estados da FSM.
*/
typedef enum{
	sMenuInicial = 0, sRanking, sInsereNome, sConfirmaJogo, sPlayGenius, sGameOver
}States;

/**
	@brief Definição do tipo ponteiro de função.
*/
typedef void (*Action)(void);

/**
	@brief Tipo de estrutura que comporta as informações de uma posição de ranking.
*/
typedef struct Posicao{
	/** @brief Campo utilizado para o nome. */
	uint8_t pName[3];
	/** @brief Campo utilizado para a pontuação. */
	uint8_t pScore;
}pos;


/**
	@brief Estrutura que representa a máquina de estados do jogo.
*/
struct StateMachine{
	/** @brief Variável que guarda o estado atual da FSM. */
	States state;
	/** @brief Vetor de ponteiros de função que recebem os ponteiros das funções referentes aos estados. */
	Action action[6];
}sm;

/** @brief Variável que guarda nome do jogador. */
uint8_t name[3];
/** @brief Variável que guarda a pontuação do jogador. */
uint8_t score = 0;
/** @brief Variável que guarda a sequência de luzes durante o jogo. */
uint8_t sequencia[MAX_SEQ];
/** @brief Variável que guarda a posição da sequência a ser verificada. */
uint8_t indexSequencia = 0;
/** @brief Variável que o número do botão de jogo pressionado. */
uint8_t numBotaoPressionado = 0;
/** @brief Flag que indica se ouve uma interrupção causada por um botão de jogo. */
bool botaoPressionado = false;

/** 
	@brief Função que inicializa a máquina de estados configurando os ponteiros de função e o estado inicial.
*/
void InitStateMachine();
/** 
	@brief Função que inicializa os periféricos e portas.
*/
void IniciaGenius();

/** 
	@brief Função que exibe uma linha de ranking no display.
*/
void PrintLinha(pos pPosicao, uint8_t ind);
/** 
	@brief Função insere um elemento de luz na sequência de jogo.
*/
bool InsereElemento();
/** 
	@brief Função que exibe a sequência de luzes nos LEDs.
*/
void MostraSequencia();


/** 
	@brief Função para o estado Menu Inicial.
*/
void MenuInicial();
/** 
	@brief Função para o estado Ranking.
*/
void Ranking();
/** 
	@brief Função para o estado Insere Nome.
*/
void InsereNome();
/** 
	@brief Função para o estado Confirma Jogo.
*/
void ConfirmaJogo();
/** 
	@brief Função para o estado Play Genius.
*/
void PlayGenius();
/** 
	@brief Função para o estado Game Over.
*/
void GameOver();


/** 
	@brief Função principal.
*/
int main(void)
{
	IniciaGenius();				// Configura os periféricos.
	InitStateMachine();			// Inicializa a máquina de estados.
	while(1)
	{		
		sm.action[sm.state]();	// Roda a máquina de estados 		
	}
	return 0;
}


void IniciaGenius()
{
	
	uint16_t i, endLinha;
	uint8_t nomeNulo[3] = {'X','X','X'};	//Valor "nulo" para todos os nomes.
	
	/* Configuração do display LCD. */	
	lcd_init();
	
	/* Configuração do timer utilizado para gerar um número aleatório. */	
	TimerInit();
	
	/* Configuração do conversor A/D utilizado nos botões de menu. */	
	ADCInit();
	
	/* Configuração das interrupções ligadas aos botões de jogo. */	
	GameButtonsInit();
	
	/* Configuração das portas que acionam os leds. */
	LEDsInit();
	
	/* Escreve ranking nulo na memória. */
	for(i=0;i<POSICOES_RANKING;i++)
	{
		endLinha = i*TAM_LINHA;
		WriteLine(END_INICIAL+endLinha,nomeNulo,0);
	}
}

void InitStateMachine()
{
	sm.state = sMenuInicial;
	sm.action[sMenuInicial] = MenuInicial;
	sm.action[sRanking] = Ranking;
	sm.action[sInsereNome] = InsereNome;
	sm.action[sConfirmaJogo] = ConfirmaJogo;
	sm.action[sPlayGenius] = PlayGenius;
	sm.action[sGameOver] = GameOver;
}


void MenuInicial()
{
	uint16_t opcao;
	ExibeMenuPrincipal();				//Mostra a tela do menu inicial.
	opcao = lerBotaoMenu();				//Tratamento do debounce inicial.
	_delay_ms(500);						//
	while(sm.state==sMenuInicial)		//Polling para os botões de menu.
	{
		opcao = lerBotaoMenu();			//Leitura da porta analógica.
		_delay_ms(150);					//Debounce.
		if(opcao==LEFT)					
		{
			sm.state = sInsereNome;		//Mudança de estado -> Insere Nome
		}
		else if(opcao==RIGHT)
		{
			sm.state = sRanking;		//Mudança de estado -> Ranking
		}
	}		
}

void Ranking()
{
	uint8_t i, endLinha;
	uint16_t opcao;
	pos posicoes[POSICOES_RANKING];				//Vetor que manipula as posições.
	ExibeTelaRanking();							//Mostra a tela inicial do ranking.
	for(i=0;i<POSICOES_RANKING;i++)				//Laço que lê todas posições 
	{											//do ranking da memória.
		endLinha = i*TAM_LINHA;
		ReadLine((END_INICIAL+endLinha),&posicoes[i]);
		_delay_us(10);
	}
	i = 0;
	PrintLinha(posicoes[i],i+1);				//Exibe a primeira posição no display.
	opcao = lerBotaoMenu();						//Debounce inicial da entrada analógica.
	_delay_ms(500);								//
	while(sm.state==sRanking)					//Polling para os botões de menu.
	{
		opcao = lerBotaoMenu();
		_delay_ms(150);
		if((opcao==UP) & (i>0))					//Exibe posição acima.
		{
			i--;
			PrintLinha(posicoes[i],i+1);
		}
		if((opcao==DOWN) & (i<POSICOES_RANKING-1))
		{
			i++;
			PrintLinha(posicoes[i],i+1);		//Exibe posição abaixo.			
		}
		else if(opcao==CANCEL)
		{
			sm.state = sMenuInicial;			//Mudança de estado -> Menu Inicial
		}
	}
}

void InsereNome()
{
	uint16_t opcao;
	uint8_t indName = 0;
	uint8_t letra = A;
	bool primeiraMudanca = true;	
	ExibeTelaName();							//Mostra a tela de inserção de nome.
	opcao = lerBotaoMenu();						//Debounce inicial da entrada analógica.
	_delay_ms(500);								//
	while(sm.state==sInsereNome)				//Polling para os botões de menu.
	{
		opcao = lerBotaoMenu();
		_delay_ms(150);
		if(opcao!=NONE)
		{
			if(opcao==RIGHT) 					//Confirmação da letra escolhida.
			{
				if(primeiraMudanca)
					letra=A;
				name[indName]=(char)letra;
				lcd_write_instruction((lcd_SetCursor)|(lcd_LineTwo+PRIM_CARACT_NOME+indName));
				_delay_us(80);
				lcd_write_character(letra);
				_delay_us(80);
				indName++;
				primeiraMudanca = true;
				if(indName==3){
					_delay_ms(1000);
					sm.state = sConfirmaJogo;	//Mudança de estado -> Confirma Jogo
				}
			}
			else if(opcao==UP)					//Navega pelo alfabeto em direção crescente.
			{
				if((letra==Z) | (primeiraMudanca))
				{
					letra=A;
					primeiraMudanca = false;
				}
				else letra++;
				
				lcd_write_instruction((lcd_SetCursor)|(lcd_LineTwo+PRIM_CARACT_NOME+indName));
				_delay_us(80);
				lcd_write_character(letra);
				_delay_us(80);
			}
			else if(opcao==DOWN)				//Navega pelo alfabeto em direção descrescente.
			{ 
				if((letra==A) | (primeiraMudanca))
				{
					letra=Z;
					primeiraMudanca = false;
				}
				else letra--;
				
				lcd_write_instruction((lcd_SetCursor)|(lcd_LineTwo+PRIM_CARACT_NOME+indName));
				_delay_us(80);
				lcd_write_character(letra);
				_delay_us(80);
			}
			else if(opcao==CANCEL)
			{
				sm.state = sMenuInicial;		//Mudança de estado -> Menu Inicial
			}
		} 
	}
}

void ConfirmaJogo()
{
	uint16_t opcao;
	ExibeJogar();							//Mostra a tela para confirmação de jogo.
	opcao = lerBotaoMenu();					//Debounce inicial da entrada analógica.
	_delay_ms(500);							//
	sm.state = sConfirmaJogo;				
	while(sm.state==sConfirmaJogo)			//Polling para os botões de menu.
	{
		opcao = lerBotaoMenu();
		_delay_ms(150);
		if(opcao==LEFT)
		{
			sm.state = sPlayGenius;			//Mudança de estado -> Play Genius
		}
		else if((opcao==RIGHT)|(opcao==CANCEL))
		{
			sm.state = sMenuInicial;		//Mudança de estado -> Menu Inicial
		}
		else
		{
			sm.state = sConfirmaJogo;
		}
	}	
}

void PlayGenius()
{
	bool sucesso;
	ExibeGenius();							//Mostra a tela de preparação para o jogo.
	score = 0;								//Zera o score.
	botaoPressionado = false;				//Desabilita a flag dos botões de jogo.
	InsereElemento();						//Insere o primeiro elemento da sequencia.
	MostraSequencia();						//Mostra a primeira luz para o jogador.
	sei();									//Botões ativos.
	while(sm.state==sPlayGenius)									//Polling para os botões de jogo.
	{
		_delay_ms(100);												//Debounce.
		if(botaoPressionado)										//Detecção da interrupção.
		{
			cli();													//Desabilita os botões.
				if(numBotaoPressionado==sequencia[indexSequencia])	//Caso de acerto do jogador.
				{
					if(indexSequencia==(score-1))					//Caso para entrada do último elemento da sequencia.
					{
						sucesso = InsereElemento();
						if(!sucesso)								//Caso para o jogador atingir o máximo de pontos.
						{
							sm.state = sGameOver;					//Mudança de estado -> Game Over
							score--;
						}
						MostraSequencia();							//Exibe novamente a sequencia de luzes.
						indexSequencia = 0;							//Reinicia o indexador de verificação da sequência.
					}
					else											//Caso para a entrada de um elemento inicial ou de meio
					{												//da sequência.
						indexSequencia++;
					}
					botaoPressionado = false;						//Desabilita a flag dos botões de jogo.
					sei();											//Botões ativos.
				}
				else												//Caso para erro do jogador.
				{
					sm.state = sGameOver;							//Mudança de estado -> Game Over
					indexSequencia = 0;								
					score--;
				}
		}
	}
}

void GameOver()
{
	uint8_t i,j=POSICOES_RANKING, endLinha;
	pos posicoes[POSICOES_RANKING];	
	ExibeGameOver(score);										//Mostra na tela o score do jogador.
	PiscaLeds();												//Pisca todos os LEDs juntos.
	for(i=0;i<POSICOES_RANKING;i++)								//Lê da memória todas as posições do ranking.
	{
		endLinha = i*TAM_LINHA;
		ReadLine((END_INICIAL+endLinha),&posicoes[i]);
	}
	for(i=0;i<POSICOES_RANKING;i++)								//Loop que procura uma posição para a inserir o novo score
	{
		if(score>=posicoes[i].pScore)							//Caso para o encontro de uma.
		{
			j=POSICOES_RANKING-1;
			while(i<j)											//Loop que desloca as outras posições para baixo.
			{
				posicoes[j].pName[0] = posicoes[j-1].pName[0];
				posicoes[j].pName[1] = posicoes[j-1].pName[1];
				posicoes[j].pName[2] = posicoes[j-1].pName[2];
				posicoes[j].pScore = posicoes[j-1].pScore;
				j--;
			}			
			posicoes[i].pName[0] = name[0];						//Guarda o nome e o score na posição encontrada.
			posicoes[i].pName[1] = name[1];						//
			posicoes[i].pName[2] = name[2];						//
			posicoes[i].pScore = score;							//
			i = POSICOES_RANKING;								//Necessário para quebrar o loop.
		}
	}	
	for(i=0;i<POSICOES_RANKING;i++)								//Escreve novamente na memória todas as posições
	{															//do ranking.
		endLinha = i*TAM_LINHA;
		WriteLine(END_INICIAL+endLinha,posicoes[i].pName,posicoes[i].pScore);
	}
	_delay_ms(1000);											//Tempo para que o jogador visualize seu score.
	sm.state = sMenuInicial;									//Mudança de estado -> Menu Inicial
}



/* Função auxiliar no estado Ranking */
void PrintLinha(pos pPosicao, uint8_t ind)
{
	uint8_t dig1Score = (pPosicao.pScore/100);								//Separa o algarismo de centena do score.
	uint8_t dig2Score = ((pPosicao.pScore-(dig1Score*100))/10);				//Separa o algarismo de dezena do score.
	uint8_t dig3Score = (pPosicao.pScore-(dig1Score*100)-(dig2Score*10));	//Separa o algarismo de unidade do score.
	uint8_t dig1Pos = (ind/100);											//Separa o algarismo de centena do número de posição.
	uint8_t dig2Pos = ((ind-(dig1Pos*100))/10);								//Separa o algarismo de dezena do número de posição.
	uint8_t dig3Pos = (ind-(dig1Pos*100)-(dig2Pos*10));						//Separa o algarismo de unidade do número de posição.
	dig1Score+=48;															//O offset de um número em relação ao valor do seu 
	dig2Score+=48;															//caractere em ASCII é 48.
	dig3Score+=48;
	dig2Pos+=48;
	dig3Pos+=48;
	lcd_write_instruction(lcd_SetCursor|(lcd_LineTwo + 1));					//Mostra o número de posição na segunda
	_delay_us(80);															//linha do display utilizando dois algarismos.
	lcd_write_character(dig2Pos);
	_delay_us(80);
	lcd_write_character(dig3Pos);
	_delay_us(80);
	lcd_write_instruction(lcd_SetCursor|(lcd_LineTwo + 6));					//Mostra os três caracteres do nome.
	_delay_us(80);
	lcd_write_character(pPosicao.pName[0]);
	_delay_us(80);
	lcd_write_character(pPosicao.pName[1]);
	_delay_us(80);
	lcd_write_character(pPosicao.pName[2]);
	_delay_us(80);
	lcd_write_instruction(lcd_SetCursor|(lcd_LineTwo + 11));				//Mostra o score com 3 algarismo.
	_delay_us(80);
	lcd_write_character(dig1Score);
	_delay_us(80);
	lcd_write_character(dig2Score);
	_delay_us(80);
	lcd_write_character(dig3Score);
	_delay_us(80);
}

/* Função auxiliar no estado Play Genius */
/**
 * @return Flag que sinaliza se a sequencia foi preenchida com sucesso ou não.
*/
bool InsereElemento()
{
	uint8_t novo = ((TIMER_RAND+rand()+(rand()%MAX_SEQ))%4)+1;	//Captura do valor do timer e geração do valor de luz.
	if(score >= MAX_SEQ)										//Caso para a sequencia completamente preenchida.
		return false;											
	sequencia[score] = novo;									//Insere o novo elemento na sequência.
	score++;													//Incrementa o score.
	return true;	
}

/* Função auxiliar no estado Play Genius */
void MostraSequencia()
{
	uint8_t i;
	for(i=0;i<score;i++)			//Loop que faz as luzes da sequência piscarem
	{								//uma de cada vez.
		switch(sequencia[i])
		{
			case Y_NUM:
				_delay_ms(800);
				YBlink();				
				break;
			case B_NUM:
				_delay_ms(800);
				BBlink();				
				break;
			case G_NUM:
				_delay_ms(800);
				GBlink();
				break;
			case R_NUM:
				_delay_ms(800);
				RBlink();
				break;
			default:
				PiscaLeds();
				break;		
		}
	}
}

/**
	@brief Função do vetor de interrupções para o botão amarelo.
*/
ISR (BOTAO_Y_FUNCT)
{
	botaoPressionado = true;		//Ativação da flag.
	numBotaoPressionado = Y_NUM;	//Indica que o botão pressionado foi o amarelo.
	YBlink();						//Pisca o LED amarelo.
}
/**
	@brief Função do vetor de interrupções para o botão azul.
*/
ISR (BOTAO_B_FUNCT)
{
	botaoPressionado = true;		//Ativação da flag.
	numBotaoPressionado = B_NUM;	//Indica que o botão pressionado foi o azul.
	BBlink();						//Pisca o LED azul.
}
/**
	@brief Função do vetor de interrupções para o botão verde.
*/
ISR (BOTAO_G_FUNCT)
{
	botaoPressionado = true;		//Ativação da flag.
	numBotaoPressionado = G_NUM;	//Indica que o botão pressionado foi o verde.
	GBlink();						//Pisca o LED verde.
}
/**
	@brief Função do vetor de interrupções para o botão vermelho.
*/
ISR (BOTAO_R_FUNCT)
{
	botaoPressionado = true;		//Ativação da flag.
	numBotaoPressionado = R_NUM;	//Indica que o botão pressionado foi o vermelho.
	RBlink();						//Pisca o LED vermelho.
}
/**
	@brief Função do vetor de interrupções para o timer de overflow.
*/
ISR (TIMER_RAND_FUNCT)
{
	return;
}

