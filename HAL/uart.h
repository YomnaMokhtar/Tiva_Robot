/*
 * uart.h
 *
 * Created : 
 * Author : Yomna_Mokhtar
 */ 

#ifndef UART_H_
#define UART_H_

#include "Common.h"

/************************************** defines ********************************/

#define		UART0			0
#define		UART1			1
#define		UART2			2
#define		UART3			3
#define		UART4			4
#define		UART5			5
#define		UART6			6
#define		UART7			7


// UART Errors 20 -> 29
typedef enum{
	No_Errors = 20,
	UNVALID_UART_NUMBER = 21,
	
}enumUARTErrors;


enumUARTErrors UART_Init(uint8 UART_Num);
void UART_Tx(uint8 UART_Num, uint8 c);
uint8 UART_Rx(uint8 UART_Num);



#endif

