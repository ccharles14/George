/*
 * File: Georges
 *
 * Description: Partie MPS 2553 du robot
 *
 * @version: 0
 */

#include <msp430g2553.h>
#include "Uart.h"
#include "SPI.h"
//#include "Mouvement.h"

void main(void) {

	WDTCTL = WDTPW | WDTHOLD;   // Stop WDT
    BCSCTL1 = CALBC1_1MHZ;      // Set DCO to 1Mhz
    DCOCTL = CALDCO_1MHZ;       // Set DCO to 1Mhz

   /* P1SEL &= ~BIT0;
    P1SEL2 &= ~BIT0;
    P1DIR |= BIT0;*/


    InitSPI();
    InitUART();


    __bis_SR_register(GIE); // interrupts enbled

    TXdata('>');
    while(1);
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    /*unsigned char c,b;

    c = UCA0RXBUF;

    b=SPIdata(c);

    TXdata(b);*/

	unsigned char d;

	d = BTdata();

	if (d == 'e')
		P1OUT |= BIT0;
	if (d == 'r')
		P1OUT &= ~BIT0;


}
