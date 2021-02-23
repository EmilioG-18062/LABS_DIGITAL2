/*//////////////////////////////////////////////////////////////////////////////
 * File:   adc.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Esclavo 0
 */

#ifndef ADC_H
#define	ADC_H

#include <xc.h>
#include <stdint.h>
#include "device_config.h"


#define Set_ADC_Channel_AN0() do{ ADCON0bits.CHS = 0x00; } while(0)
#define Set_ADC_Channel_AN1() do{ ADCON0bits.CHS = 0x01; } while(0)

#define GOnDONE_SetHigh()     do{ ADCON0bits.GO_nDONE = 1; } while(0)
#define GOnDONE_SetLow()      do{ ADCON0bits.GO_nDONE = 0; } while(0)

#define ADC_FLAG_SetLow()     do{ PIR1bits.ADIF = 0; } while(0)
#define ADC_FLAG_SetHigh()    do{ PIR1bits.ADIF = 0; } while(0)

void ADC_Initialize(void);

#endif	/* ADC_H */

