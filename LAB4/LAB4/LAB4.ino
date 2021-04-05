// Electronica Digital - Laboratorio 4
//  Seccion 20
//  Emilio Gordillo, 18062

//Bibliotecas
#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/tm4c123gh6pm.h"
#include"driverlib/sysctl.h"
#include"driverlib/gpio.h"

int status;

int main(void) {
  //Establecer reloj del microcontrolador
  SysCtlClockSet(SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_5);
  //Habilitar periférico GPIO F
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  //Habilitar pines de salida y entrada
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
  //Configurar tipo de entrada
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

  while(true){
    //Lee el pin de entrada
    status = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
    //Si el botón está presionado enciende el LED y si no, lo apaga.
    if (status==0){
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 6);
    }else{
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
    }
  }
}
