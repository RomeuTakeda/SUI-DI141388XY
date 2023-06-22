/**********************************************************************
*    Filename: keys.h                                                 *
*    Date: 10/09/1999                                                 *
*                                                                     *
*    Declarações das implementações das funções do teclado 4x4        *
*                                                                     *
*    Authors: Michelle Souza Nery e Thiago Turchetti Maia             *
*    Company: Di-Elétrons Eletrônica Industrial Ltda                  *
**********************************************************************/

#define COUNT_5S 192
extern char menu_dec;
extern char menu_inc;
extern char flagenter;

extern void incDigit2 (char position);
// tecla 2x1
extern void keyPress2x1 (void);

extern void PresetInFuncao(void);
extern void keyRelease2x1 (void);
extern void keyPeriodic2x1 (void);
extern void keyDelayedPeriodic2x1 (void);
 
// tecla 2x2
extern void keyPress2x2 (void);
extern void keyRelease2x2 (void);
extern void keyPeriodic2x2 (void);
extern void keyDelayedPeriodic2x2 (void);

// tecla 2x3
extern void keyPress2x3 (void);
extern void keyRelease2x3 (void);
extern void keyPeriodic2x3 (void);
extern void keyDelayedPeriodic2x3 (void);

extern unsigned char Pos;

extern unsigned  TECLA;

/*
// tecla 3x0
extern void keyPress3x0 (void);
extern void keyRelease3x0 (void);
extern void keyPeriodic3x0 (void);
extern void keyDelayedPeriodic3x0 (void);

// tecla 3x1
extern void keyPress3x1 (void);
extern void keyRelease3x1 (void);
extern void keyPeriodic3x1 (void);
extern void keyDelayedPeriodic3x1 (void);

// tecla 3x2
extern void keyPress3x2 (void);
extern void keyRelease3x2 (void);
extern void keyPeriodic3x2 (void);
extern void keyDelayedPeriodic3x2 (void);

// tecla 3x3
extern void keyPress3x3 (void);
extern void keyRelease3x3 (void);
extern void keyPeriodic3x3 (void);
extern void keyDelayedPeriodic3x3 (void);

 
*/
