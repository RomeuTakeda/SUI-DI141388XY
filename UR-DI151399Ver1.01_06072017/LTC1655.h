/**********************************************************************
*    Filename: LTC1452.h                                               *
*    Date: 06/07/1999                                                 *
*                                                                     *
*    Definições para comunicação com o DAC714                         *
*                                                                     *
*    Authors: Michelle Souza Nery e Thiago Turchetti Maia             *
*    Company: Di-Elétrons Eletrônica Industrial Ltda                  *
**********************************************************************/



#define	TA0PIN1		TRISDbits.TRISD5
#define	A0PIN1	PORTDbits.RD5	// pino 17 PIC para pino 3 do DAC

#define	TA0PIN2		TRISEbits.TRISE0
#define	A0PIN2	PORTEbits.RE0	// pino 17 PIC para pino 3 do DAC


#define	TCLKPIN		TRISDbits.TRISD6
#define	CLKPIN	PORTDbits.RD6	// pino 14 PIC para pino 1 do DAC

#define	DATAPIN	PORTDbits.RD7	// pino 16 PIC para pino 2 do DAC
#define	TDATAPIN	TRISDbits.TRISD7




//invertido
#define HI	0
#define LOW	1

extern void dacSend1 (unsigned int value);
extern void dacSend2 (unsigned int value);
extern void LTC1655Init (void);
