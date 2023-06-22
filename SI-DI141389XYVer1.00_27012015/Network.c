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

#include <p18f252.h>
#include "network.h"
#include "main.h"
#include <stdlib.h>
#include <string.h>


char aux;

// Variaveis
unsigned char netBuf[BUFSIZE];	// Buffer de transmissao e recepcao
unsigned int msgTimer;
char byteCount, msgsize;
bit msgReady;
unsigned long baud_rate;
char addr;

// inicializa dispositivo serial do chip
	
void networkInit (void)
{
/*	float aux;
	TDEPIN = 0;		// Drive Enable é uma saida
	TTXPIN = 0;
	TRXPIN = 1;
	
	DEPIN = 0;		        // desabilita driver de transmissao
addr = 0x01;
	baud_rate = 9600;
//	aux = 2500000.0/(float)baud_rate - 1.0;
//	SPBRG = (((unsigned int)(aux*10.0)%(unsigned int)aux)>=5)?(aux+1):aux;

	SPBRG = 64;

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
*/
	float aux;
	TDEPIN = 0;		// Drive Enable é uma saida
	TTXPIN = 0;
	TRXPIN = 1;
	
	DEPIN = 0;		        // desabilita driver de transmissao

	addr = 0x01;
	baud_rate = 115200;
	aux = 2500000.0/(float)baud_rate - 1.0;
	SPBRG = (((unsigned int)(aux*10.0)%(unsigned int)aux)>=5)?(aux+1):aux;

	
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

// inicializa escalonador
void init_tmr2 (void)
{
/*
	float aux = 0;
	INTCONbits.GIE = 0;
	TMR2 = 0; // inicializa TMR2
	PR2 = 250; // configura limite de TMR2 127
	T2CONbits.TOUTPS3 = 1; // configura o postscaler
	T2CONbits.TOUTPS0 = 1; //
	T2CONbits.TOUTPS2 = 1; //
	T2CONbits.TOUTPS1 = 1; //


	T2CONbits.T2CKPS1 = 0; // era 0// configura o prescaler
	T2CONbits.T2CKPS0 = 1; // 


	T2CONbits.TMR2ON = 1; // habilita TMR2
	INTCONbits.PEIE = 1; // habilita interrupções dos periféricos (TMR2 inclusive)
	PIE1bits.TMR2IE = 1; // habilita interrupções do TMR2
	IPR1bits.TMR2IP = 0;
*/
	float aux = 0;
	INTCONbits.GIE = 0;

	TMR2 = 0; // inicializa TMR2
	PR2 = 250; // configura limite de TMR2 127
	T2CONbits.TOUTPS3 = 1; // configura o postscaler
	T2CONbits.TOUTPS0 = 1; //
	T2CONbits.TOUTPS2 = 1; //
	T2CONbits.TOUTPS1 = 1; //

	T2CONbits.T2CKPS1 = 1; // configura o prescaler
	T2CONbits.T2CKPS0 = 0; // 
	T2CONbits.TMR2ON = 1; // habilita TMR2
	INTCONbits.PEIE = 1; // habilita interrupções dos periféricos (TMR2 inclusive)
	PIE1bits.TMR2IE = 1; // habilita interrupções do TMR2
	IPR1bits.TMR2IP = 0;

}


/* Funcao de envio da mensagem 
 * buf: mensagem a ser enviada
 * cnt: tamanho da mensagem*/
void sendMsg (char cnt)
{	
	char i;
	PIE1bits.RCIE = 0;
	DEPIN = 1;  // habilita o driver de linha para transmissão
//retirei esse delay aki1
	Delay10KTCYx(8);
	
	for(i=0;i<cnt;i++){
		while(!(TXSTAbits.TRMT && PIR1bits.TXIF));
		TXREG = netBuf[i];
	}

	// Espera ate ter transmitido tudo para poder desabilitar a linha
	while(!(TXSTAbits.TRMT&&PIR1bits.TXIF));
//retirei esse delay aki1
	Delay10KTCYx(8);	

	DEPIN = 0;  // volta a escuta da rede
	aux = RCREG;
	aux = RCREG;
	RCSTAbits.CREN=0;
	RCSTAbits.CREN=1;
	PIR1bits.RCIF = 0;
	PIE1bits.RCIE = 1;
}


void transmitir (void)
{
	unsigned int crc_recebido, crc_calculado;
	unsigned int i, kr, nr;
	char j;
	long valor, valor1;
	char coils=0, coils2=0;
	if(msgReady){

		// Checagem do CRC
		crc_calculado = calcCRC(netBuf, msgsize-2);
		*(char *)&crc_recebido = netBuf[msgsize-2];
		*((char *)&crc_recebido+1) = netBuf[msgsize-1];
		// Nao houve erro de CRC
		if(crc_recebido==crc_calculado){
			crc_recebido = 1;
			crc_calculado = 2;

			Adis16209Read(INCLINACAO,&valorx);
			Inclinacao = leitura_sem_sinal;
			Sinal=Polaridade;
	
			Adis16209Read(INCLINACAOX,&valorx);
			InclinacaoX = leitura_sem_sinal;
			SinalX=Polaridade;
	
			Adis16209Read(INCLINACAOY,&valorx);
			InclinacaoY = leitura_sem_sinal;
			SinalY=Polaridade;
	
			Adis16209Read(TEMPERATURA,&valorx);
			Temperatura = (unsigned char)leitura_sem_sinal;
			

			ContReset = 0;
			
			netBuf[2]= 10;


			netBuf[3]=*(((char *)&Inclinacao)+1);
			netBuf[4]=*((char *)(&Inclinacao));

			netBuf[5]=*(((char *)&InclinacaoX)+1);
			netBuf[6]=*((char *)(&InclinacaoX));

			netBuf[7]=*(((char *)&InclinacaoY)+1);
			netBuf[8]=*((char *)(&InclinacaoY));

			netBuf[9]=Sinal;
			netBuf[10]=SinalX;

			netBuf[11]=SinalY;
			netBuf[12]=Temperatura;//Temperatura
	
			crc_recebido=calcCRC(netBuf, 13);
			netBuf[13] = *(char *)&crc_recebido;
			netBuf[14] = *(((char *)&crc_recebido)+1);
			sendMsg(15);
		}
		msgReady = 0;

	}
}


