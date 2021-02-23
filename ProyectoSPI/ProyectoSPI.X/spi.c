/*//////////////////////////////////////////////////////////////////////////////
 * File:   spi.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Maestro
 */

#include "spi.h"

void SPI_MANAGER_Initialize(void) {
    
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC5 = 0;
    SSPCON  = 0b00100000;
    SSPSTAT = 0;
}
    