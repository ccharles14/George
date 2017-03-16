/*
 * File: George
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

    InitSPI();
    InitUART();


    __bis_SR_register(GIE); // interrupts enabled

    TXdata('>');
    while(1);
	
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    unsigned char c,b;

    c = UCA0RXBUF;

    b=SPIdata(c);

    TXdata(b);
}
