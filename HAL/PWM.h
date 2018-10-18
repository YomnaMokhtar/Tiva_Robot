/*
 * PWM.h
 *
 * Created : 
 * Author : Yomna_Mokhtar
 */ 

#ifndef PWM_H_
#define PWM_H_

#include "Common.h"

#define USE_PWM_GENERATOR0
#define USE_PWM_GENERATOR1
#define USE_PWM_GENERATOR2
#define USE_PWM_GENERATOR3


/********************************** Declarations *********************************/

// PWM Errors 10 -> 19
typedef enum{
	
	NO_ERRORS = 11,
	Unvalid_parameter = 12,
	UNVALID_MODULE = 13,
	UNVALID_GENERATOR = 14,
	UNVALID_OUTPUT = 15,
	
}PWM_ERRORS;

typedef struct{
	uint8 PWM_Module;
	uint8 PWM_Generator;
	uint8 PWM_Output;
	
}strPWMInit;

/********************************** Functions *********************************/

PWM_ERRORS PWM_Init(strPWMInit* ptr);
PWM_ERRORS Set_Duty(strPWMInit* ptr, uint32 duty);

/********************************** defines *********************************/

#define			MODULE0							0
#define			MODULE1							1

#define			PWM_GENERATOR_0			0
#define			PWM_GENERATOR_1			1
#define			PWM_GENERATOR_2			2
#define			PWM_GENERATOR_3			3

#define			PWM_OUTPUT_A				0
#define			PWM_OUTPUT_B				1

#endif

