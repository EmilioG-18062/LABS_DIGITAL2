/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto I2C - DIGITAL 2
 * PIC Maestro
 */


/*//////////////////////////////////////////////////////////////////////////////
 * LIBRERIAS
 */
#include "lcs.h"

/*//////////////////////////////////////////////////////////////////////////////
 * VARIABLES
 */
int cont = 0;
int contador = 50;

char read_value;
char Buffer[20];
char Buffer2[20];

/*//////////////////////////////////////////////////////////////////////////////
 * INTERRUPCIONES
 */
void __interrupt() myISR(void){
    if(PIR1bits.RCIF == HIGH){
        read_value = RCREG;
    }
    
    if(PIR1bits.TXIF == HIGH){
        TXREG = cont;
        if (cont == 254){
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
    OSCCONbits.IRCF = 0b111;
    while(1){
        PORTD = read_value;
    }   
}

