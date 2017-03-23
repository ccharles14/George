/*
 * 	Georges.h
 *
 *	Author: Corentin
 */

//
//						 _______________
//						|				|
//						|VCC		 GND|
//				  LED <-|P1.0		 XIN|
//				  RDX <-|P1.1		XOUT|
//				  TDX <-|P1.2		TEST|
//	 					|P1.3		 RST|
//			   CS SPI <-|P1.4		P1.7|-> SIMO
//			  CLK SPI <-|P1.5		P1.6|-> SOMI
//						|P2.0		P2.5|-> Sens roue gauche
//	 Sens roue droite <-|P2.1		P2.4|-> CLK roue gauche
//	  CLK roue droite <-|P2.2		P2.3|
//						|_______________|
//						   MSP430G2553
//							"Georges"
//
//
//




#ifndef GEORGES_H_
#define GEORGES_H_

#include <msp430.h>
#include "Uart.h"
#include "SPI.h"
#include "Mouvement.h"
#include <stdlib.h>
#include <time.h>


#endif /* GEORGES_H_ */
