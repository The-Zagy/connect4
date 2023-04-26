/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  DIO.c
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
#include "../LIBRARIES/common/Mcu_Hw.h"
#include "../MCAL/DIO/Inc/Dio.h"
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

DIO_LevelType DIO_ReadChannel (DIO_PortType PortId ,DIO_ChannelType ChannelId)
{
	switch(PortId)
	{
		case PORTA:
				return GET_BIT(((GPIOA->GPIODATA) + (1 << (2 + ChannelId) )),ChannelId);
		case PORTB:
				return GET_BIT(((GPIOB->GPIODATA) + (1 << (2 + ChannelId) )),ChannelId);
		case PORTC:
				return GET_BIT(((GPIOC->GPIODATA) + (1 << (2 + ChannelId) )),ChannelId);
		case PORTD:
				return GET_BIT(((GPIOD->GPIODATA) + (1 << (2 + ChannelId) )),ChannelId);
		case PORTE:
				return GET_BIT(((GPIOE->GPIODATA) + (1 << (2 + ChannelId) )),ChannelId);
		case PORTF:
				return GET_BIT(((GPIOF->GPIODATA) + (1 << (2 + ChannelId) )),ChannelId);
	}
	

	return 0;
}

void DIO_WriteChannel ( DIO_PortType PortId , DIO_ChannelType ChannelId, DIO_LevelType Level)
{
	if (Level)
	{
		switch(PortId)
		{
			case PORTA:
					SET_BIT_PERIPH_BAND(GPIOA->GPIODATA ,ChannelId);
					
					break;
			case PORTB:
					SET_BIT_PERIPH_BAND(GPIOB->GPIODATA ,ChannelId);
					break;
			case PORTC:
					SET_BIT_PERIPH_BAND(GPIOC->GPIODATA ,ChannelId);
					break;
			case PORTD:
					SET_BIT_PERIPH_BAND(GPIOD->GPIODATA ,ChannelId);
					break;
			case PORTE:
					SET_BIT_PERIPH_BAND(GPIOE->GPIODATA ,ChannelId);
					break;
			case PORTF:
					SET_BIT_PERIPH_BAND(GPIOF->GPIODATA ,ChannelId);
					break;
		}
	}else
	{
		switch(PortId)
		{
			case PORTA:
					CLEAR_BIT_PERIPH_BAND(GPIOA->GPIODATA ,ChannelId);
					
					break;
			case PORTB:
					CLEAR_BIT_PERIPH_BAND(GPIOB->GPIODATA ,ChannelId);
					break;
			case PORTC:
					CLEAR_BIT_PERIPH_BAND(GPIOC->GPIODATA ,ChannelId);
					break;
			case PORTD:
					CLEAR_BIT_PERIPH_BAND(GPIOD->GPIODATA ,ChannelId);
					break;
			case PORTE:
					CLEAR_BIT_PERIPH_BAND(GPIOE->GPIODATA ,ChannelId);
					break;
			case PORTF:
					CLEAR_BIT_PERIPH_BAND(GPIOF->GPIODATA ,ChannelId);
					break;
		}
	}
}

DIO_PortLevelType DIO_ReadPort (DIO_PortType PortId)
{
	switch(PortId)
	{
		case PORTA:
				return (*(volatile DIO_PortLevelType *)(((uint32_t)(&GPIOA->GPIODATA) + 0x3FC)));
					//(DIO_PortLevelType)((GPIOA->GPIODATA) + (255 << (2) ));
		case PORTB:
				return (*(volatile DIO_PortLevelType *)(((uint32_t)(&GPIOB->GPIODATA) + 0x3FC)));	
				//return (DIO_PortLevelType)((GPIOB->GPIODATA) + (255 << (2) ));
		case PORTC:
				return (*(volatile DIO_PortLevelType *)(((uint32_t)(&GPIOC->GPIODATA) + 0x3FC)));	
				//return (DIO_PortLevelType)((GPIOC->GPIODATA) + (255 << (2) ));
		case PORTD:
				return (*(volatile DIO_PortLevelType *)(((uint32_t)(&GPIOD->GPIODATA) + 0x3FC)));	
				//return (DIO_PortLevelType)((GPIOD->GPIODATA) + (255 << (2) ));
		case PORTE:
				return (*(volatile DIO_PortLevelType *)(((uint32_t)(&GPIOE->GPIODATA) + 0x3FC)));	
				//return (DIO_PortLevelType)((GPIOE->GPIODATA) + (255 << (2) ));
		case PORTF:
				return (*(volatile DIO_PortLevelType *)(((uint32_t)(&GPIOF->GPIODATA) + 0x3FC)));	
				//return (DIO_PortLevelType)((GPIOF->GPIODATA) + (255 << (2) ));
	}

	return 0;
}

void DIO_WritePort (DIO_PortType PortId, DIO_PortLevelType Level)
{
	switch(PortId)
	{
		case PORTA:
				WRITE_BIT_PERIPH_BAND_DATA_VAL(GPIOA->GPIODATA,Level);
				break;
		case PORTB:
				WRITE_BIT_PERIPH_BAND_DATA_VAL(GPIOB->GPIODATA,Level);
				break;	
		case PORTC:
				WRITE_BIT_PERIPH_BAND_DATA_VAL(GPIOC->GPIODATA,Level);
				break;
		case PORTD:
				WRITE_BIT_PERIPH_BAND_DATA_VAL(GPIOD->GPIODATA,Level);
				break;
		case PORTE:
				WRITE_BIT_PERIPH_BAND_DATA_VAL(GPIOE->GPIODATA,Level);
				break;
		case PORTF:
				WRITE_BIT_PERIPH_BAND_DATA_VAL(GPIOF->GPIODATA,Level);
				break;
	}

}

void DIO_FlipChannel (DIO_PortType PortId,DIO_ChannelType ChannelId)
{
	switch(PortId)
		{
			case PORTA:
					TOGGLE_BIT(*((uint32_t*)((GPIOA->GPIODATA) + (1 << (2 + ChannelId) ))),ChannelId);
					
					break;
			case PORTB:
					if(GPIOB->GPIODATA != 0)
						CLEAR_BIT_PERIPH_BAND_DATA((GPIOB->GPIODATA),ChannelId);
					else
						SET_BIT_PERIPH_BAND_DATA((GPIOB->GPIODATA),ChannelId);
					break;
			case PORTC:
					TOGGLE_BIT(*((uint32_t*)((GPIOC->GPIODATA) + (1 << (2 + ChannelId) ))),ChannelId);
					break;
			case PORTD:
					TOGGLE_BIT(*((uint32_t*)((GPIOD->GPIODATA) + (1 << (2 + ChannelId) ))),ChannelId);
					break;
			case PORTE:
					TOGGLE_BIT(*((uint32_t*)((GPIOE->GPIODATA) + (1 << (2 + ChannelId) ))),ChannelId);
					break;
			case PORTF:
					TOGGLE_BIT(*((uint32_t*)((GPIOF->GPIODATA) + (1 << (2 + ChannelId) ))),ChannelId);
					break;
		}

}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
