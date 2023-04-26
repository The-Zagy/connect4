/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  BIT_MATH_H
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../LIBRARIES/common/Std_Types.h"
#include "../LIBRARIES/common/Platform_Types.h"
#include "../LIBRARIES/common/Mcu_Hw.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define SET_BIT(REGISTER,PIN)							(REGISTER |= (1 << PIN))

#define CLEAR_BIT(REGISTER,PIN)						(REGISTER &= ~(1 << PIN))

#define GET_BIT(REGISTER,PIN)							((REGISTER >> PIN)& (1))

#define TOGGLE_BIT(REGISTER,PIN)					(REGISTER ^= (1 << PIN))


#define SET_BIT_PERIPH_BAND(REG,PIN)										((*(volatile uint32_t *)(PERIPH_BIT_BAND_ALIAS + ((uint32_t)(&REG) - PERIPH_BIT_BAND_REGION ) * 32 + PIN *4  )) = STD_HIGH )
#define CLEAR_BIT_PERIPH_BAND(REG,PIN)									((*(volatile uint32_t *)(PERIPH_BIT_BAND_ALIAS + ((uint32_t)(&REG) - PERIPH_BIT_BAND_REGION ) * 32 + PIN *4  )) = STD_LOW )	

#define SET_BIT_PERIPH_BAND_VAL(REG,VALUE)							((*(volatile uint32_t *)(((uint32_t)(&REG)))) = VALUE )

#define SET_BIT_PERIPH_BAND_DATA(REG,PIN)								((*(volatile uint32_t *)(PERIPH_BIT_BAND_ALIAS + ((uint32_t)(&REG) - PERIPH_BIT_BAND_REGION + 0x3FC) * 32 + PIN *4  )) = STD_HIGH )
#define CLEAR_BIT_PERIPH_BAND_DATA(REG,PIN)							((*(volatile uint32_t *)(PERIPH_BIT_BAND_ALIAS + ((uint32_t)(&REG) - PERIPH_BIT_BAND_REGION + 0x3FC) * 32 + PIN *4  )) = STD_HIGH )
#define TOGGLE_BIT_PERIPH_BAND_DATA(REG,PIN)						(~(*(volatile uint32_t *)(PERIPH_BIT_BAND_ALIAS + ((uint32_t)(&REG) - PERIPH_BIT_BAND_REGION + 0x3FC) * 32 + PIN *4  )))	

#define WRITE_BIT_PERIPH_BAND_DATA_VAL(REG,VALUE)				((*(volatile uint32_t *)(((uint32_t)(&REG) + 0x3FC))) = VALUE )

#define SET_BIT_SRAM_BAND(REG,PIN)				((*(volatile uint32_t *)(SRAM_BIT_BAND_ALIAS + ((uint32_t)(&REG) - SRAM_BIT_BAND_REGION ) * 32 + PIN *4  )) = STD_HIGH )
#define CLEAR_BIT_SRAM_BAND(REG,PIN)			((*(volatile uint32_t *)(SRAM_BIT_BAND_ALIAS + ((uint32_t)(&REG) - SRAM_BIT_BAND_REGION ) * 32 + PIN *4  )) = STD_LOW )	

//bit_word_addr = bit_band_base + bit_word_offset

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
