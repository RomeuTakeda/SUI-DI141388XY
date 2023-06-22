
#include <p18f4620.h>
#include "main.h"
#include "keyboard.h"
#include "keys.h"
#include "hcms297x.h"
#include "Network.h"
#define bit unsigned


char flagenter=0;
char ab=0, mult_cont;
char menu_flag=0, menu_dec=0, menu_inc=0;
char i;
char aux55;
unsigned char Pos = 0;


void PresetInFuncao(void){

}

/*********************************************************************************************
TECLA 2x1 - MENU, 1
*********************************************************************************************/
void keyPress2x1 (void) {
	

//counter.decPoint++;
//if(counter.decPoint>4)counter.decPoint = 0;


	tecla=2;
	inc = 0;
	cont_time_out_menu=0;





	position++;
	if(position>=3)position = 0;
	


	if(modo==MODO_PROGRAMAR){
		switch (menu_aux.tag){
			case LIM1:
			case LIM2:
			case LIM3:
			case LIM4:
	//		case LIM1HIST:
	//		case LIM2HIST:
	//		case LIM3HIST:
	//		case LIM4HIST:
			case ESCALA0:
			case ESCALA1:
			case ESCALA0_2:
			case ESCALA1_2:
			case PRESET://Preset
			case PRESET2://Preset
			case CONSTMULT://k2 troca dígito a ser piscado
			case CONSTMULT2://k2 troca dígito a ser piscado
				if(Pos<5)Pos++;
				else Pos = 0;
			break;
			case LIM1HIST:
			case LIM2HIST:
			case LIM3HIST:
			case LIM4HIST:
				if(Pos<4)Pos++;
				else Pos = 0;
			break;
			case FILTRO:
			case FILTRO2:
				if(Pos<1)Pos++;
				else Pos = 0;
			break;
			case MEDIA:
				if(Pos<1)Pos++;
				else Pos = 0;
			break;
			case TALIM1:
			case TDLIM1:
			case TALIM2:
			case TDLIM2:
			case TALIM3:
			case TDLIM3:
			case TALIM4:
			case TDLIM4:
				if(Pos<2)Pos++;
				else Pos = 0;
			break;
		}
	}


	if (modo == MODO_PROGRAMAR)
	{
		incremento = 0;
		inc_dec();
	}





	menu_flag=1;
} 
void keyRelease2x1 (void){
	menu_flag=0;
	flagenter=0;
} 
void keyPeriodic2x1 (void) {
	cont_time_out_menu=0;
} 
void keyDelayedPeriodic2x1 (void) 
{

	if (!flagenter)
	{
		incremento = 0;
		inc = 0;

		if (modo == MODO_NORMAL)
		{
			tecla=0;
		
			senha_aux_var = 0;


		
			modo = MODO_SENHA; 
			
			position = 0;
			TextoBuffer[0] =  60;//C
			TextoBuffer[1] = 250;//o
			TextoBuffer[2] = 195;//d
			TextoBuffer[3] = 200;//e
			TextoBuffer[4] = 350;//:
			TextoBuffer[5] = 310;
			TextoBuffer[6] = 310;
			TextoBuffer[7] = 310;
			fetchcharDspic8dig( TextoBuffer[0],TextoBuffer[1],TextoBuffer[2],TextoBuffer[3],TextoBuffer[4],TextoBuffer[5],TextoBuffer[6],TextoBuffer[7]);

		

		}
		else if (modo == MODO_MENU)
		{
			modo = MODO_PROGRAMAR;
			position = 0;
			tecla=0;

			incremento = 0;
			if(menu_aux.tag==SENHA) 
				TextoBuffer[0] =  60;//C
				TextoBuffer[1] = 250;//o
				TextoBuffer[2] = 195;//d
				TextoBuffer[3] = 200;//e
				TextoBuffer[4] = 350;//:
				TextoBuffer[5] = 310;
				TextoBuffer[6] = 310;
				TextoBuffer[7] = 310;
				

			inc_dec();

		}
		else if (modo == MODO_PROGRAMAR){
			if ( (modo == MODO_PROGRAMAR)&&(menu_aux.tag!=SENHA) ){
				modo = MODO_GRAVAR;
				inc_dec();
			}
			else if ( (modo == MODO_PROGRAMAR)&&(menu_aux.tag==SENHA) ){
				if(controle_senha==0){
					modo = MODO_PROGRAMAR;
					controle_senha=1;
					senha_nova_var1 = buffer_senha_nova_var1;
					buffer_senha_nova_var1 = 0;


				}	
				else{
					senha_nova_var2 = buffer_senha_nova_var2;
					buffer_senha_nova_var2 = 0;
					if(senha_nova_var1==senha_nova_var2){
						
						modo = MODO_MENU;
						senha_var = senha_nova_var1;
						position = 0;

						sendToEEPROM(55,(char*)&senha_var,4);		
		

					}
					else {
						modo = MODO_PROGRAMAR;
						
					}

					controle_senha=0;
					
				}
			
				position = 0;
				inc_dec();
				

			}
		}
		else if (modo == MODO_GRAVAR)
		{
			modo = MODO_MENU;
			TextoBuffer[0] = 310;//' '
			TextoBuffer[1] = 310;
			TextoBuffer[2] = 310;
			TextoBuffer[3] = 310;
			TextoBuffer[4] = 310;
			TextoBuffer[5] = 310;
			TextoBuffer[6] = 310;
			TextoBuffer[7] = 310;
			inc_dec();
		}
		else if (modo == MODO_SENHA){

			if(senha_aux_var==senha_var){
				modo = MODO_MENU;
				TextoBuffer[0] = 310;//' '
				TextoBuffer[1] = 310;
				TextoBuffer[2] = 310;
				TextoBuffer[3] = 310;
				TextoBuffer[4] = 310;
				TextoBuffer[5] = 310;
				TextoBuffer[6] = 310;
				TextoBuffer[7] = 310;
			
				position = 0;
				incremento = 0;
				inc_dec();
			}
			else{
				
				modo = MODO_NORMAL;
				VarTroca = 0;
				position = 0;

			}

		}

		if (modo != MODO_GRAVAR) flagenter=1;
	}

}

/*********************************************************************************************
TECLA 2x2 - DEC, 2
*********************************************************************************************/
void keyPress2x2 (void){

	if(modo==MODO_NORMAL){
		VarTroca++;
		if(VarTroca>=2)VarTroca = 0;
	}

	tecla=1;
	cont_time_out_menu=0;

	incremento = -1;
	inc = -1;


	if(modo==MODO_PROGRAMAR){
		switch (menu_aux.tag){
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
			case PRESET://Pd preset
			case PRESET2://Preset
			case PONTODEC://Pd  altera ponto decimal
			case CONSTMULT://k1  altera ponto decimal
			case CONSTMULT2:
				if(tempValue.decPoint<4)tempValue.decPoint++;
				else tempValue.decPoint = 0;
			break;
		}
	}

	if (menu_flag && (modo == MODO_PROGRAMAR)) {
		menu_dec=1;




		keyboardDelayedPeriodic=0;
	}


	inc_dec();
}
void keyRelease2x2 (void){
	ab=0;
	mult_cont=0;
	menu_dec=0;
}
void keyPeriodic2x2 (void){
	cont_time_out_menu=0;
	if (modo == MODO_PROGRAMAR && ab) inc_dec();
}
void keyDelayedPeriodic2x2(void){
	mult_cont++;
	if (mult_cont == 50){
		mult_cont=0;

		if (inc > -100) inc*=10;
	}
	if (modo == MODO_PROGRAMAR)	ab=1;

    if (modo == MODO_NORMAL)
	{
	    TECLA = 1;
	}
}

/*********************************************************************************************
TECLA 2x3 - INC, 3
*********************************************************************************************/
void keyPress2x3 (void){



			
//----------------------------
	tecla=3;
	cont_time_out_menu=0;
	incremento = 1;
	inc = 1;

	if (menu_flag && (modo == MODO_PROGRAMAR)) {
		menu_inc=1;
		keyboardDelayedPeriodic=0;
	}


	if(modo==MODO_PROGRAMAR){
		switch (menu_aux.tag){
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
			case FILTRO:
			case FILTRO2:
			case PRESET://Preset
			case PRESET2://Preset
			case MEDIA:
			case TALIM1:
			case TDLIM1:
			case TALIM2:
			case TDLIM2:
			case TALIM3:
			case TDLIM3:
			case TALIM4:
			case TDLIM4:

			case CONSTMULT://k1  incrementa o dígito
			case CONSTMULT2:
				incDigit2(Pos);		
			break;
		}
	}

//---------	

	if(modo==MODO_NORMAL){
	
		if(ContDelayPreset<TEMPO_PRESET){//segunda pressionada
			if(Hold1X==ON){
				if(!FlagLim1Out){
					ContPiscadaDisplay = 0;	//TEMPO_PISCA_DISPLAY
					ContDelayPreset = TEMPO_PRESET;//desabilita a espera de nova pressionada da tecla
					LIM1_OUT = 0;
				}
			}

			if(Hold2X==ON){
				if(!FlagLim2Out){
					ContPiscadaDisplay = 0;	//TEMPO_PISCA_DISPLAY
					ContDelayPreset = TEMPO_PRESET;//desabilita a espera de nova pressionada da tecla
					LIM2_OUT = 0;
				}
			}
			if(Hold3Y==ON){
				if(!FlagLim3Out){
					ContPiscadaDisplay = 0;	//TEMPO_PISCA_DISPLAY
					ContDelayPreset = TEMPO_PRESET;//desabilita a espera de nova pressionada da tecla
					LIM3_OUT = 0;
				}
			}
			if(Hold4Y==ON){
				if(!FlagLim4Out){
					ContPiscadaDisplay = 0;	//TEMPO_PISCA_DISPLAY
					ContDelayPreset = TEMPO_PRESET;//desabilita a espera de nova pressionada da tecla
					LIM4_OUT = 0;
				}
			}
		}
		else{//primeira pressionada
			ContDelayPreset = 0;
		}	
	}
	inc_dec();
} 
void keyRelease2x3 (void){
	ab=0;
	mult_cont=0;
	menu_inc=0;
//	if(mostra_var ==2) mostra_var = 0;
}
void keyPeriodic2x3 (void){
	cont_time_out_menu=0;
	if (modo == MODO_PROGRAMAR && ab) inc_dec();
}
void keyDelayedPeriodic2x3(void){
	mult_cont++;
	if (mult_cont == 50){
		mult_cont=0;

		if (inc < 100) inc=inc*10;
	}
	if (modo == MODO_PROGRAMAR)	ab=1;

	    if (modo == MODO_NORMAL)
		{
			TECLA = 1;

	}
}

void incDigit2 (char position) {
	char i;
	long fator;
	static bit si;

	if(position<5){
		fator = 10000;
		for (i = 0; i < position; i++) fator *= 10;
		for (i = 0; i < tempValue.decPoint; i++) fator /= 10;
				
		if (tempValue.value < 0){
			si=1; 
			tempValue.value = -tempValue.value;
		}
		else si=0;
		
		tempValue.value += fator;
	
		if (((tempValue.value / fator) % 10) == 0) tempValue.value -= (fator * 10);	
		if(si)tempValue.value=-tempValue.value;
	}
	else tempValue.value = -tempValue.value;
}
