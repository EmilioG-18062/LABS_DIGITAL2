/*//////////////////////////////////////////////////////////////////////////////
 * File:   adc.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Esclavo 0
 */


#include "adc.h"

void ADC_Initialize(void) {
    
    ADCON0 = 0b10000001; // - ADCS/CHS/GOnDONE/ADON - 
    ADCON1 = 0x00; // Selecciono la justificacion hacia la izquierda
    ADRESL = 0x00; // ADRESL 0; 
    ADRESH = 0x00; // ADRESH 0;
    PIR1bits.ADIF = 1;
    PIE1bits.ADIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    
    
}