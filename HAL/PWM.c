/*
 * PWM.c
 *
 * Created : 
 * Author : Yomna_Mokhtar
 */ 

#include "PWM.h"
#include "Common.h"
#include "PWM_HW_Types.h"


#define  WRITE_REGISTER(address,value) (*(volatile uint32*)address = value)
#define  READ_REGISTER(address)        (*(volatile uint32*)address)
#define  SET_BIT(reg_address, pin)     (*(volatile uint32*)reg_address = *(volatile uint32*)reg_address | (1<<pin))
#define  CLEAR_BIT(reg_address, pin)   (*(volatile uint32*)reg_address = *(volatile uint32*)reg_address & ~(1<<pin))
#define  READ_BIT(reg_address, bit)		 (*(volatile uint32*)reg_address & (1<<bit))


uint32 Module_Bases[] = {MODULE0_BASE, MODULE1_BASE};

PWM_ERRORS PWM_Init(strPWMInit* ptr){
	
	if(ptr == NULL){
		return Unvalid_parameter;
	}
	
	if((ptr->PWM_Module != MODULE0) && (ptr->PWM_Module != MODULE1)){
		return UNVALID_MODULE;
	}
	
	SET_BIT(SYSCTL_RCGCPWM_R, ptr->PWM_Module);
	while(READ_BIT(SYSCTL_PRPWM_R, ptr->PWM_Module) == 0){}
	CLEAR_BIT(SYSCTL_RCC_R, bit20);
	
	#ifdef USE_PWM_GENERATOR0
	if(ptr->PWM_Generator == PWM_GENERATOR_0){
		WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM0_CTL), 0x0);
		if(ptr->PWM_Output == PWM_OUTPUT_A){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM0_GENA), 0x0C8);
		} else if(ptr->PWM_Output == PWM_OUTPUT_B){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM0_GENB), 0xC08);
		} else{
			return UNVALID_OUTPUT;
		}
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM0_LOAD), 16000-1);
	}
		
	#endif
		
	#ifdef USE_PWM_GENERATOR1
	if(ptr->PWM_Generator == PWM_GENERATOR_1){
		WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM1_CTL), 0x0);
		
		if(ptr->PWM_Output == PWM_OUTPUT_A){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM1_GENA), 0x0C8);
		} else if(ptr->PWM_Output == PWM_OUTPUT_B){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM1_GENB), 0xC08);
		} else{
			return UNVALID_OUTPUT;
		}
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM1_LOAD), 16000-1);
	} 
	#endif
	
	#ifdef USE_PWM_GENERATOR2

	if(ptr->PWM_Generator == PWM_GENERATOR_2){
		WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM2_CTL), 0x0);
		
		if(ptr->PWM_Output == PWM_OUTPUT_A){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM2_GENA), 0x0C8);
		} else if(ptr->PWM_Output == PWM_OUTPUT_B){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM2_GENB), 0xC08);
		} else{
			return UNVALID_OUTPUT;
		}
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM2_LOAD), 16000-1);
	} 
	#endif
	
	#ifdef USE_PWM_GENERATOR3
	if(ptr->PWM_Generator == PWM_GENERATOR_3){
		WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM3_CTL), 0x0);
		
		if(ptr->PWM_Output == PWM_OUTPUT_A){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM3_GENA), 0x0C8);
		} else if(ptr->PWM_Output == PWM_OUTPUT_B){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM3_GENB), 0xC08);
		} else{
			return UNVALID_OUTPUT;
		}
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM3_LOAD), 16000-1);
		
	}
	#endif
	if((ptr->PWM_Generator != PWM_GENERATOR_0) && (ptr->PWM_Generator != PWM_GENERATOR_1) && (ptr->PWM_Generator != PWM_GENERATOR_2) && (ptr->PWM_Generator != PWM_GENERATOR_3)){
		return UNVALID_GENERATOR;
	}
	return NO_ERRORS;
}


/***************************************************************************************/

PWM_ERRORS Set_Duty(strPWMInit* ptr, uint32 duty){
	
	if((ptr->PWM_Module != MODULE0) && (ptr->PWM_Module != MODULE1)){
		return UNVALID_MODULE;
	}

	#ifdef USE_PWM_GENERATOR0
	if(ptr->PWM_Generator == PWM_GENERATOR_0){
		if(ptr->PWM_Output == PWM_OUTPUT_A){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM0_CMPA), duty-2);
		} else if(ptr->PWM_Output == PWM_OUTPUT_B){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM0_CMPB), duty-2);
		} else{
			return UNVALID_OUTPUT;
		}
		
		SET_BIT((Module_Bases[ptr->PWM_Module] + PWM0_CTL), bit0);
		
		if(ptr->PWM_Output == PWM_OUTPUT_A){
			SET_BIT((Module_Bases[ptr->PWM_Module] + PWM_ENABLE), bit0);
		} else if(ptr->PWM_Output == PWM_OUTPUT_B){
			SET_BIT((Module_Bases[ptr->PWM_Module] + PWM_ENABLE), bit1);
		}
		
	}
	#endif
	
	#ifdef USE_PWM_GENERATOR1
	if(ptr->PWM_Generator == PWM_GENERATOR_1){
		if(ptr->PWM_Output == PWM_OUTPUT_A){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM1_CMPA), duty-2);
		} else if(ptr->PWM_Output == PWM_OUTPUT_B){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM1_CMPB), duty-2);
		} else{
			return UNVALID_OUTPUT;
		}
		SET_BIT((Module_Bases[ptr->PWM_Module] + PWM1_CTL), bit0);
				
		if(ptr->PWM_Output == PWM_OUTPUT_A){
			SET_BIT((Module_Bases[ptr->PWM_Module] + PWM_ENABLE), bit2);
		} else if(ptr->PWM_Output == PWM_OUTPUT_B){
			SET_BIT((Module_Bases[ptr->PWM_Module] + PWM_ENABLE), bit3);
		}
		
	}
	#endif
	
	#ifdef USE_PWM_GENERATOR2
	if(ptr->PWM_Generator == PWM_GENERATOR_2){
		if(ptr->PWM_Output == PWM_OUTPUT_A){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM2_CMPA), duty-2);
		} else if(ptr->PWM_Output == PWM_OUTPUT_B){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM2_CMPB), duty-2);
		} else{
			return UNVALID_OUTPUT;
			}
			SET_BIT((Module_Bases[ptr->PWM_Module] + PWM2_CTL), bit0);
					
			if(ptr->PWM_Output == PWM_OUTPUT_A){
				SET_BIT((Module_Bases[ptr->PWM_Module] + PWM_ENABLE), bit4);
			} else if(ptr->PWM_Output == PWM_OUTPUT_B){
				SET_BIT((Module_Bases[ptr->PWM_Module] + PWM_ENABLE), bit5);
			}
		
		}
	#endif
		
	#ifdef USE_PWM_GENERATOR3
	 if(ptr->PWM_Generator == PWM_GENERATOR_3){
		if(ptr->PWM_Output == PWM_OUTPUT_A){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM3_CMPA), duty-2);
		} else if(ptr->PWM_Output == PWM_OUTPUT_B){
			WRITE_REGISTER((Module_Bases[ptr->PWM_Module] + PWM3_CMPB), duty-2);
		} else{
			return UNVALID_OUTPUT;
			}
			SET_BIT((Module_Bases[ptr->PWM_Module] + PWM3_CTL), bit0);
					
		if(ptr->PWM_Output == PWM_OUTPUT_A){
			SET_BIT((Module_Bases[ptr->PWM_Module] + PWM_ENABLE), bit6);
		} else if(ptr->PWM_Output == PWM_OUTPUT_B){
			SET_BIT((Module_Bases[ptr->PWM_Module] + PWM_ENABLE), bit7);
		}
		
	}
	#endif
	
	if((ptr->PWM_Generator != PWM_GENERATOR_0) && (ptr->PWM_Generator != PWM_GENERATOR_1) && (ptr->PWM_Generator != PWM_GENERATOR_2) && (ptr->PWM_Generator != PWM_GENERATOR_3)){
		return UNVALID_GENERATOR;
	}
	
	return NO_ERRORS;
}
