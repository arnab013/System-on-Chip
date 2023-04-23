/*
 * gpio_control.h
 *
 *  Created on: Mar 2, 2023
 *      Author: ASUS
 */

#ifndef SRC_GPIO_CONTROL_H_
#define SRC_GPIO_CONTROL_H_

#include "xgpio.h"
#include "xil_types.h"
#include "xparameters.h"
#include "sleep.h"
#include "xscugic.h"
#include "xil_exception.h"


//variables

XGpio_Config *cfg_ptr; // contain GPIO configuration 1
XGpio_Config *cfg_ptr2; // contain GPIO configuration 2
XGpio leds; // LEDs
XGpio pushbtn; //buttons
XGpio switches; // switches
u8 switch_status;
u8 i;
XScuGic interup_controller;
XScuGic_Config *Interup_Config_ptr; // contain Interrupt configuration

// function prototype to configure AXI GPIO
void init_axi_gpio();
// function prototype to toggle LEDs
void toggle_leds();
// function prototype to configure interrupt controller
void inter_setup();
// function prototype for the interrupt routine
void inter_handler();


#endif /* SRC_GPIO_CONTROL_H_ */
