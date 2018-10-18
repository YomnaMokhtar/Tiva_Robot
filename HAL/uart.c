/*
 * uart.c
 *
 * Created : 
 * Author : Yomna_Mokhtar
 */ 

#include "uart.h"
#include "Common.h"
#include "UART_HW_Types.h"

/**************************************defines***********************************************/

#define  WRITE_REGISTER(address,value) (*(volatile uint32*)address = value)
#define  READ_REGISTER(address)        (*(volatile uint32*)address)
#define  SET_BIT(reg_address, bit)     (*(volatile uint32*)reg_address = *(volatile uint32*)reg_address | (1<<bit))
#define  CLEAR_BIT(reg_address, bit)   (*(volatile uint32*)reg_address = *(volatile uint32*)reg_address & ~(1<<bit))
#define  READ_BIT(reg_address, bit)		 (*(volatile uint32*)reg_address & (1<<bit))

#define			IBRD_VALUE				0x68
#define			FBRD_VALUE				0xB
#define			MAX_UART_NUMBER		7

/********************************* Declarations********************************************/

uint32 Arr_Bases[8] = {BASE_UART0, BASE_UART1, BASE_UART2, BASE_UART3, BASE_UART4, BASE_UART5, BASE_UART6, BASE_UART7};
	

/******************************** functions ************************************************/


enumUARTErrors UART_Init(uint8 UART_Num){
	
	if(UART_Num > MAX_UART_NUMBER){
		return UNVALID_UART_NUMBER;
	}
	
	SET_BIT(RCGC_UART, UART_Num);														 			 // enable clock to UART
	while((READ_BIT(PR_UART, UART_Num)) == 0){}	 									 // wait for peripheral to be ready
	CLEAR_BIT((Arr_Bases[UART_Num] + CTL), bit1);                  // Disable UART until finishing initialization
	WRITE_REGISTER((Arr_Bases[UART_Num] + IBRD), IBRD_VALUE);			 // Integer Baud Rate division
	WRITE_REGISTER((Arr_Bases[UART_Num] + FBRD), FBRD_VALUE);			 // Fractional Baud Rate division
	WRITE_REGISTER((Arr_Bases[UART_Num] + LCRH), 0x70);			       // Serial parameters select -> select the word length = 8 bits
	WRITE_REGISTER((Arr_Bases[UART_Num] + CC), 0x0);				 			 // Clock source control  
	//SET_BIT((Arr_Bases[UART_Num] + CTL), bit7);								 	 // Loop back enable
	SET_BIT((Arr_Bases[UART_Num] + CTL), bit9);								 		 // Enable RX
	SET_BIT((Arr_Bases[UART_Num] + CTL), bit8);							   		 // Enable TX
	SET_BIT((Arr_Bases[UART_Num] + CTL), bit0);							   		 // Enable UART
	
	return No_Errors;
}

/*******************************************************************************************/

void UART_Tx(uint8 UART_Num, uint8 c)
{
	while(READ_BIT((Arr_Bases[UART_Num] + FR), bit5) != 0){}           
	WRITE_REGISTER((Arr_Bases[UART_Num] + DR), c);
}

/*******************************************************************************************/

uint8 UART_Rx(uint8 UART_Num)
{
	uint8 c;
	while(READ_BIT((Arr_Bases[UART_Num] + FR), bit4) != 0){
		return ((uint8)6);
	}
	c = (uint8)READ_REGISTER(Arr_Bases[UART_Num] + DR);
	return c;
}

/*******************************************************************************************/

