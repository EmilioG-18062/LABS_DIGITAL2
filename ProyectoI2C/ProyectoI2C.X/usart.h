/*//////////////////////////////////////////////////////////////////////////////
 * File:   usart.h
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 3 - DIGITAL 2
 */


#ifndef USART_H
#define	USART_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void USART_Initialize(const long int baudrate);

#endif	/* USART_H */

