/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * LABORATORIO 1 - DIGITAL 1
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
uint8_t game = 0;
uint8_t J1_Count = 1;
uint8_t J2_Count = 1;


/*//////////////////////////////////////////////////////////////////////////////
 * PROTOTIPOS DE FUNCIONES
 */

void setup(void){
    
    ANSEL = 0;  //Todos los pines A de I/O se configuran como digitales
    TRISA = 0b00000111; //Configuro el PORTA como salida excepto el pin 0/1/2
    PORTA = 0;  //Inicio el PORTA con todos en 0
    
    
    ANSELH = 0; //Todos los pines B de I/O se configuran como digitales
    TRISB = 0; ////Configuro el PORTB como salida
    PORTB = 0;  //Inicio el PORTB con todos en 0
    
    TRISC = 0; ////Configuro el PORTC como salida
    PORTC = 0;  //Inicio el PORTB con todos en 0
    
    TRISD = 0; ////Configuro el PORTD como salida
    PORTD = 0;  //Inicio el PORTB con todos en 0
    
    TRISE = 0; ////Configuro el PORTE como salida
    PORTE = 0;  //Inicio el PORTB con todos en 0
}

void semaforo(void){
    PORTEbits.RE0 = 1;
    __delay_ms(100);
    PORTEbits.RE0 = 0;
            
    PORTEbits.RE1 = 1;
    __delay_ms(100);
    PORTEbits.RE1 = 0;
            
    PORTEbits.RE2 = 1;
    game = 1;
}

void reset(void){
    J1_Count = 1;
    J2_Count = 1;
    PORTEbits.RE2 = 0;
    PORTBbits.RB0 = 0;
    PORTBbits.RB1 = 0;
    PORTC = 0;
    PORTD = 0;
}

/*//////////////////////////////////////////////////////////////////////////////
 * CICLO PRINCIPAL
 */

void main(void) { 
    setup();
    while(1){
        if (PORTAbits.RA2 == 0){
            reset();
            semaforo();
        }
        else{
            __delay_ms(50);  
        }
        while(game == 1){
            __delay_ms(50); 
            if (PORTAbits.RA0 == 0){
                if(J1_Count == 0){
                    PORTBbits.RB0 = 1;
                    game = 0;
                }
                PORTC = J1_Count;
                J1_Count = J1_Count*2;
            }
            else if (PORTAbits.RA1 == 0){
                if(J2_Count == 0){
                    PORTBbits.RB1 = 1;
                    game = 0;
                }
                PORTD = J2_Count;
                J2_Count = J2_Count*2;
                
            }
        }
    }
}