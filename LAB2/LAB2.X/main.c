/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 2 - DIGITAL 2
 */

/*//////////////////////////////////////////////////////////////////////////////
 * LIBRERIAS
 */
#include <xc.h>
#include <stdint.h>

/*//////////////////////////////////////////////////////////////////////////////
 * PIC16F887 Configuration Bit Settings
 */

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

/*//////////////////////////////////////////////////////////////////////////////
 * MACROS
 */
#define _XTAL_FREQ 8000000 //8MHz

/*//////////////////////////////////////////////////////////////////////////////
 * VARIABLES
 */
volatile uint8_t reference_count    = 0; 
volatile uint8_t display_count      = 0;
volatile uint8_t timer0_count       = 0;
volatile uint8_t second_display     = 0;
volatile uint8_t first_display     = 0;

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
void setup(void) {
    
    INTCON  = 0b11101000; // Enable Global Interrupt
    PIR1    = 0b01000000;
    PIE1    = 0b01000000;
    ADCON1  = 0;
    ADCON0  = 0b10000001;
    
    ADRESH  = 0; //Limpiar Registro del ADC
    ADRESL  = 0;
    
    OPTION_REG = 0b00000110;

    ANSEL   = 0b00000001; //Todos los pines A de I/O se configuran como digitales
    TRISA   = 0b00000001; //Configuro el PORTA como salida
    PORTA   = 0; //Inicio el PORTA con todos en 0


    ANSELH  = 0; //Todos los pines B de I/O se configuran como digitales
    TRISB   = 0b00000011; ////Configuro el PORTB como salida excepto pin 0/1
    PORTB   = 0; //Inicio el PORTB con todos en 0
    IOCB    = 0b00000011; //Enciendo las Interrupciones On-Change del pin 0/1

    TRISC   = 0; ////Configuro el PORTC como salida
    PORTC   = 0; //Inicio el PORTB con todos en 0

    TRISD   = 0; ////Configuro el PORTD como salida
    PORTD   = 0; //Inicio el PORTB con todos en 0

    TRISE   = 0; ////Configuro el PORTE como salida
    PORTE   = 0; //Inicio el PORTB con todos en 0 
}

/*//////////////////////////////////////////////////////////////////////////////
 * CICLO PRINCIPAL
 */
void main(void) {
    setup();
    __delay_us(25);
    ADCON0bits.GO_nDONE = 1;
    PORTEbits.RE0 = 1;
    TMR0 = 212;
    while(1){
        PORTC = reference_count;
        PORTD = display_array[display_count];
        if (reference_count < (second_display + first_display)){
            PORTEbits.RE2 = 1;
        }
        else{
           PORTEbits.RE2 = 0; 
        }
    }
}
