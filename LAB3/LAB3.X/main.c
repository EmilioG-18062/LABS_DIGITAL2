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

/*//////////////////////////////////////////////////////////////////////////////
 * MACROS
 */

/*//////////////////////////////////////////////////////////////////////////////
 * VARIABLES
 */
int cont = 0;
uint8_t adc_value = 0;
uint8_t adc_channel_pointer = 0;
uint8_t i = 0;
uint16_t voltage_int = 0;

float voltage = 0.00;

char read_value;
char Buffer[20];
char Buffer1[20];

char Buffer2[20];

char digits1[3];
char digits2[3];
unsigned char contador=0;

/*//////////////////////////////////////////////////////////////////////////////
 * INTERRUPCIONES
 */
void __interrupt () myISR(void){
    
    //ADC Interrups
    if (PIR1bits.ADIF == HIGH && ADCON0bits.GO_nDONE == LOW){
        voltage = ADRESH;
        adc_channel_pointer++;
        ADC_FLAG_SetLow();
    }
    
    if(PIR1bits.RCIF == HIGH){
        read_value = RCREG;
        if(read_value == '+'){
            contador++;
        } 
        else if(read_value == '-'){
            contador--;
        }
    }
    
    if(PIR1bits.TXIF == HIGH){
        TXREG = Buffer2[cont];
        if (cont == 16){
            cont = 0;
        } 
        else{
            cont++;
        }
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
    LCDPutStr(" S1    S2    S3 ");
    
    while(HIGH){
        voltage_int = (uint16_t)(((voltage*500)/255));
        
        if (!adc_channel_pointer){
            for (i = 0; i < 3; i++)
            {
               digits1[i] = (char)(voltage_int % 10);
               voltage_int /= 10;
            }
            sprintf(Buffer, "%i.%i%iV", digits1[2],digits1[1],digits1[0]);
            LCDGoto(0,1);
            LCDPutStr(Buffer);
            
        }
        
        if (adc_channel_pointer){
            for (i = 0; i < 3; i++)
            {
               digits2[i] = (char)(voltage_int % 10);
               voltage_int /= 10;
            }     
            sprintf(Buffer, "%i.%i%iV", digits2[2],digits2[1],digits2[0]);
            LCDGoto(6,1);
            LCDPutStr(Buffer);
            
        }
        sprintf(Buffer1, "%3i", contador);
        LCDGoto(12,1);
        LCDPutStr(Buffer1);
        
        sprintf(Buffer2, "%i.%i%iV %i.%i%iV %iC\r\n",digits1[2],digits1[1],
                digits1[0],digits2[2],digits2[1],digits2[0],contador);

        if( !ADCON0bits.GO_nDONE ){
            ADCON0bits.CHS = adc_channel_pointer;
            if(adc_channel_pointer){
                adc_channel_pointer = 255;
            }
            __delay_us(25);
            GOnDONE_SetHigh();
        }
    }
}
/*//////////////////////////////////////////////////////////////////////////////
 * END OF THE PROGRAM
 */