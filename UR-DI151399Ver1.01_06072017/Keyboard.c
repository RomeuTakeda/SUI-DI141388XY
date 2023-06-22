
#include <p18f4620.h>
#include "keyboard.h"
#include "keys.h"
#include "main.h"


union keyboardType currentKeys; // tipo de 16 bits para armazenar estado das teclas
union keyboardType referenceKeys; // tipo de 16 bits para armazenar estado de referência das teclas
struct keyboardFlagsType keyboardFlags; // flags do mecanismo do teclado
unsigned int keyboardDelayedPeriodic=0; // contador do redutor de frequência para funções do teclado (keyDelayedPeriodic)
unsigned char keyboardPeriodicity; // contador do redutor de frequência para funções do teclado (keyDelayedPeriodic)


void keyboardScan (void)
{
	union keyboardType lastKeys;
	char i;
	
	lastKeys = currentKeys; // armazena estado anterior das teclas

	// inicia varredura das teclas
	currentKeys.keys.key2x1 = !TEC_IN1; 
	currentKeys.keys.key2x2 = !TEC_IN2; 
	currentKeys.keys.key2x3 = !TEC_IN3; 
//	currentKeys.keys.PresetIn = !PRESET_IN;
	// finaliza varredura das teclas


	// identifica modificações no teclado (XOR)
	if (lastKeys.data ^ currentKeys.data) {
		// caso as teclas tenham se modificado, reinicialize o timer e armazene valor de referência

		TMR0L = 0; // configura período do timer0
		INTCONbits.TMR0IF = 0; //TMR0 register did not overflow

		// seta referencia para estado atual para que possa ser comparada ao final do tempo de debounce
		referenceKeys = lastKeys;
	} else {
	
		if (keyboardFlags.timeOut) {
			if ((currentKeys.keys.key2x1) && (!referenceKeys.keys.key2x1)) { keyPress2x1(); }
			if ((!currentKeys.keys.key2x1) && (referenceKeys.keys.key2x1)) { keyRelease2x1();}
			if ((currentKeys.keys.key2x2) && (!referenceKeys.keys.key2x2)) { keyPress2x2(); }
			if ((!currentKeys.keys.key2x2) && (referenceKeys.keys.key2x2)) { keyRelease2x2();}
			if ((currentKeys.keys.key2x3) && (!referenceKeys.keys.key2x3)) { keyPress2x3(); }
			if ((!currentKeys.keys.key2x3) && (referenceKeys.keys.key2x3)) { keyRelease2x3();}
			//if ((currentKeys.keys.PresetIn) && (!referenceKeys.keys.PresetIn)) { PresetInFuncao();}

			// reduz frequencia de periodicidade
			if (++keyboardPeriodicity == PERIODICITY) {
				keyboardPeriodicity = 0;

				// aciona eventos periódicos
				if (currentKeys.keys.key2x1) { keyPeriodic2x1(); }
				if (currentKeys.keys.key2x2) { keyPeriodic2x2(); }
				if (currentKeys.keys.key2x3) { keyPeriodic2x3(); }
				
				// aciona eventos periódicos depois de um tempo mínimo
				if (keyboardDelayedPeriodic >= PERIODIC_DELAY) 
				{	
					//if (currentKeys.keys.key2x1) { keyDelayedPeriodic2x1(); }//acrescentei
					if (currentKeys.keys.key2x2) { keyDelayedPeriodic2x2(); }
					if (currentKeys.keys.key2x3) { keyDelayedPeriodic2x3(); }
				}

				if (keyboardDelayedPeriodic == PERIODIC_DELAY2) 
				{
					if ((currentKeys.keys.key2x1) &&  (TEC_IN2) && (TEC_IN3) && (!(TECLA))) { keyDelayedPeriodic2x1();}
					else if ((currentKeys.keys.key2x1) &&  (TEC_IN2) && (TEC_IN3) && ((TECLA))) { 
						TECLA = 0;
						keyboardDelayedPeriodic = 0;}
				}


			}
		
			// zera contador de tempo mínimo quando nenhuma tecla estiver apertada
			if (currentKeys.data == 0) {
				keyboardDelayedPeriodic = 0;
			}

			// seta referencia para estado atual para garantir apenas uma execução de cada ação
			referenceKeys = currentKeys;
		}
		if (TEC_IN1 && TEC_IN2 && TEC_IN3) TECLA = 0;
	}

	// garante que o flag de timeout = 0
	keyboardFlags.timeOut = 0;
}

void keyboardInit (void)
{

	TRISTEC_IN1 = 1;
	TRISTEC_IN2 = 1;
	TRISTEC_IN3 = 1;
	INTCON2bits.RBPU = 0;//Pull Up ligado
	T0CONbits.T016BIT = 1; //Timer0 is configured as an 8-bit timer/counter
	T0CONbits.T0CS = 0; //internal instruction cycle clock (CLKO)
	T0CONbits.PSA = 0;	//timer0 prescaler is assigned. timer0 clock input comes from prescaler output
	T0CONbits.T0PS2 = 1; //1:64 prescale value
	T0CONbits.T0PS1 = 0; //
	T0CONbits.T0PS0 = 1; //
	TMR0L = 0; // configura período do timer0
	INTCONbits.TMR0IF = 0; // garante que nao ha interrupcoes setadas
	INTCONbits.TMR0IE = 1; // habilita interrupcoes do timer2
	currentKeys.data = 0; // inicializa todas as teclas como nao pressionadas
	referenceKeys.data = 0; // inicializa estrutura de refencia como todas as teclas nao pressionadas
	keyboardFlags.timeOut = 0; // seta estado inicial do temporizador
	keyboardScan(); // varre teclado pela primeira vez para registrar teclas iniciais
}
