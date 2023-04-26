/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PORT_CFG_H
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef PORT_CFG_H
#define PORT_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define ANALOG_ENABLE									0 // 0 to disable and 1 to enable

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#include "../LIBRARIES/common/Std_Types.h"
#include "../MCAL/DIO/Inc/Dio.h"
#include "../MCAL/INTERRUPT/inc/IntCtrl.h"
#include "../LIBRARIES/common/Mcu_Hw.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

typedef enum
{
	/*********************** PORTA Alternate functions pins  ***********************/
	DIGITAL_PIN					= -1,
	/*********************** ANALOG PINS  ***********************/
	AIN0 								= 0,
	AIN1,
	AIN2,
	AIN3,
	AIN4,
	AIN5,
	AIN6,
	AIN7,
	AIN8,
	AIN9,
	AIN10,
	AIN11,
	/*********************** PORTA Alternate functions pins  ***********************/
	PA0_U0Rx						= 1,
	PA0_CAN1Rx					= 8,
	PA1_U0Tx						= 1,
	PA1_CAN1Tx					= 8,
	PA2_SSI0CLK					= 2,
	PA3_SSI0Fss					= 2,
	PA4_SSI0Rx					= 2,
	PA5_SSI0Tx					= 2,
	PA6_I2C1SCL					= 3,
	PA6_M1PWM2					= 5,
	PA7_I2C1SDA					= 3,
	PA7_M1PWM3					= 5,
	/*********************** PORTB Alternate functions pins  ***********************/
	PB0_U1Rx						= 1,
	PB0_T2CCP0					= 7,
	PB1_U1Tx						= 1,
	PB1_T2CCP1					= 7,
	PB2_I2C0SCL					= 3,
	PB2_T3CCP0					= 7,
	PB3_I2C0SDA					= 3,
	PB3_T3CCP1					= 7,
	PB4_SSI2CLK					= 1,
	PB4_M0PWM2					= 4,
	PB4_T1CCP0					= 7,
	PB4_CAN0Rx					= 8,
	PB5_SSI2Fss					= 1,
	PB5_M0PWM3					= 4,
	PB5_T1CCP1					= 7,
	PB5_CAN0Tx					= 8,
	PB6_SSI2Rx					= 2,
	PB6_M0PWM0					= 4,
	PB6_T0CCP0					= 7,
	PB7_SSI2Tx					= 2,
	PB7_M0PWM1					= 4,
	PB7_T0CCP1					= 7,
	/*********************** PORTC Alternate functions pins  ***********************/
	PC0_TCK_SWCLK				= 1,
	PC0_T4CCP0					= 7,
	PC1_TMS_SWDIO				= 1,
	PC1_T4CCP1					= 7,
	PC2_TDI							= 1,
	PC2_T5CCP0					= 7,
	PC3_TDO_SWO					= 1,
	PC3_T5CCP1					= 7,
	PC4_U4Rx						= 1,
	PC4_U1Rx						= 2,
	PC4_M0PWM6					= 4,
	PC4_IDX1						= 6,
	PC4_WT0CCP0					= 7,
	PC4_U1RTS						= 8,
	PC5_U4Tx						= 1,
	PC5_U1Tx						= 2,
	PC5_M0PWM7					= 4,	
	PC5_PhA1						= 6,
	PC5_WT0CCP1					= 7,
	PC5_U1CTS						= 8,	
	PC6_U3Rx						= 1,
	PC6_PhB1						= 6,
	PC6_WT1CCP0					= 7,	
	PC6_USB0EPEN				= 8,
	PC7_U3Tx						= 1,
	PC7_WT1CCP1					= 7,
	PC7_USB0PFLT				= 8,	
	/*********************** PORTD Alternate functions pins  ***********************/
	PD0_SSI3Clk					= 1,
	PD0_SSI1Clk					= 2,
	PD0_I2C3SCL					= 3,
	PD0_M0PWM6					= 4,
	PD0_M1PWM0					= 5,
	PD0_WT2CCP0					= 7,
	PD1_SSI3Fss					= 1,
	PD1_SSI1Fss					= 2,
	PD1_I2C3SDA					= 3,
	PD1_M0PWM7					= 4,
	PD1_M1PWM1					= 5,
	PD1_WT2CCP1					= 7,
	PD2_SSI3Rx					= 1,
	PD2_SSI1Rx					= 2,
	PD2_M0FAULT0				= 4,	
	PD2_WT3CCP0					= 7,
	PD2_USB0EPEN				= 8,
	PD3_SSI3Tx					= 1,
	PD3_SSI1Tx					= 2,
	PD3_IDX0						= 6,		
	PD3_WT3CCP1					= 7,
	PD3_USB0PFLT				= 8,	
	PD4_U6Rx						= 1,
	PD4_WT4CCP0					= 7,
	PD5_U6Tx						= 1,
	PD5_WT4CCP1					= 7,
	PD6_U2Rx						= 1,
	PD6_M0FAULT0				= 4,
	PD6_PhA0						= 6,
	PD6_WT5CCP0					= 7,
	PD7_U2Tx						= 1,
	PD7_PhB0						= 6,
	PD7_WT5CCP1					= 7,
	PD7_NMI							= 8,
	/*********************** PORTE Alternate functions pins  ***********************/
	PE0_U7Rx						= 1,
	PE1_U7Tx						= 1,
	PE4_U5Rx						= 1,
	PE4_I2C2SCL					= 3,
	PE4_M0PWM4					= 4,	
	PE4_M1PWM2					= 5,
	PE4_CAN0Rx					= 8,
	PE5_U5Tx						= 1,
	PE5_I2C2SDA					= 3,
	PE5_M0PWM5					= 4,	
	PE5_M1PWM3					= 5,
	PE5_CAN0Tx				  = 8,
	/*********************** PORTF Alternate functions pins  ***********************/
	PF0_U1RTS						= 1,
	PF0_SSI1Rx					= 2,
	PF0_CAN0Rx					= 3,					
	PF0_M1PWM4					= 5,
	PF0_PhA0						= 6,	
	PF0_T0CCP0					= 7,	
	PF0_NMI							= 8,
	PF0_C0o							= 9,
	PF1_U1CTS						= 1,
	PF1_SSI1Tx					= 2,
	PF1_M1PWM5					= 5,
	PF1_PhB0						= 6,
	PF1_T0CCP1					= 7,
	PF1_C1o							= 9,
	PF1_TRD1						= 14,
	PF2_SSI1Clk					= 2,	
	PF2_M0FAULT0				= 4,	
	PF2_M1PWM6					= 5,
	PF2_T1CCP0					= 7,
	PF2_TRD0						= 14,
	PF3_SSI1Fss					= 2,
	PF3_CAN0Tx					= 3,
	PF3_M1PWM7					= 5,
	PF3_T1CCP1					= 7,
	PF3_TRCLK						= 14,
	PF4_M1FAULT0				= 5,
	PF4_IDX0						= 6,
	PF4_T2CCP0					= 7,
	PF4_USB0EPEN				= 8
}Port_PinModeType;


typedef enum
{
	INPUT = 0,
	OUTPUT
	
}Port_PinDirectionType;

typedef enum
{
	PULL_UP,
	PULL_DOWN,
	OPEN_DRAIN
}Port_PinAttachType;

typedef enum 
{
	R2R,
	R4R,
	R8R
}Port_PinOutputCurrentType;

typedef enum 
{
	EDGE_SENSITIVE = 0,
	LEVEL_SENSETIVE
}GPIO_InterruptSense_Type;

typedef enum 
{
	EDGE_CONTROLLED = 0,
	BOTH_EDGES
}GPIO_InterruptBothEdges_Type;
typedef enum 
{
	FALLING_LOW = 0,
	RISING_HIGH
}GPIO_InterruptEvent_Type;

typedef struct 
{
	GPIO_Type *GPIOx; 
	DIO_ChannelType ChannelId;
	GPIO_InterruptSense_Type interruptSense;
	GPIO_InterruptBothEdges_Type interruptBothEdges;
	GPIO_InterruptEvent_Type interruptEvent ;
	IRQn_Type interruptIRQn;
	
}GPIO_EXTI_ConfigType;
	

typedef struct 
{
	GPIO_Type *GPIOx; 														// select the port registers
	DIO_PortType PortType; 												//enum for port name
	DIO_ChannelType ChannelId; 										// select the channel of the port
	Port_PinModeType PinMode; 										// select the type of the pin in the case of alternate function
	DIO_LevelType PortPinLevelValue; 							// select the initial value of the pin
	Port_PinDirectionType PortPinDirection; 			// select the mode of the pin if it out or in
	Port_PinAttachType PortPinInternalAttach; 		// select if it pull up or down or open drain
	Port_PinOutputCurrentType  PinOutputCurrent; 	// select the current of the pin in case output

}Port_ConfigType;
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr); 
void Port_EXTI_Init(const GPIO_EXTI_ConfigType *ConfigPtr);
#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
