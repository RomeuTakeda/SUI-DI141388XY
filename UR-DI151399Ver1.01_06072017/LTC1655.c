/**********************************************************************
*                                                                     *
*    Date: 06/07/1999                                                 *
*                                                                     *
*    Rotinas de comunica��o com o DAC714                              *
*                                                                     *
*    Authors: Michelle Souza Nery e Thiago Turchetti Maia             *
*    Company: Di-El�trons Eletr�nica Industrial Ltda                  *
**********************************************************************/


//INCLUS�O DE BIBLIOTECAS

#include <p18f4620.h>
#include "main.h"
#include "keyboard.h"
#include "keys.h"
#include "hcms297x.h"
#include "LTC1655.h"


void dacSend1 (unsigned int data)
{
	char i;


	A0PIN1 = LOW;	
	Delay1KTCYx(1);
	for (i = 0; i < 16; i++) {	// loop para transmiss�o dos 16 bits
		CLKPIN = LOW;		// abaixa CLKPIN para que um novo bit seja sinalizado
		Delay1KTCYx(1);
		if (data & 0x8000){
			DATAPIN = HI;
		}
		else{
			DATAPIN = LOW;
		}
		Delay1KTCYx(1);
		data <<= 1;		// rotaciona os 16 bits a serem transmitidos
		CLKPIN = HI;		// pulsa CLKPIN e transmite bit
		Delay1KTCYx(1);
	}
	Delay1KTCYx(1);
	CLKPIN = LOW;
	Delay1KTCYx(1);
	DATAPIN = LOW;
	Delay1KTCYx(1);
	A0PIN1 = HI;	// sobe A0PIN e abaixa CLKPIN e DATAPIN para encerrar transmiss�o

}
void dacSend2 (unsigned int data)
{
	char i;


	A0PIN2 = LOW;	
	Delay1KTCYx(1);
	for (i = 0; i < 16; i++) {	// loop para transmiss�o dos 16 bits
		CLKPIN = LOW;		// abaixa CLKPIN para que um novo bit seja sinalizado
		Delay1KTCYx(1);
		if (data & 0x8000){
			DATAPIN = HI;
		}
		else{
			DATAPIN = LOW;
		}
		Delay1KTCYx(1);
		data <<= 1;		// rotaciona os 16 bits a serem transmitidos
		CLKPIN = HI;		// pulsa CLKPIN e transmite bit
		Delay1KTCYx(1);
	}
	
	Delay1KTCYx(1);
	CLKPIN = LOW;
	Delay1KTCYx(1);
	DATAPIN = LOW;
	Delay1KTCYx(1);
	A0PIN2 = HI;	// sobe A0PIN e abaixa CLKPIN e DATAPIN para encerrar transmiss�o

}


	
void LTC1655Init (void)
{

	TCLKPIN = 0;	// seta par�metros de comunica��o com o DAC
	TA0PIN1 = 0;	// seta par�metros de comunica��o com o DAC
	TA0PIN2 = 0;	// seta par�metros de comunica��o com o DAC
	TDATAPIN = 0;	// seta par�metros de comunica��o com o DAC
//normal
	DATAPIN = LOW;//0;	// seta par�metros de comunica��o com o DAC
	Delay1KTCYx(1);
	CLKPIN = LOW;//0;	// seta par�metros de comunica��o com o DAC

	Delay1KTCYx(1);
	A0PIN1 = HI;//1;	// seta par�metros de comunica��o com o DAC
	A0PIN2 = HI;//1;	// seta par�metros de comunica��o com o DAC
	Delay1KTCYx(1);

}
