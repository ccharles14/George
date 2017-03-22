/*
 * File: Georges
 *
 * Description: Partie MPS 2553 du robot
 *
 * @version: 0
 */


#include "Georges.h"

void main(void) {

	WDTCTL = WDTPW | WDTHOLD;   // Stop WDT

	P1DIR |= BIT0;
	P1OUT &= ~BIT0;
	P1DIR &= ~(BIT3);
	P1REN |= BIT3;
	P1OUT |= BIT3;
	P1IES |= BIT3;
	P1IE |= (BIT3);
	P1IFG &= ~(BIT3);

    P1SEL &= ~BIT0;
    P1SEL2 &= ~BIT0;
    P1DIR |= BIT0;


    //InitSPI();
    //InitUART();
	Init_move();

    __bis_SR_register(GIE); // interrupts enbled

    //TXdata('>');
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

	if (d == 'z')
		avancer();
	else if (d == 's')
		reculer();
	else if (d=='d')
		tournerDroite();
	else if (d=='q')
		tournerGauche();
	else if (d=='e')
		oui();
	else if (d=='r')
		non();
	else if (d=='t')
		P1OUT |= BIT0;
	else if (d=='g')
		P1OUT &= ~BIT0;
}
