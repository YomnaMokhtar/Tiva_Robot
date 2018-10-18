/*
 * main.c
 *
 * Created : 1/10/2018
 * Author : Yomna_Mokhtar
 */ 
 
/*	Project Description	*/
/*
		This is a Blutooth Controlled Robot via a mobile appliction
		This code is written using Finite State Machine(FSM)
*/

/**************** Pins description ****************/

// Motor1 --> Right Motor :
//					 M1_1 --> PE1 --> IN3
//					 M1_2 --> PE2 --> IN5
//					 M1_PWM --> PF1 (Module1, PWM2, GENB)
// Motor2 --> Left Motor :
//					 M2_1 --> PE4 --> IN1
//					 M2_2 --> PE5 --> IN2
//					 M2_PWM --> PF2 (Module1, PWM3, GENA)

// UART PINS
//		input(RX) : PB0
//		Output(TX) : PB1

/* Received data*/
/*
	0 --> Forward
	1 --> Backward
	2 --> Right
	3 --> Left
	4 --> Increase Speed
  5 --> Decrease Speed
	6 --> Idle
*/

#include "HAL/common.h"
#include "HAL/GPIO.h"
#include "HAL/PWM.h"
#include "HAL/uart.h"
#include "HAL/GPIO_HW_Types.h"
#include "HAL/PWM_HW_Types.h"
#include "HAL/UART_HW_Types.h"
#include "HAL/HALIF.h"
#include "HAL/Systic.h"


#define SCB_CPAC (*((volatile unsigned int*)0xE000ED88))


/**************** GPIO STRUCTS ****************/

strGPIOPinInit M1_1;
strGPIOPinInit* ptr_M1_1;
enumGPIOErrors GPIO_error1;

strGPIOPinInit M1_2;
strGPIOPinInit* ptr_M1_2;
enumGPIOErrors GPIO_error2;

strGPIOPinInit M1_PWM;
strGPIOPinInit* ptr_M1_PWM;
enumGPIOErrors GPIO_error3;

strGPIOPinInit M2_1;
strGPIOPinInit* ptr_M2_1;
enumGPIOErrors GPIO_error4;

strGPIOPinInit M2_2;
strGPIOPinInit* ptr_M2_2;
enumGPIOErrors GPIO_error5;

strGPIOPinInit M2_PWM;
strGPIOPinInit* ptr_M2_PWM;
enumGPIOErrors GPIO_error6;

strGPIOPinInit UART_TX_Pin;
strGPIOPinInit* ptr_UART_TX_Pin;
enumGPIOErrors GPIO_error7;

strGPIOPinInit UART_RX_Pin;
strGPIOPinInit* ptr_UART_RX_Pin;
enumGPIOErrors GPIO_error8;

/**************** PWM STRUCTS ****************/

strPWMInit PWM_M1_2_B;
strPWMInit* ptr_PWM_M1_2_B;
PWM_ERRORS PWM_Error1;

strPWMInit PWM_M1_3_A;
strPWMInit* ptr_PWM_M1_3_A;
PWM_ERRORS PWM_Error2;


enumUARTErrors UART_error1;

/******** FSM STRUCT ********/
typedef struct{
	uint32 out1;
	uint32 out2;
	uint32 wait;
	uint32 next[7];
} stype;

#define	OUT1_F	0x12 
#define	OUT1_B	0x24
#define	OUT1_R	0x12
#define	OUT1_L	0x12
#define OUT1_Idle 0x00


#define OUT2_F0 650006500
#define	OUT2_F1 800008000
#define	OUT2_F2 1400014000

#define OUT2_B0 650006500   
#define	OUT2_B1 800008000
#define	OUT2_B2 1400014000

#define OUT2_R0 650001000
#define	OUT2_R1 800001000
#define	OUT2_R2 1400001000

#define OUT2_L0 100006500
#define	OUT2_L1 100008000
#define	OUT2_L2 100014000

#define OUT2_Idle	0000200002

#define	F0	0
#define	F1	1
#define	F2	2
#define	B0	3
#define	B1	4
#define	B2	5
#define	R0	6
#define	R1	7
#define	R2	8
#define	L0	9
#define	L1	10
#define	L2	11
#define IDLE 12

#define FSM_DELAY 5


stype FSM[13] = {
	
	{OUT1_F, OUT2_F0, FSM_DELAY, {F0, B0, R0, L0, F1, F0, IDLE}},
  {OUT1_F, OUT2_F1, FSM_DELAY, {F1, B1, R1, L1, F2, F0, IDLE}},
	{OUT1_F, OUT2_F2, FSM_DELAY, {F2, B2, R2, L2, F2, F1, IDLE}},
	{OUT1_B, OUT2_B0, FSM_DELAY, {F0, B0, R0, L0, B1, B0, IDLE}},
	{OUT1_B, OUT2_B1, FSM_DELAY, {F1, B1, R1, L1, B2, B0, IDLE}},
	{OUT1_B, OUT2_B2, FSM_DELAY, {F2, B2, R2, L2, B2, B1, IDLE}},
	{OUT1_R, OUT2_R0, FSM_DELAY, {F0, B0, R0, L0, R1, R0, IDLE}},
	{OUT1_R, OUT2_R1, FSM_DELAY, {F1, B1, R1, L1, R2, R0, IDLE}},
	{OUT1_R, OUT2_R2, FSM_DELAY, {F2, B2, R2, L2, R2, R1, IDLE}},
	{OUT1_L, OUT2_L0, FSM_DELAY, {F0, B0, R0, L0, L1, L0, IDLE}},
	{OUT1_L, OUT2_L1, FSM_DELAY, {F1, B1, R1, L1, L2, L0, IDLE}},
	{OUT1_L, OUT2_L2, FSM_DELAY, {F2, B2, R2, L2, L2, L1, IDLE}},
	{OUT1_Idle, OUT2_Idle, FSM_DELAY, {F0, B0, R0, L0, F2,  F0, IDLE}}
	
};



int main(void){
	
	/****************************** Variables Definition ******************************/
	
	uint32 cstate;
	uint8 input;
	uint8 last_state;


	/**************************************** Motor1 ****************************************/
	
	ptr_M1_1 = &M1_1;
	GPIO_error1 = GPIO_Configure(ptr_M1_1, PortE, 1, Pin_Output, Pin_Digital_Enable_Analog_Disable, NON);
	
	ptr_M1_2 = &M1_2;
	GPIO_error2 = GPIO_Configure(ptr_M1_2, PortE, 2, Pin_Output, Pin_Digital_Enable_Analog_Disable, NON);
	
	ptr_M1_PWM = &M1_PWM;
	GPIO_error3 = GPIO_Configure(ptr_M1_PWM, PortF, 1, Pin_Output, Pin_Digital_Enable_Analog_Disable, PWM_M1);
	
  /**************************************** Motor2 ****************************************/
	
	ptr_M2_1 = &M2_1;
	GPIO_error4 = GPIO_Configure(ptr_M2_1, PortE, 4, Pin_Output, Pin_Digital_Enable_Analog_Disable, NON);
	
	ptr_M2_2 = &M2_2;
	GPIO_error5 = GPIO_Configure(ptr_M2_2, PortE, 5, Pin_Output, Pin_Digital_Enable_Analog_Disable, NON);
	
	ptr_M2_PWM = &M2_PWM;
	GPIO_error6 = GPIO_Configure(ptr_M2_PWM, PortF, 2, Pin_Output, Pin_Digital_Enable_Analog_Disable, PWM_M1);
	
	 /**************************************** UART1 ****************************************/
	
	ptr_UART_TX_Pin = &UART_TX_Pin;
	GPIO_error7 = GPIO_Configure(ptr_UART_TX_Pin, PortB, 1, Pin_Output, Pin_Digital_Enable_Analog_Disable, UART);
	
	ptr_UART_RX_Pin = &UART_RX_Pin;
	 GPIO_Configure(ptr_UART_RX_Pin, PortB, 0, Pin_Input, Pin_Digital_Enable_Analog_Disable, UART);
	
	UART_error1 = UART_Init(UART1);
	
	 /**************************************** PWM ****************************************/
	 
	 
	ptr_PWM_M1_2_B = &PWM_M1_2_B;
	PWM_Error1 = PWM_Configure(ptr_PWM_M1_2_B, MODULE1, PWM_GENERATOR_2, PWM_OUTPUT_B);
	
	ptr_PWM_M1_3_A = &PWM_M1_3_A;
	PWM_Error2 = PWM_Configure(ptr_PWM_M1_3_A, MODULE1, PWM_GENERATOR_3, PWM_OUTPUT_A);
	
	
	cstate = F0;
	
	while(1){
		
		
		Write_Port(PortE, FSM[cstate].out1);
		Set_Duty(ptr_PWM_M1_2_B, (FSM[cstate].out2 % 100000));
		Set_Duty(ptr_PWM_M1_3_A, (FSM[cstate].out2 / 100000));
		SysTick_Wait10ms(FSM[cstate].wait);
		input = UART_Rx(UART1);
		
		if(cstate != IDLE){
		last_state = cstate;
		}
			cstate = FSM[last_state].next[input];
		
	}

}


void SystemInit(void){
	SCB_CPAC |= 0x00F00000;
}

