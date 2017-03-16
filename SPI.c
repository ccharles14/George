/*
 * SPI.c Master
 *
 *  Created on: 2 mars 2017
 *      Author: c.charles.14
 */
#include <msp430g2553.h>

void InitSPI(void)
{
    UCB0CTL1 = UCSWRST;
    P1DIR |= BIT4; // CS output
    P1OUT |= BIT4; // CS high
    P1SEL |= BIT7 | BIT6 | BIT5;  // Enable SIMO + MOSI + SCLK
    P1SEL2 |= BIT7 | BIT6 | BIT5; // Enable SIMO + MOSI + SCLK
    UCB0CTL0 |= UCCKPH | UCMSB | UCMST | UCSYNC; // 3-pin, 8-bit SPI master
    UCB0CTL1 |= UCSSEL_2; // SMCLK
    UCB0CTL1 &= ~UCSWRST;
}

unsigned char SPIdata( unsigned char value )
{
	unsigned char reception;

	P1OUT &= ~BIT4; //CS select
	while(!(IFG2 & UCB0TXIFG)); //attente buffer
	UCB0TXBUF = value; // envoi de value
	while(!(IFG2 & UCB0RXIFG)); //receptionUSCI_A0 ?
	reception = UCB0RXBUF;
	P1OUT |= BIT4; //CS unselect

	return reception;
}
