/*
 * MemoriaGenius.c
 *
 */ 

#include <avr/io.h>

/**
 * @param uiAddress Endereço de 2 bytes da memória EEPROM onde será escrito o dado.
 * @param ucData Dado de um byte que será escrito no endereço indicado.
 */
void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
	while(EECR & (1<<EEPE));	//Aguarda término de escrita anterior.
	EEAR = uiAddress;			//Configura o registrador de endereço.
	EEDR = ucData;				//Configura o registrador de dado.
	EECR |= (1<<EEMPE);			//Habilita possibilidade de escrita na memória.
	EECR |= (1<<EEPE);			//Habilita a escrita na memória.
}
/**
 * @param uiAddress Endereço de 2 bytes da memória EEPROM de onde será lido um dado de um byte.
 * @return Conteúdo de um byte do endereço passado para a função.
 */
uint8_t EEPROM_read(unsigned int uiAddress)
{
	while(EECR & (1<<EEPE))	;	//Aguarda término de escrita anterior.
	EEAR = uiAddress;			//Configura o registrador de endereço.
	EECR |= (1<<EERE);			//Habilita leitura.
	return EEDR;				//Retorna o valor lido.
}

/**
 * @param wAddress Endereço de 2 bytes da memória EEPROM onde iniciará a escrita da linha.
 * @param wName[3] Nome de 3 caracteres a ser escrito na linha.
 * @param wScore Score a ser escrito na memória logo após o nome.
 */
void WriteLine(uint16_t wAddress, uint8_t wName[3], uint8_t wScore)
{
	EEPROM_write(wAddress, wName[0]);	//Escreve primeiro caractere.
	EEPROM_write(wAddress+1, wName[1]);	//Escreve o segundo caractere na próxima posição.
	EEPROM_write(wAddress+2, wName[2]);	//Escreve o terceiro caractere na posição seguinte.
	EEPROM_write(wAddress+3, wScore);	//Escreve o score na última posição da linha.
}
/**
 * @param wAddress Endereço de 2 bytes da memória EEPROM onde iniciará a leitura da linha.
 * @param rLine Endereço da memória de dados do processador onde deverá ser guardada a linha lida.
 */
void ReadLine(uint16_t rAddress, uint8_t* rLine)
{
	rLine[0] = EEPROM_read(rAddress);	//Leitura do primeiro caractere do nome.
	rLine[1] = EEPROM_read(rAddress+1);	//Leitura do segundo caractere do nome.
	rLine[2] = EEPROM_read(rAddress+2);	//Leitura do terceiro caractere do nome.
	rLine[3] = EEPROM_read(rAddress+3);	//Leitura do score.
}