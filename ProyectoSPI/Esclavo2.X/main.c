/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Esclavo 2
 */

/*//////////////////////////////////////////////////////////////////////////////
 * LIBRERIAS
 */
#include "lcs.h"

/*//////////////////////////////////////////////////////////////////////////////
 * MACROS
 */

/*//////////////////////////////////////////////////////////////////////////////
 * VARIABLES
 */
uint16_t temperature = 0;
float temperature_float = 0.00;


/*//////////////////////////////////////////////////////////////////////////////
 * INTERRUPCIONES
 */
void __interrupt () myISR(void){
    //ADC Interrups
    if (PIR1bits.ADIF == 1 && ADCON0bits.GO_nDONE == 0){
        temperature_float = ADRESH;
        __delay_us(35);
        ADC_FLAG_SetLow();
        GOnDONE_SetHigh();
    }
    
    if(PIR1bits.SSPIF){
        if(!SSPSTATbits.BF){
            PORTD = SSPBUF;
        }
        SSPBUF = temperature;
        PIR1bits.SSPIF = 0;
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
        temperature = (uint16_t)temperature_float*2;
  
        if(temperature > 36){
            PORTD = 4;
        }
        if((temperature < 36) && (temperature > 25)){
            PORTD = 2;
        }
        if(temperature < 25){
            PORTD = 1;
        }
            
    }
}
/*//////////////////////////////////////////////////////////////////////////////
 * END OF THE PROGRAM
 */


