/********************************************************************************************************
//Compilador C18 V3.02
//MPLAB IDE superior a V8.80
//by Michelle Nery Nascimento, Data da ultima compilagco: 15:01h    06/07/2017
//Usar o lindker da pasta do programa
//o display 0 i o mais a esquerda, enquanto que o 3 i o mais a direita.
*********************************************************************************************************/

#include <p18f4620.h>
#include "main.h"
#include "keyboard.h"
#include "keys.h"
#include "LTC1655.h"
#include "network.h"
#include "hcms297x.h"



#pragma udata gpr0
menu menu_aux;
menu *ptrglobal;
menu main_menu[MENU_CONT];
#pragma udata 

#pragma udata gpr1
signed char incremento;
signed long inc;
char modo;
unsigned int TextoBuffer[8] = {0,0,0,0,0,0,0,0};
unsigned int ContPiscadaDisplay = TEMPO_PISCA_DISPLAY;
char TCODE[1];
char TSAIR[1];
char TENT[1];
char TNUMDIG[1];
char TPONTODEC[1];
char TCONSTMULT[1];
char TCONSTMULT2[1];
char TPRESET[1];
char TPRESET2[1];


char TOPPRESET1[1];
char TOPPRESET2[1];
char TOPPRESETY[1];
char TOPPRESETZ[1];

char TOPLIM1[1];
char TLIM1[1];
char TLIM2[1];
char TLIM1HIST[1];
char TLIM2HIST[1];
char TOPLIM2[1];
char TESCALA0[1];
char TESCALA1[1];
char TANALOGICA0[1];
char TANALOGICA1[1];
char TSENHA[1];
char TSAIR[1];
//-----------
char TANALOGICA0_2[1];
char TANALOGICA1_2[1];
char TESCALA0_2[1];
char TESCALA1_2[1];
char TOPLIM3[1];
char TLIM3[1];
char TLIM3HIST[1];
char TTALIM3[1];
char TLIM4[1];
char TLIM4HIST[1];
char TOPLIM4[1];
char TOPLIM4[1];
char TTALIM4[1];
char TTDLIM4[1];
//--------------



unsigned char Sinal, SinalX, SinalY;
char TUNIDADE[1];
char TTALIM1[1];
char TTDLIM1[1];
char TTDLIM3[1];
char TTALIM2[1];
char TTDLIM2[1];
char THOLD1X[1];
char THOLD2X[1];
char THOLD3Y[1];
char THOLD4Y[1];
char TFILTRO[1];
char TFILTRO2[1];
char TMODOMED1[1];
char TMODOMED2[1];
char TMEDIA[1];
unsigned int ContDelay;
unsigned char FlagContDelay=0;
unsigned char ContFalhaComunic=0;
//unsigned char sendMsg [8];	//modbus
unsigned char ContLedRx = 0, ContLedTx=0;
#pragma udata


#pragma udata gpr2
signed long SaidaAnaParametrizada = 0;
unsigned char oplim1,oplim2, oplim3, oplim4;
long NumDigDisplay;
unsigned char Falha = 0, Falha2;
unsigned int config_value,temp;
/*
union pacote_limites2{
	struct{
		unsigned lim5:1;//menos significativo
		unsigned lim6:1;
		unsigned lim7:1;
		unsigned lim8:1;
		unsigned lim9:1;
		unsigned lim10:1;
		unsigned lim11:1;
		unsigned lim12:1;//mais significativo
	} flag;
	unsigned char limites;
};
union pacote_limites2 placa_externa;  //placa_externa.limites

union pacote_limites1{
	struct{
		unsigned lim1:1;//menos significativo
		unsigned lim2:1;
		unsigned lim3:1;
		unsigned lim4:1;
		unsigned reserva:4;
	} flag;
	unsigned char limites;
};
union pacote_limites1 placa_interna;  //placa_interna.limites */
#pragma udata


#pragma udata gpr3
//FLAGS
volatile union flagsbits {
	struct {
		unsigned : 1;
		unsigned Key : 1;
		unsigned  : 1;
		unsigned  : 1;
		unsigned  : 1;
		unsigned  : 1;
		unsigned  : 1;
		unsigned  : 1;
		unsigned  : 1;
		unsigned  : 1;
		unsigned  : 1;
		unsigned  : 1;
		unsigned  : 1;
		unsigned pisca_1s : 1;
		unsigned  : 1;
		unsigned time_out_menu : 1;
	} flag;
	unsigned int data;
};
volatile union flagsbits f;
unsigned int valor;
unsigned long var_long = 0;
unsigned char position;
unsigned char var_segundos=0, flag_segundos=0, flag_time_out=0;
unsigned char  controle_senha =0;
float  b1,a1, b2, a2;
unsigned TECLA = 0;
char *ptr;
long senha_var=123, senha_aux_var=0;
unsigned int senha_nova_var1=0,buffer_senha_nova_var1=0, senha_nova_var2=0,buffer_senha_nova_var2=0;
char tecla=0;
unsigned char mostra_var=0;
volatile unsigned int cont_time_out_menu=0;
unsigned char cont_disp, atualiza_disp;
char prog_mem_value[2];
unsigned long baud_rate;
char addr;
float MedidaFilt = 0, rcAux = 0, MedidaFiltX = 0, MedidaFiltY=0, MedidaFiltZ=0,rcAux2 = 0;
signed long SigLongMedida=0;
long Preset_ef_1,Preset_ef_2, Preset_ef_Z;
unsigned char FlagLim1Out = 0, FlagLim2Out = 0;
unsigned char FlagLim3Out = 0, FlagLim4Out = 0;
unsigned char ContSerialMuda = 0;
unsigned char tamanho;

signed long Preset=0;
signed long MedidaTransdutor = 0, MedidaTransdutorAnterior =0, MedidaTransdutor1 = 0, MedidaTeste,MedidaTransdutor2=0,MedidaTransdutor3=0;
unsigned long UnsigMd__, x__;
unsigned long ContFiltro = 0;
signed long Media = 0, MediaOut = 0, MediaX=0, MediaY=0,MediaZ=0;	
signed char ContMedia = 0;
signed long  NumTotalMedia = 5;
signed long VetorMediaZ[100];
signed long VetorMediaX[100];
#pragma udata 
#pragma udata gpr10
signed long VetorMediaY[100];
#pragma udata
#pragma udata gpr4
struct valueType tempValue;
struct valueType k2;
struct valueType k3;
struct valueType k1;
struct valueType lim1;
struct valueType lim2;
struct valueType counter;
//-------------------------
long analogica0_2,analogica1_2;
struct valueType lim3;
struct valueType lim4;
struct valueType lim3hist;
struct valueType escala0_2;
struct valueType escala1_2;


//-------------------------
//ruct valueType CounterEixoX;
//ruct valueType CounterEixoY;
//ruct valueType CounterEixoZ;


struct valueType preset;
struct valueType preset1;
struct valueType preset2;
struct valueType presetY;
struct valueType presetZ;
struct valueType presetbuffer;
struct valueType escala0;
struct valueType escala1;
struct valueType lim1hist;
struct valueType lim2hist;

struct valueType TdLim4;
struct valueType lim4hist;
struct valueType TaLim4;



struct valueType FiltroRc;
struct valueType FiltroRc2;
struct valueType TaLim1;
struct valueType TdLim3;
struct valueType TaLim3;
struct valueType TdLim1;
struct valueType TaLim2;
struct valueType TdLim2;
unsigned int ContTaLim1 = 0, ContTdLim1 = 0, ContTaLim2 = 0, ContTdLim2 =0;
unsigned int ContTaLim3 = 0, ContTdLim3 = 0, ContTaLim4 = 0, ContTdLim4 =0;
unsigned char OpPreset1, OpPresetY, OpPresetZ, Hold1X,Unidade, ModoMed1, ModoMedY, ModoMedZ,ModoMed2,OpPreset2;
unsigned char Hold2X, Hold3Y, Hold4Y;
long analogica0, analogica1;
struct valueType Media_;

unsigned char VarTroca = 0;


unsigned char position;

double d,hist;
long val, ValX, Val2, ValZ,ValDisp, ValTeste;   
unsigned char ContDelayPreset = TEMPO_PRESET;
unsigned char FlagFiltroDigital = 0, Cont55ms = 0,Cont100ms = 0;
unsigned char Flag100ms=0;
#pragma udata
/*********************************************************************************************
PROTSTIPOS DAS FUNGUES
*********************************************************************************************/
void InterruptVectorHigh (void);
void InterruptHandlerHigh (void);
void initPorts (void);
void MensInicial(void);
void inc_dec(void);
void cria_menus(void);
void atraso2(void);
void FiltroDigital(void);
signed long round(float x);
void EfetivaPreset(void);
void LimOut(void);
void EnviaEEProm(unsigned char endereco,long variavel);
unsigned long incDigit (unsigned char num_dig,unsigned long var_long);
long LeEEprom(unsigned char x);
void Restaurar_Boot (void);
void CalAnalogica(void);
void CalAnalogica2(void);
void pergunta(void);		//modbus
//void sendMsg (char cnt);	//modbus

void AtualizaDisp(void);
void transmitir (void);
void init_tmr2 (void);
unsigned char eeprom_read(unsigned char addr);
void eeprom_write(unsigned char addr, unsigned char data);
void sendToEEPROM(char add, char *p, char num);
void initTimer1(void);
void ModosOperacao(void);
void transmitir (void);
/*********************************************************************************************
FUNGCO PRINCIPAL
*********************************************************************************************/

void main (void) 
{
	char i=0;


	for (i=0;i<100;i++){
		VetorMediaX[i] = 0;
		VetorMediaY[i] = 0;
		VetorMediaZ[i] = 0;
	}


	initPorts();
	cria_menus();
	inithcms297x();
	keyboardInit();

	MensInicial();

init_tmr2();


	networkInit();

	LTC1655Init();
	Restaurar_Boot();// boot tecla INC

	initTimer1();

	INTCONbits.GIE = 1;
	
	TRISBbits.TRISB6 = 0;
	PORTBbits.RB6 = 0;

	while(TRUE)
	{	
		clrwdt();
		if(f.flag.Key)
		{
			keyboardScan();
			f.flag.Key = 0;
		}

		LimOut();	

		transmitir();

		if(FlagContDelay){
			if((modo==MODO_NORMAL)&&(!msgReady)){
				pergunta();		
			}			
			FiltroDigital();
			FlagContDelay = 0;
		}
		AtualizaDisp();
		ModosOperacao();	
		EfetivaPreset();


	}//chave do while infinito
}//chave do main


//---------------------------------------------------------------------------------
//Fungues 
//---------------------------------------------------------------------------------

//FUNGCO DE INICIALIZAGCO DAS PORTAS DO PIC18F252
void initPorts(void)
{
	TRISA = 0;
	TRISB = 0;
	TRISC = 0;
	TRISD = 0;
	TRISE = 0;

	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;

	
	CMCON = 0x07;
	TRISEbits.PSPMODE = 0;
	ADCON1 = 0x0f;
	//////////
	//SAMDAS
	TLED_TX = 0;//
	LED_TX = 0;//
	
	TLED_RX = 0;//
	LED_RX = 0;//
	
	TLIM1_OUT = 0;//
	LIM1_OUT = 0;//
	TLIM2_OUT = 0;//
	LIM2_OUT = 0;//
	TLIM3_OUT = 0;//
	LIM3_OUT = 0;//
	TLIM4_OUT = 0;//
	LIM4_OUT = 0;//
	
	TDEPIN = 0;//
	DEPIN = 0;//
	TTXPIN = 0;//
	TXPIN = 0;//
	//////////
	//ENTRADAS
//	TPRESET_IN = 1;//
	TRXPIN = 1;//

	TRISTEC_IN1 = 1;
	TRISTEC_IN2 = 1;
	TRISTEC_IN3 = 1;

//	TPRESET_IN = 1;
	//////////
	//PINOS  NCO USADOS
	TRISEbits.TRISE2 = 0;
	PORTEbits.RE2 = 0;
	TRISBbits.TRISB6 = 0;
	PORTBbits.RB6 = 0;
	TRISBbits.TRISB7 = 0;
	PORTBbits.RB7 = 0;
	TRISCbits.TRISC2 = 0;
	PORTCbits.RC2 = 0;
	TRISCbits.TRISC3 = 0;
	PORTCbits.RC3 = 0;
	TRISCbits.TRISC4 = 0;
	PORTCbits.RC4 = 0;
	TRISCbits.TRISC5 = 0;
	PORTCbits.RC5 = 0;
	f.data = 0;

	modo = MODO_NORMAL;
VarTroca = 0;
	position = 0;

	ptrglobal = &main_menu[0];
	menu_aux = *ptrglobal;
	cont_time_out_menu=0;

	RCONbits.IPEN = 0;		//Disable priority levels on interrupts.
	INTCONbits.GIE = 1;		//Disables all interrupts.
	INTCONbits.PEIE = 1;	//Disables all peripheral interrupst.

}

/*********************************************************************************************
Procedimento que cria menus
*********************************************************************************************/
void cria_menus(void)
{

	main_menu[0].indice_display = TUNIDADE;
	main_menu[0].prox			= &main_menu[1];
	main_menu[0].tag			= UNIDADE;

	main_menu[1].indice_display = TPONTODEC;
	main_menu[1].prox			= &main_menu[2];
	main_menu[1].tag			= PONTODEC;

	main_menu[2].indice_display = TNUMDIG;
	main_menu[2].prox			= &main_menu[3];
	main_menu[2].tag			= NUMDIGITO;

	main_menu[3].indice_display = TMEDIA;//
	main_menu[3].prox			= &main_menu[4];
	main_menu[3].tag			= MEDIA;

	main_menu[4].indice_display = TCONSTMULT;
	main_menu[4].prox			= &main_menu[5];
	main_menu[4].tag			= CONSTMULT;

	main_menu[5].indice_display = TOPLIM1;
	main_menu[5].prox			= &main_menu[6];
	main_menu[5].tag			= OPLIM1;

	main_menu[6].indice_display = TLIM1;
	main_menu[6].prox			= &main_menu[7];
	main_menu[6].tag			= LIM1;

	main_menu[7].indice_display = TLIM1HIST;
	main_menu[7].prox			= &main_menu[8];
	main_menu[7].tag			= LIM1HIST;

	main_menu[8].indice_display = TTALIM1;
	main_menu[8].prox			= &main_menu[9];
	main_menu[8].tag			= TALIM1;

	main_menu[9].indice_display = TTDLIM1;
	main_menu[9].prox			= &main_menu[10];
	main_menu[9].tag			= TDLIM1;

	main_menu[10].indice_display = THOLD1X;//Preset
	main_menu[10].prox			= &main_menu[11];
	main_menu[10].tag			= HOLD1X;

	main_menu[11].indice_display = TOPLIM2;
	main_menu[11].prox			= &main_menu[12];
	main_menu[11].tag			= OPLIM2;

	main_menu[12].indice_display = TLIM2;
	main_menu[12].prox			= &main_menu[13];
	main_menu[12].tag			= LIM2;

	main_menu[13].indice_display = TLIM2HIST;
	main_menu[13].prox			= &main_menu[14];
	main_menu[13].tag			= LIM2HIST;

	main_menu[14].indice_display = TTALIM2;
	main_menu[14].prox			= &main_menu[15];
	main_menu[14].tag			= TALIM2;

	main_menu[15].indice_display = TTDLIM2;
	main_menu[15].prox			= &main_menu[16];
	main_menu[15].tag			= TDLIM2;

	main_menu[16].indice_display = THOLD2X;//Preset
	main_menu[16].prox			= &main_menu[17];
	main_menu[16].tag			= HOLD2X;

	main_menu[17].indice_display = TOPPRESET1;
	main_menu[17].prox			= &main_menu[18];
	main_menu[17].tag			= OPPRESET1;

	main_menu[18].indice_display = TPRESET;//Preset
	main_menu[18].prox			= &main_menu[19];
	main_menu[18].tag			= PRESET;

	main_menu[19].indice_display = TFILTRO;//Preset
	main_menu[19].prox			= &main_menu[20];
	main_menu[19].tag			= FILTRO;

	main_menu[20].indice_display = TESCALA0;
	main_menu[20].prox			= &main_menu[21];
	main_menu[20].tag			= ESCALA0;

	main_menu[21].indice_display = TESCALA1;
	main_menu[21].prox			= &main_menu[22];
	main_menu[21].tag			= ESCALA1;

	main_menu[22].indice_display = TANALOGICA0;
	main_menu[22].prox			= &main_menu[23];
	main_menu[22].tag			= ANALOGICA0;

	main_menu[23].indice_display = TANALOGICA1;
	main_menu[23].prox			= &main_menu[24];
	main_menu[23].tag			= ANALOGICA1;

	main_menu[24].indice_display = TMODOMED1;
	main_menu[24].prox			= &main_menu[25];
	main_menu[24].tag			= MODOMED1;

//-----------------------------------------------------------------------------------------

	main_menu[25].indice_display = TCONSTMULT2;
	main_menu[25].prox			= &main_menu[26];
	main_menu[25].tag			= CONSTMULT2;

	main_menu[26].indice_display = TOPLIM3;
	main_menu[26].prox			= &main_menu[27];
	main_menu[26].tag			= OPLIM3;

	main_menu[27].indice_display = TLIM3;
	main_menu[27].prox			= &main_menu[28];
	main_menu[27].tag			= LIM3;

	main_menu[28].indice_display = TLIM3HIST;
	main_menu[28].prox			= &main_menu[29];
	main_menu[28].tag			= LIM3HIST;

	main_menu[29].indice_display = TTALIM3;
	main_menu[29].prox			= &main_menu[30];
	main_menu[29].tag			= TALIM3;

	main_menu[30].indice_display = TTDLIM3;
	main_menu[30].prox			= &main_menu[31];
	main_menu[30].tag			= TDLIM3;

	main_menu[31].indice_display = THOLD3Y;
	main_menu[31].prox			= &main_menu[32];
	main_menu[31].tag			= HOLD3Y;

	main_menu[32].indice_display = TOPLIM4;
	main_menu[32].prox			= &main_menu[33];
	main_menu[32].tag			= OPLIM4;

	main_menu[33].indice_display = TLIM4;
	main_menu[33].prox			= &main_menu[34];
	main_menu[33].tag			= LIM4;

	main_menu[34].indice_display = TLIM4HIST;
	main_menu[34].prox			= &main_menu[35];
	main_menu[34].tag			= LIM4HIST;

	main_menu[35].indice_display = TTALIM4;
	main_menu[35].prox			= &main_menu[36];
	main_menu[35].tag			= TALIM4;

	main_menu[36].indice_display = TTDLIM4;
	main_menu[36].prox			= &main_menu[37];
	main_menu[36].tag			= TDLIM4;

	main_menu[37].indice_display = THOLD4Y;//Preset
	main_menu[37].prox			= &main_menu[38];
	main_menu[37].tag			= HOLD4Y;

	main_menu[38].indice_display = TOPPRESET2;
	main_menu[38].prox			= &main_menu[39];
	main_menu[38].tag			= OPPRESET2;

	main_menu[39].indice_display = TPRESET2;//
	main_menu[39].prox			= &main_menu[40];
	main_menu[39].tag			= PRESET2;

	main_menu[40].indice_display = TFILTRO2;//Preset
	main_menu[40].prox			= &main_menu[41];
	main_menu[40].tag			= FILTRO2;

	main_menu[41].indice_display = TESCALA0_2;
	main_menu[41].prox			= &main_menu[42];
	main_menu[41].tag			= ESCALA0_2;

	main_menu[42].indice_display = TESCALA1_2;
	main_menu[42].prox			= &main_menu[43];
	main_menu[42].tag			= ESCALA1_2;

	main_menu[43].indice_display = TANALOGICA0_2;
	main_menu[43].prox			= &main_menu[44];
	main_menu[43].tag			= ANALOGICA0_2;

	main_menu[44].indice_display = TANALOGICA1_2;
	main_menu[44].prox			= &main_menu[45];
	main_menu[44].tag			= ANALOGICA1_2;

	main_menu[45].indice_display = TMODOMED2;
	main_menu[45].prox			= &main_menu[46];
	main_menu[45].tag			= MODOMED2;

	main_menu[46].indice_display = TSENHA;    
	main_menu[46].prox			= &main_menu[47];
	main_menu[46].tag			= SENHA;

	main_menu[47].indice_display = TSAIR;
	main_menu[47].prox			= &main_menu[0];
	main_menu[47].tag			= SAIR;
}


void inc_dec(void)
{
	char i;

	menu_aux = *ptrglobal;
	if ((incremento == 1) && (menu_aux.prox != NULL_) && (modo == MODO_MENU))
	{
		ptrglobal = menu_aux.prox;
		menu_aux = *ptrglobal;
	}
	else if ((incremento == -1) /*&& (menu_aux.anter != NULL_) */&& (modo == MODO_MENU))
	{
		//ptrglobal = menu_aux.anter;
		//menu_aux = *ptrglobal;
		if(ptrglobal== &main_menu[0])ptrglobal = &main_menu[47];
		else if(ptrglobal== &main_menu[47])ptrglobal = &main_menu[46];
		else ptrglobal = (menu_aux.prox-2);

		menu_aux = *ptrglobal;
	}

	if ((modo == MODO_MENU) || (modo == MODO_PROGRAMAR) || (modo == MODO_GRAVAR))
	{
	
		if (modo == MODO_MENU)
		{	Pos = 0;
			if(menu_aux.indice_display==TPRESET){
				TextoBuffer[0] = 125;//P
				TextoBuffer[1] = 265;//r
				TextoBuffer[2] = 200;//e
				TextoBuffer[3] = 270;//s
				TextoBuffer[4] = 275;//t
				TextoBuffer[5] = 165;//X
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = preset1.value;
				tempValue.decPoint = preset1.decPoint;
			}
			if(menu_aux.indice_display==TPRESET2){
				TextoBuffer[0] = 125;//P
				TextoBuffer[1] = 265;//r
				TextoBuffer[2] = 200;//e
				TextoBuffer[3] = 270;//s
				TextoBuffer[4] = 275;//t
				TextoBuffer[5] = 170;//Y
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = preset2.value;
				tempValue.decPoint = preset2.decPoint;
			}
			else if(menu_aux.indice_display==TOPPRESET1){
				TextoBuffer[0] = 120;//O
				TextoBuffer[1] = 255;//p
				TextoBuffer[2] = 125;//P
				TextoBuffer[3] = 265;//r
				TextoBuffer[4] = 200;//e
				TextoBuffer[5] = 270;//s
				TextoBuffer[6] = 275;//t
				TextoBuffer[7] =  165;//X
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TOPPRESET2){
				TextoBuffer[0] = 120;//O
				TextoBuffer[1] = 255;//p
				TextoBuffer[2] = 125;//P
				TextoBuffer[3] = 265;//r
				TextoBuffer[4] = 200;//e
				TextoBuffer[5] = 270;//s
				TextoBuffer[6] = 275;//t
				TextoBuffer[7] =  170;//Y
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TPONTODEC){
				TextoBuffer[0] = 125;//P
				TextoBuffer[1] = 250;//o
				TextoBuffer[2] = 245;//n
				TextoBuffer[3] = 275;//t
				TextoBuffer[4] = 250;//o
				TextoBuffer[5] = 65;//D
				TextoBuffer[6] = 200;//e
				TextoBuffer[7] = 190;//c
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = counter.value;
				tempValue.decPoint = counter.decPoint;
			}
			else if(menu_aux.indice_display==TNUMDIG){//
				TextoBuffer[0] = 115;//N
				TextoBuffer[1] = 280;//u
				TextoBuffer[2] = 240;//m
				TextoBuffer[3] = 65;//D
				TextoBuffer[4] = 220;//i
				TextoBuffer[5] = 210;//g
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TCONSTMULT){
				TextoBuffer[0] = 60;//C
				TextoBuffer[1] = 250;//o
				TextoBuffer[2] = 245;//n
				TextoBuffer[3] = 270;//s
				TextoBuffer[4] = 275;//t
				TextoBuffer[5] = 365;//* (vezes)
				TextoBuffer[6] = 165;//X
				TextoBuffer[7] = 310;//)
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = k2.value;
				tempValue.decPoint = k2.decPoint;
			}
			else if(menu_aux.indice_display==TCONSTMULT2){
				TextoBuffer[0] = 60;//C
				TextoBuffer[1] = 250;//o
				TextoBuffer[2] = 245;//n
				TextoBuffer[3] = 270;//s
				TextoBuffer[4] = 275;//t
				TextoBuffer[5] = 365;//* (vezes)
				TextoBuffer[6] = 170;//Y
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = k3.value;
				tempValue.decPoint = k3.decPoint;
			}
			else if(menu_aux.indice_display==TLIM1){
				TextoBuffer[0] = 105;//L
				TextoBuffer[1] = 220;//i
				TextoBuffer[2] = 240;//m
				TextoBuffer[3] = 5;  //1
				TextoBuffer[4] = 165;//X
				TextoBuffer[5] = 310;//
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = lim1.value;
				tempValue.decPoint = lim1.decPoint;
			}
			else if(menu_aux.indice_display==TOPLIM1){
				TextoBuffer[0] = 120;//O
				TextoBuffer[1] = 255;//p
				TextoBuffer[2] = 105;//L
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 240;//m
				TextoBuffer[5] = 5;//1
				TextoBuffer[6] = 165;//X
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TLIM1HIST){
				TextoBuffer[0] = 85;//H
				TextoBuffer[1] = 220;//i
				TextoBuffer[2] = 270;//s
				TextoBuffer[3] = 275;//t
				TextoBuffer[4] = 5;//1
				TextoBuffer[5] = 165;//X
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = lim1hist.value;
				tempValue.decPoint = lim1hist.decPoint;
			}
			else if(menu_aux.indice_display==TLIM2){
				TextoBuffer[0] = 105;//L
				TextoBuffer[1] = 220;//i
				TextoBuffer[2] = 240;//m
				TextoBuffer[3] = 10;//2
				TextoBuffer[4] = 165;//X
				TextoBuffer[5] = 310;//
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = lim2.value;
				tempValue.decPoint = lim2.decPoint;
			}
			else if(menu_aux.indice_display==TOPLIM2){
				TextoBuffer[0] = 120;//O
				TextoBuffer[1] = 255;//p
				TextoBuffer[2] = 105;//L
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 240;//m
				TextoBuffer[5] = 10;//2
				TextoBuffer[6] = 165;//X
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TLIM2HIST){
				TextoBuffer[0] = 85;//H
				TextoBuffer[1] = 220;//i
				TextoBuffer[2] = 270;//s
				TextoBuffer[3] = 275;//t
				TextoBuffer[4] = 10;//2
				TextoBuffer[5] = 165;//X
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//

				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = lim2hist.value;
				tempValue.decPoint = lim2hist.decPoint;
			}
			else if(menu_aux.indice_display==TESCALA0){
				TextoBuffer[0] = 70;//E
				TextoBuffer[1] = 0;//0
				TextoBuffer[2] = 165;//X
				TextoBuffer[3] = 310;//
				TextoBuffer[4] = 310;//
				TextoBuffer[5] = 310;//
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = escala0.value;
				tempValue.decPoint = escala0.decPoint;
			}
			else if(menu_aux.indice_display==TANALOGICA0){
				TextoBuffer[0] = 50;//A
				TextoBuffer[1] = 245;//n
				TextoBuffer[2] = 180;//a
				TextoBuffer[3] = 60;//C
				TextoBuffer[4] = 180;//a
				TextoBuffer[5] = 235;//l
				TextoBuffer[6] = 0;//0
				TextoBuffer[7] = 165;//X
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TMEDIA){
				TextoBuffer[0] = 110;//M
				TextoBuffer[1] = 200;//e
				TextoBuffer[2] = 195;//d
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 180;//a
				TextoBuffer[5] = 310;//
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = Media_.value;
				tempValue.decPoint = Media_.decPoint;
			}
			else if(menu_aux.indice_display==TESCALA1){
				TextoBuffer[0] = 70;//E
				TextoBuffer[1] = 5;//1
				TextoBuffer[2] = 165;//X
				TextoBuffer[3] = 310;//
				TextoBuffer[4] = 310;//
				TextoBuffer[5] = 310;//
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = escala1.value;
				tempValue.decPoint = escala1.decPoint;
			}
			else if(menu_aux.indice_display==TANALOGICA1){
				TextoBuffer[0] = 50;//A
				TextoBuffer[1] = 245;//n
				TextoBuffer[2] = 180;//a
				TextoBuffer[3] = 60;//C
				TextoBuffer[4] = 180;//a
				TextoBuffer[5] = 235;//l
				TextoBuffer[6] = 5;//1
				TextoBuffer[7] = 165;//X
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TSENHA){//Senha
				TextoBuffer[0] = 140;//S
				TextoBuffer[1] = 200;//e
				TextoBuffer[2] = 245;//n
				TextoBuffer[3] = 215;//h
				TextoBuffer[4] = 180;//a
				TextoBuffer[5] = 310;//
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}	
			else if(menu_aux.indice_display==TSAIR){//Sair
				TextoBuffer[0] = 140;//S
				TextoBuffer[1] = 180;//a
				TextoBuffer[2] = 220;//i
				TextoBuffer[3] = 265;//r
				TextoBuffer[4] = 310;//
				TextoBuffer[5] = 310;//
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TUNIDADE){//Unidade
				TextoBuffer[0] = 150;//U
				TextoBuffer[1] = 245;//n
				TextoBuffer[2] = 220;//i
				TextoBuffer[3] = 195;//d
				TextoBuffer[4] = 180;//a
				TextoBuffer[5] = 195;//d
				TextoBuffer[6] = 200;//e
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TTALIM1){//Ta.Lim1
				TextoBuffer[0] = 145;//T
				TextoBuffer[1] = 180;//a
				TextoBuffer[2] = 105;//L
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 240;//m
				TextoBuffer[5] = 5;//1
				TextoBuffer[6] = 165;//X
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = TaLim1.value;
				tempValue.decPoint = TaLim1.decPoint;
			}
			else if(menu_aux.indice_display==TTDLIM1){//Td.Lim1
				TextoBuffer[0] = 145;//T
				TextoBuffer[1] = 195;//d
				TextoBuffer[2] = 105;//L
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 240;//m
				TextoBuffer[5] = 5;//1
				TextoBuffer[6] = 165;//X
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = TdLim1.value;
				tempValue.decPoint = TdLim1.decPoint;
			}
			else if(menu_aux.indice_display==TTDLIM3){
				TextoBuffer[0] = 145;//T
				TextoBuffer[1] = 195;//d
				TextoBuffer[2] = 105;//L
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 240;//m
				TextoBuffer[5] = 3*5;//3
				TextoBuffer[6] = 170;//Y
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = TdLim3.value;
				tempValue.decPoint = TdLim3.decPoint;
			}
			else if(menu_aux.indice_display==TTALIM2){//Ta.Lim2
				TextoBuffer[0] = 145;//T
				TextoBuffer[1] = 180;//a
				TextoBuffer[2] = 105;//L
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 240;//m
				TextoBuffer[5] = 10;//2
				TextoBuffer[6] = 165;//X
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = TaLim2.value;
				tempValue.decPoint = TaLim2.decPoint;
			}
			else if(menu_aux.indice_display==TTDLIM2){//Td.Lim2
				TextoBuffer[0] = 145;//T
				TextoBuffer[1] = 195;//d
				TextoBuffer[2] = 105;//L
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 240;//m
				TextoBuffer[5] = 10;//2
				TextoBuffer[6] = 165;//X
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = TdLim2.value;
				tempValue.decPoint = TdLim2.decPoint;
			}
			else if(menu_aux.indice_display==THOLD1X){
				TextoBuffer[0] = 85;//H
				TextoBuffer[1] = 250;//o
				TextoBuffer[2] = 235;//l
				TextoBuffer[3] = 195;//d
				TextoBuffer[4] = 5;//1
				TextoBuffer[5] = 165;//X
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==THOLD2X){
				TextoBuffer[0] = 85;//H
				TextoBuffer[1] = 250;//o
				TextoBuffer[2] = 235;//l
				TextoBuffer[3] = 195;//d
				TextoBuffer[4] = 10;//2
				TextoBuffer[5] = 165;//X
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==THOLD3Y){
				TextoBuffer[0] = 85;//H
				TextoBuffer[1] = 250;//o
				TextoBuffer[2] = 235;//l
				TextoBuffer[3] = 195;//d
				TextoBuffer[4] = 15;//3
				TextoBuffer[5] = 170;//Y
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==THOLD4Y){
				TextoBuffer[0] = 85;//H
				TextoBuffer[1] = 250;//o
				TextoBuffer[2] = 235;//l
				TextoBuffer[3] = 195;//d
				TextoBuffer[4] = 20;//4
				TextoBuffer[5] = 170;//Y
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TFILTRO){//Filtro
				TextoBuffer[0] = 75;//F
				TextoBuffer[1] = 220;//i
				TextoBuffer[2] = 235;//l
				TextoBuffer[3] = 275;//t
				TextoBuffer[4] = 265;//r
				TextoBuffer[5] = 250;//o
				TextoBuffer[6] = 165;//X
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = FiltroRc.value;
				tempValue.decPoint = FiltroRc.decPoint;
			}
			else if(menu_aux.indice_display==TFILTRO2){//Filtro2
				TextoBuffer[0] = 75;//F
				TextoBuffer[1] = 220;//i
				TextoBuffer[2] = 235;//l
				TextoBuffer[3] = 275;//t
				TextoBuffer[4] = 265;//r
				TextoBuffer[5] = 250;//o
				TextoBuffer[6] = 170;//Y
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = FiltroRc2.value;
				tempValue.decPoint = FiltroRc2.decPoint;
			}
			else if(menu_aux.indice_display==TMODOMED1){//Modo Med
				TextoBuffer[0] = 110;//M
				TextoBuffer[1] = 250;//o
				TextoBuffer[2] = 195;//d
				TextoBuffer[3] = 250;//o
				TextoBuffer[4] = 110;//M
				TextoBuffer[5] = 200;//e
				TextoBuffer[6] = 195;//d
				TextoBuffer[7] = 165;//X
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TMODOMED2){//Modo Med2
				TextoBuffer[0] = 110;//M
				TextoBuffer[1] = 250;//o
				TextoBuffer[2] = 195;//d
				TextoBuffer[3] = 250;//o
				TextoBuffer[4] = 110;//M
				TextoBuffer[5] = 200;//e
				TextoBuffer[6] = 195;//d
				TextoBuffer[7] = 170;//Y
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
//-------------------------------------------------------------------------------------------
			else if(menu_aux.indice_display==TESCALA0_2){
				TextoBuffer[0] = 70;//E
				TextoBuffer[1] = 0;//0
				TextoBuffer[2] = 170;//Y
				TextoBuffer[3] = 310;//
				TextoBuffer[4] = 310;//
				TextoBuffer[5] = 310;//
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = escala0_2.value;
				tempValue.decPoint = escala0_2.decPoint;
			}
			else if(menu_aux.indice_display==TESCALA1_2){
				TextoBuffer[0] = 70;//E
				TextoBuffer[1] = 5;//1
				TextoBuffer[2] = 170;//Y
				TextoBuffer[3] = 310;//
				TextoBuffer[4] = 310;//
				TextoBuffer[5] = 310;//
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = escala1_2.value;
				tempValue.decPoint = escala1_2.decPoint;
			}
			else if(menu_aux.indice_display==TANALOGICA0_2){
				TextoBuffer[0] = 50;//A
				TextoBuffer[1] = 245;//n
				TextoBuffer[2] = 180;//a
				TextoBuffer[3] = 60;//C
				TextoBuffer[4] = 180;//a
				TextoBuffer[5] = 235;//l
				TextoBuffer[6] = 0;//0
				TextoBuffer[7] = 170;//Y
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TANALOGICA1_2){
				TextoBuffer[0] = 50;//A
				TextoBuffer[1] = 245;//n
				TextoBuffer[2] = 180;//a
				TextoBuffer[3] = 60;//C
				TextoBuffer[4] = 180;//a
				TextoBuffer[5] = 235;//l
				TextoBuffer[6] = 5;//1
				TextoBuffer[7] = 170;//Y
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TOPLIM3){
				TextoBuffer[0] = 120;//O
				TextoBuffer[1] = 255;//p
				TextoBuffer[2] = 105;//L
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 240;//m
				TextoBuffer[5] = 3*5;//3
				TextoBuffer[6] = 170;//Y
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
			else if(menu_aux.indice_display==TLIM3HIST){
				TextoBuffer[0] = 85;//H
				TextoBuffer[1] = 220;//i
				TextoBuffer[2] = 270;//s
				TextoBuffer[3] = 275;//t
				TextoBuffer[4] = 3*5;//3
				TextoBuffer[5] = 170;//Y
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = lim3hist.value;
				tempValue.decPoint = lim3hist.decPoint;
			}
			else if(menu_aux.indice_display==TLIM3){
				TextoBuffer[0] = 105;//L
				TextoBuffer[1] = 220;//i
				TextoBuffer[2] = 240;//m
				TextoBuffer[3] = 3*5;//3
				TextoBuffer[4] = 170;//Y
				TextoBuffer[5] = 310;//
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = lim3.value;
				tempValue.decPoint = lim3.decPoint;
			}
			else if(menu_aux.indice_display==TLIM4){
				TextoBuffer[0] = 105;//L
				TextoBuffer[1] = 220;//i
				TextoBuffer[2] = 240;//m
				TextoBuffer[3] = 4*5;//4
				TextoBuffer[4] = 170;//Y
				TextoBuffer[5] = 310;//
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = lim4.value;
				tempValue.decPoint = lim4.decPoint;
			}
			else if(menu_aux.indice_display==TTALIM3){//Ta.Lim3
				TextoBuffer[0] = 145;//T
				TextoBuffer[1] = 180;//a
				TextoBuffer[2] = 105;//L
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 240;//m
				TextoBuffer[5] = 3*5;//3
				TextoBuffer[6] = 170;//Y
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = TaLim3.value;
				tempValue.decPoint = TaLim3.decPoint;
			}
			else if(menu_aux.indice_display==TLIM4HIST){
				TextoBuffer[0] = 85;//H
				TextoBuffer[1] = 220;//i
				TextoBuffer[2] = 270;//s
				TextoBuffer[3] = 275;//t
				TextoBuffer[4] = 4*5;//4
				TextoBuffer[5] = 170;//Y
				TextoBuffer[6] = 310;//
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = lim4hist.value;
				tempValue.decPoint = lim4hist.decPoint;
			}
			else if(menu_aux.indice_display==TTALIM4){//Ta.Lim4
				TextoBuffer[0] = 145;//T
				TextoBuffer[1] = 180;//a
				TextoBuffer[2] = 105;//L
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 240;//m
				TextoBuffer[5] = 4*5;//4
				TextoBuffer[6] = 170;//Y
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = TaLim4.value;
				tempValue.decPoint = TaLim4.decPoint;
			}
			else if(menu_aux.indice_display==TTDLIM4){//Td.Lim4
				TextoBuffer[0] = 145;//T
				TextoBuffer[1] = 195;//d
				TextoBuffer[2] = 105;//L
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 240;//m
				TextoBuffer[5] = 4*5;//4
				TextoBuffer[6] = 170;//Y
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				tempValue.value = TdLim4.value;
				tempValue.decPoint = TdLim4.decPoint;
			}
			else if(menu_aux.indice_display==TOPLIM4){
				TextoBuffer[0] = 120;//O
				TextoBuffer[1] = 255;//p
				TextoBuffer[2] = 105;//L
				TextoBuffer[3] = 220;//i
				TextoBuffer[4] = 240;//m
				TextoBuffer[5] = 4*5;//4
				TextoBuffer[6] = 170;//Y
				TextoBuffer[7] = 310;//
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			}
		}
		else
		{
			switch(menu_aux.tag)
			{
			case NUMDIGITO:		
				if (((((NumDigDisplay+(inc)) <=5) && (incremento > 0)) || (((NumDigDisplay+inc) >= 1) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					NumDigDisplay += (inc);

					DispSigLong(NumDigDisplay,counter.decPoint,1,PISCA_OFF);

				if (modo == MODO_GRAVAR){	
					sendToEEPROM(45,(char*)&NumDigDisplay,4);	
				}	
				break;

			case CONSTMULT://constante de multiplicagco

				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);

				if(modo==MODO_GRAVAR){
					k2.value = tempValue.value;
					k2.decPoint= tempValue.decPoint;

	

					sendToEEPROM(10,(char*)&k2.value,4);
					sendToEEPROM(14,(char*)&k2.decPoint,1);
				}	
				break;

			case CONSTMULT2://constante de multiplicagco

				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);

				if(modo==MODO_GRAVAR){
					k3.value = tempValue.value;
					k3.decPoint= tempValue.decPoint;
					sendToEEPROM(180,(char*)&k3.value,4);
					sendToEEPROM(184,(char*)&k3.decPoint,1);


				}	
				break;
			case PRESET://Preset
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);

				if (modo == MODO_GRAVAR){			

					preset1.value = tempValue.value;
					preset1.decPoint= tempValue.decPoint;

			
					sendToEEPROM(50,(char*)&preset1.value,4);		
					sendToEEPROM(54,(char*)&preset1.decPoint,1);
				}	
				break;
			case PRESET2://Preset
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);

				if (modo == MODO_GRAVAR){			

					preset2.value = tempValue.value;
					preset2.decPoint= tempValue.decPoint;

			
					sendToEEPROM(185,(char*)&preset2.value,4);
					sendToEEPROM(189,(char*)&preset2.decPoint,1);

				}	
				break;
			case ESCALA0:

				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);

				if(modo==MODO_GRAVAR){
					escala0.value = tempValue.value;
					escala0.decPoint= tempValue.decPoint;	
					CalAnalogica();
					sendToEEPROM(23,(char*)&escala0.value,4);
					sendToEEPROM(27,(char*)&escala0.decPoint,1);
				}
				
				break;
			case ESCALA1:

				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);

				if(modo==MODO_GRAVAR){
					escala1.value = tempValue.value;
					escala1.decPoint= tempValue.decPoint;	
					CalAnalogica();		
					sendToEEPROM(28,(char*)&escala1.value,4);
					sendToEEPROM(32,(char*)&escala1.decPoint,1);		
				}
				
				break;
			case MEDIA:

				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);

				if(modo==MODO_GRAVAR){
					Media_.value = tempValue.value;
					Media_.decPoint= tempValue.decPoint;

					if(Media_.value ==0)Media_.value = 10000;//Nunca pode assumir o valor 0, forgo para 1 caso alguim configure com 0	
					NumTotalMedia = round((float)Media_.value/(float)10000.0);

					sendToEEPROM(101,(char*)&Media_.value,4);
					sendToEEPROM(105,(char*)&Media_.decPoint,1);
		
					for (i=0;i<100;i++){
						VetorMediaX[i] = 0;
						VetorMediaY[i] = 0;
						VetorMediaZ[i] = 0;
					}
					Media = 0;
MediaX=0;
MediaY=0;
MediaZ=0;
					ContMedia = 0;



				}
				
				break;


			case ANALOGICA0:		
				if (((((analogica0+(inc)) <=65535) && (incremento > 0)) || (((analogica0+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					analogica0 += (inc);
					dacSend1 (analogica0);
					DispSigLong(analogica0,0,7,PISCA_OFF);

				if (modo == MODO_GRAVAR){			
			
					CalAnalogica();
					sendToEEPROM(15,(char*)&analogica0,4);
				}	
				break;
			case ANALOGICA1:		
				if (((((analogica1+(inc)) <=65535) && (incremento > 0)) || (((analogica1+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					analogica1 += (inc);
					dacSend1 (analogica1);
					DispSigLong(analogica1,0,7,PISCA_OFF);

				if (modo == MODO_GRAVAR){
					CalAnalogica();			
					sendToEEPROM(19,(char*)&analogica1,4);
				}	
				break;

			case PONTODEC:
				ValDisp = val;
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_OFF);

				if(modo==MODO_GRAVAR){
					counter.decPoint = tempValue.decPoint;	
					sendToEEPROM(4,(char*)&counter.decPoint,1);
				}

				break;
			case HOLD1X:
				if (((((Hold1X+inc) <=1) && (incremento > 0)) || (((Hold1X+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					Hold1X += inc;

				switch(Hold1X){
					case  OFF:
						TextoBuffer[0] = 120;//O
						TextoBuffer[1] = 205;//f
						TextoBuffer[2] = 205;//f
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
					case  ON:
						TextoBuffer[0] = 120;//O
						TextoBuffer[1] = 245;//n
						TextoBuffer[2] = 310;//
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
				}
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

				if (modo == MODO_GRAVAR){			
					sendToEEPROM(69,(char*)&Hold1X,1);
				}	
				break;
			case HOLD2X:
				if (((((Hold2X+inc) <=1) && (incremento > 0)) || (((Hold2X+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					Hold2X += inc;

				switch(Hold2X){
					case  OFF:
						TextoBuffer[0] = 120;//O
						TextoBuffer[1] = 205;//f
						TextoBuffer[2] = 205;//f
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
					case  ON:
						TextoBuffer[0] = 120;//O
						TextoBuffer[1] = 245;//n
						TextoBuffer[2] = 310;//
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
				}

				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

				if (modo == MODO_GRAVAR){			
					sendToEEPROM(195,(char*)&Hold2X,1);
				}	

				break;
			case HOLD3Y:
				if (((((Hold3Y+inc) <=1) && (incremento > 0)) || (((Hold3Y+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					Hold3Y += inc;
				switch(Hold3Y){
					case  OFF:
						TextoBuffer[0] = 120;//O
						TextoBuffer[1] = 205;//f
						TextoBuffer[2] = 205;//f
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
					case  ON:
						TextoBuffer[0] = 120;//O
						TextoBuffer[1] = 245;//n
						TextoBuffer[2] = 310;//
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
				}
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

				if (modo == MODO_GRAVAR){			
					sendToEEPROM(196,(char*)&Hold3Y,1);
				}	
				break;
			case HOLD4Y:
				if (((((Hold4Y+inc) <=1) && (incremento > 0)) || (((Hold4Y+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					Hold4Y += inc;
				switch(Hold4Y){
					case  OFF:
						TextoBuffer[0] = 120;//O
						TextoBuffer[1] = 205;//f
						TextoBuffer[2] = 205;//f
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
					case  ON:
						TextoBuffer[0] = 120;//O
						TextoBuffer[1] = 245;//n
						TextoBuffer[2] = 310;//
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
				}
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

				if (modo == MODO_GRAVAR){			
					sendToEEPROM(197,(char*)&Hold4Y,1);
				}	
				break;

			case MODOMED1:
				if (((((ModoMed1+inc) <=1) && (incremento > 0)) || (((ModoMed1+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					ModoMed1+= inc;
				switch(ModoMed1){
					case  INVERSA:
/*						TextoBuffer[0] = 90;//I
						TextoBuffer[1] = 245;//n
						TextoBuffer[2] = 285;//v
						TextoBuffer[3] = 200;//e
						TextoBuffer[4] = 265;//r
						TextoBuffer[5] = 270;//s
						TextoBuffer[6] = 180;//a
						TextoBuffer[7] = 310;//
*/
						TextoBuffer[0] = 50;//A
						TextoBuffer[1] = 215;//h
						TextoBuffer[2] = 250;//o
						TextoBuffer[3] = 265;//r
						TextoBuffer[4] = 180;//a
						TextoBuffer[5] = 265;//r
						TextoBuffer[6] = 220;//i
						TextoBuffer[7] = 250;//o


					break;
					case  DIRETA:
/*
						TextoBuffer[0] = 65;//D
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 265;//r
						TextoBuffer[3] = 200;//e
						TextoBuffer[4] = 275;//t
						TextoBuffer[5] = 180;//a
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
*/
						TextoBuffer[0] = 85;//H
						TextoBuffer[1] = 250;//o
						TextoBuffer[2] = 265;//r
						TextoBuffer[3] = 180;//a
						TextoBuffer[4] = 265;//r
						TextoBuffer[5] = 220;//i
						TextoBuffer[6] = 250;//o
						TextoBuffer[7] = 310;//
					break;
				}
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

				if (modo == MODO_GRAVAR){			
					sendToEEPROM(70,(char*)&ModoMed1,1);
				}	
				break;
			case MODOMED2:
				if (((((ModoMed2+inc) <=1) && (incremento > 0)) || (((ModoMed2+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					ModoMed2+= inc;
				switch(ModoMed2){
					case  INVERSA:
/*						TextoBuffer[0] = 90;//I
						TextoBuffer[1] = 245;//n
						TextoBuffer[2] = 285;//v
						TextoBuffer[3] = 200;//e
						TextoBuffer[4] = 265;//r
						TextoBuffer[5] = 270;//s
						TextoBuffer[6] = 180;//a
						TextoBuffer[7] = 310;//
*/
						TextoBuffer[0] = 50;//A
						TextoBuffer[1] = 215;//h
						TextoBuffer[2] = 250;//o
						TextoBuffer[3] = 265;//r
						TextoBuffer[4] = 180;//a
						TextoBuffer[5] = 265;//r
						TextoBuffer[6] = 220;//i
						TextoBuffer[7] = 250;//o


					break;
					case  DIRETA:
/*
						TextoBuffer[0] = 65;//D
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 265;//r
						TextoBuffer[3] = 200;//e
						TextoBuffer[4] = 275;//t
						TextoBuffer[5] = 180;//a
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
*/
						TextoBuffer[0] = 85;//H
						TextoBuffer[1] = 250;//o
						TextoBuffer[2] = 265;//r
						TextoBuffer[3] = 180;//a
						TextoBuffer[4] = 265;//r
						TextoBuffer[5] = 220;//i
						TextoBuffer[6] = 250;//o
						TextoBuffer[7] = 310;//
					break;
				}
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

				if (modo == MODO_GRAVAR){			
		
					sendToEEPROM(179,(char*)&ModoMed2,1);

	
				}	
				break;
			case UNIDADE:
				if (((((Unidade+inc) <=1) && (incremento > 0)) || (((Unidade+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					Unidade += inc;
				switch(Unidade){
					case  MM:
						TextoBuffer[0] = 80;//G
						TextoBuffer[1] = 265;//r 
						TextoBuffer[2] = 180;//a
						TextoBuffer[3] = 280;//u
						TextoBuffer[4] = 270;//s
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
					case  CM:
						TextoBuffer[0] = 190;//c
						TextoBuffer[1] = 240;//m
						TextoBuffer[2] = 310;//
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
					case  M:
						TextoBuffer[0] = 240;//m
						TextoBuffer[1] = 310;//
						TextoBuffer[2] = 310;//
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
					case  LIVRE:
						TextoBuffer[0] = 105;//L
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 285;//v
						TextoBuffer[3] = 265;//r
						TextoBuffer[4] = 200;//e
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
				}
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

				if (modo == MODO_GRAVAR){			
					sendToEEPROM(71,(char*)&Unidade,1);
				}	
				break;


			case OPPRESET1://Op Preset
				if (((((OpPreset1+inc) <=1) && (incremento > 0)) || (((OpPreset1+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					OpPreset1 += inc;
				switch(OpPreset1){
					case  OFF:
						TextoBuffer[0] = 120;//O
						TextoBuffer[1] = 205;//f
						TextoBuffer[2] = 205;//f
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
					case  ON:
						TextoBuffer[0] = 120;//O
						TextoBuffer[1] = 245;//n
						TextoBuffer[2] = 310;//
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
				}
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

				if (modo == MODO_GRAVAR){			
					sendToEEPROM(49,(char*)&OpPreset1,1);
				}	
				break;

			case OPPRESET2://Op Preset
				if (((((OpPreset2+inc) <=1) && (incremento > 0)) || (((OpPreset2+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					OpPreset2 += inc;
				switch(OpPreset2){
					case  OFF:
						TextoBuffer[0] = 120;//O
						TextoBuffer[1] = 205;//f
						TextoBuffer[2] = 205;//f
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
					case  ON:
						TextoBuffer[0] = 120;//O
						TextoBuffer[1] = 245;//n
						TextoBuffer[2] = 310;//
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//
					break;
				}
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

				if (modo == MODO_GRAVAR){			
					
					sendToEEPROM(190,(char*)&OpPreset2,1);
				}	
				break;
			case OPLIM1://opLimite1
				if (((((oplim1+inc) <=3) && (incremento > 0)) || (((oplim1+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					oplim1 += inc;
					switch(oplim1){
						case  OP_GE:
							TextoBuffer[0] = 105;//L
							TextoBuffer[1] = 220;//i
							TextoBuffer[2] = 240;//m
							TextoBuffer[3] = 5;//1
							TextoBuffer[4] = 315;//-
							TextoBuffer[5] = 330;//(
							TextoBuffer[6] = 340;//>=
							TextoBuffer[7] = 335;//)
						break;
						case  OP_LE:
							TextoBuffer[0] = 105;//L
							TextoBuffer[1] = 220;//i
							TextoBuffer[2] = 240;//m
							TextoBuffer[3] = 5;//1
							TextoBuffer[4] = 315;//-
							TextoBuffer[5] = 330;//(
							TextoBuffer[6] = 345;//<=
							TextoBuffer[7] = 335;//)
						break;
						case  OP_NOP:
							TextoBuffer[0] = 105;//L
							TextoBuffer[1] = 220;//i
							TextoBuffer[2] = 240;//m
							TextoBuffer[3] = 5;//1
							TextoBuffer[4] = 315;//.
							TextoBuffer[5] = 120;//O
							TextoBuffer[6] = 205;//f
							TextoBuffer[7] = 205;//f
						break;
					case  OP_MODULO:
						TextoBuffer[0] = 105;//L
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 240;//m
						TextoBuffer[3] = 5;//1
						TextoBuffer[4] = 315;//-
						TextoBuffer[5] = 330;//(
						TextoBuffer[6] = 360;//+-
						TextoBuffer[7] = 335;//)
					break;
					}
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

					if (modo == MODO_GRAVAR){			
						sendToEEPROM(33,(char*)&oplim1,1);
					}

				break;

			case LIM1:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					
				lim1.value = tempValue.value;
					lim1.decPoint= tempValue.decPoint;
					sendToEEPROM(34,(char*)&lim1.value,4);
					sendToEEPROM(38,(char*)&lim1.decPoint,1);
				}
				break;

			case FILTRO:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					FiltroRc.value = tempValue.value;
					FiltroRc.decPoint= tempValue.decPoint;


					rcAux = (float)FiltroRc.value/(float)10000.0;//  filtro i de 1 segundo

					sendToEEPROM(76,(char*)&FiltroRc.value,4);		
					sendToEEPROM(80,(char*)&FiltroRc.decPoint,1);


				}
				break;
			case FILTRO2:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					FiltroRc2.value = tempValue.value;
					FiltroRc2.decPoint= tempValue.decPoint;
					rcAux2 = (float)FiltroRc2.value/(float)10000.0;//  filtro i de 1 segundo

					sendToEEPROM(174,(char*)&FiltroRc2.value,4);
					sendToEEPROM(178,(char*)&FiltroRc2.decPoint,1);

				}
				break;
			case TALIM1:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					TaLim1.value = tempValue.value;
					TaLim1.decPoint= tempValue.decPoint;
					sendToEEPROM(81,(char*)&TaLim1.value,4);		
					sendToEEPROM(85,(char*)&TaLim1.decPoint,1);

				}
				break;
			case TDLIM1:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					TdLim1.value = tempValue.value;
					TdLim1.decPoint= tempValue.decPoint;
					sendToEEPROM(86,(char*)&TdLim1.value,4);		
					sendToEEPROM(90,(char*)&TdLim1.decPoint,1);
				}
				break;
			case TDLIM3:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					TdLim3.value = tempValue.value;
					TdLim3.decPoint= tempValue.decPoint;

					sendToEEPROM(154,(char*)&TdLim3.value,4);
					sendToEEPROM(158,(char*)&TdLim3.decPoint,1);
	
				}
				break;

			case TALIM2:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					TaLim2.value = tempValue.value;
					TaLim2.decPoint= tempValue.decPoint;
					sendToEEPROM(91,(char*)&TaLim2.value,4);		
					sendToEEPROM(95,(char*)&TaLim2.decPoint,1);
				}
				break;
			case TDLIM2:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					TdLim2.value = tempValue.value;
					TdLim2.decPoint= tempValue.decPoint;
					sendToEEPROM(96,(char*)&TdLim2.value,4);		
					sendToEEPROM(100,(char*)&TdLim2.decPoint,1);
				}
				break;
			case LIM1HIST:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					lim1hist.value = tempValue.value;
					lim1hist.decPoint= tempValue.decPoint;
					sendToEEPROM(59,(char*)&lim1hist.value,4);		
					sendToEEPROM(63,(char*)&lim1hist.decPoint,1);
				}
				break;
			case LIM2HIST:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					lim2hist.value = tempValue.value;
					lim2hist.decPoint= tempValue.decPoint;			
					sendToEEPROM(64,(char*)&lim2hist.value,4);		
					sendToEEPROM(68,(char*)&lim2hist.decPoint,1);
				}
				break;
			case OPLIM2://opLimite1
				if (((((oplim2+inc) <=3) && (incremento > 0)) || (((oplim2+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					oplim2 += inc;
				switch(oplim2){
					case  OP_GE:
						TextoBuffer[0] = 105;//L
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 240;//m
						TextoBuffer[3] = 10;//2
						TextoBuffer[4] = 315;//-
						TextoBuffer[5] = 330;//(
						TextoBuffer[6] = 340;//>=
						TextoBuffer[7] = 335;//)
					break;
					case  OP_LE:
						TextoBuffer[0] = 105;//L
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 240;//m
						TextoBuffer[3] = 10;//2
						TextoBuffer[4] = 315;//-
						TextoBuffer[5] = 330;//(
						TextoBuffer[6] = 345;//<=
						TextoBuffer[7] = 335;//)
					break;
					case  OP_NOP:
						TextoBuffer[0] = 105;//L
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 240;//m
						TextoBuffer[3] = 10;//2
						TextoBuffer[4] = 315;//.
						TextoBuffer[5] = 120;//O
						TextoBuffer[6] = 205;//f
						TextoBuffer[7] = 205;//f
					break;
					case  OP_MODULO:
						TextoBuffer[0] = 105;//L
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 240;//m
						TextoBuffer[3] = 10;//2
						TextoBuffer[4] = 315;//-
						TextoBuffer[5] = 330;//(
						TextoBuffer[6] = 360;//+-
						TextoBuffer[7] = 335;//)
					break;
				}
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

				if (modo == MODO_GRAVAR){			
					sendToEEPROM(39,(char*)&oplim2,1);	
				}
				break;

			case LIM2:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					lim2.value = tempValue.value;
					lim2.decPoint= tempValue.decPoint;
					sendToEEPROM(40,(char*)&lim2.value,4);
					sendToEEPROM(44,(char*)&lim2.decPoint,1);
				}

				break;

			case SENHA:

				if(controle_senha==0){
					if (tecla == 3)// INCREMENTO
					{
						buffer_senha_nova_var1=incDigit (3,(unsigned long)buffer_senha_nova_var1);	
						DispUnsigLong(buffer_senha_nova_var1,8,3);
						
					}
					
					DispUnsigLong(buffer_senha_nova_var1,8,3);
										
					
				}
				else{
					if (tecla == 3)// INCREMENTO
					{
						buffer_senha_nova_var2=incDigit (3,(unsigned long)buffer_senha_nova_var2);
					}
					
					DispUnsigLong(buffer_senha_nova_var2,8,3);
				
				}
				tecla=0;
				break;
//-----------------------------------------------
			case LIM3:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					lim3.value = tempValue.value;
					lim3.decPoint= tempValue.decPoint;
					sendToEEPROM(134,(char*)&lim3.value,4);
					sendToEEPROM(138,(char*)&lim3.decPoint,1);
				}
				break;
			case LIM4:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					lim4.value = tempValue.value;
					lim4.decPoint= tempValue.decPoint;

					sendToEEPROM(139,(char*)&lim4.value,4);
					sendToEEPROM(143,(char*)&lim4.decPoint,1);

				}
				break;

			case LIM3HIST:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					lim3hist.value = tempValue.value;
					lim3hist.decPoint= tempValue.decPoint;
					sendToEEPROM(149,(char*)&lim3hist.value,4);
					sendToEEPROM(153,(char*)&lim3hist.decPoint,1);
				}
				break;
			case TALIM3:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					TaLim3.value = tempValue.value;
					TaLim3.decPoint= tempValue.decPoint;

					sendToEEPROM(144,(char*)&TaLim3.value,4);		
					sendToEEPROM(148,(char*)&TaLim3.decPoint,1);
				}
				break;
			case ANALOGICA0_2:		
				if (((((analogica0_2+(inc)) <=65535) && (incremento > 0)) || (((analogica0_2+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					analogica0_2 += (inc);
					dacSend2 (analogica0_2);
					DispSigLong(analogica0_2,0,7,PISCA_OFF);

				if (modo == MODO_GRAVAR){			
			
					
					sendToEEPROM(124,(char*)&analogica0_2,4);
					CalAnalogica2();
				}	
				break;
			case ANALOGICA1_2:		
				if (((((analogica1_2+(inc)) <=65535) && (incremento > 0)) || (((analogica1_2+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					analogica1_2 += (inc);
					dacSend2 (analogica1_2);
					DispSigLong(analogica1_2,0,7,PISCA_OFF);

				if (modo == MODO_GRAVAR){
					CalAnalogica2();			
					sendToEEPROM(129,(char*)&analogica1_2,4);
				
				}	
				break;

			case LIM4HIST:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					lim4hist.value = tempValue.value;
					lim4hist.decPoint= tempValue.decPoint;

			
					sendToEEPROM(164,(char*)&lim4hist.value,4);		
					sendToEEPROM(168,(char*)&lim4hist.decPoint,1);


				}
				break;
			case TALIM4:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					TaLim4.value = tempValue.value;
					TaLim4.decPoint= tempValue.decPoint;


					sendToEEPROM(159,(char*)&TaLim4.value,4);	
					sendToEEPROM(163,(char*)&TaLim4.decPoint,1);

				}
				break;

			case TDLIM4:	
				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				if (modo == MODO_GRAVAR){	
					TdLim4.value = tempValue.value;
					TdLim4.decPoint= tempValue.decPoint;

					sendToEEPROM(169,(char*)&TdLim4.value,4);
					sendToEEPROM(198,(char*)&TdLim4.decPoint,1);
				



				}
				break;

			case OPLIM4://opLimite1
				if (((((oplim4+inc) <=3) && (incremento > 0)) || (((oplim4+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					oplim4 += inc;
				switch(oplim4){
					case  OP_GE:
						TextoBuffer[0] = 105;//L
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 240;//m
						TextoBuffer[3] = 4*5;//4
						TextoBuffer[4] = 315;//-
						TextoBuffer[5] = 330;//(
						TextoBuffer[6] = 340;//>=
						TextoBuffer[7] = 335;//)
					break;
					case  OP_LE:
						TextoBuffer[0] = 105;//L
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 240;//m
						TextoBuffer[3] = 4*5;//4
						TextoBuffer[4] = 315;//-
						TextoBuffer[5] = 330;//(
						TextoBuffer[6] = 345;//<=
						TextoBuffer[7] = 335;//)
					break;
					case  OP_NOP:
						TextoBuffer[0] = 105;//L
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 240;//m
						TextoBuffer[3] = 4*5;//4
						TextoBuffer[4] = 315;//.
						TextoBuffer[5] = 120;//O
						TextoBuffer[6] = 205;//f
						TextoBuffer[7] = 205;//f
					break;
					case  OP_MODULO:
						TextoBuffer[0] = 105;//L
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 240;//m
						TextoBuffer[3] = 4*5;//4
						TextoBuffer[4] = 315;//-
						TextoBuffer[5] = 330;//(
						TextoBuffer[6] = 360;//+-
						TextoBuffer[7] = 335;//)
					break;
				}
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

				if (modo == MODO_GRAVAR){			
					sendToEEPROM(173,(char*)&oplim4,1);


				}
				break;

			case ESCALA0_2:

				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);

				if(modo==MODO_GRAVAR){
					escala0_2.value = tempValue.value;
					escala0_2.decPoint= tempValue.decPoint;	
					CalAnalogica2();
					sendToEEPROM(114,(char*)&escala0_2.value,4);
					sendToEEPROM(118,(char*)&escala0_2.decPoint,1);
				}
				
				break;
			case ESCALA1_2:

				ValDisp = tempValue.value;//valor em long que i enviado para o display
				for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
				DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);

				if(modo==MODO_GRAVAR){
					escala1_2.value = tempValue.value;
					escala1_2.decPoint= tempValue.decPoint;	
					CalAnalogica2();		
					sendToEEPROM(119,(char*)&escala1_2.value,4);
					sendToEEPROM(123,(char*)&escala1_2.decPoint,1);		
				}
				
				break;
			case OPLIM3:
				if (((((oplim3+inc) <=3) && (incremento > 0)) || (((oplim3+inc) >= 0) && (incremento < 0))) && (modo == MODO_PROGRAMAR))
					oplim3 += inc;
					switch(oplim3){
						case  OP_GE:
							TextoBuffer[0] = 105;//L
							TextoBuffer[1] = 220;//i
							TextoBuffer[2] = 240;//m
							TextoBuffer[3] = 3*5;//3
							TextoBuffer[4] = 315;//-
							TextoBuffer[5] = 330;//(
							TextoBuffer[6] = 340;//>=
							TextoBuffer[7] = 335;//)
						break;
						case  OP_LE:
							TextoBuffer[0] = 105;//L
							TextoBuffer[1] = 220;//i
							TextoBuffer[2] = 240;//m
							TextoBuffer[3] = 3*5;//3
							TextoBuffer[4] = 315;//-
							TextoBuffer[5] = 330;//(
							TextoBuffer[6] = 345;//<=
							TextoBuffer[7] = 335;//)
						break;
						case  OP_NOP:
							TextoBuffer[0] = 105;//L
							TextoBuffer[1] = 220;//i
							TextoBuffer[2] = 240;//m
							TextoBuffer[3] = 3*5;//3
							TextoBuffer[4] = 315;//.
							TextoBuffer[5] = 120;//O
							TextoBuffer[6] = 205;//f
							TextoBuffer[7] = 205;//f
						break;
					case  OP_MODULO:
						TextoBuffer[0] = 105;//L
						TextoBuffer[1] = 220;//i
						TextoBuffer[2] = 240;//m
						TextoBuffer[3] = 3*5;//3
						TextoBuffer[4] = 315;//-
						TextoBuffer[5] = 330;//(
						TextoBuffer[6] = 360;//+-
						TextoBuffer[7] = 335;//)
					break;
					}
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

					if (modo == MODO_GRAVAR){			

						sendToEEPROM(133,(char*)&oplim3,1);	


					}

				break;

//------------------------------------------------



			case SAIR:
				if (modo == MODO_PROGRAMAR) 
				{	
					modo = MODO_NORMAL;
					position = 0;
					VarTroca = 0;
					ptrglobal = &main_menu[0];
					menu_aux = *ptrglobal;

					TextoBuffer[7] = 310;// apaga o display
					TextoBuffer[6] = 310;
					TextoBuffer[5] = 310;
					TextoBuffer[4] = 310;
					TextoBuffer[3] = 310;
					TextoBuffer[2] = 310;
					TextoBuffer[1] = 310;
					TextoBuffer[0] = 310;
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				
				}
				break;
				
			}
			
		}//ELSE
	}

}//inc_dec




void Restaurar_Boot (void) {
char i, *p;
		
	keyboardScan();
	if (!TEC_IN3){//Boot tecla incremento
		TextoBuffer[0] =  55;//B
		TextoBuffer[1] = 250;//o
		TextoBuffer[2] = 250;//o
		TextoBuffer[3] = 275;//t
		TextoBuffer[4] = 310;
		TextoBuffer[5] = 310;
		TextoBuffer[6] = 310;
		TextoBuffer[7] = 310;
		fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

		counter.value = 0;
		sendToEEPROM(0,(char*)&counter.value,4);

		counter.decPoint = 1;
		sendToEEPROM(4,(char*)&counter.decPoint,1);
		
		tempValue.value = 0;
		sendToEEPROM(5,(char*)&tempValue.value,4);

		tempValue.decPoint = 0;
		sendToEEPROM(9,(char*)&tempValue.decPoint,1);

		k2.value = 10000;//multiplicagco
		sendToEEPROM(10,(char*)&k2.value,4);

		k2.decPoint = 1;
		sendToEEPROM(14,(char*)&k2.decPoint,1);
		
		analogica0 = 12747;
		sendToEEPROM(15,(char*)&analogica0,4);
		
		analogica1 = 63733;
		sendToEEPROM(19,(char*)&analogica1,4);	
	
		escala0.value = -300000;
		sendToEEPROM(23,(char*)&escala0.value,4);
		
		escala0.decPoint = 1;
		sendToEEPROM(27,(char*)&escala1.decPoint,1);
		
		escala1.value = 300000;
		sendToEEPROM(28,(char*)&escala1.value,4);
		
		escala1.decPoint = 1;
		sendToEEPROM(32,(char*)&escala1.decPoint,1);
		
		oplim1 = OP_MODULO;//OP_NOP;//OP_GE; OP_LE  
		sendToEEPROM(33,(char*)&oplim1,1);
		
		lim1.value = 50000;
		sendToEEPROM(34,(char*)&lim1.value,4);
		
		lim1.decPoint = 1;
		sendToEEPROM(38,(char*)&lim1.decPoint,1);
		
		oplim2 = OP_NOP;//OP_GE;//OP_LE  OP_NOP
		sendToEEPROM(39,(char*)&oplim2,1);	
	
		lim2.value = 0;//200000= 20.0
		sendToEEPROM(40,(char*)&lim2.value,4);
		
		lim2.decPoint = 1;
		sendToEEPROM(44,(char*)&lim2.decPoint,1);		

		NumDigDisplay = 5;
		sendToEEPROM(45,(char*)&NumDigDisplay,4);		

		OpPreset1 = ON;
		sendToEEPROM(49,(char*)&OpPreset1,1);		

		preset1.value = 0;//200000;
		sendToEEPROM(50,(char*)&preset1.value,4);		

		preset1.decPoint = 1;
		sendToEEPROM(54,(char*)&preset1.decPoint,1);

		senha_var = 123;
		sendToEEPROM(55,(char*)&senha_var,4);
		//micnery em 05/02
		lim1hist.value = 10000;
		sendToEEPROM(59,(char*)&lim1hist.value,4);		

		lim1hist.decPoint = 1;
		sendToEEPROM(63,(char*)&lim1hist.decPoint,1);

		lim2hist.value = 0;
		sendToEEPROM(64,(char*)&lim2hist.value,4);		

		lim2hist.decPoint = 1;
		sendToEEPROM(68,(char*)&lim2hist.decPoint,1);

		Hold1X = OFF;//ON;
		sendToEEPROM(69,(char*)&Hold1X,1);

		ModoMed1 =  DIRETA;
		sendToEEPROM(70,(char*)&ModoMed1,1);

		Unidade = MM;// MM=GRAU
		sendToEEPROM(71,(char*)&Unidade,1);

		Preset_ef_1 = 0;
		sendToEEPROM(72,(char*)&Preset_ef_1,4);

		FiltroRc.value = 2000;//0,2
		//FiltroRc.value = 0;
		sendToEEPROM(76,(char*)&FiltroRc.value,4);		

		FiltroRc.decPoint = 1;
		sendToEEPROM(80,(char*)&FiltroRc.decPoint,1);

		TaLim1.value = 10000;//10000; 10000= 1segundo
		sendToEEPROM(81,(char*)&TaLim1.value,4);		

		TaLim1.decPoint = 1;
		sendToEEPROM(85,(char*)&TaLim1.decPoint,1);

		TdLim1.value = 10000;//10000; 10000= 1segundo
		sendToEEPROM(86,(char*)&TdLim1.value,4);		
		TdLim1.decPoint = 1;
		sendToEEPROM(90,(char*)&TdLim1.decPoint,1);

		TaLim2.value = 0;//10000; 10000= 1segundo
		sendToEEPROM(91,(char*)&TaLim2.value,4);		
		TaLim2.decPoint = 1;
		sendToEEPROM(95,(char*)&TaLim2.decPoint,1);

		TdLim2.value = 0;//10000; 10000= 1segundo
		sendToEEPROM(96,(char*)&TdLim2.value,4);		
		TdLim2.decPoint = 1;
		sendToEEPROM(100,(char*)&TdLim2.decPoint,1);

		Media_.value = 10000;
		sendToEEPROM(101,(char*)&Media_.value,4);
		Media_.decPoint = 0;
		sendToEEPROM(105,(char*)&Media_.decPoint,1);
		NumTotalMedia = round((float)Media_.value/(float)10000.0);

		presetbuffer.value = 0;
		sendToEEPROM(110,(char*)&presetbuffer.value,4);

////////////////////////
		escala0_2.value = -300000;
		sendToEEPROM(114,(char*)&escala0_2.value,4);
		escala0_2.decPoint = 1;
		sendToEEPROM(118,(char*)&escala0_2.decPoint,1);

		escala1_2.value = 300000;
		sendToEEPROM(119,(char*)&escala1_2.value,4);
		escala1_2.decPoint = 1;
		sendToEEPROM(123,(char*)&escala1_2.decPoint,1);

		analogica0_2 = 12769;//12698;
		sendToEEPROM(124,(char*)&analogica0_2,4);

		analogica1_2 = 63733;
		sendToEEPROM(129,(char*)&analogica1_2,4);

		oplim3 = OP_MODULO;//OP_NOP;//OP_GE;//OP_LE  OP_NOP	
		sendToEEPROM(133,(char*)&oplim3,1);	

		lim3.value = 50000;//5,0
		sendToEEPROM(134,(char*)&lim3.value,4);
		lim3.decPoint = 1;
		sendToEEPROM(138,(char*)&lim3.decPoint,1);

		lim4.value = 0;//200000= 20.0
		sendToEEPROM(139,(char*)&lim4.value,4);
		lim4.decPoint = 1;
		sendToEEPROM(143,(char*)&lim4.decPoint,1);

		TaLim3.value = 10000;//10000; 10000= 1,0segundo
		sendToEEPROM(144,(char*)&TaLim3.value,4);		
		TaLim3.decPoint = 1;
		sendToEEPROM(148,(char*)&TaLim3.decPoint,1);

		lim3hist.value = 10000;//456000;
		sendToEEPROM(149,(char*)&lim3hist.value,4);	
	
		lim3hist.decPoint = 1;
		sendToEEPROM(153,(char*)&lim3hist.decPoint,1);

		TdLim3.value = 10000;
		sendToEEPROM(154,(char*)&TdLim3.value,4);
		TdLim3.decPoint = 1;
		sendToEEPROM(158,(char*)&TdLim3.decPoint,1);

		TaLim4.value = 0;//10000; 10000= 1,0segundo	
		sendToEEPROM(159,(char*)&TaLim4.value,4);	
		TaLim4.decPoint = 1;
		sendToEEPROM(163,(char*)&TaLim4.decPoint,1);


//-----------------------------------------
		lim4hist.value = 0;//888000;
		sendToEEPROM(164,(char*)&lim4hist.value,4);		
		lim4hist.decPoint = 1;
		sendToEEPROM(168,(char*)&lim4hist.decPoint,1);

		TdLim4.value = 0;//5 segundos
		sendToEEPROM(169,(char*)&TdLim4.value,4);
		TdLim4.decPoint = 1;
		sendToEEPROM(198,(char*)&TdLim4.decPoint,1);

		oplim4 = OP_NOP;//OP_GE;//OP_LE  OP_NOP	
		sendToEEPROM(173,(char*)&oplim4,1);


///////////////
		FiltroRc2.value = 2000;//0,2
		sendToEEPROM(174,(char*)&FiltroRc2.value,4);
		FiltroRc2.decPoint = 1;
		sendToEEPROM(178,(char*)&FiltroRc2.decPoint,1);

		ModoMed2 =  DIRETA;
		sendToEEPROM(179,(char*)&ModoMed2,1);

		k3.value = 10000;//multiplicagco
		sendToEEPROM(180,(char*)&k3.value,4);
		k3.decPoint = 1;
		sendToEEPROM(184,(char*)&k3.decPoint,1);

		preset2.value = 0;//2220000;
		sendToEEPROM(185,(char*)&preset2.value,4);
		preset2.decPoint = 1;
		sendToEEPROM(189,(char*)&preset2.decPoint,1);

		OpPreset2 = ON;
		sendToEEPROM(190,(char*)&OpPreset2,1);	


		Preset_ef_2 = 0;
		sendToEEPROM(191,(char*)&Preset_ef_2,4);


		Hold2X = OFF;//ON;
		sendToEEPROM(195,(char*)&Hold2X,1);

		Hold3Y = OFF;//ON;
		sendToEEPROM(196,(char*)&Hold3Y,1);

		Hold4Y = OFF;//ON;
		sendToEEPROM(197,(char*)&Hold4Y,1);





/////////////


		while (!TEC_IN3);
	}else{//restaura as variaveis sem boot
		p=(char *)&counter.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i);
	
		p=(char *)&counter.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+4);
	
		p=(char *)&tempValue.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+5);
	
		p=(char *)&tempValue.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+9);
	
		p=(char *)&k2.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+10);
	
		p=(char *)&k2.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+14);	
	
		p=(char *)&analogica0;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+15);
	
		p=(char *)&analogica1;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+19);
		
		p=(char *)&escala0.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+23);
	
		p=(char *)&escala0.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+27);		
		
		p=(char *)&escala1.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+28);
	
		p=(char *)&escala1.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+32);
			
		p=(char *)&oplim1;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+33);
	
		p=(char *)&lim1.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+34);
	
		p=(char *)&lim1.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+38);
			
		p=(char *)&oplim2;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+39);
	
		p=(char *)&lim2.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+40);
	
		p=(char *)&lim2.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+44);
			
		p=(char *)&NumDigDisplay;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+45);
	
		p=(char *)&OpPreset1;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+49);
	
		p=(char *)&preset1.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+50);
	
		p=(char *)&preset1.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+54);
	
		p=(char *)&senha_var;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+55);
	
		p=(char *)&lim1hist.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+59);
	
		p=(char *)&lim1hist.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+63);
	
		p=(char *)&lim2hist.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+64);
	
		p=(char *)&lim2hist.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+68);

		p=(char *)&Hold1X;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+69);
	
		p=(char *)&ModoMed1;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+70);

		p=(char *)&Unidade;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+71);

		p=(char *)&Preset_ef_1;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+72);

		p=(char *)&FiltroRc.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+76);

		p=(char *)&FiltroRc.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+80);

		p=(char *)&TaLim1.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+81);

		p=(char *)&TaLim1.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+85);

		p=(char *)&TdLim1.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+86);

		p=(char *)&TdLim1.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+90);

		p=(char *)&TaLim2.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+91);

		p=(char *)&TaLim2.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+95);

		p=(char *)&TdLim2.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+96);

		p=(char *)&TdLim2.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+100);

		p=(char *)&Media_.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+101);

		p=(char *)&Media_.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+105);
		
		NumTotalMedia = round((float)Media_.value/(float)10000.0);

		p=(char *)&presetbuffer.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+110);
//-----------------------------

		p=(char *)&escala0_2.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+114);

		p=(char *)&escala0_2.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+118);

		p=(char *)&escala1_2.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+119);

		p=(char *)&escala1_2.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+123);

		p=(char *)&analogica0_2;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+124);
		
		p=(char *)&analogica1_2;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+129);
		
		p=(char *)&oplim3;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+133);

		p=(char *)&lim3.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+134);

		p=(char *)&lim3.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+138);
	
		p=(char *)&lim4.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+139);

		p=(char *)&lim4.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+143);

		p=(char *)&TaLim3.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+144);		

		p=(char *)&TaLim3.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+148);
	
		p=(char *)&lim3hist.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+149);		

		p=(char *)&lim3hist.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+153);

		p=(char *)&TdLim3.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+154);

		p=(char *)&TdLim3.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+158);
	
		p=(char *)&TaLim4.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+159);	

		p=(char *)&TaLim4.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+163);

		p=(char *)&lim4hist.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+164);	

		p=(char *)&lim4hist.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+168);

		p=(char *)&TdLim4.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+169);

		p=(char *)&TdLim4.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+198);
		 
		p=(char *)&oplim4;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+173);

		p=(char *)&FiltroRc2.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+174);

		p=(char *)&FiltroRc2.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+178);

		p=(char *)&ModoMed2;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+179);

		p=(char *)&k3.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+180);
	
		p=(char *)&k3.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+184);

		p=(char *)&preset2.value;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+185);

		p=(char *)&preset2.decPoint;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+189);

		p=(char *)&OpPreset2;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+190);

		p=(char *)&Preset_ef_2;
		for(i=0;i<4;i++) *(p++) = eeprom_read(i+191);



		p=(char *)&Hold2X;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+195);

		p=(char *)&Hold3Y;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+196);

		p=(char *)&Hold4Y;
		for(i=0;i<1;i++) *(p++) = eeprom_read(i+197);
	}

	rcAux = (float)FiltroRc.value/(float)10000.0;//  filtro i de 1 segundo
	CalAnalogica();
	rcAux2 = (float)FiltroRc2.value/(float)10000.0;//  filtro i de 1 segundo
	CalAnalogica2();
}


unsigned long incDigit (unsigned char num_dig,unsigned long var_long) {
	char i;
	long fator;

	if(position>=num_dig)position = 0;
	fator = 1;
	for (i = 0; i < position; i++)
	{
 		fator *= 10;
	}
	var_long += fator;
	if (((var_long / fator) % 10) == 0) 
	{
		var_long -= (fator * 10);	
	}
	return(var_long);
}
void CalAnalogica(void)
{
	a1 = ((float)analogica1-(float)analogica0)/((float)escala1.value-(float)escala0.value);
	b1 = (float)(analogica0) - (a1 * (float)escala0.value);

}
void CalAnalogica2(void)
{
	a2 = ((float)analogica1_2-(float)analogica0_2)/((float)escala1_2.value-(float)escala0_2.value);
	b2 = (float)(analogica0_2) - (a2 * (float)escala0_2.value);

}


signed long round(float x)
{
	float y;
	signed long z, w;

	if (x < 0)
		y = -x*10;
	else
		y = x*10;

	z = (signed long)y;
	w = z/10;
	z = z % 10;

	if (z >= 5)
		w++;

	if (x < 0) w=-w;

	return(w);
}




void atraso2(void)
{
	unsigned long index=0, tempo;
	for(tempo=0;tempo<125;tempo++)
	{ 
		for(index=0;index<10000;index++)
		{
//ClrWdt();
		Nop();
		}
	}
}


void EnviaEEProm(unsigned char endereco,long variavel){
	unsigned int VarLow, VarHi;

}


long LeEEprom(unsigned char x){
	unsigned long var, enderecoHi, enderecoLow;

	return ;
}



void MensInicial(void){
	TextoBuffer[0] = 155;//V	VERSCO
	TextoBuffer[1] = 5;  //1
	TextoBuffer[2] = 325;//.
	TextoBuffer[3] = 0;  //0
	TextoBuffer[4] = 5;  //1       
	TextoBuffer[5] = 310;// 
	TextoBuffer[6] = 310;// 
	TextoBuffer[7] = 310;// 
	fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
	atraso2();

}

void LimOut(void){
	counter.value = (signed long)MedidaFiltX;
	if(Unidade!=LIVRE){
		d = ( long)((double)lim1.value ) ;
		hist = ( long)((double)lim1hist.value ) ;
	}else{
		d = ( long)((double)lim1.value /(k2.value/10000)) ;
		hist = ( long)((double)lim1hist.value /(k2.value/10000)) ;
	}
	switch (oplim1) {
		case OP_GE:
			if (counter.value >= d){
				ContTdLim1 = 0;
				FlagLim1Out = 1;
			}
			else if (counter.value < d-hist){
				FlagLim1Out = 0;
				ContTaLim1 = 0;
			}
			break;
		case OP_LE:
			if (counter.value <= d){
				ContTdLim1 = 0;
				FlagLim1Out = 1;
			}
			else if (counter.value > d+hist){
				FlagLim1Out = 0;
				ContTaLim1 = 0;
			}
			break;
		case OP_MODULO:
			if(d<0)d = -d;
			if ( (counter.value>=d) || (counter.value<=-d) ){
				ContTdLim1 = 0;
				FlagLim1Out = 1;
			}
			else if( (counter.value<d-hist) && (counter.value>-d+hist) ){
				FlagLim1Out = 0;
				ContTaLim1 = 0;
			}
			break;

		case OP_NOP:
			FlagLim1Out = 0;
	}
	

	if(Unidade!=LIVRE){
		d = ( long)((double)lim2.value ) ;
		hist = ( long)((double)lim2hist.value ) ;
	}else{
		d = ( long)((double)lim2.value /(k2.value/10000)) ;
		hist = ( long)((double)lim2hist.value /(k2.value/10000)) ;
	}

	switch (oplim2) {
		case OP_GE:
			if (counter.value >= d){
				ContTdLim2 = 0;
				FlagLim2Out = 1;
			}
			else if (counter.value < d-hist){
				FlagLim2Out = 0;
				ContTaLim2 = 0;
			}
			break;
		case OP_LE:
			if (counter.value <= d){
				ContTdLim2 = 0;
				FlagLim2Out = 1;
			}
			else if (counter.value > d+hist){
				FlagLim2Out = 0;
				ContTaLim2 = 0;
			}
			break;
		case OP_MODULO:
			if(d<0)d = -d;
			if ( (counter.value>=d) || (counter.value<=-d) ){
				ContTdLim2 = 0;
				FlagLim2Out = 1;
			}
			else if( (counter.value<d-hist) && (counter.value>-d+hist) ){
				FlagLim2Out = 0;
				ContTaLim2 = 0;
			}
			break;
		case OP_NOP:
			FlagLim2Out = 0;
	}


	counter.value = (signed long)MedidaFiltY;
	if(Unidade!=LIVRE){
		d = ( long)((double)lim3.value ) ;
		hist = ( long)((double)lim3hist.value ) ;
	}else{
		d = ( long)((double)lim3.value /(k3.value/10000)) ;
		hist = ( long)((double)lim3hist.value /(k3.value/10000)) ;
	}
	switch (oplim3) {
		case OP_GE:
			if (counter.value >= d){
				ContTdLim3 = 0;
				FlagLim3Out = 1;
			}
			else if (counter.value < d-hist){
				FlagLim3Out = 0;
				ContTaLim3 = 0;
			}
			break;
		case OP_LE:
			if (counter.value <= d){
				ContTdLim3 = 0;
				FlagLim3Out = 1;
			}
			else if (counter.value > d+hist){
				FlagLim3Out = 0;
				ContTaLim3 = 0;
			}
			break;
		case OP_MODULO:
			if(d<0)d = -d;
			if ( (counter.value>=d) || (counter.value<=-d) ){
				ContTdLim3 = 0;
				FlagLim3Out = 1;
			}
			else if( (counter.value<d-hist) && (counter.value>-d+hist) ){
				FlagLim3Out = 0;
				ContTaLim3 = 0;
			}
			break;

		case OP_NOP:
			FlagLim3Out = 0;
	}

	if(Unidade!=LIVRE){
		d = ( long)((double)lim4.value ) ;
		hist = ( long)((double)lim4hist.value ) ;
	}else{
		d = ( long)((double)lim4.value /(k3.value/10000)) ;
		hist = ( long)((double)lim4hist.value /(k3.value/10000)) ;
	}

	switch (oplim4) {
		case OP_GE:
			if (counter.value >= d){
				ContTdLim4 = 0;
				FlagLim4Out = 1;
			}
			else if (counter.value < d-hist){
				FlagLim4Out = 0;
				ContTaLim4 = 0;
			}
			break;
		case OP_LE:
			if (counter.value <= d){
				ContTdLim4 = 0;
				FlagLim4Out = 1;
			}
			else if (counter.value > d+hist){
				FlagLim4Out = 0;
				ContTaLim4 = 0;
			}
			break;
		case OP_MODULO:
			if(d<0)d = -d;
			if ( (counter.value>=d) || (counter.value<=-d) ){
				ContTdLim4 = 0;
				FlagLim4Out = 1;
			}
			else if( (counter.value<d-hist) && (counter.value>-d+hist) ){
				FlagLim4Out = 0;
				ContTaLim4 = 0;
			}
			break;
		case OP_NOP:
			FlagLim4Out = 0;
	}



	if(Flag100ms){
		if(Hold1X==OFF){
			if(FlagLim1Out){
				ContTaLim1++;
				if((ContTaLim1)>=(TaLim1.value/1000)){
					LIM1_OUT = 1;
					ContTaLim1 = 0;
				}
			}
			if(!FlagLim1Out){
				ContTdLim1++;
				if(ContTdLim1>=(TdLim1.value/1000)){
					LIM1_OUT = 0;
					ContTdLim1 = 0;
				}
			}
		}else{//on
			if(FlagLim1Out){
				ContTaLim1++;
				if((ContTaLim1)>=(TaLim1.value/1000)){
					LIM1_OUT = 1;
					ContTaLim1 = 0;
				}
			}
		}
	
		if(Hold2X==OFF){
			if(FlagLim2Out){
				ContTaLim2++;
				if((ContTaLim2)>=(TaLim2.value/1000)){
					LIM2_OUT = 1;
					ContTaLim2 = 0;
				}
			}
			if(!FlagLim2Out){
				ContTdLim2++;
				if(ContTdLim2>=(TdLim2.value/1000)){
					LIM2_OUT = 0;
					ContTdLim2 = 0;
				}
			}
		}else{//on
			if(FlagLim2Out){
				ContTaLim2++;
				if((ContTaLim2)>=(TaLim2.value/1000)){
					LIM2_OUT = 1;
					ContTaLim2 = 0;
				}
			}
	
		}
	
		if(Hold3Y==OFF){
			if(FlagLim3Out){
				ContTaLim3++;
				if((ContTaLim3)>=(TaLim3.value/1000)){
					LIM3_OUT = 1;
					ContTaLim3 = 0;
				}
			}
			if(!FlagLim3Out){
				ContTdLim3++;
				if(ContTdLim3>=(TdLim3.value/1000)){
					LIM3_OUT = 0;
					ContTdLim3 = 0;
				}
			}
		}else{//on
			if(FlagLim3Out){
				ContTaLim3++;
				if((ContTaLim3)>=(TaLim3.value/1000)){
					LIM3_OUT = 1;
					ContTaLim3 = 0;
				}
			}
		}
		if(Hold4Y==OFF){
			if(FlagLim4Out){
				ContTaLim4++;
				if((ContTaLim4)>=(TaLim4.value/1000)){
					LIM4_OUT = 1;
					ContTaLim4 = 0;
				}
			}
			if(!FlagLim4Out){
				ContTdLim4++;
				if(ContTdLim4>=(TdLim4.value/1000)){
					LIM4_OUT = 0;
					ContTdLim4 = 0;
				}
			}
		}else{//on
			if(FlagLim4Out){
				ContTaLim4++;
				if((ContTaLim4)>=(TaLim4.value/1000)){
					LIM4_OUT = 1;
					ContTaLim4 = 0;
				}
			}
		}
		Flag100ms = 0;
	}




}





void AtualizaDisp(void){
	char i;
	if(atualiza_disp){//aproximadamente 300ms
		if(modo==MODO_NORMAL){			
			if(VarTroca==0)	val=ValX;	
			else if(VarTroca==1)val = Val2;
			else if(VarTroca==2)val = ValZ;	

			if(ContDelayPreset<TEMPO_PRESET)ContDelayPreset++;
	
			if(ContPiscadaDisplay<TEMPO_PISCA_DISPLAY)ContPiscadaDisplay++;
			if(!Falha2){
				if(ContDelayPreset>=TEMPO_PRESET){
					if((ContPiscadaDisplay<3)||
					   (ContPiscadaDisplay>6)&&(ContPiscadaDisplay<=9)||
					   (ContPiscadaDisplay>12)&&(ContPiscadaDisplay<15)){//apaga
						TextoBuffer[0] = 310;//
						TextoBuffer[1] = 310;//
						TextoBuffer[2] = 310;//
						TextoBuffer[3] = 310;//
						TextoBuffer[4] = 310;//
						TextoBuffer[5] = 310;//
						TextoBuffer[6] = 310;//
						TextoBuffer[7] = 310;//				
						fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);					
					}else {
						
						ValDisp = val;//400000000 aparece 40000 no display
						if(Unidade == LIVRE){
							for (i = 0; i < (4- counter.decPoint); i++)ValDisp /= 10;
							DispSigLong12(ValDisp,counter.decPoint,7,VarTroca);
						}else if(Unidade == MM){
							for (i = 0; i < (4- 1); i++)ValDisp /= 10;
							DispSigLong12(ValDisp,1,7,VarTroca);
						}else if(Unidade == CM){
							for (i = 0; i < (4- 2); i++)ValDisp /= 10;
							DispSigLong(ValDisp,2,7,PISCA_OFF);
						}
						else if(Unidade == M){
							for (i = 0; i < (4- 4); i++)ValDisp /= 10;
							DispSigLong(ValDisp,4,7,PISCA_OFF);
						}
					}
				}
				else{//mostra o preset no display
					ValDisp = val;//400000000 aparece 40000 no display
					if(Unidade == LIVRE){
						for (i = 0; i < (4- counter.decPoint); i++)ValDisp /= 10;
						DispSigLong12(ValDisp,counter.decPoint,7,VarTroca);
					}else if(Unidade == MM){
				 		for (i = 0; i < (4- 1); i++)ValDisp /= 10;
						DispSigLong12(ValDisp,1,7,VarTroca);
					}else if(Unidade == CM){
						for (i = 0; i < (4- 2); i++)ValDisp /= 10;
						DispSigLong(ValDisp,2,7,PISCA_OFF);
					}
					else if(Unidade == M){
						for (i = 0; i < (4- 4); i++)ValDisp /= 10;
						DispSigLong(ValDisp,4,7,PISCA_OFF);
					}
				}
	
			}//SEM FALHA
			else if(Falha2==ERRO){
				if(flag_segundos!=0){
					TextoBuffer[0] = 70;////ERRO
					TextoBuffer[1] = 265;//
					TextoBuffer[2] = 265;//
					TextoBuffer[3] = 250;//
					TextoBuffer[4] = 310;//
					TextoBuffer[5] = 310;//
					TextoBuffer[6] = 310;//
					TextoBuffer[7] = 310;//				
				}else for(i=0;i<8;i++)TextoBuffer[i] = 310;//' '
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);					
			}
			else if(Falha2==COMUNIC){
				if(flag_segundos!=0){
		
					TextoBuffer[0] = 75;//F
					TextoBuffer[1] = 180;//a
					TextoBuffer[2] = 235;//l
					TextoBuffer[3] = 215;//h
					TextoBuffer[4] = 180;//a
					TextoBuffer[5] = 60;//C
					TextoBuffer[6] = 250;//o
					TextoBuffer[7] = 240;//	m
				}else for(i=0;i<8;i++)TextoBuffer[i] = 310;//' '
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);					
			}

		}//MODO_NORMAL
	
	
		if(flag_time_out){
			TextoBuffer[0] = 310;
			TextoBuffer[1] = 310;
			TextoBuffer[2] = 310;
			TextoBuffer[3] = 310;
			TextoBuffer[4] = 310;
			TextoBuffer[5] = 310;
			TextoBuffer[6] = 310;
			TextoBuffer[7] = 310;
			fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);				
			flag_time_out = 0;
		}
	
		atualiza_disp = 0;
	}
}
void init_tmr2 (void)
{
	float aux = 0;
	addr = 0x01;
	baud_rate = 9600;
	aux = 2500000.0/(float)baud_rate - 1.0;
	SPBRG = (((unsigned int)(aux*10.0)%(unsigned int)aux)>=5)?(aux+1):aux;
	// TMR2 i a base de todo o kernel do sistema!!!
	TMR2 = 0; // inicializa TMR2
	PR2 = 250; // configura limite de TMR2 127


	T2CONbits.T2OUTPS3 = 1; // configura o postscaler
	T2CONbits.T2OUTPS2 = 1; //
	T2CONbits.T2OUTPS1 = 1; //
	T2CONbits.T2OUTPS0 = 1; //

	T2CONbits.T2CKPS1 = 1; // configura o prescaler
	T2CONbits.T2CKPS0 = 0; // 
///////////
	T2CONbits.TMR2ON = 1; // habilita TMR2
	INTCONbits.PEIE = 1; // habilita interrupgues dos perifiricos (TMR2 inclusive)
	PIE1bits.TMR2IE = 1; // habilita interrupgues do TMR2
	IPR1bits.TMR2IP = 0;

/*
//aki
	T2CONbits.T2CKPS1 = 0; // configura o prescaler
	T2CONbits.T2CKPS0 = 1; // 
*/

}






/*********************************************************************************************
EEPROM
*********************************************************************************************/

void eeprom_write(unsigned char addr, unsigned char data)
{
	EEADR  = addr;
	EEDATA = data;
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS  = 0;
	EECON1bits.WREN  = 1;

	INTCONbits.GIEH = 0;
	EECON2 = 0x55;
	EECON2 = 0xAA;
	EECON1bits.WR = 1;
	INTCONbits.GIEH = 1;

	while(EECON1bits.WR == 1);
	EECON1bits.WREN  = 0;
}

unsigned char eeprom_read(unsigned char addr)
{
	EEADR =	addr;
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS  = 0;
	EECON1bits.RD    = 1;
	return(EEDATA);
}

void sendToEEPROM(char add, char *p, char num)
{

	char i;
	
	EECON1bits.WREN = 1;
	EECON1bits.EEPGD = 0;
	di();
	
	for(i=0;i<num;i++){
		eeprom_write(i+add,*(p++));
	}
	ei();
	EECON1bits.WREN = 0;
	PIR2bits.EEIF=0;

}

void initTimer1(void){
	IPR1bits.TMR1IP = 1;

	T1CONbits.TMR1CS=0;

	T1CONbits.RD16=1;//16bits

	T1CONbits.T1OSCEN=0;//enable oscilagco



	T1CONbits.T1CKPS1=0;
	T1CONbits.T1CKPS0=0; //1:1  

	TMR1L = 0;
	TMR1H = 0;

	PIR1bits.TMR1IF=0;
	PIE1bits.TMR1IE = 1;
	PIR1bits.TMR1IF =0;
	T1CONbits.TMR1ON=1;
}


void FiltroDigital(void){

	unsigned int crc_recebido, crc_calculado;
	unsigned int i, kr, nr;
	unsigned int vel_unsig_int;
	char j;

	if(FlagFiltroDigital){
		//PORTBbits.RB6 = !PORTBbits.RB6;	

		if(ContMedia>=(NumTotalMedia-1))ContMedia = 0;
		else ContMedia++;				

//---------------------------------------------------------------------------------------------------
//Eixo X
//---------------------------------------------------------------------------------------------------
		if (ModoMed1 == DIRETA)MedidaTransdutor= MedidaTransdutor3;
		else MedidaTransdutor= MedidaTransdutor3*-1;

		if(OpPreset1==ON)MedidaTransdutor = MedidaTransdutor+Preset_ef_1;
//Media Msvel Inicio
		MediaX-= VetorMediaX[ContMedia];
		VetorMediaX[ContMedia] = MedidaTransdutor;
		MediaX += VetorMediaX[ContMedia];
		SigLongMedida = (float)MediaX/(float)NumTotalMedia;

//Media Fim	

		//exemplo: 12345, em mm= 1234.5, em cm = 123.45, em m = 1.2345
		if(Unidade==MM||Unidade == LIVRE) SigLongMedida = SigLongMedida *1000;
		else if(Unidade==CM)SigLongMedida = SigLongMedida *100;
		else if(Unidade==M) SigLongMedida = SigLongMedida ;


//Filtro inmcio
	//-----------------------------------------------------------------------------------------
	//Filtro do software
	//-----------------------------------------------
	//rcAux: 0.1=100ms, 1 = 1s, 10 = 10s
	//-----------------------------------------------
	// Taxa de amostragem .301ms (estava com 300 eu coloquei 101, depois medir a taxa real para atualizar
		MedidaFiltX = (float)rcAux*(float)MedidaFiltX;
		MedidaFiltX = MedidaFiltX+(0.05*(float)(SigLongMedida));  
		MedidaFiltX = MedidaFiltX/(0.05 + (float)rcAux);
		counter.value = (signed long)MedidaFiltX;
//Filtro fim
		if(Unidade==LIVRE) ValX = (long)((double)counter.value*(double)((double)k2.value/10000.0));
		else ValX = (long)((double)counter.value);//valor em long que i enviado para o display


//---------------------------------------------------------------------------------------------------
//Eixo Y
//---------------------------------------------------------------------------------------------------
	if (ModoMed2 == DIRETA)MedidaTransdutor= MedidaTransdutor2*-1;
		else MedidaTransdutor= MedidaTransdutor2;

		if(OpPreset2==ON)MedidaTransdutor = MedidaTransdutor+Preset_ef_2;
//Media Msvel Inicio
		MediaY-= VetorMediaY[ContMedia];
		VetorMediaY[ContMedia] = MedidaTransdutor;
		MediaY += VetorMediaY[ContMedia];
		SigLongMedida = (float)MediaY/(float)NumTotalMedia;

//Media Fim	

		//exemplo: 12345, em mm= 1234.5, em cm = 123.45, em m = 1.2345
		if(Unidade==MM||Unidade == LIVRE) SigLongMedida = SigLongMedida *1000;
		else if(Unidade==CM)SigLongMedida = SigLongMedida *100;
		else if(Unidade==M) SigLongMedida = SigLongMedida ;


//Filtro inmcio
	//-----------------------------------------------------------------------------------------
	//Filtro do software
	//-----------------------------------------------
	//rcAux: 0.1=100ms, 1 = 1s, 10 = 10s
	//-----------------------------------------------
	// Taxa de amostragem .301ms (estava com 300 eu coloquei 101, depois medir a taxa real para atualizar
		MedidaFiltY = (float)rcAux2*(float)MedidaFiltY;
		MedidaFiltY = MedidaFiltY+(0.05*(float)(SigLongMedida));  
		MedidaFiltY = MedidaFiltY/(0.05 + (float)rcAux2);
		counter.value = (signed long)MedidaFiltY;
//Filtro fim
		if(Unidade==LIVRE) Val2 = (long)((double)counter.value*(double)((double)k3.value/10000.0));
		else Val2 = (long)((double)counter.value);//valor em long que i enviado para o displaZ

/*
//---------------------------------------------------------------------------------------------------
//Eixo Z
//---------------------------------------------------------------------------------------------------
	if (ModoMedZ == DIRETA)MedidaTransdutor= MedidaTransdutorZ*-1;
		else MedidaTransdutor= MedidaTransdutorZ;

		if(OpPresetZ==ON)MedidaTransdutor = MedidaTransdutor+Preset_ef_Z;
//Media Msvel Inicio
		MediaZ-= VetorMediaZ[ContMedia];
		VetorMediaZ[ContMedia] = MedidaTransdutor;
		MediaZ += VetorMediaZ[ContMedia];
		SigLongMedida = (float)MediaZ/(float)NumTotalMedia;

//Media Fim	

		//exemplo: 12345, em mm= 1234.5, em cm = 123.45, em m = 1.2345
		if(Unidade==MM||Unidade == LIVRE) SigLongMedida = SigLongMedida *1000;
		else if(Unidade==CM)SigLongMedida = SigLongMedida *100;
		else if(Unidade==M) SigLongMedida = SigLongMedida ;


//Filtro inmcio
	//-----------------------------------------------------------------------------------------
	//Filtro do software
	//-----------------------------------------------
	//rcAux: 0.1=100ms, 1 = 1s, 10 = 10s
	//-----------------------------------------------
	// Taxa de amostragem .301ms (estava com 300 eu coloquei 101, depois medir a taxa real para atualizar
		MedidaFiltZ = (float)rcAux*(float)MedidaFiltZ;
		MedidaFiltZ = MedidaFiltZ+(0.05*(float)(SigLongMedida));  
		MedidaFiltZ = MedidaFiltZ/(0.05 + (float)rcAux);
		counter.value = (signed long)MedidaFiltZ;
//Filtro fim
		if(Unidade==LIVRE) ValZ = (long)((double)counter.value*(double)((double)k2.value/10000.0));
		else ValZ = (long)((double)counter.value);//valor em long que i enviado para o displaZ
*/
		FlagFiltroDigital = 0;
	}

}

void EfetivaPreset(void){

	if((modo==MODO_MENU)&&(OpPreset1==ON)&&(!TEC_IN2)&&(!TEC_IN3)){//efetiva Preset
		INTCONbits.GIE = 0;
		if (ModoMed1 == DIRETA)MedidaTransdutor= MedidaTransdutor3;
		else MedidaTransdutor= MedidaTransdutor3*-1;
		Preset_ef_1 = (preset1.value/1000)-MedidaTransdutor;
		sendToEEPROM(72,(char*)&Preset_ef_1,4);
		modo=MODO_NORMAL;
		VarTroca = 0;
		INTCONbits.GIE = 1;
	}


	if((modo==MODO_MENU)&&(OpPreset2==ON)&&(!TEC_IN1)&&(!TEC_IN3)){//efetiva Preset
		INTCONbits.GIE = 0;
		if (ModoMed2 == DIRETA)MedidaTransdutor= MedidaTransdutor2*-1;
		else MedidaTransdutor= MedidaTransdutor2;
		Preset_ef_2 = (preset2.value/1000)-MedidaTransdutor;
		sendToEEPROM(191,(char*)&Preset_ef_2,4);
		modo=MODO_NORMAL;
		VarTroca = 0;
		INTCONbits.GIE = 1;
	}

}

/**************************************************************************************
*******************************MODBUS*************************************************/
void pergunta(void){	//envia pergunta sobre a medida do ultrassom
	
	netBuf[0] = 0x01;	//Addres
	netBuf[1] = 0x03;	//Function
	netBuf[2] = 0x00;	//Starting Add. MSB	0208 corresponde ao codigo de distancia para o ultrassom
	netBuf[3] = 0x00;	//Starting Add. LSB
	netBuf[4] = 0x00;	//Register Count MSB
	netBuf[5] = 0x05;//0x01;	//Register Count LSB - Lj apenas um enderego
	netBuf[6] = 0x85;//0x84;	//CRC LSB
	netBuf[7] = 0xc9;//0x0a;	//CRC MSB
	sendMsg(8);			//Envia a MSG de tamanho = 8


	ContLedTx = 0;
	LED_TX = 1;	
	
}



void ModosOperacao(void){
unsigned char i;

		if(modo==MODO_NORMAL){	
			SaidaAnaParametrizada = (signed long)(a1* (float)ValX + b1); //inclinagco da reta
			if(SaidaAnaParametrizada>65535)SaidaAnaParametrizada = 65535;//limita para nco estourar a samda analogica
			if(SaidaAnaParametrizada<0)SaidaAnaParametrizada = 0;//limita para nco estourar a samda analogica
		    //-------------------------------------------------------------------------------------
			dacSend1((unsigned int)SaidaAnaParametrizada);	
			//-------------------------------------------------------------------------------------
			SaidaAnaParametrizada = (signed long)(a2* (float)Val2 + b2); //inclinagco da reta
			if(SaidaAnaParametrizada>65535)SaidaAnaParametrizada = 65535;//limita para nco estourar a samda analogica
			if(SaidaAnaParametrizada<0)SaidaAnaParametrizada = 0;//limita para nco estourar a samda analogica
			dacSend2((unsigned int)SaidaAnaParametrizada);
		}
		if (modo == MODO_SENHA){
			if (tecla == 3)// INCREMENTO
			{
				senha_aux_var=incDigit (3,(unsigned long)senha_aux_var);
			}
			tecla=0;
			//----- BLOCO
			if(flag_segundos!=0)DispUnsigLong(senha_aux_var,8,3);
			else{
				di();
				TextoBuffer[7-position]=310;//' '
				fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				ei();
			}
		}//fecha chave do if
		else if (modo == MODO_PROGRAMAR){
			switch(menu_aux.tag){
				case PONTODEC://c1 pisca o valor no loop infinito
					ValDisp = val;//
					for (i = 0; i < (4- tempValue.decPoint); i++)ValDisp /= 10;
					DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_OFF);
				break;
				case LIM1:
				case LIM2:
				case LIM3:
				case LIM4:
				case LIM1HIST:
				case LIM2HIST:
				case LIM3HIST:
				case LIM4HIST:
				case ESCALA0:
				case ESCALA1:
				case ESCALA0_2:
				case ESCALA1_2:
				case CONSTMULT:
				case CONSTMULT2:
				case FILTRO:
				case FILTRO2:

				case MEDIA:
				case TALIM1:
				case TDLIM1:
				case TDLIM3:
				case TALIM2:
				case TALIM3:
				case TDLIM2:
				case PRESET:
				case PRESET2://Preset
				case TALIM4:
				case TDLIM4:
					DispSigLong(ValDisp,tempValue.decPoint,7,PISCA_ON);
				break;

				case SENHA://Senha
					if(!controle_senha){
						if(flag_segundos!=0)DispUnsigLong(buffer_senha_nova_var1,8,3);
						else{
							di();
							TextoBuffer[7-position]=310;//' '
							fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
							ei();				
						}
					}
					else{
						if(flag_segundos!=0)DispUnsigLong(buffer_senha_nova_var2,8,3);
						else{
							di();
							TextoBuffer[7-position]=310;//' '
							fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
							ei();	
						}
					}
				break;
			}
		}


}



/*********************************************************************************************
VETOR DE INTERRUPGCO DE ALTA PRIORIDADE
*********************************************************************************************/
#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh(void)
{
	_asm
		goto	InterruptHandlerHigh	//jump to interrupt routine
	_endasm
}
#pragma code


/*********************************************************************************************
ROTINA DE INTERRUPGCO DE ALTA PRIORIDADE
*********************************************************************************************/
#pragma interrupt InterruptHandlerHigh

void InterruptHandlerHigh()
{




	unsigned char cont_radio;
	static unsigned int crc_recebido, crc_calculado;
	static unsigned int kr, nr;
	static char cntRS;
	static char iRS, jRS;
	static unsigned int tempRS, flagRS;

	//aki
	networkInterrupt();
	schedulerInterrupt();
	
	Nop();




	if ((INTCONbits.TMR0IF)&&(INTCONbits.TMR0IE)) //Permodo: MS(13) acrecentei INTCONbits.TMR0IE
	{
		
//Fungco 1 minuto = 60segundos/ 41,6m segundos = 1442,30

		cont_time_out_menu++;
		if ((cont_time_out_menu >= 65500)&&(modo!=MODO_NORMAL))
		{

			if((menu_aux.tag==OPPRESET1)&&(modo==MODO_PROGRAMAR)){
				buffer_senha_nova_var1 = 0;
				buffer_senha_nova_var2 = 0;
			}


			modo= MODO_NORMAL;
			VarTroca = 0;
			ptrglobal = &main_menu[0];
			menu_aux = *ptrglobal;


			position = 0;

    		cont_time_out_menu=0;

			flag_time_out= !flag_time_out;
		}

		if(cont_disp>=10){//10 = 288ms  estava com 40
			atualiza_disp = 1; 
			
			cont_disp = 0;
		}else cont_disp++;
				
//----- variavel usada para piscar o display 
//		no dmgito que esta sendo incrementado
		var_segundos++;
		if(var_segundos>=40){// 40 i para 40MHz
			flag_segundos=!flag_segundos;//flag de controle
			var_segundos = 0;
		}

		ContDelay++;
		if(ContDelay>=50){//50//100
			ContDelay = 0;
			FlagContDelay = 1;
		}

		
		keyboardInterrupt();
		f.flag.Key = 1;

		INTCONbits.TMR0IF = 0;
	}
	if(PIR1bits.TMR1IF){//5ms

		if(LED_RX){
			if(ContLedRx<2)ContLedRx++;
			else LED_RX = 0;
		}
		if(LED_TX){
			if(ContLedTx<2)ContLedTx++;
			else LED_TX = 0;
		}

		TMR1H = 0x3c;
		TMR1L = 0xaf;
		if(Cont55ms<10)Cont55ms++; //aproximadamente 56ms
		else{
			FlagFiltroDigital = 1;
			Cont55ms = 0;
		}

		if(Cont100ms<20)Cont100ms++; //aproximadamente 100ms
		else{
			if(modo==MODO_NORMAL){
				if(ContFalhaComunic<=20)ContFalhaComunic++;//aproximadamente 2 segundos
				else Falha2 = COMUNIC;
			}else{
				ContFalhaComunic = 0;
				Falha2 = 0;
			}
			Flag100ms = 1;			
			Cont100ms = 0;
		}


		PIR1bits.TMR1IF = 0;
	}
	if(INTCON3bits.INT1IF&&INTCON3bits.INT1IE){

		INTCON3bits.INT1IF = 0; // certifica-se que a interrupgco nco foi acionada pelo pull-up
	}
}




void transmitir (void)
{
	unsigned int crc_recebido, crc_calculado;
	unsigned int i, kr, nr;
	char j;
	
	char coils=0, coils2=0;
	if(msgReady){
		INTCONbits.GIE=0;
		// Checagem do CRC
		crc_calculado = calcCRC(netBuf, msgsize-2);
		*(char *)&crc_recebido = netBuf[msgsize-2];
		*((char *)&crc_recebido+1) = netBuf[msgsize-1];
		// Nao houve erro de CRC
		if(crc_recebido==crc_calculado){

			ContLedRx = 0;
			LED_RX = 1;	



			ContFalhaComunic=0;
			Falha2 = 0;

			MedidaTransdutor = (((unsigned int)netBuf[3] << 8) + (unsigned int)netBuf[4]);
			Sinal = (unsigned int)netBuf[9];
			if(Sinal)MedidaTransdutor1 = -MedidaTransdutor;
			else MedidaTransdutor1 = MedidaTransdutor;


			MedidaTransdutor = (((unsigned int)netBuf[5] << 8) + (unsigned int)netBuf[6]);
			Sinal = (unsigned int)netBuf[10];
			if(Sinal)MedidaTransdutor2 = -MedidaTransdutor;
			else MedidaTransdutor2 = MedidaTransdutor;


			MedidaTransdutor = (((unsigned int)netBuf[7] << 8) + (unsigned int)netBuf[8]);
			Sinal = (unsigned int)netBuf[11];
			if(Sinal)MedidaTransdutor3 = -MedidaTransdutor;
			else MedidaTransdutor3 = MedidaTransdutor;


	
			for(j=0;j<=14;j++)netBuf[j] = 0x55;
			crc_recebido = 123;
			crc_calculado = 0;


		}

		msgReady = 0;
		INTCONbits.GIE=1;
	}



}

