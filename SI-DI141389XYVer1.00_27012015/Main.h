/*********************************************************************************************
DEFINIÇÕES RELATIVAS AOS PINOS
*********************************************************************************************/
//#define bank2 
#define di() INTCONbits.GIE = 0
#define ei() INTCONbits.GIE = 1

#define INCLINACAO 0x10
#define INCLINACAOX 0x0c
#define INCLINACAOY 0x0e
#define TEMPERATURA 0x0a

#define OP_ON	1
#define OP_NOP	0
#define UM_EIXO		0x10
#define EIXO_X		0x0C
#define EIXO_Y		0x0E

#define TLED_TESTE	TRISCbits.TRISC4
#define LED_TESTE	PORTCbits.RC4
#define HORARIO 1
#define ANTI_HORARIO 0

#define RELE1	PORTBbits.RB0
#define RELE2	PORTDbits.RD7
#define RELE3	PORTCbits.RC1
#define RELE4	PORTCbits.RC2

#define TRELE1	TRISBbits.TRISB0
#define TRELE2	TRISDbits.TRISD7
#define TRELE3	TRISCbits.TRISC1
#define TRELE4	TRISCbits.TRISC2


#define TDATA_OUT	TRISEbits.TRISE0
#define	TCLOCK_OUT	TRISEbits.TRISE2
#define	TLOAD_OUT	TRISEbits.TRISE1

#define DATA_OUT	PORTEbits.RE0
#define	CLOCK_OUT	PORTEbits.RE2
#define	LOAD_OUT	PORTEbits.RE1


/*
#define TRISSS				TRISAbits.TRISA5	
#define TRISSDO				TRISCbits.TRISC5
#define	TRISLIM_1			TRISDbits.TRISD1
#define	TRISLIM_2			TRISDbits.TRISD2
#define TRISDEFECT			TRISDbits.TRISD3
*/
/*

#define DISTANCIA			0
#define VOLUME				1
#define	LIVRE				2

#define MM					0
#define CM					1
#define M					2
#define L					3
#define M3					4

#define MAIOR_IGUAL			0
#define MENOR_IGUAL			1
#define COMP_DELIGADO		2
*/
/*********************************************************************************************
OUTRAS DEFINIÇÕES
*********************************************************************************************/
#define TRUE	1
#define ASCII(X)	(X+48)
#define	NULL_	((void *)0)
#define MS(t) ((unsigned int)((t * (TICKFREQ/5)) /200))
#define ON 1
#define OFF 0
#define TEMPO 766 //115 //766 = 5seg , 115 = 750mseg e 23 = 150ms

#define MODO_NORMAL				0
#define MODO_MENU				1
#define MODO_PROGRAMAR			2
//#define MODO_DIGITANDO			3
#define MODO_GRAVAR				4
#define MODO_SENHA				5

#define MENU_1					1
#define MENU_2					2
#define MENU_3					3
#define MENU_4					4
#define MENU_5					5
#define MENU_6					6
#define MENU_7					7
#define MENU_8					8
#define MENU_9					9
#define MENU_10					10
#define MENU_11					11
#define MENU_12					12
#define MENU_13					13
#define MENU_14					14
#define MENU_15					15
#define MENU_16					16
#define MENU_17					17
#define MENU_18					18
#define MENU_19					19
#define MENU_20					20
#define MENU_21					21
#define MENU_22					22
#define MENU_23					23
#define MENU_24					24
#define MENU_25					25
#define MENU_26					26
#define MENU_27					27
#define MENU_28					28
#define MENU_29					29
#define MENU_30					30
#define MENU_31					31
#define MENU_32					32
#define MENU_33					33
#define MENU_34					34
#define MENU_35					35
#define MENU_36					36
#define MENU_37					37
#define MENU_38					38
#define MENU_39					39
#define MENU_40					40
#define MENU_41					41
#define MENU_42					42
#define MENU_43					43
#define MENU_44					44
#define MENU_45					45
#define MENU_46					46
#define MENU_47					47
#define MENU_48					48
#define MENU_49					49
#define MENU_50					50
#define MENU_51					51
#define MENU_52					52
#define MENU_53					53
#define MENU_54					54
#define MENU_55					55
#define MENU_56					56
#define MENU_57					57
#define MENU_58					58
#define MENU_59					59
#define MENU_60					60

extern unsigned int ContDelay , ContReset , FlagReset ;

extern unsigned char Polaridade,Sinal, SinalX, SinalY, Temperatura;
extern unsigned char valorx[2];
extern unsigned int leitura_sem_sinal, temperatura, fonte ;
extern signed int SignedIntLeitura;
extern signed int leitura_com_sinal;
extern unsigned char flag_menos;

extern unsigned int rampa;
extern unsigned int adj_preset_buffer, adj_preset;
extern unsigned char sentido, sentido_buffer;
extern unsigned char cont_erro, cont_int;
extern unsigned char flag_erro;
extern unsigned char bauds;
extern signed char incremento;
extern signed long inc;
extern float a_p;
extern unsigned int senha_var, senha_aux_var, var_sinal_test;
extern /*un*/signed int var_xtempo, flag_xtempo;
//extern unsigned int id,status,var_global2, pressao, bateria,ocupado, sinal_localiz;
extern unsigned char flag_ocupado;
extern unsigned char mostra_var;
extern unsigned long var_long;
extern unsigned char position;
extern  unsigned char ini_link;
extern  unsigned int var_tempo;
//extern unsigned char vetor[10];
extern char modo;
extern unsigned int posicao;
extern unsigned TECLA;
//extern unsigned char flag_contador;
//extern  unsigned int var_contador;
extern volatile unsigned int cont_time_out_menu;
extern char tecla;
extern char TCODE[1];    // COdE
extern char menu_flag;
//extern unsigned int id_buffer;
extern unsigned char flag_mudou_radio;
extern unsigned char  controle_senha;
extern unsigned int senha_nova_var1,buffer_senha_nova_var1, senha_nova_var2,buffer_senha_nova_var2;
//-----
extern struct _menu
{
	char *indice_display;
	struct _menu *anter;
	struct _menu *prox;
//	struct _menu *submenu;
	char tag;
};

extern char TMENU1[1];
extern char TMENU2[1];
extern char TMENU3[1];
extern char TMENU4[1];
extern char TMENU5[1];
extern char TMENU6[1];
extern unsigned char local;
extern unsigned int Cal_PLow,Cal_PHi;

typedef struct _menu menu;
extern menu menu_aux;
extern menu main_menu[1];
extern menu *ptrglobal;
extern unsigned char flag_atualiza;
extern unsigned int inclinacao;
extern unsigned int Inclinacao, InclinacaoX,InclinacaoY;

//-----
extern void inc_dec(void);
extern void display_num(int valor );
extern void eeprom_write(unsigned char addr, unsigned char data);
extern void sendDAC(signed long x);
extern void sendToEEPROM(char add, char *p, char num);
extern unsigned char flag_segundos;
extern unsigned long incDigit (unsigned char num_dig,unsigned long var_long);
