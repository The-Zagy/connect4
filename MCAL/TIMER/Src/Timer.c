#include "Std_Types.h"
#include "Timer_Cfg.h"
#include "Mcu_Hw.h"
#include "Bit_Math.h"
#include "Timer.h"

void Gpt_Init(const Gpt_ConfigType *ConfigPtr)
{

	CLEAR_BIT_PERIPH_BAND(ConfigPtr->TIMERx->GPTMCTL, 0);
	switch (ConfigPtr->GptChannelMode)
	{
	case GPT_CH_MODE_CONTINUOUS:
		SET_BIT_PERIPH_BAND(ConfigPtr->TIMERx->GPTMTAMR, 1);
		break;
	case GPT_CH_MODE_ONESHOT:
		SET_BIT_PERIPH_BAND(ConfigPtr->TIMERx->GPTMTAMR, 0);
		break;
	}
	switch (ConfigPtr->GptChannelCount)
	{
	case COUNT_UP:
		SET_BIT_PERIPH_BAND(ConfigPtr->TIMERx->GPTMTAMR, 4);
		break;
	case COUNT_DOWN:
		CLEAR_BIT_PERIPH_BAND(ConfigPtr->TIMERx->GPTMTAMR, 4);
		break;
	}
}
void Gpt_Predefined_Timer_1US_16Bit(void)
{
	CLEAR_BIT_PERIPH_BAND(TIMER0->GPTMCTL, 0);
}
