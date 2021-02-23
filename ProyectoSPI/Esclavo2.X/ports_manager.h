/*//////////////////////////////////////////////////////////////////////////////
 * File:   ports_manager.h
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Esclavo 2
 */

#ifndef PORTS_MANAGER_H
#define	PORTS_MANAGER_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

//PORTA 0
#define Channel_RA0_SetLow()  do{   PORTAbits.RA0 = 0;  } while(0)
#define Channel_RA0_SetHigh() do{   PORTAbits.RA0 = 1;  } while(0)


void PORTS_MANAGER_Initialize(void);

#endif	/* PORTS_MANAGER_H */

