
//INCLUSÃO DE BIBLIOTECAS

#include <p18f4620.h>
#include "main.h"
#include "keyboard.h"
#include "keys.h"
#include "hcms297x.h"



//ESCOPO DAS SUBROTINAS/FUNÇÕES
void fetchcharDspic8dig( unsigned int dig7,unsigned int dig6,unsigned int dig5,unsigned int dig4,
						 unsigned int dig3,unsigned int dig2,unsigned int dig1,unsigned int dig0);
void inithcms297x (void);
void contsx (char word0, char word1);

void fetchchar2(char text[]);
void fetchcharDspic(char text[]);
void DispSigLong(signed long md, char inicio, char dig, char LigPisca);


void DispUnsigLong(unsigned long md,char inicio, char dig);



void display_decimal(unsigned int md);
void display_decimal_signed(signed int md); //Kellen



char texto[8];
char texto2[8];
unsigned char caracter[41];
// 1°- 2°- 3°- 4°- 5° 	
//001-001-001-001-001 
//002-002-002-002-002   Menos sig    
//004-004-004-004-004                
//008-008-008-008-008_____________
//001-001-001-001-001
//002-002-002-002-002    Mais sig
//004-004-004-004-004
#pragma udata gpr4
const char rets[600]={//só está usando até o 305
0x3e,//0.......0
0x51,//1.......
0x49,//2.......
0x45,//3.......
0x3e,//4.......

0x00,//5.......1
0x42,//6.......
0x7f,//7.......
0x40,//8.......
0x00,//9.......

0x62,//10.......2
0x51,//11.......
0x49,//12.......
0x49,//13.......
0x46,//14.......

0x22,//15.......3
0x41,//16.......
0x49,//17.......
0x49,//18.......
0x36,//19.......

0x18,//20.......4
0x14,//21.......
0x12,//22.......
0x7f,//23.......
0x10,//24.......

0x27,//25.......5
0x45,//26.......
0x45,//27.......
0x45,//28.......
0x39,//29.......

0x3c,//30.......6
0x4a,//31.......
0x49,//32.......
0x49,//33.......
0x30,//34.......

0x01,//35.......7
0x71,//36.......
0x09,//37.......
0x05,//38.......
0x03,//39.......

0x36,//40.......8
0x49,//41.......
0x49,//42.......
0x49,//43.......
0x36,//44.......

0x06,//45.......9
0x49,//46.......
0x49,//47.......
0x29,//48.......
0x1e,//49.......

0x7e,//50.......A
0x09,//51.......
0x09,//52.......
0x09,//53.......
0x7e,//54.......

0x7e,//55.......B
0x49,//56.......
0x49,//57.......
0x49,//58.......
0x36,//59.......

0x3e,//60.......C
0x41,//61.......
0x41,//62.......
0x41,//63.......
0x22,//64.......

0x7f,//65.......D
0x41,//66.......
0x41,//67.......
0x41,//68.......
0x3e,//69.......

0x7f,//70.......E
0x49,//71.......
0x49,//72.......
0x49,//73.......
0x41,//74.......

0x7f,//75.......F
0x09,//76.......
0x09,//77.......
0x09,//78.......
0x01,//79.......

0x3e,//80.......G
0x41,//81.......
0x41,//82.......
0x51,//83.......
0x32,//84.......

0x7f,//85.......H
0x08,//86.......
0x08,//87.......
0x08,//88.......
0x7f,//89.......

0x00,//90.......I
0x41,//91.......
0x7f,//92.......
0x41,//93.......
0x00,//94.......

0x20,//95.......J
0x40,//96.......
0x40,//97.......
0x40,//98.......
0x3f,//99.......

0x7f,//100.......K
0x08,//101.......
0x14,//102.......
0x22,//103.......
0x41,//104.......

0x7f,//105.......L
0x40,//106.......
0x40,//107.......
0x40,//108.......
0x40,//109.......

0x7f,//110.......M
0x02,//111.......
0x0c,//112.......
0x02,//113.......
0x7f,//114.......

0x7f,//115.......N
0x04,//116.......
0x08,//117.......
0x10,//118.......
0x7f,//119.......

0x3e,//120.......O
0x41,//121.......
0x41,//122.......
0x41,//123.......
0x3e,//124.......

0x7f,//125.......P
0x09,//126.......
0x09,//127.......
0x09,//128.......
0x06,//129.......

0x3e,//130.......Q
0x41,//131.......
0x51,//132.......
0x21,//133.......
0x5e,//134.......

0x7f,//135.......R
0x09,//136.......
0x19,//137.......
0x29,//138.......
0x46,//139.......

0x26,//140.......S
0x49,//141.......
0x49,//142.......
0x49,//143.......
0x32,//144.......

0x01,//145.......T
0x01,//146.......
0x7f,//147.......
0x01,//148.......
0x01,//149.......

0x3f,//150.......U
0x40,//151.......
0x40,//152.......
0x40,//153.......
0x3f,//154.......

0x07,//155.......V
0x18,//156.......
0x60,//157.......
0x18,//158.......
0x07,//159.......

0x7f,//160.......W
0x20,//161.......
0x18,//162.......
0x20,//163.......
0x7f,//164.......

0x63,//165.......X
0x14,//166.......
0x08,//167.......
0x14,//168.......
0x63,//169.......

0x03,//170.......Y
0x04,//171.......
0x78,//172.......
0x04,//173.......
0x03,//174.......

0x61,//175.......Z
0x51,//176.......
0x49,//177.......
0x45,//178.......
0x43,//179.......

0x38,//180.......a
0x44,//181.......
0x44,//182.......
0x3c,//183.......
0x40,//184.......

0x7f,//185.......b
0x48,//186.......
0x44,//187.......
0x44,//188.......
0x38,//189.......

0x38,//190.......c
0x44,//191.......
0x44,//192.......
0x44,//193.......
0x44,//194.......

0x38,//195.......d
0x44,//196.......
0x44,//197.......
0x48,//198.......
0x7f,//199.......

0x38,//200.......e
0x54,//201.......
0x54,//202.......
0x54,//203.......
0x08,//204.......

0x08,//205.......f
0x7e,//206.......
0x09,//207.......
0x02,//208.......
0x00,//209.......

0x08,//210.......g
0x14,//211.......
0x54,//212.......
0x54,//213.......
0x3c,//214.......

0x7f,//215.......h
0x08,//216.......
0x04,//217.......
0x04,//218.......
0x78,//219.......

0x00,//220.......i
0x44,//221.......
0x7d,//222.......
0x40,//223.......
0x00,//224.......

0x20,//225.......j
0x40,//226.......
0x44,//227.......
0x3d,//228.......
0x00,//229.......

0x00,//230.......k
0x7f,//231.......
0x10,//232.......
0x28,//233.......
0x44,//234.......

0x00,//235.......l
0x41,//236.......
0x7f,//237.......
0x40,//238.......
0x00,//239.......

0x78,//240.......m
0x04,//241.......
0x18,//242.......
0x04,//243.......
0x78,//244.......

0x7c,//245.......n
0x08,//246.......
0x04,//247.......
0x04,//248.......
0x78,//249.......

0x38,//250.......o
0x44,//251.......
0x44,//252.......
0x44,//253.......
0x38,//254.......

0x7c,//255.......p
0x14,//256.......
0x24,//257.......
0x24,//258.......
0x18,//259.......

0x18,//260.......q
0x24,//261.......
0x14,//262.......
0x7c,//263.......
0x40,//264.......

0x00,//265.......r
0x7c,//266.......
0x08,//267.......
0x04,//268.......
0x04,//269.......

0x48,//270.......s
0x54,//271.......
0x54,//272.......
0x54,//273.......
0x20,//274.......

0x04,//275.......t
0x3e,//276.......
0x44,//277.......
0x20,//278.......
0x00,//279.......

0x3c,//280.......u
0x40,//281.......
0x40,//282.......
0x20,//283.......
0x7c,//284.......

0x1c,//285.......v
0x20,//286.......
0x40,//287.......
0x20,//288.......
0x1c,//289.......

0x3c,//290.......w
0x40,//291.......
0x30,//292.......
0x40,//293.......
0x3c,//294.......

0x44,//295.......x
0x28,//296.......
0x10,//297.......
0x28,//298.......
0x44,//299.......

0x04,//300.......y
0x48,//301.......
0x30,//302.......
0x08,//303.......
0x04,//304.......

0x44,//305.......z
0x64,//306.......
0x54,//307.......
0x4c,//308.......
0x44,//309.......

0x00,//310....... espaço
0x00,//311.......
0x00,//312.......
0x00,//313.......
0x00,//314.......

0x08,//315....... -
0x08,//316.......
0x08,//317.......
0x08,//318.......
0x08,//319.......

0x08,//320....... +
0x08,//321.......
0x3e,//322.......
0x08,//323.......
0x08,//324.......

0x00,//325....... .
0x70,//326.......
0x70,//327.......
0x70,//328.......
0x00,//329.......

0x3e,//330....... (
0x41,//331.......
0x00,//332.......
0x00,//333.......
0x00,//334.......

0x00,//335....... )
0x00,//336.......
0x00,//337.......
0x41,//338.......
0x3e,//339.......

0x00,//340....... >=
0x51,//341.......
0x4a,//342.......
0x44,//343.......
0x00,//344.......

0x00,//345....... <=
0x44,//346.......
0x4a,//347.......
0x51,//348.......
0x00,//349.......

0x00,//350....... :
0x66,//351.......
0x66,//352.......
0x00,//353.......
0x00,//354.......

0x00,//355....... °
0x06,//356.......
0x09,//357.......
0x09,//358.......
0x06,//359.......

0x44,//360....... +-
0x44,//361.......
0x5f,//362.......
0x44,//363.......
0x44,//364.......

//0x2a,//365....... *
//0x1c,//366.......
//0x3e,//367.......
//0x1c,//368.......
//0x2a,//369.......

0x00,//365....... x (vezes)
0x50,//366.......
0x20,//367.......
0x50,//368.......
0x00,//369.......

};

//SUBROTINA INITHCMS297X 
//INICIALIZA HCMS297X

void inithcms297x (void){
//#ifdef disp_hcms
	//char aux1[]="        ";
	//CONFIGURAÇÃO DAS PORTAS DO PIC COMO SAÍDAS PARA O HCMS297X


	T_DATA_LINE = 0;
	T_REGISTER_SELECT = 0;
	T_CHIP_ENABLE = 0;
	T_CLOCK = 0;
	T_RESET = 0;

	//"RESET" O DISPLAY
	RESET = 0;	//reset do HCMS297X
	RESET = 1;	//operação normal do HCMS297
	
	//"CLEARED" O DISPLAY
	TextoBuffer[0] = 310;//
	TextoBuffer[1] = 310;//
	TextoBuffer[2] = 310;//
	TextoBuffer[3] = 310;//
	TextoBuffer[4] = 310;//
	TextoBuffer[5] = 310;//
	TextoBuffer[6] = 310;//
	TextoBuffer[7] = 310;//1

	fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
	
	//ENDEREÇAMENTO DA "CONTROL WORDS"
	contsx(W0_DEFAULT, W1_DEFAULT);//W0_MAXBRIGHTNESS ==100%brilho W0_AVEBRIGHTNESS= 50% brilho
//#endif
}



//SUBROTINA CONTSX
//CONTROLE DO "SLEEP", BRILHO, "PRESCALER" E MODO SERIAL/PARALELO

void contsx (char word0, char word1){
//#ifdef disp_hcms
	char aux1;
	char aux2;
	char aux3;
	char controlWord;	//palavra de controle
	
	//SELECIONA REGISTRADOR DE CONTROLE
	CHIP_ENABLE = 1;	
	REGISTER_SELECT = 1;	
	
	//ENVIA PALAVRA 1 PRIMEIRO, ENTÃO ENVIA A PALAVRA 0
	for(aux2=0; aux2<2; aux2++){
		
		//PRIMEIRO MESTRE, DEPOIS ESCRAVO
		for(aux1=0; aux1<2; aux1++){

			if(aux2==0)
				controlWord = word1; //palavra de controle 1, simultâneo
			if(aux2==1)
				controlWord = word0; //palavra de controle 0, brilho=44%, acordado
	
			CHIP_ENABLE = 0; //"set" CE=0 para entrar dado
			
			//CARREGA REGISTRADOR DE CONTROLE
			for(aux3=0; aux3<8; aux3++){		
				CLOCK = 0;
				if(controlWord & 0x80)		//	 
					DATA_LINE = 1;	//move o carry para 	
				else			//o DATA_LINE	
					DATA_LINE = 0;	//
		
				controlWord <<= 1; //gira MSB para carry, carry para LSB

				CLOCK = 1; //"set" CLOCK=1 para receber bit de dado
			}
			
			//ARMAZENA DADO PARA A PALAVRA DE CONTROLE
			CLOCK = 0;
			CHIP_ENABLE = 1; //"set" CE=1 para finalizar a entrada de dados
		}
	}
//#endif
}





void fetchcharDspic(char text[])
{

	char aux1, aux2, aux3;
	char column;
	unsigned int aux4;

	di();

	CHIP_ENABLE = 1;

	REGISTER_SELECT = 0;

	CHIP_ENABLE = 0;

	for(aux3=0; aux3<NUMDIG; aux3++){//8 dígitos no vetor
		
		for(aux1=0;aux1<5;aux1++){//5 colunas
		
			column = rets[aux4];
			aux4++;
			for(aux2=0; aux2<8; aux2++){//8 linhas
				CLOCK = 0;
				if(column & 0x80)	//	 
					DATA_LINE = 1;	//move o carry para 	
				else			//o DATA_LINE	
					DATA_LINE = 0;	//
				column <<= 1; //gira MSB para carry, carry para LSB
				CLOCK = 1; //"set" CLOCK=1 para receber bit de dado
			}
		}

	}	

	//COPIA DADO DO "DOT REGISTER" PARA O "DOT LATCH"
	CLOCK = 0;
	CHIP_ENABLE = 1; //"set" CE em "high" para finalizar entrada de dados

//	ei();


}

void fetchcharDspic8dig( unsigned int dig7,unsigned int dig6,unsigned int dig5,unsigned int dig4,
						 unsigned int dig3,unsigned int dig2,unsigned int dig1,unsigned int dig0){

	char aux1, aux2, aux3;
	char column;
	unsigned int aux4;

	CHIP_ENABLE = 1;

	REGISTER_SELECT = 0;

	CHIP_ENABLE = 0;
	for(aux3=0; aux3<NUMDIG; aux3++){//8 dígitos no vetor	
		switch(aux3){
			case 0:
				aux4 = dig7;
			break;
			case 1:
				aux4 = dig6;
			break;
			case 2:
				aux4 = dig5;
			break;
			case 3:
				aux4 = dig4;
			break;
			case 4:
				aux4 = dig3;
			break;
			case 5:
				aux4 = dig2;
			break;
			case 6:
				aux4 = dig1;
			break;
			case 7:
				aux4 = dig0;
			break;
		}
		for(aux1=0;aux1<5;aux1++){//5 colunas
		
			column = rets[aux1+aux4];
	
			for(aux2=0; aux2<8; aux2++){//8 linhas
				CLOCK = 0;
				if(column & 0x80)	//	 
					DATA_LINE = 1;	//move o carry para 	
				else			//o DATA_LINE	
					DATA_LINE = 0;	//
				column <<= 1; //gira MSB para carry, carry para LSB
				CLOCK = 1; //"set" CLOCK=1 para receber bit de dado
			}
		}
	}
	//COPIA DADO DO "DOT REGISTER" PARA O "DOT LATCH"
	CLOCK = 0;
	CHIP_ENABLE = 1; //"set" CE em "high" para finalizar entrada de dados

}

//SUBROTINA DISPLAYTEXT
//ENVIA UM TEXTO DE 8 CARACTERES PARA O DISPLAY


void fetchchar2(char text[])
{


	char aux1, aux2, aux3;
	char column;
	
	CHIP_ENABLE = 1;

	REGISTER_SELECT = 0;

	CHIP_ENABLE = 0;
	for(aux3=0; aux3<NUMDIG; aux3++){
		for(aux1=0;aux1<5;aux1++){

			for(aux2=0; aux2<8; aux2++){
				CLOCK = 0;
				if(column & 0x80)	//	 
					DATA_LINE = 1;	//move o carry para 	
				else			//o DATA_LINE	
					DATA_LINE = 0;	//
				column <<= 1; //gira MSB para carry, carry para LSB
				CLOCK = 1; //"set" CLOCK=1 para receber bit de dado
			}
		}
	}	

	//COPIA DADO DO "DOT REGISTER" PARA O "DOT LATCH"
	CLOCK = 0;
	CHIP_ENABLE = 1; //"set" CE em "high" para finalizar entrada de dados


}

void display_decimal(unsigned int md)
{
	static char x;
	unsigned int valor;
	texto[0] = ' ';
	texto[1] = ' ';
	texto[2] = ' ';
	texto[3] = ' ';





	valor = md;
	texto[6] = '.';
	
	x = (md%10);
	texto[7] = 48+x;//digito unidade
	md/=10;

	x = (md%10);
	texto[5] = 48+x;//digito dezena
	md/=10;

	x = (md%10);
	texto[4] = 48+x;//digito centena


	md/=10;
	x = md;
	texto[3] = 48+x;//digito milhar

	if(valor<100){
		texto[4] = ' ';
	}
	if(valor<1000){
		texto[3] = ' ';
	}
/*
		texto[4]='1';//msb
		texto[5]='2';
		texto[6]='.';
		texto[7]='3';//lsb           00,0
*/
	fetchchar2(texto);
}
//LigPisca = 1, pisca o dígito correspondente ao valor de Pos
//dig, limita a quantidade de dígitos serão apresentados no display
void DispSigLong(signed long SigMd,char Pd, char dig, char LigPisca)
{
//Apresentação no display
///////////////////////////////////////////
//Dig0-Dig1-Dig2-Dig3-Dig4-Dig5-Dig6-Dig7//
///////////////////////////////////////////
	static char i,x;
	unsigned long UnsigMd;
//-----------------------------------------------------
//Coloca sinal no valor
	if(SigMd==0){
		TextoBuffer[0]=310;//' '
		UnsigMd = 0;
		if(Pos==5)Pos = 0;
	}
	else if(SigMd<0){
		UnsigMd = (unsigned long)((SigMd)*(-1));
		TextoBuffer[0]=315;//-
	}
	else{
		UnsigMd = (unsigned long)(SigMd);
		TextoBuffer[0]=320;//+
	}
//---------

	for(i=7;i>2;i--)TextoBuffer[i] = 0;//'0'
	
	TextoBuffer[1] = 310;//' '
	TextoBuffer[2] = 310;//' '

	for (i=0;i<5;i++)
	{
		x = (char)(UnsigMd%10);
		TextoBuffer[7-i] = 5*x;
		UnsigMd/=10;
		
		if ((UnsigMd == 0)) break;	
	}
	

//-----------------------------------------------------
//Apaga o display conforme o número de dígitos a serem mostrados

if(menu_aux.tag!=ANALOGICA0&&menu_aux.tag!=ANALOGICA1&&menu_aux.tag!=ANALOGICA0_2&&menu_aux.tag!=ANALOGICA1_2){
	for(i=0;i<(7-NumDigDisplay);i++)TextoBuffer[i+1] = 310;//' '
}
	if((LigPisca==PISCA_ON)&&(flag_segundos!=0)){
		if(Pos<5)TextoBuffer[7-Pos] = 310;//' '
		else TextoBuffer[0] = 310;//' '
	}



	
	if(modo==MODO_PROGRAMAR){
		switch(menu_aux.tag){
			case FILTRO:
			case FILTRO2:
			case MEDIA:
				TextoBuffer[0] =310;
				TextoBuffer[1] =310;
				TextoBuffer[2] =310;
				TextoBuffer[3] =310;
				TextoBuffer[4] =310;
				TextoBuffer[5] =310;
			break;
			case TALIM1:
			case TALIM2:
			case TALIM3:
			case TALIM4:
			case TDLIM1:
			case TDLIM2:
			case TDLIM3:
			case TDLIM4:
				TextoBuffer[0] =310;
				TextoBuffer[1] =310;
				TextoBuffer[2] =310;
				TextoBuffer[3] =310;
				TextoBuffer[4] =310;
			break;
			case NUMDIGITO:
				TextoBuffer[0] =310;
			break;
		}
	}



	switch (Pd){
		case 0:
			fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
		break;

		case 1:
			if(NumDigDisplay<=1)fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],310,TextoBuffer[7]);
			else fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],325,TextoBuffer[7]);
		break;

		case 2:
			if(NumDigDisplay<=2)fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],310,TextoBuffer[6],TextoBuffer[7]);
			else fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],325,TextoBuffer[6],TextoBuffer[7]);
		break;

		case 3:
			if(NumDigDisplay<=3)fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],310,TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			else fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],325,TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
		break;

		case 4:
			if(NumDigDisplay<=4)fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],310,TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
			else fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],325,TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
		break;


	}

}
//LigPisca = 1, pisca o dígito correspondente ao valor de Pos
//dig, limita a quantidade de dígitos serão apresentados no display
void DispSigLongXYZ(signed long SigMd,char Pd, char dig, char LigPisca,char eixo)
{
//Apresentação no display
///////////////////////////////////////////
//Dig0-Dig1-Dig2-Dig3-Dig4-Dig5-Dig6-Dig7//
///////////////////////////////////////////
	static char i,x;
	unsigned long UnsigMd;
//-----------------------------------------------------
//Coloca sinal no valor
	if(SigMd==0){
		TextoBuffer[0]=310;//' '
		UnsigMd = 0;
		if(Pos==5)Pos = 0;
	}
	else if(SigMd<0){
		UnsigMd = (unsigned long)((SigMd)*(-1));
		TextoBuffer[0]=315;//-
	}
	else{
		UnsigMd = (unsigned long)(SigMd);
		TextoBuffer[0]=320;//+
	}
//---------

	for(i=7;i>2;i--)TextoBuffer[i] = 0;//'0'
	
	TextoBuffer[1] = 310;//' '
	TextoBuffer[2] = 310;//' '

	for (i=0;i<5;i++)
	{
		x = (char)(UnsigMd%10);
		TextoBuffer[7-i] = 5*x;
		UnsigMd/=10;
		
		if ((UnsigMd == 0)) break;	
	}
	

//-----------------------------------------------------
//Apaga o display conforme o número de dígitos a serem mostrados
	for(i=0;i<(7-NumDigDisplay);i++)TextoBuffer[i+1] = 310;//' '

	if((LigPisca==PISCA_ON)&&(flag_segundos!=0)){
		if(Pos<5)TextoBuffer[7-Pos] = 310;//' '
		else TextoBuffer[0] = 310;//' '
	}
	
	if(modo==MODO_PROGRAMAR){
		switch(menu_aux.tag){
			case FILTRO:
			case FILTRO2:
			case MEDIA:
				TextoBuffer[0] =310;
				TextoBuffer[1] =310;
				TextoBuffer[2] =310;
				TextoBuffer[3] =310;
				TextoBuffer[4] =310;
				TextoBuffer[5] =310;
			break;
			case TALIM1:
			case TALIM2:
			case TALIM3:
			case TALIM4:
			case TDLIM1:
			case TDLIM2:
			case TDLIM3:
			case TDLIM4:
				TextoBuffer[0] =310;
				TextoBuffer[1] =310;
				TextoBuffer[2] =310;
				TextoBuffer[3] =310;
				TextoBuffer[4] =310;
			break;
			case NUMDIGITO:
				TextoBuffer[0] =310;
			break;
		}
	}




	switch (Pd){
		case 0:
			
			TextoBuffer[1] = TextoBuffer[2];
			TextoBuffer[2] = TextoBuffer[3];
			TextoBuffer[3] = TextoBuffer[4];
			TextoBuffer[4] = TextoBuffer[5];
			TextoBuffer[5] = TextoBuffer[6];
			TextoBuffer[6] = TextoBuffer[7];
	if(eixo==X)TextoBuffer[7] = 295;
	else if(eixo==Y)TextoBuffer[7] = 300;
	else if(eixo==Z)TextoBuffer[7] = 305;
			fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
		break;

		case 1:
			if(NumDigDisplay<=1){
				//fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],310,TextoBuffer[7]);
				TextoBuffer[2] = TextoBuffer[3];
				TextoBuffer[3] = TextoBuffer[4];
				TextoBuffer[4] = TextoBuffer[5];
				TextoBuffer[5] = TextoBuffer[6];
				TextoBuffer[6] = 310;
				TextoBuffer[1] = TextoBuffer[7];
				//TextoBuffer[7] = 295;//x
			}
			else {
				//fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],325,TextoBuffer[7]);
				TextoBuffer[2] = TextoBuffer[3];
				TextoBuffer[3] = TextoBuffer[4];
				TextoBuffer[4] = TextoBuffer[5];
				TextoBuffer[5] = TextoBuffer[6];
				TextoBuffer[6] = 325;
				TextoBuffer[1] = TextoBuffer[7];
				//TextoBuffer[7] = 295;//x
			}
	if(eixo==X)TextoBuffer[7] = 295;
	else if(eixo==Y)TextoBuffer[7] = 300;
	else if(eixo==Z)TextoBuffer[7] = 305;
			fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[1],TextoBuffer[7]);
		break;

		case 2:
			if(NumDigDisplay<=2){
				//fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],310,TextoBuffer[6],TextoBuffer[7]);
				TextoBuffer[2] = TextoBuffer[3];
				TextoBuffer[3] = TextoBuffer[4];
				TextoBuffer[4] = TextoBuffer[5];
				TextoBuffer[5] = 310;
				TextoBuffer[1] = TextoBuffer[6];
				TextoBuffer[6] = TextoBuffer[7];
				//TextoBuffer[7] = 295;//x
			}
			else{
				//fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],325,TextoBuffer[6],TextoBuffer[7]);
				TextoBuffer[2] = TextoBuffer[3];
				TextoBuffer[3] = TextoBuffer[4];
				TextoBuffer[4] = TextoBuffer[5];
				TextoBuffer[5] = 325;
				TextoBuffer[1] = TextoBuffer[6];
				TextoBuffer[6] = TextoBuffer[7];
				//TextoBuffer[7] = 295;//x
			}
	if(eixo==X)TextoBuffer[7] = 295;
	else if(eixo==Y)TextoBuffer[7] = 300;
	else if(eixo==Z)TextoBuffer[7] = 305;
			fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[1],TextoBuffer[6],TextoBuffer[7]);
		break;

		case 3:
			if(NumDigDisplay<=3){
				//fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],310,TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				TextoBuffer[2] = TextoBuffer[3];
				TextoBuffer[3] = TextoBuffer[4];
				TextoBuffer[4] = 310;
				TextoBuffer[5] = TextoBuffer[5];
				TextoBuffer[1] = TextoBuffer[6];
				TextoBuffer[6] = TextoBuffer[7];
				//TextoBuffer[7] = 295;//x
			}
			else{
				//fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],325,TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				TextoBuffer[2] = TextoBuffer[3];
				TextoBuffer[3] = TextoBuffer[4];
				TextoBuffer[4] = 325;
				TextoBuffer[5] = TextoBuffer[5];
				TextoBuffer[1] = TextoBuffer[6];
				TextoBuffer[6] = TextoBuffer[7];
				//TextoBuffer[7] = 295;//x

			}
	if(eixo==X)TextoBuffer[7] = 295;
	else if(eixo==Y)TextoBuffer[7] = 300;
	else if(eixo==Z)TextoBuffer[7] = 305;
			fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[1],TextoBuffer[6],TextoBuffer[7]);
		break;

		case 4:
			if(NumDigDisplay<=4){
				//fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],310,TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				TextoBuffer[2] = TextoBuffer[3];
				TextoBuffer[3] = 310;
				TextoBuffer[4] = TextoBuffer[4];
				TextoBuffer[5] = TextoBuffer[5];
				TextoBuffer[1] = TextoBuffer[6];
				TextoBuffer[6] = TextoBuffer[7];
				//TextoBuffer[7] = 295;//x

			}
			else{
				//fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],325,TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				TextoBuffer[2] = TextoBuffer[3];
				TextoBuffer[3] = 325;
				TextoBuffer[4] = TextoBuffer[4];
				TextoBuffer[5] = TextoBuffer[5];
				TextoBuffer[1] = TextoBuffer[6];
				TextoBuffer[6] = TextoBuffer[7];
				//TextoBuffer[7] = 295;//x

			}
	if(eixo==X)TextoBuffer[7] = 295;
	else if(eixo==Y)TextoBuffer[7] = 300;
	else if(eixo==Z)TextoBuffer[7] = 305;
			fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[1],TextoBuffer[6],TextoBuffer[7]);
		break;


	}

}


void DispUnsigLong(unsigned long md,char inicio, char dig)
{
	static char i,x, ini;
	ini = inicio-1;

		if( (modo==MODO_NORMAL)&&(mostra_var!=1))for(i=ini;i>(ini-dig);i--)TextoBuffer[i] = 310;//apaga
		else for(i=ini;i>(ini-dig);i--)TextoBuffer[i] = 0;//'0'

		for (i=0;i<inicio;i++)
		{
			x = (char)(md%10);
			TextoBuffer[ini-i] = 5*x;
			md/=10;
			
			if ((md == 0)) break;
			
		}
	fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

}



//----------------------------------------------------------------------------
//----------- PARA FAZER O ANGULO COM SINAL -108 E 180 GRAUS -----------------

void display_decimal_signed(signed int md) // TESTE - KELLEN
{
	static char x;
	signed int valor;
	texto[0] = ' ';
	texto[1] = ' ';
	texto[2] = ' ';
	texto[3] = ' ';

	md = md -1800; // PARA VARIAR DE -180 A 180 - KELLEN 



	if(md<0){			//Essa condição coloca o sinal de negativo quando for <0. KELLEN
		md = md*(-1);
		texto[0] = ' ';
		texto[1] = ' ';
		texto[2] = '-';
	}

	valor = md;
	texto[6] = '.';
	
	x = (md%10); //JOGA O RESTO DA DIVISÃO EM X
	texto[7] = 48+x;//digito unidade
	md/=10;

	x = (md%10);
	texto[5] = 48+x;//digito dezena
	md/=10;

	x = (md%10);
	texto[4] = 48+x;//digito centena


	md/=10;
	x = md;
	texto[3] = 48+x;//digito milhar

	if(valor<100){
		texto[4] = ' ';
	}
	if(valor<1000){
		texto[3] = ' ';
	}
/*
		texto[4]='1';//msb
		texto[5]='2';
		texto[6]='.';
		texto[7]='3';//lsb           00,0
*/
	fetchchar2(texto);
}



//LigPisca = 1, pisca o dígito correspondente ao valor de Pos
//dig, limita a quantidade de dígitos serão apresentados no display
void DispSigLong12(signed long SigMd,char Pd, char dig,char eixo)
{
//Apresentação no display
///////////////////////////////////////////
//Dig0-Dig1-Dig2-Dig3-Dig4-Dig5-Dig6-Dig7//
///////////////////////////////////////////
	static char i,x;
	unsigned long UnsigMd;

	if(eixo==X)TextoBuffer[0] = 165;//X
	else if(eixo==Y)TextoBuffer[0] = 170;//Y
	else if(eixo==Z)TextoBuffer[0] = 305;//Z
	TextoBuffer[1] = 350; //:
//-----------------------------------------------------
//Coloca sinal no valor
	if(SigMd==0){
		TextoBuffer[2]=310;//' '
		UnsigMd = 0;
		if(Pos==5)Pos = 0;
	}
	else if(SigMd<0){
		UnsigMd = (unsigned long)((SigMd)*(-1));
		TextoBuffer[2]=315;//-
	}
	else{
		UnsigMd = (unsigned long)(SigMd);
		TextoBuffer[2]=320;//+
	}
//-----------------------------------------------------

//-----------------------------------------------------------
//Converte o número em string
//-----------------------------------------------------------
//onde: -TextoBuffer[7] é o menos significativo
//      -TextoBuffer[3] é o mais significativo
	
	for(i=0;i<5;i++)TextoBuffer[i+3] = 0;//'0'




	for (i=0;i<5;i++)
	{
		x = (char)(UnsigMd%10);
		TextoBuffer[7-i] = 5*x;//x = 0 escreve 0 no display
		UnsigMd/=10;
		
		if ((UnsigMd == 0)) break;	
	}
//-----------------------------------------------------------


//--------------------------------------------------------------
//Apaga o display conforme o número de dígitos a serem mostrados
	switch(NumDigDisplay){
		case 1:
			TextoBuffer[3] = 310;//' '
			TextoBuffer[4] = 310;//' '
			TextoBuffer[5] = 310;//' '
			TextoBuffer[6] = 310;//' '
			fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
		break;
		case 2:
			TextoBuffer[3] = 310;//' '
			TextoBuffer[4] = 310;//' '
			TextoBuffer[5] = 310;//' '
			switch(Pd){
				case 0:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;
				case 1:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],325,TextoBuffer[7]);
				break;
				case 2:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;
				case 3:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;	
				case 4:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;
			}
		break;
		case 3:
			TextoBuffer[3] = 310;//' '
			TextoBuffer[4] = 310;//' '
			switch(Pd){
				case 0:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;
				case 1:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],325,TextoBuffer[7]);
				break;
				case 2:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[5],325,TextoBuffer[6],TextoBuffer[7]);
				break;
				case 3:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;
				case 4:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;
			}
		break;
		case 4:
			TextoBuffer[3] = 310;//' '
			switch(Pd){
				case 0:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;
				case 1:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],325,TextoBuffer[7]);
				break;
				case 2:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[4],TextoBuffer[5],325,TextoBuffer[6],TextoBuffer[7]);
				break;
				case 3:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[4],325,TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;
				case 4:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],325,TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;	
			}
		break;
		case 5:
			switch(Pd){
				case 0:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;
				case 1:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],325,TextoBuffer[7]);
				break;
				case 2:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[4],TextoBuffer[5],325,TextoBuffer[6],TextoBuffer[7]);
				break;
				case 3:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[4],325,TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;
				case 4:
					fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],325,TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);
				break;
	
			}
		break;
	}


}
