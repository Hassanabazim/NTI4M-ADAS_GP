/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MEXTI_prog.c
 *         @Module	:  EXTI
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
#include "MEXTI_config.h"
#include "MEXTI_int.h"
#include "MEXTI_priv.h"

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
static void (*MEXTI_CALLBACK[MEXTI_MAX_LINES])(void) = {0};

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : ErrorState_t MEXTI_enInit(void)
 *
 * \Description     : This Services for Intialize the EXTI with LINE and Mode
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 *******************************************************************************/
ErrorState_t MEXTI_enInit(void)
{
	/*	@berif	This API Intialize the EXTI with LINE and Mode
	 *  based on the pre selected Mode of operation and LINE on their Registers  */

#if (MEXTI_MODE == MEXTI_RISING_TRIG)
	SET_BIT(EXTI->EXTI_RTSR,MEXTI_LINE);

#elif(MEXTI_MODE == MEXTI_FAILING_TRIG)
	SET_BIT(EXTI->EXTI_FTSR,MEXTI_LINE);

#elif(MEXTI_MODE == MEXTI_LOGIC_CHANGE)
	SET_BIT(EXTI->EXTI_RTSR,MEXTI_LINE);
	SET_BIT(EXTI->EXTI_FTSR,MEXTI_LINE);

#else
#error("Wrong EXTI MODE!");
#endif

	SET_BIT(EXTI->EXTI_IMR, MEXTI_LINE);

	return SUCCESS;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MEXTI_enSetLatch(u8 Copy_u8LineId, u8 Copy_u8Mode)
 *
 * \Description     : This Services for change EXTI LINE and Mode in runtime
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_u8LineId, Copy_u8Mode
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MEXTI_enSetLatch(u8 Copy_u8LineId, u8 Copy_u8Mode)
{
	/*	@berif 	This API use to change EXTI LINE and Mode in runtime
	 * based on the selected LINE and Mode of Opeation in Run time
	 * */
	ErrorState_t local_state = SUCCESS ;

	if (Copy_u8LineId < MEXTI_MAX_LINES)
	{
		SET_BIT(EXTI->EXTI_IMR, Copy_u8LineId);
		switch (Copy_u8Mode)
		{
		case MEXTI_RISING_TRIG:
			SET_BIT(EXTI->EXTI_RTSR,Copy_u8LineId);
			break;

		case MEXTI_FAILING_TRIG:
			SET_BIT(EXTI->EXTI_FTSR,Copy_u8LineId);
			break;

		case MEXTI_LOGIC_CHANGE:
			SET_BIT(EXTI->EXTI_RTSR,Copy_u8LineId);
			SET_BIT(EXTI->EXTI_FTSR,Copy_u8LineId);
			break;

		default:
			local_state = OUT_OF_RANG_ERR;
			break;
		}
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MEXTI_enDisable(u8 Copy_u8LineId)
 *
 * \Description     : This Services for Disable the EXTI LINE and Mode
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_u8LineId
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MEXTI_enDisable(u8 Copy_u8LineId)
{
	/*	@berif 	This API use to Disable The EXTI LINE
	 * based on the selected LINE in Run time, it will Disable EXTI LINE
	 * */
	ErrorState_t local_state = SUCCESS ;

	if (Copy_u8LineId < MEXTI_MAX_LINES)
	{
		CLR_BIT(EXTI->EXTI_IMR, Copy_u8LineId);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MEXTI_enCallBack(u8 Copy_u8LineId, void (*ptr) (void))
 *
 * \Description     : This Services for Interput Call Back Fun
 *
 * \Sync\Async      : ASynchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_u8LineId, void (*ptr) (void)
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> NULL_PTR_ERR
 *******************************************************************************/
ErrorState_t MEXTI_enCallBack(u8 Copy_u8LineId, void (*ptr) (void))
{
	/*	@berif 	This API use to Interrupt Call Back Fun
	 * based on the selected LINE in Run time, it will be called from MCAL Layer to APP
	 * */
	ErrorState_t local_state = SUCCESS ;
	if (ptr == NULL)
	{
		local_state = NULL_PTR_ERR;
	}
	else
	{
		MEXTI_CALLBACK[Copy_u8LineId] = ptr;
	}

	return local_state ;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MEXTI_enSWInterrupt(u8 Copy_u8LineId)
 *
 * \Description     : This Services for firing an Software Interrupt
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_u8LineId
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MEXTI_enSWInterrupt(u8 Copy_u8LineId)
{
	/*	@berif 	This API use to fire a software Interrupt
	 * based on the selected LINE in Run time, it will fire SW interrupt
	 *
	 * @hint 	SW interrupt maianly used in debugging and testing software
	 * */
	ErrorState_t local_state = SUCCESS ;

	if (Copy_u8LineId < MEXTI_MAX_LINES)
	{
		SET_BIT(EXTI->EXTI_SWIER, Copy_u8LineId);
		CLR_BIT(EXTI->EXTI_PR, Copy_u8LineId);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MEXTI_enClearPendingBit(u8 Copy_u8LineId)
 *
 * \Description     : This Services for clear EXTI pending bit
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_u8LineId
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MEXTI_enClearPendingBit(u8 Copy_u8LineId)
{
	/*	@berif 	This API use to clear EXTI pending bit
	 * based on the selected LINE in Run time, it will clear the pending bit
	 * */
	ErrorState_t local_state = SUCCESS ;

	if (Copy_u8LineId < MEXTI_MAX_LINES)
	{
		SET_BIT(EXTI->EXTI_PR, Copy_u8LineId);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}


/**********************************************************************************************************************
 *  HANDLER REQUEST
 *********************************************************************************************************************/
/*	@brief 	Handlear has an callback fun from the App layer and Excecuted based on
 * 			the Selected Line on the Callback fun. */

void EXTI0_IRQHandler(void)
{
	if (MEXTI_CALLBACK[MEXTI0_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI0_LINE]();
	}
}

void EXTI1_IRQHandler(void)
{
	if (MEXTI_CALLBACK[MEXTI1_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI1_LINE]();
	}

}
void EXTI2_IRQHandler(void)
{
	if (MEXTI_CALLBACK[MEXTI2_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI2_LINE]();
	}
}
void EXTI3_IRQHandler(void)
{
	if (MEXTI_CALLBACK[MEXTI3_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI3_LINE]();
	}
}
void EXTI4_IRQHandler(void)
{
	if (MEXTI_CALLBACK[MEXTI4_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI4_LINE]();
	}
}
void EXTI9_5_IRQHandler(void)
{
	if (MEXTI_CALLBACK[MEXTI5_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI5_LINE]();
	}
	else if (MEXTI_CALLBACK[MEXTI6_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI6_LINE]();

	}
	else if (MEXTI_CALLBACK[MEXTI7_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI7_LINE]();

	}
	else if (MEXTI_CALLBACK[MEXTI8_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI8_LINE]();

	}
	else if (MEXTI_CALLBACK[MEXTI9_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI9_LINE]();

	}
}

void EXTI15_10_IRQHandler(void)
{
	if (MEXTI_CALLBACK[MEXTI10_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI10_LINE]();
	}
	else if (MEXTI_CALLBACK[MEXTI11_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI11_LINE]();

	}
	else if (MEXTI_CALLBACK[MEXTI12_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI12_LINE]();

	}
	else if (MEXTI_CALLBACK[MEXTI13_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI13_LINE]();

	}
	else if (MEXTI_CALLBACK[MEXTI14_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI14_LINE]();

	}
	else if (MEXTI_CALLBACK[MEXTI15_LINE] != NULL)
	{
		MEXTI_CALLBACK[MEXTI15_LINE]();

	}
}

/**********************************************************************************************************************
 *  END OF FILE: MEXTI_prog.c
 *********************************************************************************************************************/
