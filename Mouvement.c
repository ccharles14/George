/*
 * 	Mouvement.c
 *
 *	Author: Corentin CHARLES
 *
 *	Version 1.0
 *
 */

#include "Georges.h"



/**
unsigned int fixaugmenter=1;
 **/

void InitMouve()
{

	//SMLK (main clock) � 1MHz
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	//Timer A1.1: Roue B (TA1CCR1) (roue gauche avec 3e roue face � soi, au plus proche de soi)

	TA1CTL = ( TASSEL_2 | MC_1| ID_0);
	// source horloge SMCLK + mode up + prediv de 1

	TA1CCTL1 |= CM_1 + CCIS_0; // front montant + CCI0A
	//TA1CCTL1 |= CCIE; // autorisation interruption			Supprim� car fonctionne sans et perturbe le programme principal.

	TA1CCTL1 |= OUTMOD_7; //mode reset/set sur TA0.1

	TA1CCTL2 |= CM_1 | CCIS_0; // front montant + CCI0A
	//TA1CCTL2 |= CCIE; // autorisation interruption			Supprim� car fonctionne sans et perturbe le programme principal.

	TA1CCTL2 |= OUTMOD_7; //mode reset/set sur TA0.1



	//on veut 200kHz donc TACCRO=5 (5micro sec pour compter)
	TA1CCR0=5000; //TACCRO va avec TA0CCTL0
	//on veut un rapport cyclique �lev�, par ex: pour 70%: TACCR1=3.5
	TA1CCR1=1; //TACCR1 va avec TA0CCTL1

	//Timer A1.2: Roue A (TA1CCR2)(roue droite avec 3e roue face � soi, au plus proche de soi)
	TA1CCR2=1; //TACCR1 va avec TA0CCTL1
	//on veut un rapport cyclique �lev�, par ex: pour 70%: TACCR1=3.5

	//P2.2, P2.4, P2.1, P2.5 en sortie
	P2DIR |= BIT2 + BIT4 + BIT1 + BIT5;

	//on met les ports P2.2, P2.4, P2.1, P2.5 en mode E/S
	P2SEL&= ~(BIT2 + BIT4 + BIT1 + BIT5);
	P2SEL2&= ~(BIT2 + BIT4 + BIT1 + BIT5);

	//on met P2.2 (=roue droite) en fonction primaire (en Timer TA0CLK)
	P2SEL|=BIT2; // P1SEL � 1
	P2SEL2&=~BIT2; // P1SEL2 � 0

	//on met P2.4 (=roue gauche) en fonction primaire (en Timer TA0CLK)
	P2SEL|=BIT4; // P1SEL � 1
	P2SEL2&=~BIT4; // P1SEL2 � 0


}


void avancer(){
	if (TA1CCR1==1){
		TA1CCR1=1370;
		TA1CCR2=1300;
	}
	//TA1CCR1=4970;
	//TA1CCR2=4900;
	// les deux roues sont en sens inverse, il faut les ramener dans le meme sens selon qu'elles avancent ou reculent.
	P2OUT &= ~ BIT1; //P2.1 � 0
	P2OUT |= BIT5; //P2.5 � 1
}

void reculer(){
	if (TA1CCR1==1){
		TA1CCR1=1370;
		TA1CCR2=1300;
	}
	//TA1CCR1=4970;
	//TA1CCR2=4900;
	P2OUT |= BIT1;
	P2OUT &= ~ BIT5;
}

void tournerGauche(){
	if (TA1CCR1==1){
		TA1CCR1=1170;
		TA1CCR2=1100;
	}
	P2OUT |= BIT1; //P2.1 � 1 (=sens du moteur A)
	P2OUT |= BIT5; //P2.5 � 1 (=sens du moteur B)

}

void tournerDroite(){
	if (TA1CCR1==1){
		TA1CCR1=1170;
		TA1CCR2=1100;
	}
	P2OUT &= ~ BIT1; //P2.1 � 0
	P2OUT &= ~ BIT5; //P2.5 � 0
}

void stop()
{

	while(TA1CCR1>500){
		TA1CCR1=TA1CCR1-400;
		TA1CCR2=TA1CCR2-400;
		__delay_cycles(100000);
	}
	TA1CCR1=1;
	TA1CCR2=1;
}

void STOP()
{
	TA1CCR1=1;
	TA1CCR2=1;
}

/*
 * fonction acc�l�ration//d�c�l�ration
 */
void accelerer()
{
	if(TA1CCR1<=4570)
	{
		TA1CCR1=TA1CCR1+400;
		TA1CCR2=TA1CCR2+400;
	}
	else	//Si on est d�j� rapide, on monte a la vitesse max et on allume la LED pour indiquer � l'utilisateur qu'on est au max.
	{
		TA1CCR1=4970;
		TA1CCR2=4900;
		AllumerLED();
	}

}

void frein()
{
	if(TA1CCR1>=450)
	{
		TA1CCR1=TA1CCR1-400;
		TA1CCR2=TA1CCR2-400;
	}
	else	//Si la vitesse est d�j� tr�s basse on s'arrete.
	{
		TA1CCR1=1;
		TA1CCR2=1;
	}


}



/*
 * Fonction ne servant pas trop au mouvement mais plus � la communication.
 */
void oui()
{

	TA1CCR1=4970;
	TA1CCR2=4900;
	int j=0;
	for (j=0;j<5;j++){
		avancer();
		__delay_cycles(80000);
		reculer();
		__delay_cycles(60000);
	}
	TA1CCR1=1;
	TA1CCR2=1;
}



void non()
{
	TA1CCR1=4970;
	TA1CCR2=4900;
	int j=0;
	for (j=0;j<3;j++){
		tournerGaucheT();
		__delay_cycles(250000);
		tournerDroiteT();
		__delay_cycles(500000);
		tournerGaucheT();
		__delay_cycles(250000);
	}
	TA1CCR1=1;
	TA1CCR2=1;
}


//fonction pour le non
/*
 * Les tourner gauche et droite classique pouvant �tre trop rapide en fonction de la vitesse � laquelle on se trouve au moment de l'execution, deux fonctions sp�cial pour le "non" sont cr��s.
 */

void tournerDroiteT(){
	TA1CCR1=1000;
	TA1CCR2=1000;
	P2OUT &= ~ BIT1; //P2.1 � 0
	P2OUT &= ~ BIT5; //P2.5 � 0
}
void tournerGaucheT(){
	TA1CCR1=1000;
	TA1CCR2=1000;
	P2OUT |= BIT1; //P2.1 � 1 (=sens du moteur A)
	P2OUT |= BIT5; //P2.5 � 1 (=sens du moteur B)
}

