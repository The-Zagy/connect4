/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Mcu_Hw.h
 *       Module:  Mcu_Hw
 *
 *  Description:  header file for Registers definition    
 *  
 *********************************************************************************************************************/
#ifndef MCU_HW_H
#define MCU_HW_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../LIBRARIES/common/Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/



/*********************** Register map for GPIO ***********************/
typedef struct
{
	
	
	volatile const uint32_t 	RESERVED[255];
	volatile uint32_t 				GPIODATA;
	volatile uint32_t 				GPIODIR;
	volatile uint32_t 				GPIOIS;
	volatile uint32_t 				GPIOIBE;
	volatile uint32_t 				GPIOIEV;
	volatile uint32_t 				GPIOIM;
	volatile uint32_t 				GPIORIS;
	volatile uint32_t 				GPIOMIS;
	volatile uint32_t 				GPIOICR;
	volatile uint32_t 				GPIOAFSEL;
	volatile const uint32_t 	RESERVED1[55];
	volatile uint32_t 				GPIODR2R;
	volatile uint32_t 				GPIOR4R;
	volatile uint32_t 				GPIOR8R;
	volatile uint32_t 				GPIOODR;
	volatile uint32_t 				GPIOPUR;
	volatile uint32_t 				GPIOPDR;
	volatile uint32_t 				GPIOSLR;
	volatile uint32_t 				GPIODEN;
	volatile uint32_t 				GPIOLOCK;
	volatile uint32_t 				GPIOCR;
	volatile uint32_t 				GPIOAMSEL;
	volatile uint32_t 				GPIOPCTL;
	volatile uint32_t 				GPIOADCCTL;
	volatile uint32_t 				GPIOADMACTL;
}GPIO_Type;

/*********************** Register map for WarchDog Timer ***********************/

typedef struct
{
	volatile uint32_t WDTLOAD;
	volatile uint32_t WDTVALUE;
	volatile uint32_t WDTCTL;
	volatile uint32_t WDTICR;
	volatile uint32_t WDTRIS;
	volatile uint32_t WDTMIS;
	volatile const uint32_t RESERVED[256];
	volatile uint32_t WDTTEST;
	volatile const uint32_t RESERVED1[505];
	volatile uint32_t WDTLOCK;

}WDT_Type;

/*********************** Register map for System Control ***********************/

typedef struct
{
	volatile uint32_t 				DID0;
	volatile uint32_t 				DID1;
	volatile uint32_t 				DC0;
	volatile uint32_t 				DC1;
	volatile uint32_t 				DC2;
	volatile uint32_t 				DC3;
	volatile uint32_t 				DC4;
	volatile uint32_t 				DC5;
	volatile uint32_t 				DC6;
	volatile uint32_t 				DC7;
	volatile uint32_t 				DC8;
	volatile uint32_t 				PDORCTL;
	volatile const uint32_t 	RESERVED[3];
	volatile uint32_t 				SRCR0;
	volatile uint32_t 				SRCR1;
	volatile uint32_t 				SRCR2;
	volatile const uint32_t 	RESERVED1;
	volatile uint32_t 				RIS;
	volatile uint32_t 				IMC;
	volatile uint32_t 				MISC;
	volatile uint32_t 				RESC;
	volatile uint32_t 				RCC;
	volatile const uint32_t 	RESERVED2[2];
	volatile uint32_t 				GPIOHBCTL;
	volatile uint32_t 				RCC2;
	volatile const uint32_t 	RESERVED3[2];
	volatile uint32_t 				MOSCCTL;
	volatile const uint32_t 	RESERVED4[32];
	volatile uint32_t 				RCGC0;
	volatile uint32_t 				RCGC1;
	volatile uint32_t 				RCGC2;
	volatile const uint32_t 	RESERVED5;
	volatile uint32_t 				SCGC0;
	volatile uint32_t 				SCGC1;
	volatile uint32_t 				SCGC2;
	volatile const uint32_t 	RESERVED6;
	volatile uint32_t 				DCGC0;
	volatile uint32_t 				DCGC1;
	volatile uint32_t 				DCGC2;
	volatile const uint32_t 	RESERVED7[6];
	volatile uint32_t 				DSLPCLKCFG;
	volatile const uint32_t 	RESERVED8;			
	volatile uint32_t 				SYSPROP;		
	volatile uint32_t 				PIOSCCAL;
	volatile uint32_t 				PIOSCSTAT;
	volatile const uint32_t 	RESERVED9[2];			
	volatile uint32_t 				PLLFREQ0;
	volatile uint32_t 				PLLFREQ1;
	volatile uint32_t 				PLLSTAT;
	volatile const uint32_t 	RESERVED10[7];			
	volatile uint32_t 				SLPPWRCFG;
	volatile uint32_t 				DSLPPWRCFG;
	volatile const uint32_t 	RESERVED11;	
	volatile uint32_t 				DC9;
  volatile const uint32_t 	RESERVED12[3];
	volatile uint32_t 				NVMSTAT;
	volatile const uint32_t 	RESERVED13[4];				
	volatile uint32_t 				LDOSPCTL;
	volatile const uint32_t 	RESERVED14;
	volatile uint32_t 				LDODPCTL;
	volatile const uint32_t 	RESERVED15[80];
	volatile uint32_t 				PPWD;
	volatile uint32_t 				PPTIMER;
	volatile uint32_t 				PPGPIO;
	volatile uint32_t 				PPDMA;
	volatile const uint32_t 	RESERVED16;
	volatile uint32_t 				PPHIB;
	volatile uint32_t 				PPUART;
	volatile uint32_t 				PPSSI;
	volatile uint32_t 				PPI2C;
	volatile const uint32_t 	RESERVED17;
	volatile uint32_t 				PPUSB;
	volatile const uint32_t 	RESERVED18[2];
	volatile uint32_t 				PPCAN;
	volatile uint32_t 				PPADC;
	volatile uint32_t 				PPACMP;
	volatile uint32_t 				PPPWM;
	volatile uint32_t 				PPQEI;
	volatile const uint32_t 	RESERVED19[4]; 				
	volatile uint32_t 				PPEEPROM;
	volatile uint32_t 				PPWTIMER;
	volatile const uint32_t 	RESERVED20[104];
	volatile uint32_t 				SRWD;
	volatile uint32_t 				SRTIMER;
	volatile uint32_t 				SRGPIO;
	volatile uint32_t 				SRDMA;
	volatile const uint32_t 	RESERVED21;
	volatile uint32_t 				SRHIB;
	volatile uint32_t 				SRUART;
	volatile uint32_t 				SRSSI;	
	volatile uint32_t 				SRI2C;
	volatile const uint32_t 	RESERVED22;
	volatile uint32_t 				SRUSB;
	volatile const uint32_t 	RESERVED23[2];
	volatile uint32_t 				SRCAN;
	volatile uint32_t 				SRADC;
	volatile uint32_t 				SRACMP;
	volatile uint32_t 				SRPWM;
	volatile uint32_t 				SRQEI;
	volatile const uint32_t 	RESERVED24[4];
	volatile uint32_t 				SREEPROM;
	volatile uint32_t 				SRWTIMER;
	volatile const uint32_t 	RESERVED25[40];
	volatile uint32_t 				RCGCWD;
	volatile uint32_t 				RCGCTIMER;
	volatile uint32_t 				RCGCGPIO;
	volatile uint32_t 				RCGCDMA;
	volatile const uint32_t 	RESERVED26;
	volatile uint32_t 				RCGCHIB;
	volatile uint32_t 				RCGCUART;
	volatile uint32_t 				RCGCSSI;
	volatile uint32_t 				RCGCI2C;
	volatile const uint32_t 	RESERVED27;
	volatile uint32_t 				RCGCUSB;
	volatile const uint32_t 	RESERVED28[2];
	volatile uint32_t 				RCGCCAN;
	volatile uint32_t 				RCGCADC;
	volatile uint32_t 				RCGCACMP;
	volatile uint32_t 				RCGCPWM;
	volatile uint32_t 				RCGCQEI;
	volatile const uint32_t 	RESERVED29[4];
	volatile uint32_t 				RCGCEEPROM;
	volatile uint32_t 				RCGCWTIMER;
	volatile const uint32_t 	RESERVED30[40];
	volatile uint32_t 				SCGCWD;
	volatile uint32_t 				SCGCTIMER;
	volatile uint32_t 				SCGCGPIO;
	volatile uint32_t 				SCGCDMA;
	volatile const uint32_t 	RESERVED31;
	volatile uint32_t 				SCGCHIB;	
	volatile uint32_t 				SCGCUART;
	volatile uint32_t 				SCGCSSI;
	volatile uint32_t 				SCGCI2C;
	volatile const uint32_t 	RESERVED32;
	volatile uint32_t 				SCGCUSB;
	volatile const uint32_t 	RESERVED33[2];
	volatile uint32_t 				SCGCCAN;
	volatile uint32_t 				SCGCADC;
	volatile uint32_t 				SCGCACMP;
	volatile uint32_t 				SCGCPWM;
	volatile uint32_t 				SCGCQEI;
	volatile const uint32_t 	RESERVED34[4];
	volatile uint32_t 				SCGCEEPROM;
	volatile uint32_t 				SCGCWTIMER;
	volatile const uint32_t 	RESERVED35[40];
	volatile uint32_t 				DCGCWD;
	volatile uint32_t 				DCGCTIMER;
	volatile uint32_t 				DCGCGPIO;
	volatile uint32_t 				DCGCDMA;
	volatile const uint32_t 	RESERVED36;
	volatile uint32_t 				DCGCHIB;
	volatile uint32_t 				DCGCUART;
	volatile uint32_t 				DCGCSSI;
	volatile uint32_t 				DCGCI2C;
	volatile const uint32_t 	RESERVED37;
	volatile uint32_t 				DCGCUSB;
	volatile const uint32_t 	RESERVED38[2];
	volatile uint32_t 				DCGCCAN;
	volatile uint32_t 				DCGCADC;
	volatile uint32_t 				DCGCACMP;
	volatile uint32_t 				DCGCPWM;
	volatile uint32_t 				DCGCQEI;
	volatile const uint32_t 	RESERVED39[4];
	volatile uint32_t 				DCGCEEPROM;
	volatile uint32_t 				DCGCWTIMER;
	volatile const uint32_t 	RESERVED40[104];
	volatile uint32_t 				PRWD;
	volatile uint32_t 				PRTIMER;
	volatile uint32_t 				PRGPIO;
	volatile uint32_t 				PRDMA;
	volatile const uint32_t 	RESERVED41;	
	volatile uint32_t 				PRHIB;
	volatile uint32_t 				PRUART;
	volatile uint32_t 				PRSSI;
	volatile uint32_t 				PRI2C;
	volatile const uint32_t 	RESERVED42;	
	volatile uint32_t 				PRUSB;
	volatile const uint32_t 	RESERVED43[2];	
	volatile uint32_t 				PRCAN;
	volatile uint32_t 				PRADC;
	volatile uint32_t 				PRACMP;
	volatile uint32_t 				PRPWM;
	volatile uint32_t 				PRQEI;
	volatile const uint32_t 	RESERVED44[4];
	volatile uint32_t 				PREEPROM;
	volatile uint32_t 				PRWTIMER;
}SYSCTRL_Type;

typedef struct 
{
	volatile uint32_t 							STCTRL;
	volatile uint32_t 							STRELOAD;
	volatile uint32_t 							STCURRENT;		
}SYSTICK_Type;



/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define CORTEXM4_PERI_BASE_ADDRESS             	0xE000E000
#define GPIO_LOCKKEY														0x4C4F434B
#define GPIO_UNLOCKKEY													0x4C4F0000


/*********************** Peripheral memory map ***********************/
#define PERIPH_BIT_BAND_ALIAS				0x42000000UL
#define PERIPH_BIT_BAND_REGION			0x40000000UL
#define SRAM_BIT_BAND_ALIAS					0x22000000UL
#define SRAM_BIT_BAND_REGION				0x20000000UL

#define WDT0_BASE										0x40000000UL
#define WDT1_BASE										0x40001000UL
#define SYSTEM_CONTROL_BASE					0x400FE000UL
#define GPIOA_BASE							   	0x40004000UL
#define GPIOA_BASE_AHB						 	0x40058000UL
#define GPIOB_BASE							   	0x40005000UL
#define GPIOB_BASE_AHB							0x40059000UL
#define GPIOC_BASE							  	0x40006000UL
#define GPIOC_BASE_AHB							0x4005A000UL
#define GPIOD_BASE							   	0x40007000UL
#define GPIOD_BASE_AHB						  0x4005B000UL
#define GPIOE_BASE							   	0x40024000UL
#define GPIOE_BASE_AHB							0x4005C000UL
#define GPIOF_BASE							  	0x40025000UL
#define GPIOF_BASE_AHB							0x4005D000UL


#define NVIC_BASE										( CORTEXM4_PERI_BASE_ADDRESS + 0x0100UL )
#define SCB_BASE										( CORTEXM4_PERI_BASE_ADDRESS + 0x0D00UL )
#define SYSTICK_BASE								( CORTEXM4_PERI_BASE_ADDRESS + 0x0010UL )


/*********************** Peripheral Declaration ***********************/

#define GPIOA									((GPIO_Type				*)	GPIOA_BASE)
#define GPIOA_AHB							((GPIO_Type				*)	GPIOA_BASE_AHB)
#define GPIOB									((GPIO_Type				*)	GPIOB_BASE)
#define GPIOB_AHB							((GPIO_Type				*)	GPIOB_BASE_AHB)
#define GPIOC									((GPIO_Type				*)	GPIOC_BASE)
#define GPIOC_AHB							((GPIO_Type				*)	GPIOC_BASE_AHB)
#define GPIOD									((GPIO_Type				*)	GPIOD_BASE)
#define GPIOD_AHB							((GPIO_Type				*)	GPIOD_BASE_AHB)
#define GPIOE									((GPIO_Type				*)	GPIOE_BASE)
#define GPIOE_AHB							((GPIO_Type				*)	GPIOE_BASE_AHB)
#define GPIOF									((GPIO_Type				*)	GPIOF_BASE)
#define GPIOF_AHB							((GPIO_Type				*)	GPIOF_BASE_AHB)

#define WDT0 									((WDT_Type 				*)	WDT0_BASE)
#define WDT1 									((WDT_Type 				*)	WDT1_BASE)

#define SYSCTRL               ((SYSCTRL_Type		*)  SYSTEM_CONTROL_BASE)

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

#define SYSTICK								((SYSTICK_Type		*)	SYSTICK_BASE)
#define NVIC									((NVIC_Type				*) 	NVIC_BASE)
#define SCB										((SCB_Type				*)	SCB_BASE)


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 

 
#endif  /* MCU_HW_H */

/**********************************************************************************************************************
 *  END OF FILE: Mcu_Hw.h
 *********************************************************************************************************************/
