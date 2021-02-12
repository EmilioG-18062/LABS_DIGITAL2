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
uint8_t i = 0;

uint16_t voltage_int = 0;

float voltage = 0.00;

char Buffer[20];
char digits[3];

/*//////////////////////////////////////////////////////////////////////////////
 * INTERRUPCIONES
 */
void __interrupt () myISR(void){
    
    //ADC Interrups
    if (PIR1bits.ADIF == HIGH && ADCON0bits.GO_nDONE == LOW){
        adc_value = ADRESH;
        voltage = adc_value;
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
    LCDGoto(0,0);
    LCDPutStr(" S1 ");
        
    LCDGoto(6,0);
    LCDPutStr(" S2 ");
        
    LCDGoto(11,0);
    LCDPutStr(" S3 ");
    
    while(HIGH){
        
        if (!adc_count){
            voltage_int = (uint16_t)(((voltage*500)/255));
            for (i = 0; i < 3; i++)
            {
               if (voltage_int == 0){
                   digits[i] = (char)(0);
               }
               digits[i] = (char)(voltage_int % 10);
               voltage_int /= 10;
            } 
            
            sprintf(Buffer, "%i.", digits[2]);
            LCDGoto(0,1);
            LCDPutStr(Buffer);
            
            sprintf(Buffer, "%i", digits[1]);
            LCDGoto(2,1);
            LCDPutStr(Buffer);
            
            sprintf(Buffer, "%iV", digits[0]);
            LCDGoto(3,1);
            LCDPutStr(Buffer);
            
        }
        
        if (adc_count){
            voltage_int = (uint16_t)(((voltage*500)/255));
            for (i = 0; i < 3; i++)
            {
               if (voltage_int == 0){
                   digits[i] = (char)(0);
               }
               digits[i] = (char)(voltage_int % 10);
               voltage_int /= 10;
            }  
            
            sprintf(Buffer, "%i.", digits[2]);
            LCDGoto(6,1);
            LCDPutStr(Buffer);
            
            sprintf(Buffer, "%i", digits[1]);
            LCDGoto(8,1);
            LCDPutStr(Buffer);
            
            sprintf(Buffer, "%iV", digits[0]);
            LCDGoto(9,1);
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