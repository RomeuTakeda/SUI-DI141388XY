/*********************************************************************************************
DEFINIÇÕES RELATIVAS AOS PINOS
*********************************************************************************************/

#define di()  	INTCONbits.GIE = 0
#define ei()  	INTCONbits.GIE = 1;
#define bit unsigned
#define MENU_CONT  48//45
#define FCY 10000000UL
#define TEMPO_PRESET 50//100
#define TEMPO_PISCA_DISPLAY	15
#define OP_ON	1
#define OP_NOP	0
#define LED_FS	PORTCbits.RC2

#define HORARIO 1
#define ANTI_HORARIO 0

#define LIM1_OUT	PORTBbits.RB1//
#define TLIM1_OUT 	TRISBbits.TRISB1//
#define LIM2_OUT 	PORTCbits.RC2//
#define TLIM2_OUT 	TRISCbits.TRISC2//
#define LIM3_OUT	PORTBbits.RB2//
#define TLIM3_OUT 	TRISBbits.TRISB2//
#define LIM4_OUT 	PORTEbits.RE2//
#define TLIM4_OUT 	TRISEbits.TRISE2//

#define TLED_TX 	TRISCbits.TRISC0//
#define LED_TX 		PORTCbits.RC0//
#define TLED_RX		TRISCbits.TRISC1//
#define LED_RX		PORTCbits.RC1//

//#define TPRESET_IN	TRISEbits.TRISE0//
//#define PRESET_IN	PORTEbits.RE0
//#define TDEPIN		TRISEbits.TRISE1//
//#define DEPIN		PORTEbits.RE1//

//#define TRXPIN		TRISCbits.TRISC7//
//#define RXPIN		PORTCbits.RC7

//#define TTXPIN		TRISCbits.TRISC6//
//#define TXPIN		PORTCbits.RC6//

#define ANGULOMAXIMO 1800 // era 3600

/*********************************************************************************************
OUTRAS DEFINIÇÕES
*********************************************************************************************/
#define ADR_EEPROM 0x7ffc00
#define TRUE	1
#define ASCII(X)	(X+48)
#define	NULL_	((void *)0)
#define MS(t) ((unsigned int)((t * (TICKFREQ/5)) /200))
#define ON 1
#define OFF 0
#define DIRETA 1
#define INVERSA 0

#define MM 0
#define CM 2//1
#define M 3//2
#define LIVRE 1//3


#define TEMPO 766 //115 //766 = 5seg , 115 = 750mseg e 23 = 150ms
#define PISCA_ON  1
#define PISCA_OFF 0
#define MODO_NORMAL				0
#define MODO_MENU				1
#define MODO_PROGRAMAR			2
#define MODO_GRAVAR				4
#define MODO_SENHA				5

#define NUMDIGITO					1
#define PONTODEC				2
#define CONSTMULT				3
#define PRESET					4

#define OPPRESET1				5
#define OPLIM1					6
#define LIM1					7
#define OPLIM2					8
#define LIM2					9
#define ESCALA0					11
#define ESCALA1					13
#define ANALOGICA0				15
#define ANALOGICA1				17
#define LIM1HIST	18
#define LIM2HIST	19
#define UNIDADE		20
#define TALIM1		21
#define TDLIM1		22
#define TALIM2		23
#define TDLIM2		24
#define HOLD1X		25
#define FILTRO 		26
#define MODOMED1		27
#define MEDIA	28
#define COMUNIC 1
#define ERRO 2

#define SENHA					33
#define SAIR					34

//------------------------------------
#define ANALOGICA0_2	35
#define ANALOGICA1_2	36
#define ESCALA0_2		37
#define ESCALA1_2		38
#define OPLIM3			39
#define LIM3			40
#define LIM3HIST		41
#define TALIM3			42
#define TDLIM3			43
#define LIM4			44

#define OPLIM4			45
#define LIM4HIST		46
#define TALIM4			47
#define TDLIM4			48
#define FILTRO2			49
#define MODOMED2		50
#define CONSTMULT2		51
#define OPPRESET2		52
#define PRESET2			53

#define HOLD2X		54
#define HOLD3Y		55
#define HOLD4Y		56
//------------------------------------

#define OP_NOP 0
#define OP_GE 1
#define OP_LE 2
#define OP_MODULO 3
#define clrwdt(); _asm CLRWDT _endasm
extern unsigned char Falha, Falha2;
extern unsigned char OpPreset,OpPreset1,OpPresetY, OpPresetZ,OpPreset2;
extern long analogica0, analogica1;
extern unsigned int Temperatura;
extern unsigned int rampa;
extern unsigned char sentido, sentido_buffer;
extern unsigned char cont_erro, cont_int;
extern unsigned char flag_erro;
//extern double k;
extern char addr;
extern unsigned int ContPiscadaDisplay;
extern signed char incremento;
extern signed long inc;
extern float a_p;
extern unsigned char ContDelayPreset;
extern unsigned int  var_sinal_test;
long extern  senha_var, senha_aux_var;
extern unsigned char mostra_var;
extern unsigned long var_long;
extern unsigned char position;
extern  unsigned int var_tempo;
extern char modo;
extern unsigned TECLA;
extern unsigned char VarTroca;
extern volatile unsigned int cont_time_out_menu;
extern char tecla;
extern float MedidaFilt,MedidaFiltX, MedidaFiltY, MedidaFiltZ;
extern char TCODE[1];
extern char menu_flag;
extern unsigned char flag_mudou_radio;
extern unsigned char  controle_senha;
extern unsigned int senha_nova_var1,buffer_senha_nova_var1, senha_nova_var2,buffer_senha_nova_var2;
extern long NumDigDisplay;
extern unsigned char FlagLim1Out, FlagLim2Out;
extern unsigned char FlagLim3Out, FlagLim4Out;
extern unsigned char Hold1X, Hold2X, Hold3Y, Hold4Y;
//-----extern float MedidaFilt;
extern long Preset_ef_1, Preset_ef_2, Preset_ef_Z;
extern signed long SigLongMedida;
extern  unsigned char Unidade;
extern signed long MedidaTransdutor, MedidaTransdutorAnterior ,MedidaTransdutor1,MedidaTransdutor2,MedidaTransdutor3;
extern unsigned char   ModoMedY, ModoMedZ,ModoMed2;
extern  long val,ValX, Val2, ValZ,ValDisp   ;
extern unsigned char ContLedRx, ContLedTx;
extern struct _menu
{
	char *indice_display;
//	struct _menu *anter;
	struct _menu *prox;
//	struct _menu *submenu;
	char tag;
};

typedef struct _menu menu;
extern menu menu_aux;


extern menu *ptrglobal;
extern menu main_menu[MENU_CONT];


extern struct valueType {
	long value;
	char decPoint;
};

extern struct valueType tempValue;
extern struct valueType k2;
extern struct valueType k3;
extern struct valueType k1;
extern struct valueType lim1;
extern struct valueType lim2;
//-------------------------
extern long analogica0_2,analogica1_2;
extern struct valueType lim3;
extern struct valueType lim4;
extern struct valueType lim3hist;

extern struct valueType escala0_2;
extern struct valueType escala1_2;


extern struct valueType TdLim4;
extern struct valueType lim4hist;
extern struct valueType TaLim4;
//-------------------------
extern struct valueType counter;
extern struct valueType preset;
extern struct valueType presetbuffer;
extern struct valueType escala0;
extern struct valueType escala1;
extern struct valueType FiltroRc;
extern struct valueType FiltroRc2;
extern struct valueType TaLim1;
extern struct valueType TdLim1;
extern struct valueType TaLim3;
extern struct valueType TdLim3;
extern struct valueType TaLim2;
extern struct valueType TdLim2;
extern struct valueType Media_;








extern char TPRESET[1];
extern char TPRESET2[1];
extern char TOPPRESET1[1];
extern char TOPPRESET2[1];
extern char TOPPRESETY[1];
extern char TOPPRESETZ[1];
extern char TPONTODEC[1];
extern char TCONSTMULT[1];
extern char TCONSTMULT2[1];
extern char TLIM1[1];
extern char TOPLIM1[1];
extern char TLIM2[1];
extern char TOPLIM2[1];
extern char TESCALA0[1];
extern char TESCALA1[1];
extern char TANALOGICA0[1];
extern char TANALOGICA1[1];
extern char TNUMDIG[1];
extern char TSENHA[1];

//---------------------
extern char TANALOGICA0_2[1];
extern char TANALOGICA1_2[1];
extern char TESCALA0_2[1];
extern char TESCALA1_2[1];
extern char TOPLIM3[1];
extern char TLIM3[1];
extern char TLIM3HIST[1];
extern char TTALIM3[1];
extern char TLIM4[1];
extern char TLIM4HIST[1];
extern char TOPLIM4[1];
extern char TTALIM4[1];
extern char TTDLIM4[1];
//-----------------
extern char TSAIR[1];
extern char TUNIDADE[1];
extern char TTALIM1[1];
extern char TTDLIM1[1];
extern char TTALIM2[1];
extern char TTDLIM3[1];
extern char TTDLIM2[1];
extern char THOLD1X[1],THOLD2X[1],THOLD3Y[1],THOLD4Y[1];
extern char TFILTRO[1];
extern char TFILTRO2[1];
extern char TMODOMED1[1];
extern char TMODOMED2[1];
extern char TMEDIA[1];


extern void eeprom_write(unsigned char addr, unsigned char data);
extern void sendToEEPROM(char add, char *p, char num);
extern void inc_dec(void);
extern void display_num(int valor );
extern void sendDAC(signed long x);
extern unsigned char flag_segundos;
extern unsigned long incDigit (unsigned char num_dig,unsigned long var_long);


extern unsigned int msgTimer;
extern char byteCount, msgsize;
extern bit msgReady;

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
				if(aux==0x01||aux==0){\
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

