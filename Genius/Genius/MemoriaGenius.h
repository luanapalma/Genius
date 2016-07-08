/*
 * MemoriaGenius.h
 *
 */ 


#ifndef MEMORIAGENIUS_H_
#define MEMORIAGENIUS_H_

/**
	@def END_INICIAL
	@brief Definição do endereço inicial da EEPROM.
*/
#define END_INICIAL 0x0000
/**
	@brief Função que escreve um dado de um byte na posição da EEPROM indicada.
*/
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
/**
	@brief Função que lê um dado de um byte na posição da EEPROM indicada.
*/
uint8_t EEPROM_read(unsigned int uiAddress);
/**
	@brief Função que escreve a partir do endereço indicado uma linha com 4 bytes de dados referentes a uma posição de ranking.
*/
void WriteLine(uint16_t wAddress, uint8_t wName[3], uint8_t wScore);
/**
	@brief Função que lê a partir do endereço indicado uma linha com 4 bytes de dados referentes a uma posição de ranking.
*/
void ReadLine(uint16_t rAddress, uint8_t* rLine);

#endif /* MEMORIAGENIUS_H_ */