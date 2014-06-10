#include <msp430g2452.h>

int setup();
int set_input(unsigned int pin);
int set_output(unsigned int pin);
char recieve();
char send();

int setup(){

    /*Make sure that we are using 1MHz.*/
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHz;
    
    /*Count limit is 1, because we want to poll at a frequency of 1MHz.*/
    TA0CCR0 = 1;
    
    /*Enable counter interrupt.*/
    TA0CCTL0 = 0x10;
    
    /*Timer runs on DCO which runs at 1MHz.
    Timer resets after reaching compare value.*/
    TA0CTL = TASSEL_2 + MC_1
    
    /*Global interrupt enable.*/
    _BIS_SR(GIE);

}
