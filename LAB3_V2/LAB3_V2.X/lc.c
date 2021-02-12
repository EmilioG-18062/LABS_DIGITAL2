/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 3 - DIGITAL 2
 */

#include "lc.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    WDT_Initialize();
    ADC_Initialize();
    INTERRUPT_MANAGER_Initialize();
    TIMER_MANAGER_Initialize();
}

void OSCILLATOR_Initialize(void)
{
}

void WDT_Initialize(void)
{
}

