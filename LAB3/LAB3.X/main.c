/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 3 - DIGITAL 2
 */

/*//////////////////////////////////////////////////////////////////////////////
 * LIBRERIAS
 */
#include "lcs.h"
#include <stdio.h>

/*//////////////////////////////////////////////////////////////////////////////
 * MACROS
 */

/*//////////////////////////////////////////////////////////////////////////////
 * VARIABLES
 */
uint8_t adc_value = 0;
uint8_t adc_count = 0;
uint8_t display_count = 0;

float voltage = 0.00;

char Buffer[20];

char display_array[16] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 
0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 
0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001};

/*//////////////////////////////////////////////////////////////////////////////
 * INTERRUPCIONES
 */
void __interrupt () myISR(void){
    
    //ADC Interrups
    if (PIR1bits.ADIF == HIGH && ADCON0bits.GO_nDONE == LOW){
        adc_value = ADRESH;
        voltage = (adc_value*5)/255;
        adc_count++;
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
    LCDGoto(1,0);
    LCDPutStr(" S1 ");
        
    LCDGoto(6,0);
    LCDPutStr(" S2 ");
        
    LCDGoto(11,0);
    LCDPutStr(" S3 ");
    
    while(HIGH){
        
        if (!adc_count){
            int i = (int)(voltage*100+ 0.5);
            sprintf(Buffer, "%i", i);
            LCDGoto(1,1);
            LCDPutStr(Buffer);
        }

        if( !ADCON0bits.GO_nDONE ){
            ADCON0bits.CHS = adc_count;
            if(adc_count){
                adc_count = 255;
            }
            __delay_us(25);
            GOnDONE_SetHigh();
        }
    }
}
/*//////////////////////////////////////////////////////////////////////////////
 * END OF THE PROGRAM
 */