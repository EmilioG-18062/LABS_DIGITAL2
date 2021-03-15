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
int cont;
int handshake; 

char sensor_value[6];
char read_value;


/*//////////////////////////////////////////////////////////////////////////////
 * INTERRUPCIONES
 */
void __interrupt() myISR(void){
    if(PIR1bits.RCIF == HIGH){
        //Guardo lo que envia el ESP32
        read_value = RCREG;
    }
    
    if(PIR1bits.TXIF == HIGH){
        //Envio los valores del acelerometro cada vez que se enciende la bandera
        //de la interrupcion
        TXREG = sensor_value[cont];
        if (cont == 5){
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
    //Inicio el PIC
    SYSTEM_Initialize();
    //Configuro el clock interno en 8MHz
    OSCCONbits.IRCF = 0b111;
    
    while(1){
        
        //Reviso los valores enviados del ESP32 para cambiar el estado de las 
        //leds
        if(read_value == 1){
            PORTDbits.RD0 = 1;
        } 
        else if(read_value == 2){
            PORTDbits.RD0 = 0;
        }
        else if(read_value == 3){
            PORTDbits.RD1 = 1;
        }
        else if(read_value == 4){
            PORTDbits.RD1 = 0;
        }
        
        //Obtengos los valores del acelerometro y los guardo en un array
        sensor_value[0] = adxl345_read(0x32); //Read X axis(LSB)
        sensor_value[1] = adxl345_read(0x33); //Read X axis(MSB)
        
        sensor_value[2] = adxl345_read(0x34); //Read Y axis(LSB)
        sensor_value[3] = adxl345_read(0x35); //Read Y axis(MSB)
        
        sensor_value[4] = adxl345_read(0x36); //Read Z axis(LSB)
        sensor_value[5] = adxl345_read(0x37); //Read Z axis(MSB)
 
    }   
}

