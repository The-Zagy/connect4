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
#include "../LIBRARIES/CpuDriver/inc/cpu_driver.h"
#include "../Nokia5110.h"
#include "../LIBRARIES/COMMON/Mcu_Hw.h"
#include "../../MCAL/PORT/Inc/Port_Cfg.h"
#include "../../LIBRARIES/Common/Bit_Math.h"
#include "connect4.h"

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

void GPIOPortB_Handler(void)
{
	if (Move_Right_Button.GPIOx->GPIORIS & (1 << Move_Right_Button.ChannelId))
	{ // s1 pressed
		SET_BIT_PERIPH_BAND(Move_Right_Button.GPIOx->GPIOICR, Move_Right_Button.ChannelId);
		// move_right();
		move_right_flag = 1;
	}
}

void GPIOPortD_Handler(void)
{

	if (Move_Left_Button.GPIOx->GPIORIS & (1 << Move_Left_Button.ChannelId))
	{
		SET_BIT_PERIPH_BAND(Move_Left_Button.GPIOx->GPIOICR, Move_Left_Button.ChannelId);
		move_left_flag = 1;
	}
	else if (Action_Button.GPIOx->GPIORIS & (1 << Action_Button.ChannelId))
	{
		SET_BIT_PERIPH_BAND(Action_Button.GPIOx->GPIOICR, Action_Button.ChannelId);
		action_flag = 1;
	}
}

// uncomment for dev
// void GPIOPortF_Handler(void)
// {

// 	if (Move_Right_Button.GPIOx->GPIORIS & (1 << Move_Right_Button.ChannelId))
// 	{ // s3 pressed
// 		SET_BIT_PERIPH_BAND(Move_Right_Button.GPIOx->GPIOICR, Move_Right_Button.ChannelId);
// 		move_right_flag = 1;
// 	}else if (Action_Button.GPIOx->GPIORIS & (1 << Action_Button.ChannelId))
// 	{ // s1 pressed
// 		SET_BIT_PERIPH_BAND(Action_Button.GPIOx->GPIOICR, Action_Button.ChannelId);
// 		action_flag = 1;
// 	}
// }
/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
