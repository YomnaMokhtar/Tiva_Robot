/*
 * Systic.h
 *
 * Created : 
 * Author : Yomna_Mokhtar
 */ 
 
#ifndef SYSTIC_H_
#define SYSTIC_H_

/************ Defines ************/

#define NVIC_ST_CTRL_R          0xE000E010
#define NVIC_ST_RELOAD_R        0xE000E014
#define NVIC_ST_CURRENT_R				0xE000E018

void SysTick_Wait(unsigned long delay);
void SysTick_Wait10ms(unsigned long delay);


#endif
