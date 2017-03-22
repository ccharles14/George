/*
 * Uart.c Georges
 *
 *  Created on: 2 mars 2017
 *      Author: c.charles.14
 */
#include "Georges.h"

void InitUART(void)
{
    P1SEL |= (BIT1 | BIT2);                 // P1.1 = RXD, P1.2=TXD
    P1SEL2 |= (BIT1 | BIT2);                // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2;                   // SMCLK
    UCA0CTL0 &= ~(UCPEN | UCPAR | UCMSB);
    UCA0CTL0 &= ~(UC7BIT | UCSPB | UCMODE1);
    UCA0CTL0 &= ~(UCMODE0 | UCSYNC);
    UCA0BR0 = 104;                          // 1MHz, 9600
    UCA0BR1 = 0;                            // 1MHz, 9600
    UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                        // Enable USCI_A0 RX interrupt
}

void TXdata( unsigned char c )
{
	while (!(IFG2&UCA0TXIFG));  // USCI_A0 TX buffer ready?
    UCA0TXBUF = c;              // TX -> RXed character
}

unsigned char BTdata(void){
	unsigned char a;
	while (!(IFG2&UCA0RXIFG));
	a = UCA0RXBUF;
	return a;
}
