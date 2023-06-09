/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <CPU_DRIVER_H>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef CPU_DRIVER_H
#define CPU_DRIVER_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


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
void cpuDriver_EnableGlobalInterrupt(void);
void cpuDriver_DisableGlobalInterrupt(void);
void cpuDriver_EnablePriviledgeMode(void);
void cpuDriver_DisablePriviledgeMode(void);

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* CPU_DRIVER_H */

/**********************************************************************************************************************
 *  END OF FILE: cpu_driver.h
 *********************************************************************************************************************/
