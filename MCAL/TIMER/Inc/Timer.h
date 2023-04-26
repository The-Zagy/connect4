/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <Write File Name>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef TIMER_H
#define TIMER_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/*********************** Register map for General Purpose Timers ***********************/

typedef struct 
{
	volatile uint32_t					GPTMCFG; 
	volatile uint32_t					GPTMTAMR;
	volatile uint32_t					GPTMTBMR;
	volatile uint32_t					GPTMCTL;
	volatile uint32_t					GPTMSYNC;
	volatile const uint32_t		RESERVED;
	volatile uint32_t					GPTMIMR;
	volatile uint32_t					GPTMRIS;
	volatile uint32_t					GPTMMIS;
	volatile uint32_t					GPTMICR;
	volatile uint32_t					GPTMTAILR;
	volatile uint32_t					GPTMTBILR;
	volatile uint32_t					GPTMTAMATCHR;
	volatile uint32_t					GPTMTBMATCHR;
	volatile uint32_t					GPTMTAPR;
	volatile uint32_t					GPTMTBPR;
	volatile uint32_t					GPTMTAPMR;
	volatile uint32_t					GPTMTBPMR;
	volatile uint32_t					GPTMTAR;
	volatile uint32_t					GPTMTBR;
	volatile uint32_t					GPTMTAV;
	volatile uint32_t					GPTMTBV;
	volatile uint32_t					GPTMRTCPD;
	volatile uint32_t					GPTMTAPS;
	volatile uint32_t					GPTMTBPS;
	volatile uint32_t					GPTMTAPV;
	volatile uint32_t					GPTMTBPV;
	volatile const uint32_t		RESERVED1[981];			
	volatile uint32_t					GPTMPP;
	
}TIMER_Type;


#define GPTIMER0_BASE								0x40030000UL
#define GPTIMER1_BASE								0x40031000UL
#define GPTIMER2_BASE								0x40032000UL
#define GPTIMER3_BASE								0x40033000UL
#define GPTIMER4_BASE								0x40034000UL
#define GPTIMER5_BASE								0x40035000UL

#define GPWTIMER0_BASE							0x40036000UL
#define GPWTIMER1_BASE							0x40037000UL
#define GPWTIMER2_BASE							0x4004C000UL
#define GPWTIMER3_BASE							0x4004D000UL
#define GPWTIMER4_BASE							0x4004E000UL
#define GPWTIMER5_BASE							0x4004F000UL


#define TIMER0								((TIMER_Type 			*)  GPTIMER0_BASE)
#define TIMER1								((TIMER_Type 			*)  GPTIMER1_BASE)
#define TIMER2								((TIMER_Type 			*)  GPTIMER2_BASE)
#define TIMER3								((TIMER_Type 			*)  GPTIMER3_BASE)
#define TIMER4								((TIMER_Type 			*)  GPTIMER4_BASE)
#define TIMER5								((TIMER_Type 			*)  GPTIMER5_BASE)

#define WTIMER0								((TIMER_Type 			*)  GPWTIMER0_BASE)
#define WTIMER1								((TIMER_Type 			*)  GPWTIMER1_BASE)
#define WTIMER2								((TIMER_Type 			*)  GPWTIMER2_BASE)
#define WTIMER3								((TIMER_Type 			*)  GPWTIMER3_BASE)
#define WTIMER4								((TIMER_Type 			*)  GPWTIMER4_BASE)
#define WTIMER5								((TIMER_Type 			*)  GPWTIMER5_BASE)
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/











