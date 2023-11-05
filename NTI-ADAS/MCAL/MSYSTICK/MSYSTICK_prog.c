/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MSYSTICK_prog.c
 *         @Module	:  SYSTICK
 *
 *  Description:  This file provide Module APIs code Implementation
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "REGISTERS.h"
#include "ERROR_STATE.h"
#include "MRCC_int.h"
#include "MSYSTICK_config.h"
#include "MSYSTICK_int.h"
#include "MSYSTICK_priv.h"

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
static void (*MSYSTICK_Callback)(void) = NULL;
static u8 global_u8flag = 0;

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
volatile u8 local_u8temp;

/******************************************************************************
 * \Syntax          : ErrorState_t MSYSTICK_enInit(void)
 *
 * \Description     : This Services for configure the Systick Prescalear
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 *******************************************************************************/
ErrorState_t MSYSTICK_enInit(void)
{
	/*@beief 	that API use to pre configure the systick Prescaler */
#if (MSYSTICK_PRESCALER == MSYSTICK_AHB_PRESCALER)
	SET_BIT(STK->STK_CTRL, CLKSOURCE);

#elif(MSYSTICK_PRESCALER == MSYSTICK_AHB_DIV8_PRESCALER)
	CLR_BIT(STK->STK_CTRL, CLKSOURCE);

#else
#error ("YOU SELECTED THE WRONG PRESCALER");
#endif

	return SUCCESS;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MSYSTICK_enDelayMS(u32 copy_u16delayMS)
 *
 * \Description     : This Services for setting the H.W delay in microSec
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_u32NumberOfTicks
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 *******************************************************************************/
ErrorState_t MSYSTICK_enSetBusyWait(u32 Copy_u32NumberOfTicks)
{
	/* @berif 	This API use to set delay based on millsec num
	 * 1. load the no.of tick into the load register
	 * 2. enable the systick
	 * 3. wait of the count flag if set, then register is zero
	 * 4. disable the systick
	 * 5. clear the value register to be reuse again */
	STK->STK_LOAD = Copy_u32NumberOfTicks;
	SET_BIT(STK->STK_CTRL, ENABLE);

	while (!(GET_BIT(STK->STK_CTRL,COUNTFLAG)));
	CLR_BIT(STK->STK_CTRL, ENABLE);

	STK->STK_VAL = MSYSTICK_REG_CLEAR;

	return SUCCESS;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MSYSTICK_enDelayMS(u16 copy_u16delayMS)
 *
 * \Description     : This Services for setting the H.W delay in millsec
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u16delayMS
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 *******************************************************************************/
ErrorState_t MSYSTICK_enDelayMS(u16 copy_u16delayMS)
{
	/* @berif 	This API use to set delay based on millsec num
	 * 1. load the no.of tick multiplyed by 1000 (from micro to milli)
	 * 2. enable the systick
	 * 3. wait of the count flag if set, then register is zero
	 * 4. disable the systick
	 * 5. clear the value register to be reuse again */

	STK->STK_LOAD = copy_u16delayMS * 1000;
	SET_BIT(STK->STK_CTRL, ENABLE);

	while (!(GET_BIT(STK->STK_CTRL, COUNTFLAG)));

	CLR_BIT(STK->STK_CTRL, ENABLE);
	STK->STK_VAL = MSYSTICK_REG_CLEAR;

	return SUCCESS;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MSYSTICK_enSetIntervalSingle
 * 								(u32 copy_u32TicksNum,void(*ptrfn)(void))
 *
 * \Description     : This Services for setting the H.W us_delay Once
 *
 * \Sync\Async      : ASynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u32TicksNum, void(*ptrfn)(void)
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> NULL_PTR_ERR
 *******************************************************************************/
ErrorState_t MSYSTICK_enSetIntervalSingle(u32 copy_u32TicksNum,void(*ptrfn)(void))
{
	/*@berif	This API for setting the H.w us_delay with no.of Ticks ONCE
	 * 1. assign ptr to function to the callback function
	 * 2. set a global flag with 1
	 * 3. load the no.of ticks in the load register
	 * 4. enable the systick and the TickInterrupt
	 * 5. Jump on the Handlear and if the flag was set to 1
	 * 6. disable the interrupt and the system
	 * 7. clear the value register with 0
	 * 8. clear the systick interrupt by reading the flag 	*/

	ErrorState_t local_state = SUCCESS;
	if (ptrfn == NULL)
	{
		local_state = NULL_PTR_ERR;
	}
	else
	{
		MSYSTICK_Callback = ptrfn;
		global_u8flag = 1;
		STK->STK_LOAD = copy_u32TicksNum;
		SET_BIT(STK->STK_CTRL, ENABLE);
		SET_BIT(STK->STK_CTRL, TICKINT);
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MSYSTICK_enSetIntervalPeriodic
 * 								(u32 copy_u32TicksNum,void(*ptrfn)(void))
 *
 * \Description     : This Services for setting the H.W us_delay periodically
 *
 * \Sync\Async      : ASynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u32TicksNum, void(*ptrfn)(void)
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> NULL_PTR_ERR
 *******************************************************************************/
ErrorState_t MSYSTICK_enSetIntervalPeriodic(u32 copy_u32TicksNum,void(*ptrfn)(void))
{
	/*@berif	This API for setting the H.w us_delay with no.of Ticks ONCE
	 * 1. assign ptr to function to the callback function
	 * 2. clear a global flag with 0
	 * 3. load the no.of ticks in the load register
	 * 4. enable the systick and the TickInterrupt
	 * 5. Jump on the Handlear and if the flag not set by 1
	 * 6. clear the systick interrupt by reading the flag	*/

	ErrorState_t local_state = SUCCESS;
	if (ptrfn == NULL)
	{
		local_state = NULL_PTR_ERR;
	}
	else
	{
		MSYSTICK_Callback = ptrfn;
		global_u8flag = 0;
		STK->STK_LOAD = copy_u32TicksNum;
		SET_BIT(STK->STK_CTRL, ENABLE);
		SET_BIT(STK->STK_CTRL, TICKINT);
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MSYSTICK_enGetElapsedTime
 * 								(u32 *copy_u32ElapsedValue)
 *
 * \Description     : This Services for getting the ticks which been counted down
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : *copy_u32ElapsedValue
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> NULL_PTR_ERR
 *******************************************************************************/
ErrorState_t MSYSTICK_enGetElapsedTime(u32 *copy_u32ElapsedValue)
{
	/*@brief	This API use to get the elapsed time of the counter by subtracting
	 * the value of registerLoad and registerValue and returned by reference with ptr*/

	ErrorState_t local_state = SUCCESS;
	if (copy_u32ElapsedValue == NULL)
	{
		local_state = NULL_PTR_ERR;
	}
	else
	{
		*copy_u32ElapsedValue = STK->STK_LOAD - STK->STK_VAL;
	}

	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MSYSTICK_enRemainingValue
 * 								(u32 *copy_u32RemainingValue)
 *
 * \Description     : This Services for getting the remaining ticks of the register
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : *copy_u32RemainingValue
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> NULL_PTR_ERR
 *******************************************************************************/
ErrorState_t MSYSTICK_enRemainingValue(u32 *copy_u32RemainingValue)
{
	/*@brief	This API use to get the remaining value of the value register
	 * 			and returned by reference with pointer	*/

	ErrorState_t local_state = SUCCESS;
	if (copy_u32RemainingValue == NULL)
	{
		local_state = NULL_PTR_ERR;
	}
	else
	{
		*copy_u32RemainingValue = STK->STK_VAL;
	}

	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MSYSTICK_enStop(void)
 *
 * \Description     : This Services for stopping the systick
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 *******************************************************************************/
ErrorState_t MSYSTICK_enStop(void)
{
	/*	@brief This API use to stop the systick
	 * 1. Disable the Tick INT \
	 * 2. Disable the systick
	 * 3. clear the load and value register */

	CLR_BIT(STK->STK_CTRL, TICKINT);
	CLR_BIT(STK->STK_CTRL, ENABLE);
	STK->STK_VAL = MSYSTICK_REG_CLEAR;
	STK->STK_LOAD = MSYSTICK_REG_CLEAR;

	return SUCCESS;
}



/**********************************************************************************************************************
 * HANDLER
 *********************************************************************************************************************/
void SysTick_Handler(void)
{
	/*@brief	The systick handler use to run the counter interval or periodically
	 * 1. clear the temp var to ba able to set the INT flag by reading it
	 * 2. disable the TICK INT
	 * 3. disable the systick
	 * 4. clear the value register
	 * 5. call the APP call back function from MCAL Layer */
	local_u8temp = 0;
	if (global_u8flag == 1)
	{
		CLR_BIT(STK->STK_CTRL, TICKINT);
		CLR_BIT(STK->STK_CTRL, ENABLE);
		STK->STK_VAL = MSYSTICK_REG_CLEAR;
	}

	if (MSYSTICK_Callback != NULL)
	{
		MSYSTICK_Callback();
	}

	local_u8temp = GET_BIT(STK->STK_CTRL,COUNTFLAG);
}

/**********************************************************************************************************************
 *  END OF FILE: MSYSTICK_prog.c
 *********************************************************************************************************************/
