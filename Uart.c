/*
 * 	Uart.c
 *
 *	Author: Corentin CHARLES
 *
 *	Version 1.0
 *
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

//Fonction pour envoyer une donée via l'Uart.
void TXdata( unsigned char c )
{
	while (!(IFG2&UCA0TXIFG));  // USCI_A0 TX buffer ready?
    UCA0TXBUF = c;              // TX -> RXed character
}


//Fonction pour recevoir une donnée via l'Uart.
unsigned char RXdata(void){
	unsigned char a;
	while (!(IFG2&UCA0RXIFG));
	a = UCA0RXBUF;
	return a;
}

//En cas de demande d'aide de la part de l'utilisateur, ce texte sera affiché sur n'importe quelle interface.
void help(void){
	unsigned char h[89]={'C','o','m','m','a','n','d',' ','s','i','m','p','l','e',':','\n','\r', 	//Commande simple:
						'a','v','a','n','c','e','r',':',' ','z','\n','\r', 							//avancer: z
						'r','e','c','u','l','e','r',':',' ','s','\n','\r', 							//reculer: s
						'd','r','o','i','t','e',':',' ','d','\n','\r', 								//droite: d
						'g','a','u','c','h','e',':',' ','q','\n','\r', 								//gauche: q
						'a','c','c','e','l','e','r','e','r',':',' ','e','\n','\r',					//accelerer: e
						'f','r','e','i','n','e','r',':',' ','a','\n','\r',}; 						//freiner: a
	int i;
	for(i=0;i<=88;i++)
		TXdata(h[i]);
}
