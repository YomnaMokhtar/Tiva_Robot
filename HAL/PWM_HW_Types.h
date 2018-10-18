/*
 * PWM_HW_Types.h
 *
 * Created : 
 * Author : Yomna_Mokhtar
 */ 
#ifndef PWM_HW_TYPES_H_
#define PWM_HW_TYPES_H_


                          /***************** BASE ADDRESSES *****************/

#define			MODULE0_BASE			0x40028000
#define			MODULE1_BASE			0x40029000

                          /***************** OFFSETS *****************/

/************GENERAL************/

#define			PWM_ENABLE		0x008

/************ PWM0 ************/

#define			PWM0_CTL			0x040
#define			PWM0_LOAD			0x050
#define			PWM0_COUNT		0x054
#define			PWM0_CMPA			0x058
#define			PWM0_CMPB			0x05C
#define			PWM0_GENA			0x060
#define			PWM0_GENB			0x064

/************ PWM1 ************/

#define			PWM1_CTL			0x080
#define			PWM1_LOAD			0x090
#define			PWM1_COUNT		0x094
#define			PWM1_CMPA			0x098
#define			PWM1_CMPB			0x09C
#define			PWM1_GENA			0x0A0
#define			PWM1_GENB			0x0A4

/************ PWM2 ************/

#define			PWM2_CTL			0x0C0
#define			PWM2_LOAD			0x0D0
#define			PWM2_COUNT		0x0D4
#define			PWM2_CMPA			0x0D8
#define			PWM2_CMPB			0x0DC
#define			PWM2_GENA			0x0E0
#define			PWM2_GENB			0x0E4

/************ PWM3 ************/

#define			PWM3_CTL			0x100
#define			PWM3_LOAD			0x110
#define			PWM3_COUNT		0x114
#define			PWM3_CMPA			0x118
#define			PWM3_CMPB			0x11C
#define			PWM3_GENA			0x120
#define			PWM3_GENB			0x124



                          /***************** BASE ADDRESSES *****************/

#define			SYSCTL_RCC_R				0x400FE060
#define			SYSCTL_RCGCPWM_R		0x400FE640
#define			SYSCTL_PRPWM_R			0x400FEA40


#endif
