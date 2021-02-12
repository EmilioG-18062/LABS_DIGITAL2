/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 3 - DIGITAL 2
 */

#include <xc.h>
#include "interrupt_manager.h"

void INTERRUPT_MANAGER_Initialize (void){
    INTCON  = 0b11101000; // Enable Global Interrupt
    PIR1    = 0b01000000;
    PIE1    = 0b01000000;
    
    //Interrupciones On-Change
    IOCB    = 0b00000011; //Enciendo las Interrupciones On-Change del pin 0/1
}