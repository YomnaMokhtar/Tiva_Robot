/*
 * Systic.c
 *
 * Created : 
 * Author : Yomna_Mokhtar
 */ 

#include "Systic.h"
#include "Common.h"

#define  WRITE_REGISTER(address,value) (*(volatile uint32*)address = value)
#define  READ_REGISTER(address)        (*(volatile uint32*)address)


void SysTick_Wait(unsigned long delay){
	WRITE_REGISTER(NVIC_ST_CTRL_R, 0);					   // disable SysTick during setup
  WRITE_REGISTER(NVIC_ST_RELOAD_R, delay-1);     // number of counts to wait
  WRITE_REGISTER(NVIC_ST_CURRENT_R, 0);          // any value written to CURRENT clears it and also clears the count flag in sysctl_R (bit 16)
	WRITE_REGISTER(NVIC_ST_CTRL_R, 0x00000005);    // enable SysTick with core clock
  while((READ_REGISTER(NVIC_ST_CTRL_R)&0x00010000)==0){}            // wait for count flag 'Polling'
  
}


void SysTick_Wait10ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    SysTick_Wait(160000);  // wait 10ms
  }
}

