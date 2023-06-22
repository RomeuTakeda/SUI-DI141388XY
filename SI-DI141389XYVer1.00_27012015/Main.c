/********************************************************************************************************
--------------------------------------------------
Data da última compilação: 15:00h 03/03/2015
IDE: MPLAB. V8.80
Compilador: mcc18 da Microchip V2.42
by Francisco Moreira

o display 0 é o mais a esquerda, enquanto que o 3 é o mais a direita.

*********************************************************************************************************/

#include <p18F252.h>
#include <delays.h>
#include "main.h"
#include "adis16209.h"
#include "network.h"
#include <usart.h>
#include <stdlib.h>
#include <string.h>


/*********************************************************************************************
//VARIÁVEIS GLOBAIS
*********************************************************************************************/


struct _menu
{
	char *indice_display;
	struct _menu *anter;
	struct _menu *prox;
//	struct _menu *submenu;
	char tag;
};
typedef struct _menu menu;

#define MENU_CONT  34//27

#pragma udata gpr4
menu main_menu[MENU_CONT];
menu *ptrglobal;
menu menu_aux;
#pragma udata 

signed char incremento;
signed long inc;
char modo;
//unsigned char vetor[30];
unsigned char sinal_posicao = 0;
char TCODE[1];
char TSAIR[1];
char TENT[1];
signed int SignedIntLeitura;
char TMENU1[1];
char TMENU2[1];
char TMENU3[1];
char TMENU4[1];
char TMENU5[1];
char TMENU6[1];
char TMENU7[1];
char TMENU8[1];
char TMENU9[1];
char TMENU10[1];
char TMENU11[1];
char TMENU12[1];
char TMENU13[1];
char TMENU14[1];
char TMENU15[1];
char TMENU16[1];
char TMENU17[1];
char TMENU18[1];
char TMENU19[1];
char TMENU20[1];
char TMENU21[1];
char TMENU22[1];
char TMENU23[1];
char TMENU24[1];
char TMENU25[1];
char TMENU26[1];
char TMENU27[1];
char TMENU28[1];
char TMENU29[1];
char TMENU30[1];
char TMENU31[1];
char TMENU32[1];
char TMENU33[1];
char TMENU34[1];
char TMENU35[1];
char TMENU36[1];
char TMENU37[1];
char TMENU38[1];
char TMENU39[1];
char TMENU40[1];
char TMENU41[1];
char TMENU42[1];
char TMENU43[1];
char TMENU44[1];
char TMENU45[1];
char TMENU46[1];
char TMENU47[1];
char TMENU48[1];
char TMENU49[1];
char TMENU50[1];
char TMENU51[1];
char TMENU52[1];
char TMENU53[1];
char TMENU54[1];
char TMENU55[1];
char TMENU56[1];
char TMENU57[1];
char TMENU58[1];
char TMENU59[1];
char TMENU60[1];
char TMENU61[1];
char TMENU62[1];
unsigned int rele, rele1;
unsigned char valorx[2];
unsigned int leitura_sem_sinal = 0, temperatura = 0, fonte = 0, inclinacao = 0,adj_preset = 0, preset = 0, filtro = 0, Inclinacao, InclinacaoX,InclinacaoY;
signed int LeituraComSinal = 0;
signed int leitura_com_sinal = 0;
unsigned int adj_preset_buffer = 0;
unsigned int teste_1 = 0;
unsigned char flag_menos  = 0;
signed int inclinacao_sinal =0, preset_sinal = 0;

unsigned char oplim1,oplim2,oplim3,oplim4,oplim5,oplim6,oplim7,oplim8,oplim9,oplim10,oplim11,oplim12;
unsigned int lim1_inf, lim1_sup, hist,lim2_inf, lim2_sup,lim3_inf, lim3_sup,lim4_inf, lim4_sup;
unsigned int lim5_inf, lim5_sup,lim6_inf, lim6_sup,lim7_inf, lim7_sup,lim8_inf, lim8_sup;
unsigned int lim9_inf, lim9_sup,lim10_inf, lim10_sup,lim11_inf, lim11_sup,lim12_inf, lim12_sup;

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
union pacote_limites1 placa_interna;  //placa_interna.limites 


unsigned int rampa = 0;
signed long porcentagem = 0,porcentagem_ch1,porcentagem_ch2,porcentagem_ch3,porcentagem_ch4;
unsigned int e0_entrada = 0, e1_entrada = 0, a0_entrada = 0, a1_entrada = 0;
unsigned int ch1_e0 = 0, ch2_e0;
unsigned int ch1_e1 = 0, ch2_e1;
unsigned int ch1_a0 = 0, ch2_a0;
unsigned int ch1_a1 = 0, ch2_a1;
unsigned int leitura_ana = 0;
unsigned char sentido = ANTI_HORARIO, sentido_buffer;

unsigned long cont_universal = 0;
//static unsigned char id_buffer = 250;
unsigned int Cal_PLow=0,Cal_PHi=100; 
unsigned char bauds = 0;
unsigned char flag_start = 1;
unsigned char cont_erro = 0, cont_int = 0;
unsigned char flag_erro = 0;
static unsigned char end_inicial = 0, primeiro_end = 0;
static unsigned char flag_muda_end = 0;
unsigned char testex = 0;
unsigned char velocidade = 0;
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
//--------------------------
//unsigned int var_contador=0;
//unsigned char flag_contador=0;
unsigned int valor;
//Variaveis do Menu
//unsigned int id=0,status=0, var_global2, pressao=0, bateria=0/*, presao_result = 0*/;
signed int presao_result=0;
unsigned long var_long = 0;
unsigned char position;
unsigned char var_segundos=0, flag_segundos=0, flag_time_out=0;
/*un*/signed int var_xtempo=0, flag_xtempo=0;
//signed int var_xtempo = 0;
//signed char flag_xtempo = -7;
//unsigned char alternado = 0;
unsigned char  controle_senha =0;
//unsigned char le_serial=0;
//unsigned int TEMPSENSOR=0;
char data[];
float  b1,a1, valor_float;
//unsigned int PHi_ana=1023, PLow_ana=0;
//float arredondamento;
unsigned char flag_atualiza = 0;
//------------------------
unsigned TECLA = 0;
char *ptr;
unsigned int senha_var=123, senha_aux_var=0;
unsigned int senha_nova_var1=0,buffer_senha_nova_var1=0, senha_nova_var2=0,buffer_senha_nova_var2=0;
char tecla=0;
unsigned char mostra_var=0;
volatile unsigned int cont_time_out_menu=0;
unsigned char local = 0;
unsigned short int entra;
unsigned char io=0;
unsigned char flag_zera = 0;
unsigned char int1_rs232 = 0;
unsigned char  ini_link = 0;
unsigned int flag_tempo=0;
unsigned int var_tempo=0;
//unsigned char var_tempo1[40];
//unsigned int ocupado;
unsigned char flag_ocupado=0;
//#pragma udata 
unsigned char flag_mudou_radio = 0;

unsigned int posicao = 0;

signed int cont_test=0, var_test = 0, analogica_entrada = 0;
unsigned int cont_sinal=0, var_sinal_test = 0;


float rcFil, rcAux , Medida_Fil;
unsigned int Medida_long, valor_lido, ciclos;
//float Medida_Fil, Medida_long, valor_lido;
unsigned char cont_disp, atualiza_disp;
unsigned int media_cont;
signed long media_ana;
float porcentagem_float;
unsigned char unidade, dezena, centena, milhar;
unsigned char Polaridade,Sinal, SinalX = 0, SinalY = 0, Temperatura = 0;
/*********************************************************************************************
PROTÓTIPOS DAS FUNÇÕES
*********************************************************************************************/
void InterruptVectorHigh (void);
void InterruptHandlerHigh (void);
void initPorts (void);
void converte_ascii(unsigned int valor_trab);

unsigned char VarChar1,VarChar2;
signed char VarSignedChar1,VarSignedChar2;
unsigned int ContDelay = 0, ContReset = 0, FlagReset = 0;
unsigned char ContTest1 = 0;
/*********************************************************************************************
FUNÇÃO PRINCIPAL
*********************************************************************************************/
// unsigned char tested=0;
void main (void) 
{	unsigned int tk;

	char i=0, x,contando, kty=0;
	unsigned char tx=0;
	unsigned char val_filtro = 0;

	init_tmr2(); 
	networkInit();

	INTCONbits.GIE = 1;
	

//	TLED_TESTE	= 0;
//	LED_TESTE = 0;

ADCON1 =0x07;
INTCONbits.PEIE = 1;
	InitPIC();
PORTBbits.RB4 = 1;	
INTCONbits.GIE = 0;	
	ConfigFiltroAdis16209();
INTCONbits.GIE = 1;


/*
for(;;){

   leitura_sem_sinal = 0x31f1;
	//leitura_sem_sinal = (((unsigned int)valorx[0] << 8) + (unsigned int)valorx[1]);
	
	flag_menos = (leitura_sem_sinal>>13)&0x0001;

	if(flag_menos){
		leitura_sem_sinal = ~leitura_sem_sinal;
		leitura_sem_sinal = leitura_sem_sinal+1;
	}

	leitura_sem_sinal = leitura_sem_sinal&0x3fff;//máscara para 14bits

}
*/



//Delay10KTCYx(250);
//clrwdt();
	while(TRUE)
	{

//		if(!FlagReset){
			clrwdt();
			Nop();
//		}


		if(ContReset>30)FlagReset=1;
		
		if(ContDelay>100){



			if(ContReset<100)ContReset++;

			PORTBbits.RB4 = !PORTBbits.RB4;
			ContDelay = 0;

		}else ContDelay++;
		


		if(ContTest1>5){
		
//			Adis16209Read(INCLINACAO,&valorx);
//			Inclinacao = leitura_sem_sinal;
//			Sinal=Polaridade;
		
			ContTest1 = 0;
		
		}else ContTest1++;

		transmitir();

//UM_EIXO
//EIXO_X
//EIXO_Y
/*

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
*/



//-------------------------------------------------------------------
	}//chave do while infinito
}//chave do main







//---------------------------------------------------------------------------------
//Funções 
//---------------------------------------------------------------------------------

//FUNÇÃO DE INICIALIZAÇÃO DAS PORTAS DO PIC18F252
void initPorts(void)
{
	RCONbits.IPEN = 0;		//Disable priority levels on interrupts.
	INTCONbits.GIE = 0;		//Disables all interrupts.
	INTCONbits.PEIE = 0;	//Disables all peripheral interrupst. 
	ADCON1 =0x07;
//	INTCON2bits.RBPU = 0;

//	TRISA = 0b00001101;	//
//	TRISC = 0b10010111;	//Configura todas as portas como entradas.
	TRISBbits.TRISB2 = 0;
	PORTBbits.RB2=0; 
//	TDEPIN = 0;
//	PORTA = 0;
//	PORTB = 0;

	Delay10KTCYx(250);
	RCONbits.IPEN = 0;		//Disable priority levels on interrupts.
	INTCONbits.GIE = 1;		//Disables all interrupts.
	INTCONbits.PEIE = 1;	//Disables all peripheral interrupst. 
}


/*********************************************************************************************
VETOR DE INTERRUPÇÃO DE ALTA PRIORIDADE
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
ROTINA DE INTERRUPÇÃO DE ALTA PRIORIDADE
*********************************************************************************************/
#pragma interrupt InterruptHandlerHigh

void InterruptHandlerHigh()
{

	schedulerInterrupt();
	networkInterrupt();

}	


void converte_ascii(unsigned int valor_trab){
	unidade = ((valor_trab%10)+0x30);
	valor_trab/=10;
	dezena = ((valor_trab%10)+0x30);
	valor_trab/=10;
	centena = ((valor_trab%10)+0x30);
	valor_trab/=10;
	milhar = ((valor_trab%10)+0x30);
}
