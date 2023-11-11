/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MAFIO_prog.c
 *         @Module	:  AFIO
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
#include "MEXTI_int.h"
#include "MAFIO_int.h"
#include "MAFIO_config.h"
#include "MAFIO_priv.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : ErrorState_t  MAFIO_enSetEXTI_Config
 * 						(u8 copy_u8EXTILineId, MAFIO_EXTI_t copy_u8PortMap)
 *
 * \Description     : This Services for configure the AF EXTI LINE
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : copy_u8EXTILineId
 * 					  MAFIO_EXTI_t -> copy_u8PortMap
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 									-> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MAFIO_enSetEXTI_Config(u8 copy_u8EXTILineId, MAFIO_t copy_u8PortMap)
{
	/*	@berif	This API use to configure the AF EXTI LINE
	 * based on the selected EXTI LINE in the runtime
	 * 1. define a local index select bet the AFIO register based on the no.of LINES
	 * 2. each register up to 4 EXTI LINES, so subustract the LINEID with (MAX_REG_LINE * localIndex)
	 * 3. clear the 4-bit for each correspoinding EXTI_LINE by ofset  4
	 * 4. Set the AFIO Memory map for each EXTI LINE correspoing with LineID by offset 4
	 * 	*/
	ErrorState_t local_state = SUCCESS ;

	u8 local_u8RegIndex;
	if (copy_u8EXTILineId < MAFIO_EXTI_REG1)
	{
		local_u8RegIndex = 0;
	}
	else if (copy_u8EXTILineId < MAFIO_EXTI_REG2)
	{
		local_u8RegIndex = 1;
		copy_u8EXTILineId -= MAFIO_EXTI_REG1;
	}
	else if (copy_u8EXTILineId < MAFIO_EXTI_REG3)
	{
		local_u8RegIndex = 2;
		copy_u8EXTILineId -= MAFIO_EXTI_REG2;
	}
	else if (copy_u8EXTILineId <= MAFIO_EXTI_MAX)
	{
		local_u8RegIndex = 3;
		copy_u8EXTILineId -= MAFIO_EXTI_REG3;
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}


	AFIO->AFIO_EXTICR[local_u8RegIndex] &= ~((MAFIO_EXTI_MASK) <<(copy_u8EXTILineId	* MAFIO_EXTI_OFFSET));
	AFIO->AFIO_EXTICR[local_u8RegIndex] |=  ((copy_u8PortMap) << (copy_u8EXTILineId * MAFIO_EXTI_OFFSET));
	return local_state;
}

/**********************************************************************************************************************
 *  END OF FILE: MAFIO_prog.c
 *********************************************************************************************************************/
