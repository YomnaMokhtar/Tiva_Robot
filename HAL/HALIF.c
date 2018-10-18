/*
 * HALIF.c
 *
 * Created : 
 * Author : Yomna_Mokhtar
 */ 

#include "HALIF.h"


enumGPIOErrors GPIO_Configure(strGPIOPinInit* PtrToStr, uint8 port, uint8 pin, uint8 Dir, uint8 digital, enumAltFunc alt_func){
	
	if(PtrToStr == NULL){
		return Unvalid_Parameter;
	}
	PtrToStr->port = port;
	PtrToStr->pin = pin;
	PtrToStr->Dir = Dir;
	PtrToStr->Digital = digital;
	PtrToStr->alt_func = alt_func;

	return GPIO_Pin_Init(PtrToStr);
}

PWM_ERRORS PWM_Configure(strPWMInit* PtrToStr, uint8 Module, uint8 Generator, uint8 Output){
	
	if(PtrToStr == NULL){
		return Unvalid_parameter;
	}
	PtrToStr->PWM_Module = Module;
	PtrToStr->PWM_Generator = Generator;
	PtrToStr->PWM_Output = Output;
	
	return PWM_Init(PtrToStr);
}

