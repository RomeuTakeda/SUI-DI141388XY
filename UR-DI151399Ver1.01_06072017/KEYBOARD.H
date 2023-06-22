/**********************************************************************
*    Filename: keyboard.h                                             *
*    Date: 01/07/1999                                                 *
*                                                                     *
*    Definições para rotinas de comunicação e debounce do teclado 4x4 *
*                                                                     *
*    Authors: Michelle Souza Nery e Thiago Turchetti Maia             *
*    Company: Di-Elétrons Eletrônica Industrial Ltda                  *
**********************************************************************/


#define TEC_IN1		PORTBbits.RB3   //MENU
#define TRISTEC_IN1 TRISBbits.TRISB3

#define TEC_IN2		PORTBbits.RB4   //Dec
#define TRISTEC_IN2 TRISBbits.TRISB4



#define TEC_IN3		PORTBbits.RB5   //INC
#define TRISTEC_IN3 TRISBbits.TRISB5

 


#define PERIODIC_DELAY 125 // configura delay do teclado para aproximadamente .65 segundo (considera o timer com 13ms)
#define PERIODIC_DELAY2 400/*50*///400 // configura delay do teclado para aproximadamente .65 segundo (considera o timer com 13ms)

#define PERIODICITY 28 // configura periodicidade do teclado para aproximadamente 0.2 segundo (considera o timer com 13ms)

// estrutura com os flags do mecanismo do teclado
struct keyboardFlagsType
{
	unsigned timeOut: 1;
};

// tipo de 16 bits para armazenar estado das teclas
union keyboardType {
	// estrutura para permitir acesso individual aos bits
	struct {
		unsigned key2x0: 1;
		unsigned key2x1: 1;
		unsigned key2x2: 1;
		unsigned key2x3: 1;
		unsigned key3x0: 1;
		unsigned key3x1: 1;
		unsigned key3x2: 1;
		unsigned key3x3: 1;
		unsigned PresetIn:1;
	} keys;
	// tipo para permitir operacoes logicas (XOR) e atribuicao (inicializacao)
	unsigned int data;
};

extern union keyboardType currentKeys; // armazena estado atual das teclas
extern union keyboardType referenceKeys; // armazena referencia em relacao ao disparo do temporizador
extern struct keyboardFlagsType keyboardFlags;
extern unsigned int keyboardDelayedPeriodic; // contador do redutor de frequência para funções do teclado (keyDelayedPeriodic)

extern void keyboardScan (void);
extern void keyboardInit (void);

#define keyboardInterrupt()\
	keyboardFlags.timeOut = 1;\
	if (keyboardDelayedPeriodic != PERIODIC_DELAY2){\
		keyboardDelayedPeriodic++;\
	}
