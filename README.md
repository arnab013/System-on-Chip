# System-on-Chip

This is a code done in xlinix SDK for a PYNQ-Z2 board which was developed based on the ZYNQ architecture. In this code, first a regular routine function is implemented. The regular routine function is as follows: 

> If Switch0 is low i.e., ’0’ \
  • Pushing button 0, LED 0 turns on \
  • Pushing button 1, LED 1 turns on \
  • Pushing button 2, LED 2 turns on \
  • Pushing button 3, LED 3 turns on \
  
> Else if Switch0 is high i.e., ’1’ \
  • All LEDs are blinking with an interval of 500 ms \
  • Pushing the buttons has no effect on the LEDs when Switch0 is high \
  
Then we introduced interrupt in switch1 to have the following functionalities:

> If Switch1 is high, an interrupt is triggered \
  • The LEDs will flash an SOS signal using Morse Code \
    – ... — ... \
    – short, short, short, long, long, long, short, short, short \
    – Short pulse is 500 ms \
    – Long pulse is 1500 ms \
    
After that, we used the axi_timer0 to generate an interrupt every 30 seconds and perform the SOS blinking.

The main() function of this code is inside the helloworld.c file.
The other user defined functions can be found in gpio_control.c and gpio_control.h files. 
