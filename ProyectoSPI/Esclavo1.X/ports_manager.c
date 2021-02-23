/*//////////////////////////////////////////////////////////////////////////////
 * File:   ports_manager.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Esclavo 1
 */

#include "ports_manager.h"    

void PORTS_MANAGER_Initialize(void) {
    
    ANSEL   = 0; //Todos los pines A de I/O se configuran como digitales
    TRISAbits.TRISA0 = 0; //Configuro el PORTA como salida
    PORTA   = 0; //Inicio el PORTA con todos en 0

    ANSELH  = 0; //Todos los pines B de I/O se configuran como digitales
    TRISB   = 0b00000011; ////Configuro el PORTB como salida excepto pin 0/1
    PORTB   = 0; //Inicio el PORTB con todos en 0
    IOCB    = 0b00000011; //Enciendo las Interrupciones On-Change del pin 0/1

    TRISD   = 0; ////Configuro el PORTD como salida
    PORTD   = 0; //Inicio el PORTB con todos en 0

    TRISE   = 0; ////Configuro el PORTE como salida
    PORTE   = 0; //Inicio el PORTB con todos en 0 
    
}
