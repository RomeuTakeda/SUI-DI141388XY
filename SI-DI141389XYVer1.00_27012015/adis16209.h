



#define RESET_ADIS	PORTAbits.RA0
#define TRESET_ADIS	TRISAbits.TRISA0
#define CS PORTAbits.RA5    // CS for SPI
extern void Adis16209Read(unsigned char addr,unsigned char *rdptr);
extern void InitPIC(void);
extern void HDByteWrite_FILTRO(void);
extern unsigned int HDByteRead_TEMP(unsigned char *rdptr);
extern unsigned int HDByteRead_INCLINACAO(unsigned char *rdptr);
extern unsigned int HDByteRead_INCLINACAO_X(unsigned char *rdptr);
extern unsigned int HDByteRead_INCLINACAO_Y(unsigned char *rdptr);
extern unsigned int HDByteRead_FONTE(unsigned char *rdptr);
extern unsigned int HDByteRead_FILTRO(unsigned char *rdptr);
extern void ConfigFiltroAdis16209(void);
