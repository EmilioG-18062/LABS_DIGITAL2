/*//////////////////////////////////////////////////////////////////////////////
 * File:   interrupt_manager.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Maestro
 */


#include "interrupt_manager.h"

void INTERRUPT_MANAGER_Initialize(void){
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE   = 1;
    PIE1bits.TXIE   = 1;
    PIE1bits.ADIE   = 1;
    PIR1bits.RCIF   = 0;
    INTCONbits.GIE  = 1;
}
