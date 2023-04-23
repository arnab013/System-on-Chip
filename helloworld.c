/*

 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "gpio_control.h"

int main()
{
	xil_printf("initialization of the platform\n\r");
    init_platform();

    xil_printf("initialization and configuration of the AXI GPIO\n\r");
    //object that holds the configuration for the GPIO (based on the device ID)
    init_axi_gpio();

    //setup the interrupt for AXI GPIO 1
    //inter_setup();
    init_timer();



    xil_printf("Blink says the LED\n\r");

    while(1)
    {
    	// function call to toggle the LEDs
    	toggle_leds();
    }




    xil_printf("cleanup of the platform\n\r");
    cleanup_platform();
    return 0;
}
