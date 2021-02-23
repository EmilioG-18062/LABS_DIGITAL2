/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Esclavo 0
 */

/*//////////////////////////////////////////////////////////////////////////////
 * LIBRERIAS
 */
#include "lcs.h"
#include <xc.h>

/*//////////////////////////////////////////////////////////////////////////////
 * MACROS
 */

/*//////////////////////////////////////////////////////////////////////////////
 * VARIABLES
 */
uint16_t voltage_int = 0;
uint16_t i = 0;
uint8_t voltage1 = 0;

float voltage = 0.00;

char digits[3];

/*//////////////////////////////////////////////////////////////////////////////
 * INTERRUPCIONES
 */
void __interrupt () myISR(void){
    //ADC Interrups
    if (PIR1bits.ADIF == 1 && ADCON0bits.GO_nDONE == 0){
        voltage = ADRESH;
        __delay_us(25);
        GOnDONE_SetHigh();
        ADC_FLAG_SetLow();
    }
}

/*//////////////////////////////////////////////////////////////////////////////
 * PROTOTIPOS DE FUNCIONES
 */

/*//////////////////////////////////////////////////////////////////////////////
 * CICLO PRINCIPAL
 */
void main(void) {
    
    SYSTEM_Initialize();
    GOnDONE_SetHigh();
    
    while(HIGH){
        voltage_int = (uint16_t)(((voltage*500)/255));
        for (i = 0; i < 3; i++)
            {
               digits[i] = (char)(voltage_int % 10);
               voltage_int /= 10;
            }
        
        PORTD = SSPBUF;
        __delay_ms(10); 
    }
}
/*//////////////////////////////////////////////////////////////////////////////
 * END OF THE PROGRAM
 */


