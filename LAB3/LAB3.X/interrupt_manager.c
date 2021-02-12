/*//////////////////////////////////////////////////////////////////////////////
 * File:   interrupt_manager.h
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 3 - DIGITAL 2
 */


#include "interrupt_manager.h"

void INTERRUPT_MANAGER_Initialize(void){
    INTCON  = 0b11000000;
    PIE1    = 0b01000000;
    PIE1    = 0b01000000;
}
