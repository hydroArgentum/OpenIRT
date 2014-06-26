/**********************************************************************
MSP430 OpenIRT protocol.
-----------------------------------------------------------------------
Contributors: Daniel Baek
-----------------------------------------------------------------------
An Open Source Communication Protocol for sending information via
infrared light.

For now, only ASCII characters can be sent and received.
**********************************************************************/

#include <msp430g2452.h>

/*Function prototyping*/
void setup();
char set_input(unsigned char pin);
char set_output(unsigned char pin);
char send();
char recieve();

/*Hopefully, no one is stupid enough to modify these global variables.
After considering the constraints that I'm working with, it's probably
better that these variables are treated globally.*/
static char input_pin = 14;
static char output_pin = 14;

void setup(){

    /*Force 1MHz DCO.*/
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    /*Count limit is 1, because we want to poll at a frequency of
    1MHz.*/
    TA0CCR0 = 1;

    /*Enable counter interrupt.*/
    TA0CCTL0 = 0x10;

    /*Timer runs on DCO which runs at 1MHz.
    Timer resets after reaching compare value.*/
    TA0CTL = TASSEL_2 + MC_1;

    /*Global interrupt enable.*/
    _BIS_SR(GIE);

}

char set_input(unsigned char pin){

    /*This function exists to make sure that we have the correct pin
    when looking for input.
    The function returns a zero when successful, and returns a one to
    indicate an error.*/

    input_pin = pin;

    /*Pins are represented sequentially with P1.0 represented as 0 and
    P2.5 represented as 13.*/

    switch (pin){

        case 0:
            P1DIR &= ~BIT0;
            P1REN |= BIT0;
            return 0;

        case 1:
            P1DIR &= ~BIT1;
            P1REN |= BIT1;
            return 0;

        case 2:
            P1DIR &= ~BIT2;
            P1REN |= BIT2;
            return 0;

        case 3:
            P1DIR &= ~BIT3;
            P1REN |= BIT3;
            return 0;

        case 4:
            P1DIR &= ~BIT4;
            P1REN |= BIT4;
            return 0;

        case 5:
            P1DIR &= ~BIT5;
            P1REN |= BIT5;
            return 0;

        case 6:
            P1DIR &= ~BIT6;
            P1REN |= BIT6;
            return 0;

        case 7:
            P1DIR &= ~BIT7;
            P1REN |= BIT7;
            return 0;

        case 8:
            P2DIR &= ~BIT0;
            P2REN |= BIT0;
            return 0;

        case 9:
            P2DIR &= ~BIT1;
            P2REN |= BIT1;
            return 0;

        case 10:
            P2DIR &= ~BIT2;
            P2REN |= BIT2;
            return 0;

        case 11:
            P2DIR &= ~BIT3;
            P2REN |= BIT3;
            return 0;

        case 12:
            P2DIR &= ~BIT4;
            P2REN |= BIT4;
            return 0;

        case 13:
            P2DIR &= ~BIT5;
            P2REN |= BIT5;
            return 0;

        default:
            return 1;

    }
}

char set_output(unsigned char pin){

    /*This function exists to make sure that we have the correct pin
    when looking for output.
    The function returns a zero when successful, and returns a one to
    indicate an error.*/

    output_pin = pin;

    /*Pins are represented sequentially with P1.0 represented as 0 and
    P2.5 represented as 13.*/

    switch (pin){

        case 0:
            P1DIR |= BIT0;
            return 0;

        case 1:
            P1DIR |= BIT1;
            return 0;

        case 2:
            P1DIR |= BIT2;
            return 0;

        case 3:
            P1DIR |= BIT3;
            return 0;

        case 4:
            P1DIR |= BIT4;
            return 0;

        case 5:
            P1DIR |= BIT5;
            return 0;

        case 6:
            P1DIR |= BIT6;
            return 0;

        case 7:
            P1DIR |= BIT7;
            return 0;

        case 8:
            P2DIR |= BIT0;
            return 0;

        case 9:
            P2DIR |= BIT1;
            return 0;

        case 10:
            P2DIR |= BIT2;
            return 0;

        case 11:
            P2DIR |= BIT3;
            return 0;

        case 12:
            P2DIR |= BIT4;
            return 0;

        case 13:
            P2DIR |= BIT5;
            return 0;

        default:
            return 1;

    }
}
