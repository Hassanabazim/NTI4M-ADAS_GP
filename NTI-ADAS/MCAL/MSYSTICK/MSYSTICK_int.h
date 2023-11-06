/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MSYSTICK_int.h
 *         @Module	:  SYSTICK
 *
 *  Description:  This file Provide the Module APIs and Interfacing MACROS and Data types
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  HEADER GUARD
 *********************************************************************************************************************/

#ifndef SYSTICK_SYSTICK_INT_H_
#define SYSTICK_SYSTICK_INT_H_

#include "ERROR_STATE.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
ErrorState_t MSYSTICK_enInit(void);
ErrorState_t MSYSTICK_enDelayMS(u16 copy_u16delayMS);
ErrorState_t MSYSTICK_enSetBusyWait(u32 Copy_u32NumberOfTicks);
ErrorState_t MSYSTICK_enSetIntervalSingle(u32 copy_u32TicksNum,void(*ptrfn)(void));
ErrorState_t MSYSTICK_enSetIntervalPeriodic(u32 copy_u32TicksNum,void(*ptrfn)(void));
ErrorState_t MSYSTICK_enGetElapsedTime(u32 *copy_u32ElapsedValue);
ErrorState_t MSYSTICK_enRemainingValue(u32 *copy_u32RemainingValue);
ErrorState_t MSYSTICK_enStop(void);


#endif /* SYSTICK_SYSTICK_INT_H_ */
/**********************************************************************************************************************
 *  END OF FILE:   MSYSTICK_int.h
 *********************************************************************************************************************/

