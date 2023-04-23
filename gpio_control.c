/*
 * gpio_control.c
 *
 *  Created on: Mar 2, 2023
 *      Author: ASUS
 */

#include "gpio_control.h"



void init_axi_gpio()
{
	//objects that holds the configuration for the GPIO (based on the device ID)
	cfg_ptr = XGpio_LookupConfig(XPAR_AXI_GPIO_0_DEVICE_ID);
	cfg_ptr2 = XGpio_LookupConfig(XPAR_AXI_GPIO_1_DEVICE_ID);

	// initialize the AXI GPIO 0 based on the configuration
	XGpio_CfgInitialize(&leds, cfg_ptr, cfg_ptr->BaseAddress);
	XGpio_CfgInitialize(&pushbtn,cfg_ptr, cfg_ptr->BaseAddress);
	// initialize the AXI GPIO 1 based on the configuration
	XGpio_CfgInitialize(&switches,cfg_ptr2, cfg_ptr2->BaseAddress);
	// set data direction
	// bit 0 --> output, bit 1 --> input
	// set the LEDs on input channel 1 as output (0)
	XGpio_SetDataDirection(&leds, 1, 0);
	// set the buttons on input channel 2 as input (1)
	XGpio_SetDataDirection(&pushbtn, 2, 1);
	//set switches on input channel 1 as input (1)
	XGpio_SetDataDirection(&switches, 1, 1);

}

/* Functiopn to toggle the LEDs*/
void toggle_leds()
{
	// GPIO read on switches
	switch_status=XGpio_DiscreteRead(&switches, 1);
	if (switch_status == 0b00000000 || switch_status==0b00000010){
		// When the buttons are checked (pressed) --> write value to LED
		XGpio_DiscreteWrite(&leds, 1, XGpio_DiscreteRead(&pushbtn, 2 ));
	    usleep(500); }
	else
	{
		// Else Blink the LEDs with 500ms interval
	    XGpio_DiscreteWrite(&leds, 1, 0b00001111);
	    usleep(500000); // 500 ms
	    XGpio_DiscreteWrite(&leds, 1, 0b00000000);
	    usleep(500000); // 500 ms
	    }

}

/**
 * Setup function for the interrupt
 */

 void inter_setup()

{

	    // initialize the interrupt controller
	    Interup_Config_ptr = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);
	    XScuGic_CfgInitialize(&interup_controller, Interup_Config_ptr, Interup_Config_ptr->CpuBaseAddress);

	    // enable the interrupt on the AXI GPIO 1
	    XGpio_InterruptEnable(&switches, XGPIO_IR_CH1_MASK);
	    XGpio_InterruptGlobalEnable(&switches);

	    // connect the interrupt controller to the interrupt-handling hardware
	    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler) XScuGic_InterruptHandler, &interup_controller);
	    Xil_ExceptionEnable();

	    // connect the AXI GPIO interrupt to the interrupt controller
	    XScuGic_Connect(&interup_controller, XPAR_FABRIC_AXI_GPIO_1_IP2INTC_IRPT_INTR, (Xil_ExceptionHandler) inter_handler, &switches);

	    // enable the AXI GPIO interrupt at the interrupt controller
	    XScuGic_Enable(&interup_controller, XPAR_FABRIC_AXI_GPIO_1_IP2INTC_IRPT_INTR);
}

 /**
  * Interrupt handler
  */

void inter_handler()

{
	    // Disable the AXI GPIO interrupts
		XGpio_InterruptDisable(&switches, XGPIO_IR_CH1_MASK);

		//sos signal generation when interrupt is triggered
		switch_status=XGpio_DiscreteRead(&switches, 1);

		if(switch_status == 0b00000010 || switch_status==0b00000011)
		{
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

		// clear the interrupt status
	    (void) XGpio_InterruptClear(&switches, XGPIO_IR_CH1_MASK);

	    //Re-enable the AXI GPIO interrupt line
	    XGpio_InterruptEnable(&switches, XGPIO_IR_CH1_MASK);


}


