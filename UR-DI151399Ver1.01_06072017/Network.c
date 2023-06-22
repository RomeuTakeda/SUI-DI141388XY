/**************************************************************
 *
 *  network.c
 *
 *  Implementação da rede RS485 Di-elétrons - MODBUS-Di
 *
 *  Luciano Bertini     06/10/2000
 *
 *  Di-elétrons Eletrônica Industrial Ltda.
 *
 ***************************************************************/

#include <p18f4620.h>
#include "network.h"

char aux;

// Variaveis
unsigned char netBuf[BUFSIZE];	// Buffer de transmissao e recepcao
unsigned int msgTimer;
char byteCount=0, msgsize;
bit msgReady;


// inicializa dispositivo serial do chip
	
void networkInit (void)
{
	float aux;
	TDEPIN = 0;		// Drive Enable é uma saida
	TTXPIN = 0;
	TRXPIN = 1;
	
	DEPIN = 0;		        // desabilita driver de transmissao



	aux = 2500000.0/(float)baud_rate - 1.0;
//	SPBRG = (((unsigned int)(aux*10.0)%(unsigned int)aux)>=5)?(aux+1):aux;

	
//SPBRGH =0x04; para 9600 bauds
//SPBRG =0x10;
SPBRGH =0x00;
SPBRG =0x56;//para 115200 bauds


BAUDCONbits.BRG16 = 1;
	TXSTAbits.TX9 = 0;
	TXSTAbits.TXEN = 1;		// enable transmission
	TXSTAbits.SYNC = 0;		// asynchronous mode
	TXSTAbits.BRGH = 1;		// seta BRGH para "baixas" taxas de transferência


	RCSTAbits.SPEN = 1;		// habilita porto serial do chip
	RCSTAbits.RX9 = 0;	
	RCSTAbits.CREN = 1;		// habilita recepcao
	RCSTAbits.ADDEN = 0;	

	PIR1bits.TXIF = 0;		// desabilita interrupções de transmissao
	PIE1bits.TXIE = 0;		// desabilita interrupções de transmissao
	IPR1bits.RCIP = 1;
	PIR1bits.RCIF = 0;		// habilita interrupcão de recepção
	PIE1bits.RCIE = 1;		// habilita interrupcão de recepção
	byteCount = 0;
	msgTimer = 0;



}

/* Funcao que calcula os 16 bits de CRC para uma mensagem 
 * buf: vetor contendo a mensagem
 * cnt: numero de bytes. Inicia no primeiro byte da mensagem
 * */

unsigned int calcCRC(char *bufRS, char cntRS)
{
   char iRS, jRS;
   unsigned int tempRS, flagRS;
   tempRS=0xFFFF;
   for (iRS=0; iRS<cntRS; iRS++){
      tempRS=tempRS ^ bufRS[iRS];
      for (jRS=1; jRS<=8; jRS++){
	 flagRS=tempRS & 0x0001;
	 tempRS=tempRS >> 1;
	 if (flagRS) tempRS=tempRS ^ 0xA001;
      }
   }
   return(tempRS);
}



/* Funcao de envio da mensagem 
 * buf: mensagem a ser enviada
 * cnt: tamanho da mensagem*/
void sendMsg (char cnt)
{	
	char i;
	PIE1bits.RCIE = 0;
	DEPIN = 1;  // habilita o driver de linha para transmissão
	Delay10KTCYx(10);//8
	
	for(i=0;i<cnt;i++){
		while(!(TXSTAbits.TRMT && PIR1bits.TXIF));
		TXREG = netBuf[i];
	}

	// Espera ate ter transmitido tudo para poder desabilitar a linha
	while(!(TXSTAbits.TRMT&&PIR1bits.TXIF));

	for(i=0;i<=14;i++)netBuf[i] = 0x55;
	

	DEPIN = 0;  // volta a escuta da rede
//	Delay10KTCYx(10);
	aux = RCREG;
	aux = RCREG;
	RCSTAbits.CREN=0;
	RCSTAbits.CREN=1;

	PIR1bits.RCIF = 0;
	PIE1bits.RCIE = 1;
	Delay10KTCYx(20);
}

