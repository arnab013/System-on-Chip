/*
 * timer_control.h
 *
 *  Created on: Mar 16, 2023
 *      Author: ASUS
 */


#include "xtmrctr.h"
#include "gpio_control.h"

#define MAX_COUNT 0xFFFFFFFF    //for 32 bit timer
#define timing_interval 30 	//for 30 seconds

//XTmrCtr_Config *timer_Config_ptr;
XTmrCtr TimerInstance;

XScuGic interup_controller;
XScuGic_Config *Interup_Config_ptr; // contain Interrupt configuration

//XGpio axi_timer;
u32 Timing_value;



void init_timer();

void TMR_Inter_Handler(void *CallbackRef);

void leds_sos();
