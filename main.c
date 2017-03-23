/*
 * File: Georges
 *
 * Description: Partie MPS 2553 du robot
 *
 * @version: 0
 */



#include "Georges.h"
unsigned char d;

void main(void) {


	WDTCTL = WDTPW | WDTHOLD;   // Stop WDT

	//Initialisation de toutes les parties de Georges
	InitLED();
    InitSPI();
    InitUART();
	Init_move();

    __bis_SR_register(GIE); // Activation des interruptions

    TXdata('>'); //Signal à l'utilisateur (si il était déjà connecté) que le robot est prêt.


    while(1){

    	if (d == 'z'){
    		avancer();
    	}
    	else if (d=='s'){
    		reculer();
    	}
    	else if (d=='d'){
    		tournerDroite();
    	}
    	else if (d=='q'){
    		tournerGauche();
    	}
    	else if (d=='e'){
    		oui();
    	}
    	else if (d=='r'){
    		non();
    	}
    	else if (d=='f'){
    		accelerer();
    	}
    	else if (d=='t'){
    		P1OUT |= BIT0;
    	}
    	else if (d=='g'){
    		P1OUT &= ~BIT0;
    	}
    }
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{

	d = BTdata();

}
