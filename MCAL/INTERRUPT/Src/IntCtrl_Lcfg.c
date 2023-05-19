#include "../LIBRARIES/common/Std_Types.h"
#include "../MCAL/INTERRUPT/Inc/IntCtrl_Cfg.h"

IntCtr_Config Int_Right_Button =
	{
		GPIO_PortF_IRQn, 0x04, 1, 0};
IntCtr_Config Int_Left_Button =
	{
		GPIO_PortF_IRQn, 0x04, 2, 0};

IntCtr_Config Int_Action_Button =
	{
		GPIO_PortD_IRQn, 0x04, 3, 0};
