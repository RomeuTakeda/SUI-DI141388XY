#include <p18f252.h>
#include <spi.h>
#include "adis16209.h"
#include "main.h"

//------------------------------------------------------------------------------------
unsigned int HDByteRead_TEMP(unsigned char *rdptr){
  CS = 0;       
  WriteSPI(0x0A);		 //hi               
  WriteSPI(0);        //low   
  CS = 1; 

  Delay10TCYx(1);//
  CS = 0; 
  getsSPI( rdptr,2);   //vai ler 2 endereços        
  CS = 1;                       

  leitura_sem_sinal=(((unsigned int)valorx[0] << 8) + (unsigned int)valorx[1]);
  leitura_sem_sinal = (leitura_sem_sinal & 0b0000111111111111);
   

  return ( leitura_sem_sinal );                
}
unsigned int HDByteRead_FONTE(unsigned char *rdptr){
  CS = 0;       
  WriteSPI(0x02);		 //hi               
  WriteSPI(0);        //low   
  CS = 1; 

  Delay10TCYx(1);//
  CS = 0; 
  getsSPI( rdptr,2);   //vai ler 2 endereços        
  CS = 1;                       
//valorx[0]== byte hi
//valorx[1]== byte low

  leitura_sem_sinal=(((unsigned int)valorx[0] << 8) + (unsigned int)valorx[1]);
  leitura_sem_sinal = (leitura_sem_sinal & 0b0011111111111111);
   

  return ( leitura_sem_sinal );                
}



unsigned int HDByteRead_INCLINACAO(unsigned char *rdptr){
	CS = 0;       
	WriteSPI(0x10);		 //hi               
	WriteSPI(0);        //low   
	CS = 1; 
	Delay10TCYx(1);//
	CS = 0; 
	getsSPI( rdptr,2);   //vai ler 2 endereços        
	CS = 1;              
	
	leitura_sem_sinal = (((unsigned int)valorx[0] << 8) + (unsigned int)valorx[1]);
	
	flag_menos = (leitura_sem_sinal>>13)&0x0001;
	
	if(flag_menos){
		leitura_sem_sinal = ~leitura_sem_sinal;
		leitura_sem_sinal = leitura_sem_sinal+1;
	}
	
	leitura_sem_sinal = leitura_sem_sinal&0x3fff;//máscara para 14bits
	
	//if(flag_menos) SignedIntLeitura = -SignedIntLeitura;
	
	//SignedIntLeitura = SignedIntLeitura*0.25; 
	
	//leitura_sem_sinal = (unsigned int)1800+(unsigned int)SignedIntLeitura;
	//return ( leitura_sem_sinal);  // retorna de 0 a 3600 

	Inclinacao = leitura_sem_sinal*0.25;
	Sinal = flag_menos;
	return (0);  // retorna de -180 a 180 com o sinal indicado em um flag 
   
}


void Adis16209Read(unsigned char addr,unsigned char *rdptr){
	CS = 0;       
	WriteSPI(addr);		 //hi               
	WriteSPI(0);        //low   
	CS = 1; 
	Delay10TCYx(10);//
	CS = 0; 
	getsSPI( rdptr,2);   //vai ler 2 endereços        
	CS = 1;              
	
	
	switch (addr){
		case INCLINACAO:	
		case INCLINACAOX:
		case INCLINACAOY:
	
			leitura_sem_sinal = (((unsigned int)valorx[0] << 8) + (unsigned int)valorx[1]);
			
			flag_menos = (leitura_sem_sinal>>13)&0x0001;
			
			if(flag_menos){
				leitura_sem_sinal = ~leitura_sem_sinal;
				leitura_sem_sinal = leitura_sem_sinal+1;
			}
			leitura_sem_sinal = (leitura_sem_sinal&0x3fff)*0.25;//máscara para 14bits e multiplicação pelo peso do led*10
			Polaridade = flag_menos;	

		break;
		case TEMPERATURA:
	
			leitura_sem_sinal = (((unsigned int)valorx[0] << 8) + (unsigned int)valorx[1]);
			
			leitura_sem_sinal = leitura_sem_sinal&0x0fff;

			SignedIntLeitura = (signed int)leitura_sem_sinal-1278;

			SignedIntLeitura = SignedIntLeitura*(-0.47) +25;


			
			if(SignedIntLeitura<0) SignedIntLeitura = -SignedIntLeitura;
			leitura_sem_sinal = (unsigned int)SignedIntLeitura;		

		break;	
	
	
	}

}





unsigned int HDByteRead_INCLINACAO_X(unsigned char *rdptr){
signed int LeituraComSinal;
unsigned int resto;


	CS = 0;       
	WriteSPI(0x0c);		 //hi               
	WriteSPI(0);        //low   
	CS = 1; 
	Delay10TCYx(1);//
	CS = 0; 
	getsSPI( rdptr,2);   //vai ler 2 endereços        
	CS = 1;              

	leitura_sem_sinal = (((unsigned int)valorx[0] << 8) + (unsigned int)valorx[1]);
	
	flag_menos = (leitura_sem_sinal>>13)&0x0001;
	
	if(flag_menos){
		leitura_sem_sinal = ~leitura_sem_sinal;
		leitura_sem_sinal = leitura_sem_sinal+1;
	}
	
	leitura_sem_sinal = leitura_sem_sinal&0x3fff;//máscara para 14bits
	
	SignedIntLeitura = (signed int)leitura_sem_sinal;
	if(flag_menos) SignedIntLeitura = -SignedIntLeitura;
	
	SignedIntLeitura = SignedIntLeitura*0.25; 
	
	leitura_sem_sinal = (unsigned int)900+(unsigned int)SignedIntLeitura;
	
	return ( leitura_sem_sinal);  // retorna de 0 a 1800 

}

unsigned int HDByteRead_INCLINACAO_Y(unsigned char *rdptr){
signed int LeituraComSinal;
unsigned int resto;
  CS = 0;       
  WriteSPI(0x0E);		 //hi               
  WriteSPI(0);        //low   
  CS = 1; 
  Delay10TCYx(1);//
  CS = 0; 
  getsSPI( rdptr,2);   //vai ler 2 endereços        
  CS = 1;                       
//valorx[0]== byte hi
//valorx[1]== byte low
//retorna em 14 bis e na forma de complemento de 2

	leitura_sem_sinal = (((unsigned int)valorx[0] << 8) + (unsigned int)valorx[1]);

	flag_menos = (leitura_sem_sinal>>13)&0x0001;

	if(flag_menos)leitura_sem_sinal = -leitura_sem_sinal;//(~leitura_sem_sinal)+1;

	SinalY = flag_menos;

	leitura_sem_sinal = leitura_sem_sinal&0b0001111111111111;

	leitura_sem_sinal = 0.250941*leitura_sem_sinal;
	resto = leitura_sem_sinal%10;
	leitura_sem_sinal = leitura_sem_sinal-resto;
	if(leitura_sem_sinal==0)SinalY = 0;

	return ( leitura_sem_sinal);  // retorna de 0 a 14400  
}


unsigned int HDByteRead_FILTRO(unsigned char *rdptr){
  CS = 0;       
  WriteSPI(0x38);		 //hi               
  WriteSPI(0);        //low   
  CS = 1; 

  Delay10TCYx(1);//
  CS = 0; 
  getsSPI( rdptr,2);   //vai ler 2 endereços        
  CS = 1;                       
//valorx[0]== byte hi
//valorx[1]== byte low

  leitura_sem_sinal=(((unsigned int)valorx[0] << 8) + (unsigned int)valorx[1]);
  leitura_sem_sinal = (leitura_sem_sinal & 0b0000000000001111);
   

  return ( leitura_sem_sinal );                
}
void HDByteWrite_FILTRO(void){
	unsigned char fil;
  CS = 0;       
  WriteSPI(0xB8);		 //hi               
//  WriteSPI(0x06);        //low   o valor do filtro pode ser de 0 a 8!!
  //fil = 8;//(unsigned char)rampa;

	fil = 8;//(unsigned char)rampa;
	WriteSPI(fil);
  CS = 1; 

  Delay10TCYx(1);//
}


void InitPIC(void)
//here is the SPI setup
{
	DDRAbits.RA5 = 0;       //Define CS as Output
	DDRCbits.RC3 = 0;       //Define SCK as Output
	DDRCbits.RC4 = 1;       //Define SDI as Input
	DDRCbits.RC5 = 0;       //Define SDO as Output

	TRISAbits.TRISA0 = 0;
	PORTAbits.RA0 = 1;//RESET
	TRISBbits.TRISB4 = 0;
	PORTBbits.RB4 = 0;

//configuração para o ADIS16209

	SSPSTAT = 0b00000000;
	SSPCON1 = 0b00000000;
	
	SSPSTATbits.SMP = 0;//recepção na borda no meio do perído
	SSPSTATbits.CKE = 0;//pulso de clock no começo do período

	SSPCON1bits.CKP =1;//clock normalmente em nível alto
	SSPCON1bits.SSPEN = 1;//habilita spi
		
/*
	SSPCON1bits.SSPM1 = 1;//Master e fosc/64 era 1
*/
//SSPCON1bits.SSPM0 = 1;
SSPCON1bits.SSPM1 = 1;


}
	void ConfigFiltroAdis16209(void){
		inclinacao = HDByteRead_INCLINACAO(&valorx);
 		HDByteWrite_FILTRO();
		Delay10KTCYx(250);
	}
