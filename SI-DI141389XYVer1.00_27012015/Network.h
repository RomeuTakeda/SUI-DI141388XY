/**************************************************************
 *
 *  network.h
 *
 *  Definições da rede RS485 Di-elétrons - MODBUS-Di
 *
 *  Luciano Bertini     06/10/2000
 *
 *  Di-elétrons Eletrônica Industrial Ltda.
 *
 ***************************************************************/
#define clrwdt(); _asm CLRWDT _endasm
#define bit unsigned

#define ADDRESS 	0x01   // Endereço do nodo na rede
#define BUFSIZE 	 20     // Tamanho do buffer de transmissao e recepcao
#define NETTIMEOUT 	10    // timeout de recepcao na rede em milisegundos



//#define CS	PORTAbits.RA5
//#define CLOCK	PORTCbits.RC3



#define DEPIN   PORTCbits.RC0	// Drive Enable
#define TDEPIN  TRISCbits.TRISC0

#define TXPIN PORTCbits.RC6
#define TTXPIN TRISCbits.TRISC6
#define RXPIN PORTCbits.RC7
#define TRXPIN TRISCbits.TRISC7

#define bit unsigned

#define NREGS 5
#define NCOILS 3
#define SERVERSPEED	 129	// ( 19200 bps @ 40MHz)

// Variaveis

extern char aux;
extern char addr;
extern unsigned char netBuf[];
extern unsigned int msgTimer;
extern char byteCount, msgsize;
extern bit msgReady;
extern unsigned long baud_rate;
// Protótipos das funções
extern void networkInit (void);
extern void sendMsg (char);
extern unsigned int calcCRC (char *, char);
extern void transmitir (void);
extern void init_tmr2 (void);
/* Macro para ser inserida na ISR para recebimento de mensagem
 * deve ser colocada antes de schedulerInterrupt(). Se colocada apos, 
 * o timeout nao funcionara o Tempo maximo entre a recepcao de caracteres
 * eh NETTIMEOUT em milisegundos. Apos NETTIMEOUT ms eh assumido o termino
 * da mensagem. O termino do recebimento eh sinalizado pelo flag msgReady FERR||OERR){\*/
#define networkInterrupt()\
	if(RCSTAbits.OERR || RCSTAbits.FERR){\
		netBuf[0] = RCREG;\
		netBuf[0] = RCREG;\
		RCSTAbits.CREN=0;\
		RCSTAbits.CREN=1;\
	}\
	else {if(PIR1bits.RCIF){\
		if (PIE1bits.RCIE) {\
			msgTimer=0;\
			aux=RCREG;\
			if(byteCount==0){\
				if(aux==addr||aux==0){\
					netBuf[0]=aux;\
					byteCount++;\
				}\
				else PIE1bits.RCIE=0;\
			}else{\
				netBuf[byteCount]=aux;\
				if(byteCount<BUFSIZE) byteCount++;\
			}\
		}\
		else {\
			aux = RCREG;\
			aux = RCREG;\
		}\
	}}

#define schedulerInterrupt()\
	if(PIR1bits.TMR2IF){\
		if(msgTimer<2)msgTimer++;\
		else{\
			if((byteCount>2)){\
				msgsize=byteCount;\
				byteCount=0;\
				msgReady=1;\
			}\
			if(!msgReady) PIE1bits.RCIE=1;\
		}\
		Nop();\
		PIR1bits.TMR2IF = 0;\
	}



