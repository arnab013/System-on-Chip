/*
 * timer_control.c
 *
 *  Created on: Mar 16, 2023
 *      Author: Arnab
 */


#include "timer_control.h"
#include "gpio_control.h"

void init_timer()
{
	// Initialize the timer
	XTmrCtr_Initialize(&TimerInstance, XPAR_TMRCTR_0_DEVICE_ID);
	//configures the timer controller according to the device ID

	XTmrCtr_SetHandler(&TimerInstance, TMR_Inter_Handler, &TimerInstance);
	//setting the interrupt handler function for the timer instance

	XTmrCtr_SetOptions(&TimerInstance, 0, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);
	//enables interrupt generation

	Timing_value= MAX_COUNT - (timing_interval * XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ) + 2;
	//TIMING_INTERVAL = (MAX_COUNT - TLRx + 2) x AXI_CLOCK_PERIOD
	// Configure the timer to generate an interrupt every 30 seconds
	XTmrCtr_SetResetValue(&TimerInstance, 0, Timing_value);
	//the value that the timer will count down from

	// initialize the interrupt controller
	Interup_Config_ptr = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);
	XScuGic_CfgInitialize(&interup_controller, Interup_Config_ptr, Interup_Config_ptr->CpuBaseAddress);

	// connect the interrupt controller to the interrupt-handling hardware
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler) XScuGic_InterruptHandler, &interup_controller);
	Xil_ExceptionEnable();

	// connect the timer to the interrupt controller
	XScuGic_Connect(&interup_controller, XPAR_FABRIC_AXI_TIMER_0_INTERRUPT_INTR, (Xil_ExceptionHandler)TMR_Inter_Handler, &TimerInstance);

	// enable the timer interrupt at the interrupt controller
	XScuGic_Enable(&interup_controller, XPAR_FABRIC_AXI_TIMER_0_INTERRUPT_INTR);

	XTmrCtr_Start(&TimerInstance, 0);
	//When the timer reaches 0, it will generate an interrupt

}



void TMR_Inter_Handler(void *CallbackRef)
{
	if(XTmrCtr_IsExpired(&TimerInstance, 0)){
	// If timer is expired do something
	XTmrCtr_Stop(&TimerInstance, 0);

	//xil_printf("Interrupt from timer\n\r");
	leds_sos();
	//timer_count += 1;
	//xil_printf("%d", timer_count, "\n\r");

    XTmrCtr_Reset(&TimerInstance, 0);
    // Reset the timer and start it again

    XTmrCtr_Start(&TimerInstance, 0);
    //When the timer reaches 0, it will generate an interrupt
	}
}


void leds_sos()
{

	int i=0;

	for(i=0;i<3;i++)
	{
		XGpio_DiscreteWrite(&leds, 1, 0b00001111);
		usleep(500000); // 500 ms
		XGpio_DiscreteWrite(&leds, 1, 0b00000000);
		usleep(500000); // 500 ms
	}

	for(i=0;i<3;i++)
	{
		XGpio_DiscreteWrite(&leds, 1, 0b00001111);
		usleep(1500000); // 500 ms
		XGpio_DiscreteWrite(&leds, 1, 0b00000000);
		usleep(500000); // 500 ms
	}

	for(i=0;i<3;i++)
	{
		XGpio_DiscreteWrite(&leds, 1, 0b00001111);
		usleep(500000); // 500 ms
		XGpio_DiscreteWrite(&leds, 1, 0b00000000);
		usleep(500000); // 500 ms
	}
}

