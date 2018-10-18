/*
 * HALIF.h
 *
 * Created : 
 * Author : Yomna_Mokhtar
 */ 

#ifndef HALIF_H_
#define HALIF_H_

#include "Common.h"
#include "GPIO.h"
#include "PWM.h"


enumGPIOErrors GPIO_Configure(strGPIOPinInit* PtrToStr, uint8 port, uint8 pin, uint8 Dir, uint8 digital, enumAltFunc alt_func);
PWM_ERRORS PWM_Configure(strPWMInit* PtrToStr, uint8 Module, uint8 Generator, uint8 Output);

#endif

