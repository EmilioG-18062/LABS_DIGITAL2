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
int handshake = 0;
char sensor_value[9];

char read_value;

/*//////////////////////////////////////////////////////////////////////////////
 * INTERRUPCIONES
 */
void __interrupt() myISR(void){
    if(PIR1bits.RCIF == HIGH){
        read_value = RCREG;
    }
    
    if(PIR1bits.TXIF == HIGH){
        if (handshake == 0){
            TXREG = 65;
        }
        else{
            TXREG = sensor_value[cont];
            if (cont == 5){            
                cont = 0;
            } 
            else{
                cont++;
            }
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
    adxl345_init();
    OSCCONbits.IRCF = 0b111;
    
    while(1){
        
        if(read_value == 65){
            handshake = 1;
        }
        
        if(read_value == 66){
            handshake = 0;
        }
        
        sensor_value[0]=adxl345_read(0x32); //Read X axis(LSB)
        sensor_value[1]=adxl345_read(0x33); //Read X axis(MSB)
        
        sensor_value[2]=adxl345_read(0x34); //Read Y axis(LSB)
        sensor_value[3]=adxl345_read(0x35); //Read Y axis(MSB)
        
        sensor_value[4]=adxl345_read(0x36); //Read Z axis(LSB)
        sensor_value[5]=adxl345_read(0x37); //Read Z axis(MSB)
        
    }   
}

