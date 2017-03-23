/*
 * LED.c
 *
 *  Created on: 23 mars 2017
 *      Author: Asus
 */
#include "Georges.h"

void InitLED(void){

    P1SEL &= ~BIT0;		//Mode E/S
    P1SEL2 &= ~BIT0;	//Mode E/S
    P1DIR |= BIT0;		//Mode sortie
    P1OUT &= ~BIT0;		//Eteinte par defaut
}

