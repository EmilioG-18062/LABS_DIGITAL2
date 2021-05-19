#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//======================== Variables ========================
uint8_t temp = 0;
uint8_t Color_LED = 0;
uint8_t UART_Previous = 0;
uint8_t UART_Received = 1;

/*
 * Prototipo de Funciones
 */
void TimerHandler1(void);
void UARTHandler(void);

//main.c
int main(void)
{
    //======================== Setup ========================
    //Colocamos el clock en 40Mhz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //Se activan  las interrupciones
    IntMasterEnable();

    //Se configura el modulo UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    UARTFIFOEnable(UART0_BASE);
    UARTIntEnable(UART0_BASE, UART_INT_RX|UART_INT_RT);
    UARTIntRegister(UART0_BASE, UARTHandler);
    UARTEnable(UART0_BASE);
    IntEnable(INT_UART0);

    //Se habilita el puerto F como salidas
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    //Se configura el TIMER0 en 32 Bits
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, ((SysCtlClockGet()/2)-1));
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);

    //======================== Loop ========================
    while(1){

    }
}


//======================== Funciones ========================
void TimerHandler1(void){
    TimerIntClear(TIMER0_BASE, TIMER_A);
    temp++;
    if (temp==1){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, Color_LED);
    }
    else if (temp==2){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        temp=0;
        }

}

void UARTHandler(void){
    UARTIntClear(UART0_BASE, UART_INT_RX|UART_INT_RT);
    UART_Received = UARTCharGet(UART0_BASE);
    if(UART_Received == UART_Previous){
        Color_LED=0;
        UART_Received=0;
    }
    else{
        if(UART_Received == 114){
            Color_LED=2;
        }
        else if(UART_Received == 103){
            Color_LED=8;
        }
        else if(UART_Received == 98){
            Color_LED=4;
        }
        UART_Previous = UART_Received;
    }

}
