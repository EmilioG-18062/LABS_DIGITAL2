#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"

int main(void)
{
    // Configuramos el Clock a 16Mhz
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    // Habilitamos el Puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    // Habilitamos los Pines 1, 2 y 3 del Puerto F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    //Se configura el boton 1 como weak pull up
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE , GPIO_PIN_4 );
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4, GPIO_STRENGTH_4MA , GPIO_PIN_TYPE_STD_WPU );

    while(1)
    {
        if ((GPIOPinRead (GPIO_PORTF_BASE,GPIO_PIN_4) & 0x16)==0) {
            //Anti  debounce
            while ((GPIOPinRead (GPIO_PORTF_BASE,GPIO_PIN_4) & 0x16)==0) { }

            // Turn on the LED Red
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x02);
            // Delay for a bit
            SysCtlDelay(20000000);
            // Turn on the LED Yellow
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0A);
            // Delay for a bit
            SysCtlDelay(20000000);
            // Turn on the LED Green
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);
            // Delay for a bit
            SysCtlDelay(20000000);
            // Turn off the LED
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
            // Delay for a bit
            SysCtlDelay(20000000);
        }
    }
}
