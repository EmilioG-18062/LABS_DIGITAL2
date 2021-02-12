/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 3 - DIGITAL 2
 */

#include <xc.h>
#include "timer_manager.h"

void TIMER_MANAGER_Initialize(void){
    OPTION_REG = 0b00000110; // Configuro el TMR0
    TMR0 = 212;
}