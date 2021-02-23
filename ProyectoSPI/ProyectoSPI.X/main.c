/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Maestro
 */

/*//////////////////////////////////////////////////////////////////////////////
 * LIBRERIAS
 */
#include "lcs.h"

/*//////////////////////////////////////////////////////////////////////////////
 * MACROS
 */

/*//////////////////////////////////////////////////////////////////////////////
 * VARIABLES
 */
uint8_t i = 0;
uint8_t contador = 0;
uint16_t voltage_int = 0;
float voltage = 0.00;
char digits[3];
char Buffer[20];
char Buffer1[20];

/*//////////////////////////////////////////////////////////////////////////////
 * INTERRUPCIONES
 */
void __interrupt() myISR(void){
}

/*//////////////////////////////////////////////////////////////////////////////
 * PROTOTIPOS DE FUNCIONES
 */


/*//////////////////////////////////////////////////////////////////////////////
 * CICLO PRINCIPAL
 */
void main(void) {
    SYSTEM_Initialize();
    
    LCDGoto(0,0);
    LCDPutStr(" S1    S2    S3 ");
    
    TRISCbits.TRISC0 = 0;
    PORTCbits.RC0 = 0;
    
    TRISCbits.TRISC1 = 0;
    PORTCbits.RC1 = 1;
    
    TRISCbits.TRISC2 = 0;
    PORTCbits.RC2 = 1;
    
    while(HIGH){
        
        PORTCbits.RC0 = 0;
        SSPBUF = 1;
        if(!SSPSTATbits.BF){
            voltage = SSPBUF;
        }
        __delay_ms(1);
        PORTCbits.RC0 = 1;
        
        PORTCbits.RC1 = 0;
        SSPBUF = 1;
        if(!SSPSTATbits.BF){
            contador = SSPBUF;
        }
        __delay_ms(1);
        PORTCbits.RC1 = 1;
        
        voltage_int = (uint16_t)(((voltage*500)/255));
        for (i = 0; i < 3; i++)
        {
           digits[i] = (char)(voltage_int % 10);
           voltage_int /= 10;
        }
        sprintf(Buffer, "%i.%i%iV", digits[2],digits[1],digits[0]);
        LCDGoto(0,1);
        LCDPutStr(Buffer);
        
        sprintf(Buffer1, "%3i", contador);
        LCDGoto(6,1);
        LCDPutStr(Buffer1);
        
    }
}
/*//////////////////////////////////////////////////////////////////////////////
 * END OF THE PROGRAM
 */
