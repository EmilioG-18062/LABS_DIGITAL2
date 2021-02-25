/*//////////////////////////////////////////////////////////////////////////////
 * File:   main.c
 * Author: Emilio Gordillo 18062
 *
 * Proyecto SPI - DIGITAL 2
 * PIC Maestro
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
uint8_t i = 0;
uint8_t cont = 0;
uint8_t contador = 0;
uint8_t temperature = 0;
uint16_t voltage_int = 0;

float voltage = 0.00;
char digits[3];
char Buffer[20];

/*//////////////////////////////////////////////////////////////////////////////
 * INTERRUPCIONES
 */
void __interrupt() myISR(void){
    
    //Interrupcion del EUSART
    if(PIR1bits.TXIF == HIGH){
        TXREG = Buffer[cont];
        //El contador sirve como un "puntero" para saber que posicion
        //del buffer mandar
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
    
    LCDGoto(0,0); //Seleccion el curso a su posicion inicial
    LCDPutStr(" S1    S2    S3 "); //Escribo el encabezado en el display
    
    while(HIGH){
        
        //Escribo y leo información del PIC Esclavo 0
        PORTCbits.RC0 = 0;
        SSPBUF = 1;
        if(!SSPSTATbits.BF){
            voltage = SSPBUF;
        }
        __delay_ms(1);
        PORTCbits.RC0 = 1;
        
        //Escribo y leo información del PIC Esclavo 1
        PORTCbits.RC1 = 0;
        SSPBUF = 1;
        if(!SSPSTATbits.BF){
            contador = SSPBUF;
        }
        __delay_ms(1);
        PORTCbits.RC1 = 1;
        
        //Escribo y leo información del PIC Esclavo 2
        PORTCbits.RC2 = 0;
        SSPBUF = 1;
        if(!SSPSTATbits.BF){
            temperature = SSPBUF;
        }
        __delay_ms(1);
        PORTCbits.RC2 = 1;
        
        //Convierto el valor en bruto del ADC en voltage 
        voltage_int = (uint16_t)(((voltage*500)/255));
        
        //Separo los valores del voltage en digitos
        for (i=0; i!=3; i++)
        {
           digits[i] = (char)(voltage_int % 10);
           voltage_int /= 10;
        }
        
        //Convierto todos los datos recibidos en una sola cadena string
        sprintf(Buffer, "%i.%i%iV %3iC %3iT\r\n", digits[2],digits[1],digits[0],
                contador,temperature);
        
        //Mueve el cursor de la LCD a una fila abajo y envio los datos
        LCDGoto(0,1);
        LCDPutStr(Buffer);
    
    }
}
/*//////////////////////////////////////////////////////////////////////////////
 * END OF THE PROGRAM
 */
