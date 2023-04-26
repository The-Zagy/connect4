/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../LIBRARIES/common/Std_Types.h"
#include "../MCAL/SYSTICK/Inc/Systick.h"
#include "../LIBRARIES/common/Mcu_Hw.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
 void (*Ptr_to_Fn)(void) = NULL_PTR;
 extern uint32_t 					ON_TIME;
 extern uint32_t 					OFF_TIME;
 extern void LedControl(void);
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
* \Syntax          : void Systick_Init(void)       
* \Description     : initiates systick timer                                   
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                  
* \Parameters (out): None                                                      
* \Return value:   : None
*                                      
*******************************************************************************/
void Systick_Init(void)
{
	SYSTICK->STCTRL = 0x06;//enable interrupt and choose system clock for clock source
}
/******************************************************************************
* \Syntax          : void Systick_StartTimer(uint32_t time)      
* \Description     : start the timer by the specified delay time
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : delay time                  
* \Parameters (out): None                                                      
* \Return value:   : None
*                                      
*******************************************************************************/
void Systick_StartTimer(uint32_t time,void(*Cbk_Ptr)(void))
{
	SYSTICK->STRELOAD = (time * SYSTICK_CLOCK_KHZ) - 1;
	SYSTICK->STCURRENT = 0;
	SYSTICK->STCTRL = 0x03;
	Ptr_to_Fn = Cbk_Ptr;
	
}
/******************************************************************************
* \Syntax          : void Systick_StopTimer(void)     
* \Description     : stops the timer                                  
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                  
* \Parameters (out): None                                                      
* \Return value:   : None
*                                      
*******************************************************************************/
void Systick_StopTimer(void)
{
	SYSTICK->STCTRL = 0x06;
}
/******************************************************************************
* \Syntax          : void Systick_ChangeTiming(uint32_t time)       
* \Description     : Change the delay time by loading the new count                                 
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : delay time                 
* \Parameters (out): None                                                      
* \Return value:   : None
*                                      
*******************************************************************************/
void Systick_ChangeTiming(uint32_t time,void(* Cbk_Ptr)(void))
{
	SYSTICK->STRELOAD = (time * SYSTICK_CLOCK_KHZ) - 1;
	SYSTICK->STCURRENT = 0;
	Ptr_to_Fn = Cbk_Ptr;
}

void SysTick_Handler(void)
{
	Systick_StopTimer();
	Ptr_to_Fn();
		
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
