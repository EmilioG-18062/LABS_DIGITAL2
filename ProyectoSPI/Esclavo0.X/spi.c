/*//////////////////////////////////////////////////////////////////////////////
 * File:   spi.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Esclavo 0
 */

#include "spi.h"

void SPI_MANAGER_Initialize(void) {
    
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC5 = 0;
    TRISAbits.TRISA5 = 1;
    SSPCON  = 0b00100100; //Configuro el PIC como Esclavo y activo el pin SS
    SSPSTAT = 0;
    
    PIR1bits.SSPIF = 0;
    PIE1bits.SSPIE = 1;
}
    