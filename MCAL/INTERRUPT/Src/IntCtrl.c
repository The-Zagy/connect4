/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCrtl.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../LIBRARIES/common/Std_Types.h"
#include "../MCAL/INTERRUPT/Inc/IntCtrl.h"
#include "../LIBRARIES/common/Mcu_Hw.h"
#include "../LIBRARIES/CpuDriver/inc/cpu_driver.h"
#include "../MCAL/INTERRUPT/Inc/IntCtrl_Cfg.h"
#include "../LIBRARIES/common/Bit_Math.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : IntCtrl_EnableIRQ(IRQn_Type interruptIRQn)                                     
* \Description     : enable specified interrupt                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Interrupt IRQn number 
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCtrl_EnableIRQ(IRQn_Type interruptIRQn)
{
	if(interruptIRQn >= 0)
	{
			SET_BIT_PERIPH_BAND_VAL(NVIC->EN[(interruptIRQn)/32],1<<(uint8_t)interruptIRQn % 32);
	}

}
/******************************************************************************
* \Syntax          : void IntCrtl_Init(IntCtr_Config* Int_Cfg)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Pointer to struct of the configuration
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCrtl_Init(IntCtr_Config* Int_Cfg)
{

	/*TODO Configure Grouping\SubGrouping System in APINT register in SCB*/
	SET_BIT_PERIPH_BAND_VAL(SCB->APINT,(uint32_t)APINT_KEY<<16);
	SET_BIT_PERIPH_BAND_VAL(SCB->APINT,(uint32_t)Int_Cfg->InterruptGrouping & (uint32_t)0x07 <<8);
	/*TODO : Assign Group\Subgroup priority in NVIC_PRIx Nvic and SCB_SYSPRIx Registers*/  
	switch(Int_Cfg->InterruptPeripheralGate % 4)
	{
		case 0:
			SET_BIT_PERIPH_BAND_VAL(NVIC->PRI[(Int_Cfg->InterruptPeripheralGate)/4],(uint32_t)Int_Cfg->InterruptGroupPriority<<5);
			break;
		case 1:
			SET_BIT_PERIPH_BAND_VAL(NVIC->PRI[(Int_Cfg->InterruptPeripheralGate)/4],(uint32_t)Int_Cfg->InterruptGroupPriority<<13);
			break;
		case 2:
			SET_BIT_PERIPH_BAND_VAL(NVIC->PRI[(Int_Cfg->InterruptPeripheralGate)/4],(uint32_t)Int_Cfg->InterruptGroupPriority<<21);
			break;
		case 3:
			SET_BIT_PERIPH_BAND_VAL(NVIC->PRI[(Int_Cfg->InterruptPeripheralGate)/4],(uint32_t)Int_Cfg->InterruptGroupPriority<<29);
			break;
		default:
			break;
	}
	
	
	/*TODO : Enable\Disable based on user configurations in NVIC_ENx and SCB_Sys Registers */
	IntCtrl_EnableIRQ(Int_Cfg->InterruptPeripheralGate);
	cpuDriver_EnableGlobalInterrupt();
}


/**********************************************************************************************************************
 *  END OF FILE: IntCrtl.c
 *********************************************************************************************************************/
