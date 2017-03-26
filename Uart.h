/*
 * 	Uart.h
 *
 *	Author: Corentin CHARLES
 *
 *	Version 1.0
 *
 */

#ifndef GEORGE_UART_H_
#define GEORGE_UART_H_

void InitUART();
void TXdata( unsigned char  );
unsigned char RXdata(void);
void help(void);


#endif /* GEORGE_UART_H_ */
