/*//////////////////////////////////////////////////////////////////////////////
 * File:   interrupt_manager.h
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 3 - DIGITAL 2
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
