/***************************************************************************
  MSP430 OpenIRT protocol.
  --------------------------------------------------------------------------
  @author: Daniel Baek
  --------------------------------------------------------------------------
  An Open Source Communication Protocol for sending information via infrared
  light.
 
  For now, only ASCII characters can be sent and received.
  *************************************************************************/
/* Kernel include. */
#include <msp430g2452.h>
/* Definitions. */
#define INVALID_PIN 14
#define IR_FREQUENCY_1kHz 0
#define IR_FREQUENCY_5kHz 1
#define IR_FREQUENCY_10kHz 2
#define IR_FREQUENCY_50kHz 3
#define IR_FREQUENCY_100kHz 4
#define IR_FREQUENCY_500kHz 5
#define IR_FREQUENCY_1MHz 6
/* Function prototyping. */
void setup();
char set_input(unsigned char pin);
char set_output(unsigned char pin);
char send(char ASCII);
char recieve();
/* Hopefully, no one is stupid enough to modify these global variables. After
considering the constraints that I'm working with, it's probably better that
these variables are globally defined. */
static char input_pin = INVALID_PIN;
static char output_pin = INVALID_PIN;
static char mode = 0;
void setup()
{
  /* Force 1MHz DCO. This library requires the DCO to be calibrated to 1MHz.*/
  BCSCTL1 = CALBC1_16MHZ;
  DCOCTL = CALDCO_16MHZ;
  /* Count limit is 1, because we want to poll at a frequency of 1MHz.*/
  TA0CCR0 = 1;
  /* Enable counter interrupt.*/
  TA0CCTL0 = 0x10;
  /* Timer runs on DCO which runs at 1MHz. Timer resets after reaching compare
  value.*/
  TA0CTL = TASSEL_2 + MC_1;
  /* Global interrupt enable.*/
  _BIS_SR(GIE);
}
char set_input(unsigned char pin){
  /*This function exists to make sure that we have the correct pin when looking
  for input. The function returns a zero when successful, and returns a one to
  indicate an error.*/
  input_pin = pin;
  /*Pins are represented sequentially with P1.0 represented as 0 and P2.5
  represented as 13.*/
switch (pin){
  case 0:
    P1DIR &= ~BIT0;
    return 0;
  case 1:
    P1DIR &= ~BIT1;
    return 0;
  case 2:
    P1DIR &= ~BIT2;
    return 0;
  case 3:
    P1DIR &= ~BIT3;
    return 0;
  case 4:
    P1DIR &= ~BIT4;
    return 0;
  case 5:
    P1DIR &= ~BIT5;
    return 0;
  case 6:
    P1DIR &= ~BIT6;
    return 0;
  case 7:
    P1DIR &= ~BIT7;
    return 0;
  case 8:
    P2DIR &= ~BIT0;
    return 0;
  case 9:
    P2DIR &= ~BIT1;
    return 0;
  case 10:
    P2DIR &= ~BIT2;
    return 0;
  case 11:
    P2DIR &= ~BIT3;
    return 0;
  case 12:
    P2DIR &= ~BIT4;
    return 0;
  case 13:
    P2DIR &= ~BIT5;
    return 0;
  default:
    return 1;
  }
}
char set_output(unsigned char pin)
{
  /* This function exists to make sure that we have the correct pin when
  looking for output.
  The function returns a zero when successful, and returns a one to indicate an
  error.*/
  output_pin = pin;
  /*Pins are represented sequentially with P1.0 represented as 0 and P2.5
  represented as 13.*/
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
char send(char ASCII)
{
}
