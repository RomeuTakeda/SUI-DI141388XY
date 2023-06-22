

//Para utilizar a biblioteca relativa ao hcms297x siga os seguintes passos:
//1  -	no arquivo hcms297x.h, altere as defini��es das portas l�gicas utilizadas na interface do PIC com o hcms297x de 
//	acordo com o hardware utilizado
//2  -	no arquivo hcms297x.h, altere a quantidade de d�gitos do display de acordo com o hardware utilizado	
//3  -	inicialize o uso do hcms297x atrav�s da sub-rotina "inithcms297x()" (esta fun��o limpa o buffer do hcms297x
//	evitando que "lixos" sejam exibidos, configura o funcionamento do hcms297x para modo normal, 132mA, 60% do 
//	brilho relativo e modo simult�neo)
//4  -	no programa principal, defina um vetor com o n�mero de posi��es igual ao n�mero de d�gitos do display + 1(devido
//	ao "/0")
//5  -	para exibir uma string no display, atualize o vetor definido conforme explicado no item 4 e use a fun��o
//	fetchchar(vetor);
//	para exibir uma vari�vel do tipo int � necess�rio transform�-la em string e armazen�-lo no vetor definido
//	conforme explicado no item 4. isto pode ser feito atrav�s da fun��o itoa(vetor, vari�vel, posi��o inicial da 
//	vari�vel no vetor(a contar da esq. p/ a dir. come�ando do 1), comprimento da vari�vel)
//	para exibir uma vari�vel de qualquer outro tipo que n�o int, � necess�rio transform�-la em int, em seguida em 
//	string atrav�s da fun��o itoa(vet, var, pos, com) e por �ltimo a fun��o fetchchar(vet)
//6  -	para colocar o display no modo sleep, ou alterar o brilho relativo e consequ�ntemente a corrente consumida pelo
//	hcms297x deve-se usar a fun��o contsx(word0, word1) onde apenas o word0 dever� ser alterado. no arquivo
//	hcms297x.h, verifique as defini��es das palavras de controle para word0
//
//
//EXEMPLO1
//exibir uma vari�vel do tipo float com 1 casa decimal, casas de unidade, dezena e centena em um display de 8 d�gitos:
//
//	float f;
//	unsigned int s;
//	unsigned int d;
//	char v[9];
//	
//	if(f<999.9)	//observe que a vari�vel do tipo float NESTA
//		f++;	//APLICA��O pode ser limitado em 4 casas
//	else		//estas 4 casas � equivalente ao n�mero
//		f=0;	//de casas que ser�o exibidas
//
//	s=(unsigned int)f; //casa de unidade, dezena e centena
//	
//	d=s/10;				//casa
//	d=(unsigned int)(f*10)-s*10;	//decimal
//	
//	itoa(v, s, 3, 3);	//
//	itoa(v, d, 5, 1);	//prepara��o 
//	v[3]= '.';		//do vetor
//	strcat(v, "m/s");	//
//	
//	fetchchar(v);		//exibe conte�do do vetor
//
//
//EXEMPLO2
//alterar modo de opera��o do display para SLEEP
//
//	contsx(W0_SLEEP, W1_DEFAULT);
//
//
//PROT�TIPO DAS FUN��ES
//
//inithcms297x();
//
//contsx(palavra de controle 0, palavra de controle 1);
//
//fetchchar(vetor de caracteres);
//
//itoa (vetor de caracteres, vari�vel ou n�metro, comprimento do n�mero, posi��o inicial do n�mero a contar da esquerda
//para a direita);



//DEFINI��O DAS PORTAS L�GICAS UTILIZADAS NA INTERFACE DO PIC COM O HCMS297X
//DEFINI��O DAS PORTAS L�GICAS UTILIZADAS NA INTERFACE DO PIC COM O HCMS297X


#define T_CLOCK 			TRISDbits.TRISD0
#define CLOCK 			PORTDbits.RD0

#define T_REGISTER_SELECT 	TRISDbits.TRISD1
#define REGISTER_SELECT PORTDbits.RD1

#define T_RESET 			TRISDbits.TRISD2
#define RESET	 		PORTDbits.RD2 

#define T_CHIP_ENABLE 		TRISDbits.TRISD3 
#define CHIP_ENABLE 	PORTDbits.RD3

#define T_DATA_LINE 		TRISDbits.TRISD4
#define DATA_LINE 		PORTDbits.RD4

//DEFINI��O DA QUANTIDADE DE D�GITOS DO DISPLAY
#define NUMDIG 8

#define X 0
#define Y 1
#define Z 2

//DEFINI��O DAS PALAVRAS DE CONTROLE
//WORD0
#define W0_DEFAULT 0b01001101 		//modo normal, 132mA, 60% do brilho relativo
#define W0_MAXBRIGHTNESS 0b01111111 	//modo normal, 280mA, 100% do brilho relativo
#define W0_MINBRIGHTNESS 0b01100001 	//modo normal, 1,78mA, 1,7% do brilho relativo
#define W0_AVEBRIGHTNESS 0b01011100 	//modo normal, 74mA, 47% do brilho relativo
#define W0_SLEEP 0b00001101 		//desabilita oscilador interno - display em branco
//WORD1
#define W1_DEFAULT 0b10000001 //MODO SIMULT�NEO


extern unsigned int TextoBuffer[8];
extern char texto[8];
extern unsigned char caracter[41];
extern void fetchcharDspic8dig( unsigned int dig7,unsigned int dig6,unsigned int dig5,unsigned int dig4,
						 unsigned int dig3,unsigned int dig2,unsigned int dig1,unsigned int dig0);

//ESCOPO DAS SUBROTINAS/FUN��ES
extern void inithcms297x (void);


extern void contsx (char word0, char word1);

extern void display_decimal(unsigned int md);
extern void fetchchar2(char text[]);
extern void fetchcharDspic(char text[]);
//extern void itoa (char *word, int number, char position, char length);
extern void displaytext(char text[]);
extern void DispUnsigLong(unsigned long md,char inicio, char dig);
extern void DispSigLong(signed long md/*, char ponto*/, char inicio, char dig, char LigPisca);
extern void DispSigLongXYZ(signed long SigMd,char Pd, char dig, char LigPisca, char eixo);
void DispSigLong12(signed long SigMd,char Pd, char dig,char eixo);


