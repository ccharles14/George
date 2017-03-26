/*
 *	File: Georges
 *
 *	Description: Partie MPS 2553 du robot
 *
 *	Author: Corentin CHARLES et Renjie ZHANG
 *
 *	Version 1.0
 *
 */


#include "Georges.h"
unsigned char donnee;
unsigned char check; //Utilisé pour savoir si la dernière commande a bien été éxécuté.

void main(void) {

	WDTCTL = WDTPW | WDTHOLD;   // Stop WDT

	//Initialisation de toutes les parties de Georges
	InitLED();
    InitSPI();
    InitUART();
	InitMouve();

    __bis_SR_register(GIE); // Activation des interruptions

    TXdata('>'); //Signal à l'utilisateur (si il était déjà connecté) que le robot est prêt.


    /*Programme principal:
     * Le programme parcour en permanance le while contenant toute les actions possibles du robot.
     * Si une touche a besoin touche'être utilisée plusieurs fois, la variable 'donnée' ne changeant pas, le programme ne pourra pas le détecter.
     * L'ajout de la variable 'check' répond à ce problème.
     *
     * Une interruption pouvant arriver à n'importe quel instant, on attendra de savoir si on a pressé sur une touche avant de parcourir la liste des actions.
     */
    while(1){

    	if (check == 1){ 		//donnée arrivé en Uart?

    		//Si oui, on fait une des actions possible.
    		if (donnee == 'z' || donnee == '8'){
    			avancer();
    		}
    		else if (donnee == 's' || donnee == '2'){
    			reculer();
    		}
    		else if (donnee == 'd' || donnee == '6'){
    			tournerDroite();
    		}
    		else if (donnee == 'q' || donnee == '4'){
    			tournerGauche();
    		}
    		else if (donnee == 'o' ){
    			oui();
    		}
    		else if (donnee == 'n'){
    			non();
    		}
    		else if (donnee == 'e' || donnee == '9'){
    			accelerer();
    		}
    		else if (donnee == 'a' || donnee == '7'){
    			frein();
    		}
    		else if (donnee == 'x' || donnee == '5'){
    			stop();
    		}
    		else if (donnee == 'l'){
    			AllumerLED();
    		}
    		else if (donnee == 'm'){
    			EteindreLED();
    		}
    		else if (donnee == 'h'){
    			help();
    		}

    		check = 0;
    	}
    }
}


#pragma vector=USCIAB0RX_VECTOR			//interuption en cas de réception de donnée via l'Uart
__interrupt void USCI0RX_ISR(void)
{
	donnee = RXdata();	//Enregistrement de la donnée.
	check = 1;			//Indication qu'une donnée est arrivée.
}
