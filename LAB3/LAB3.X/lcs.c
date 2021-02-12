/*//////////////////////////////////////////////////////////////////////////////
 * File:   lcs.c
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 3 - DIGITAL 2
 */

#include "lcs.h"

void SYSTEM_Initialize(void) {
    ADC_Initialize();
    PORTS_MANAGER_Initialize();
    INTERRUPT_MANAGER_Initialize();
    LCD_Initialize();
}
