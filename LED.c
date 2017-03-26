/*
 * 	LED.c
 *
 *	Author: Corentin CHARLES
 *
 *	Version 1.0
 *
 */
#include "Georges.h"

void InitLED(void){
    P1SEL &= ~BIT0;		//Mode E/S
    P1SEL2 &= ~BIT0;	//Mode E/S
    P1DIR |= BIT0;		//Mode sortie
    P1OUT &= ~BIT0;		//Eteinte par defaut
}

void AllumerLED(void){
	P1OUT |= BIT0;
}

void EteindreLED(void){
	P1OUT &= ~BIT0;
}
