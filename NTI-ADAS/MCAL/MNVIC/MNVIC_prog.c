/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MNVIC.c
 *         @Module	:  NVIC
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
#include "MNVIC_int.h"
#include "MNVIC_config.h"
#include "MNVIC_priv.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : ErrorState_t MNVIC_enEnableNVIC(void)
 *
 * \Description     : This Services for Set up the Pritiries Group and Sub-group
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 *******************************************************************************/
ErrorState_t MNVIC_enEnableNVIC(void)
{
	/*	@brief	This APIs allow the system to has a Pritories-Group and Sub-group
	 * 	To write to this register, you must write 0x5FA to the VECTKEY[16-31] field, otherwise the
		processor ignores the write. */

	SCB_AIRCR = MNVIC_GROUPSUB_PRI;

	return SUCCESS;
}

/******************************************************************************
 * \Syntax          : MNVIC_enEnableInt(u8 copy_u8IRQnum)
 *
 * \Description     : This Services for Enable the NVIC PERIPHERIAL INT
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8IRQnum
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MNVIC_enEnableInt(u8 copy_u8IRQnum)
{
	/*	@berif	This APIs set to Enable the Peripherial INT
	 * 	1. based on the ID of the INT, it will select the correspoinding Register
	 *
	 * 	@hint 	This API used An atomic access to execuate the statement in one Asm Inst.
	 * */

	ErrorState_t  local_state = SUCCESS;

	if (copy_u8IRQnum < MNVIC_MAX_REG1)
	{
		NVIC->NVIC_ISER[0] = (1<<copy_u8IRQnum);
	}
	else if (copy_u8IRQnum < MNVIC_MAX_REG2)
	{
		copy_u8IRQnum -= MNVIC_MAX_REG1;
		NVIC->NVIC_ISER[1] = (1<<copy_u8IRQnum);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : MNVIC_enDisableInt(u8 copy_u8IRQnum)
 *
 * \Description     : This Services for Disable the NVIC PERIPHERIAL INT
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8IRQnum
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MNVIC_enDisableInt(u8 copy_u8IRQnum)
{
	ErrorState_t  local_state = SUCCESS;
	/*	@berif	This API set to Disable the Peripherial INT
	 * 	1. based on the ID of the INT, it will select the correspoinding Register
	 *
	 * 	@hint 	This API used An atomic access to execuate the statement in one Asm Inst.
	 * */

	if (copy_u8IRQnum < MNVIC_MAX_REG1)
	{
		NVIC->NVIC_ICER[0] = (1<<copy_u8IRQnum);
	}
	else if (copy_u8IRQnum < MNVIC_MAX_REG2)
	{
		copy_u8IRQnum -= MNVIC_MAX_REG1;
		NVIC->NVIC_ICER[1] = (1<<copy_u8IRQnum);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : MNVIC_enSetPendingFlag(u8 copy_u8IRQnum)
 *
 * \Description     : This Services for set the NVIC PERIPHERIAL INT pending flag
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8IRQnum
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MNVIC_enSetPendingFlag(u8 copy_u8IRQnum)
{
	ErrorState_t  local_state = SUCCESS;
	/*	@berif	This API set the NVIC PERIPHERIAL INT pending flag
	 * 	1. based on the ID of the INT, it will select the correspoinding Register
	 *
	 * 	@hint 	This API used An atomic access to execuate the statement in one Asm Inst.
	 * */

	if (copy_u8IRQnum < MNVIC_MAX_REG1)
	{
		NVIC->NVIC_ISPR[0] = (1<<copy_u8IRQnum);
	}
	else if (copy_u8IRQnum < MNVIC_MAX_REG2)
	{
		copy_u8IRQnum -= MNVIC_MAX_REG1;
		NVIC->NVIC_ISPR[1] = (1<<copy_u8IRQnum);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : MNVIC_enClrPendingFlag(u8 copy_u8IRQnum)
 *
 * \Description     : This Services for clear the NVIC PERIPHERIAL INT pending flag
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8IRQnum
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MNVIC_enClrPendingFlag(u8 copy_u8IRQnum)
{
	ErrorState_t  local_state = SUCCESS;
	/*	@berif	This API clear the NVIC PERIPHERIAL INT pending flag
	 * 	1. based on the ID of the INT, it will select the correspoinding Register
	 *
	 * 	@hint 	This API used An atomic access to execuate the statement in one Asm Inst.
	 * */
	if (copy_u8IRQnum < MNVIC_MAX_REG1)
	{
		NVIC->NVIC_ICPR[0] = (1<<copy_u8IRQnum);
	}
	else if (copy_u8IRQnum < MNVIC_MAX_REG2)
	{
		copy_u8IRQnum -= MNVIC_MAX_REG1;
		NVIC->NVIC_ICPR[1] = (1<<copy_u8IRQnum);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : MNVIC_enGetPendingFlag(u8 copy_u8IRQnum)
 *
 * \Description     : This Services for get the NVIC PERIPHERIAL INT pending flag
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8IRQnum,  *PendingState
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MNVIC_enGetPendingFlag(u8 copy_u8IRQnum, u8 *PendingState)
{
	ErrorState_t  local_state = SUCCESS;
	/*	@berif	This API GET the NVIC PERIPHERIAL INT pending flag
	 * 	1. based on the ID of the INT, it will select the correspoinding Register
	 * 	2. return the value by Reference with ptr_state
	 * */
	if (copy_u8IRQnum < MNVIC_MAX_REG1)
	{
		*PendingState = GET_BIT(NVIC->NVIC_ICPR[0],copy_u8IRQnum);
	}
	else if (copy_u8IRQnum < MNVIC_MAX_REG2)
	{
		copy_u8IRQnum -= MNVIC_MAX_REG1;
		*PendingState = GET_BIT(NVIC->NVIC_ICPR[1],copy_u8IRQnum);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : MNVIC_enGetActiveFlag(u8 copy_u8IRQnum, u8 *ActiveState)
 *
 * \Description     : This Services for get the NVIC PERIPHERIAL INT Active flag
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8IRQnum,  *ActiveState
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MNVIC_enGetActiveFlag(u8 copy_u8IRQnum, u8 *ActiveState)
{
	/*	@berif	This API GET the NVIC PERIPHERIAL INT Active flag
	 * 	1. based on the ID of the INT, it will select the correspoinding Register
	 * 	2. return the value by Reference with ptr_state
	 * */
	ErrorState_t  local_state = SUCCESS;

	if (copy_u8IRQnum < MNVIC_MAX_REG1)
	{
		*ActiveState = GET_BIT(NVIC->NVIC_IABR[0],copy_u8IRQnum);
	}
	else if (copy_u8IRQnum < MNVIC_MAX_REG2)
	{
		copy_u8IRQnum -= MNVIC_MAX_REG1;
		*ActiveState = GET_BIT(NVIC->NVIC_IABR[1],copy_u8IRQnum);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : MNVIC_enSetPriority(u8 copy_u8IRQnum, u8 copy_u8Group, u8 copy_u8Sub)
 *
 * \Description     : This Services for set the NVIC PERIPHERIAL INT Group,Sub Pritory
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8IRQnum, copy_u8Group, copy_u8Sub
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MNVIC_enSetPriority(u8 copy_u8IRQnum, u8 copy_u8Group, u8 copy_u8Sub)
{
	ErrorState_t local_state = SUCCESS;

	/*	@berif	This API set the NVIC PERIPHERIAL INT Group,Sub Pritory
	 * 	1. Clear the 8-bit of the NVIC PERIPHERIAL PRI Register
	 * 	2. Set the Sub index from [4-5]
	 * 	3. Set the Grp index from [6-7]
	 *
	 * 	@hint it's disallowed to write on Register[0-3]
	 * */
	if (copy_u8IRQnum <= MNVIC_MAX_INT)
	{
		NVIC->NVIC_IPR[copy_u8IRQnum] &= MNVIC_SETPRI_MASK;

		if (copy_u8Group <= MNVIC_PRI_SIZE && copy_u8Sub <= MNVIC_PRI_SIZE)
		{
			NVIC->NVIC_IPR[copy_u8IRQnum] |= (copy_u8Sub << MNVIC_SUB_OFFSET);
			NVIC->NVIC_IPR[copy_u8IRQnum] |= (copy_u8Group << MNVIC_GRP_OFFSET);
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state;
}

/**********************************************************************************************************************
 *  END OF FILE: MNVIC_prog.c
 *********************************************************************************************************************/

