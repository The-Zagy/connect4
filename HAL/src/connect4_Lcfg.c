#include "../MCAL/PORT/Inc/Port_Cfg.h"

Port_ConfigType Move_Right_Button =
	{
		GPIOF,
		PORTF,
		PF1,
		DIGITAL_PIN,
		HIGH,
		INPUT,
		PULL_UP,
		R4R};

// uncomment for dev
// Port_ConfigType Move_Right_Button =
// 	{
// 		GPIOF,
// 		PORTF,
// 		PF0,
// 		DIGITAL_PIN,
// 		HIGH,
// 		INPUT,
// 		PULL_UP,
// 		R4R
// };

GPIO_EXTI_ConfigType EXTI_Right_Button =
	{
		GPIOF,
		PF1,
		EDGE_SENSITIVE,
		EDGE_CONTROLLED,
		FALLING_LOW,
		GPIO_PortF_IRQn};

// uncomment for dev
// GPIO_EXTI_ConfigType EXTI_Right_Button =
// 	{
// 		GPIOF,
// 		PF0,
// 		EDGE_SENSITIVE,
// 		EDGE_CONTROLLED,
// 		FALLING_LOW,
// 		GPIO_PortF_IRQn};

Port_ConfigType Action_Button =
	{
		GPIOD,
		PORTD,
		PD1,
		DIGITAL_PIN,
		HIGH,
		INPUT,
		PULL_UP,
		R4R};

// uncomment for dev
// Port_ConfigType Action_Button =
// 	{
// 		GPIOF,
// 		PORTF,
// 		PF4,
// 		DIGITAL_PIN,
// 		HIGH,
// 		INPUT,
// 		PULL_UP,
// 		R4R
// };

GPIO_EXTI_ConfigType EXTI_Action_Button =
	{
		GPIOD,
		PD1,
		EDGE_SENSITIVE,
		EDGE_CONTROLLED,
		FALLING_LOW,
		GPIO_PortD_IRQn};

// uncomment for dev
// GPIO_EXTI_ConfigType EXTI_Action_Button =
// 	{
// 		GPIOF,
// 		PF4,
// 		EDGE_SENSITIVE,
// 		EDGE_CONTROLLED,
// 		FALLING_LOW,
// 		GPIO_PortF_IRQn};

Port_ConfigType Move_Left_Button =
	{
		GPIOD,
		PORTD,
		PD0,
		DIGITAL_PIN,
		HIGH,
		INPUT,
		PULL_UP,
		R4R

};
GPIO_EXTI_ConfigType EXTI_Left_Button =
	{
		GPIOD,
		PD0,
		EDGE_SENSITIVE,
		EDGE_CONTROLLED,
		FALLING_LOW,
		GPIO_PortD_IRQn};
