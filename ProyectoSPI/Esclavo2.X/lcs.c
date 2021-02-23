/*//////////////////////////////////////////////////////////////////////////////
 * File:   lcs.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Esclavo 2
 */


#include "lcs.h"

void SYSTEM_Initialize(void) {
    PORTS_MANAGER_Initialize();
    ADC_Initialize();
    SPI_MANAGER_Initialize();
}
