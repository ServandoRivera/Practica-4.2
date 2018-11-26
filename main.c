#include <xc.h>
#include "configuracion.h"
#define _XTAL_FREQ 32000000


void __interrupt() isr (void){
    char foco1;
    char foco2;
    
     foco1=RC1REG; // leer el dato recibido
     foco2=RC1REG;
     
    if(foco1==65)
        LATB0=1;
    if (foco1==80)
        LATB0=0;
    PIR3bits.RCIF=0;
    if (foco2==66)
        LATB1=1;
    if(foco2==76)
            LATB1=0;
    PIR3bits.RCIF=0;
    
}

void main(void) {


    //oscilador 
    OSCFRQbits.HFFRQ=0b110;
    //puertos
    PORTB=0;
    TRISB=0;
    ANSELB=0;
    PORTC=0;
    ANSELC=0;
    TRISC=0b10000000;
    //PPS
    RXPPS=0x17;//RX--->RC7
    
 
    
    //PUERTO SERIE
    RC1STAbits.SPEN=1; //habilita puerto serie
    TX1STAbits.BRGH=0; //low speed
    TX1STAbits.SYNC=0; //asincrono
    RC1STAbits.CREN=1; //recepcion continua
    TX1STAbits.TXEN=1;// trasmision
 
    //BAUD RATE
    BAUD1CONbits.BRG16=0; //timer USART 8 bits
    SPBRG=51; //9600 BAUDS
    //INTERRUPCION
    PIR3bits.RCIF=0;
    PIE3bits.RCIE=1;
    INTCONbits.PEIE=1; //
    INTCONbits.GIE=1; //int global
    //converidor analogico digital
   
    //ciclo infinito
    while(1);
    
    return;
}
