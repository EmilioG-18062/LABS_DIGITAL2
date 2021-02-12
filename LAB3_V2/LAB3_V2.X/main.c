/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 3 - DIGITAL 2
 */

/*//////////////////////////////////////////////////////////////////////////////
 * LIBRERIAS
 */
#include "lc.h"

/*//////////////////////////////////////////////////////////////////////////////
 * MACROS
 */

/*//////////////////////////////////////////////////////////////////////////////
 * VARIABLES
 */
volatile uint8_t reference_count; 
volatile uint8_t display_count;
volatile uint8_t timer0_count;
volatile uint8_t second_display;
volatile uint8_t first_display;

char display_array[16] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001};

/*//////////////////////////////////////////////////////////////////////////////
 * INTERRUPCIONES
 */
void __interrupt () myISR(void){
    //On-Change Interrupts
    if (INTCONbits.RBIE == 1 && INTCONbits.RBIF == 1){
        if (PORTBbits.RB0 == 0){
            reference_count++;
        }
        if (PORTBbits.RB1 == 0){
            reference_count--;
        }
        INTCONbits.RBIF=0;
    }
    //ADC Interrups
    if (PIR1bits.ADIF == 1 && ADCON0bits.GO_nDONE == 0){
        second_display = (ADRESH & 0xF0)>>4;
        first_display = (ADRESH & 0x0F);
        __delay_us(25);
        ADCON0bits.GO_nDONE = 1;
        PIR1bits.ADIF = 0;
    }
    
   //Timer0
    if (INTCONbits.T0IE == 1 && INTCONbits.T0IF == 1){
        PORTEbits.RE1 = PORTEbits.RE0;
        PORTEbits.RE0 = !PORTEbits.RE1;
        if (PORTEbits.RE0){
            display_count = first_display;
        }
        if (PORTEbits.RE1){
            display_count = second_display;
        }
        timer0_count = 0;
        INTCONbits.T0IF = 0;
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
    reference_count= 0;
    display_count = 0;
    timer0_count = 0;
    second_display = 0;
    first_display = 0;
    __delay_us(25);
    ADCON0bits.GO_nDONE = 1;
    PORTEbits.RE0 = 1;
    while(1){
        PORTC = reference_count;
        PORTD = display_array[display_count];
        if (reference_count < (second_display + (first_display << 4))){
            PORTEbits.RE2 = 1;
        }
        else{
           PORTEbits.RE2 = 0; 
        }
    }
}