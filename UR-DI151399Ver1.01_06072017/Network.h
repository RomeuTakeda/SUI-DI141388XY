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
#define bit unsigned

#define ADDRESS 	0x01   // Endereço do nodo na rede
#define BUFSIZE 	 20     // Tamanho do buffer de transmissao e recepcao
#define NETTIMEOUT 	10    // timeout de recepcao na rede em milisegundos



#define DEPIN   PORTEbits.RE1	// Drive Enable
#define TDEPIN  TRISEbits.TRISE1
#define TXPIN PORTCbits.RC6
#define TTXPIN TRISCbits.TRISC6
#define RXPIN PORTCbits.RC7
#define TRXPIN TRISCbits.TRISC7


#define SERVERSPEED	 129	// ( 19200 bps @ 40MHz)

#define bit unsigned
#define NREGS 5
#define NCOILS 3


extern unsigned long baud_rate;
// Variaveis
extern char aux;
extern unsigned char netBuf[];
extern unsigned int msgTimer;
extern char byteCount, msgsize;
extern bit msgReady;

// Protótipos das funções
extern void networkInit (void);
extern void sendMsg (char);
extern unsigned int calcCRC (char *, char);










