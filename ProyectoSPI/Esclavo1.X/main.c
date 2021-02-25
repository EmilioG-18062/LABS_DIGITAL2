/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Esclavo 1
 */

/*//////////////////////////////////////////////////////////////////////////////
 * LIBRERIAS
 */
#include "lcs.h"
#include <xc.h>

/*//////////////////////////////////////////////////////////////////////////////
 * MACROS
 */

/*//////////////////////////////////////////////////////////////////////////////
 * VARIABLES
 */
uint8_t reference_count = 0;
uint8_t read_value;

/*//////////////////////////////////////////////////////////////////////////////
 * INTERRUPCIONES
 */
void __interrupt () myISR(void){
    //On-Change Interrupts
    if (INTCONbits.RBIE == 1 && INTCONbits.RBIF == 1){
        if (PORTBbits.RB0 == 0){
            reference_count++;
        }
        if (PORTBbits.RB1 == 0){
            reference_count--;
        }
        INTCONbits.RBIF=0;
    }
    
    //Interrupcion del SPI
    if(PIR1bits.SSPIF){
        if(!SSPSTATbits.BF){
            read_value = SSPBUF;
        }
        SSPBUF = reference_count;
        PIR1bits.SSPIF = 0;
    }
}

/*//////////////////////////////////////////////////////////////////////////////
 * PROTOTIPOS DE FUNCIONES
 */

/*//////////////////////////////////////////////////////////////////////////////
 * CICLO PRINCIPAL
 */
void main(void) {
    
    SYSTEM_Initialize();
    INTCON  = 0b11001000; // Enable Global Interrupt
    INTCONbits.RBIF = 1;
    
    while(HIGH){
        PORTD = reference_count;
    }
}
/*//////////////////////////////////////////////////////////////////////////////
 * END OF THE PROGRAM
 */


