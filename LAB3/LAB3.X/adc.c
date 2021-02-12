/*//////////////////////////////////////////////////////////////////////////////
 * File:   adc.c
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 3 - DIGITAL 2
 */

#include "adc.h"

void ADC_Initialize(void) {
    
    ADCON0 = 0b10000001; // - ADCS/CHS/GOnDONE/ADON - 
    ADCON1 = 0x00; // Selecciono la justificacion hacia la izquierda
    ADRESL = 0x00; // ADRESL 0; 
    ADRESH = 0x00; // ADRESH 0; 
    
}