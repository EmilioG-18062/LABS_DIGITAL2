/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 3 - DIGITAL 2
 */

#ifndef LC_H
#define	LC_H

#include <xc.h>
#include "device_config.h"
#include "pin_manager.h"
#include <stdint.h>
#include "adc.h"
#include "interrupt_manager.h"
#include "timer_manager.h"

void SYSTEM_Initialize(void);
void OSCILLATOR_Initialize(void);
void WDT_Initialize(void);

#endif	/* LC_H */

