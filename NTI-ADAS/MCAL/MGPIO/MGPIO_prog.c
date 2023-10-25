/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MGPIO.c
 *         @Module	:  GPIO
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
#include "MGPIO_int.h"
#include "MGPIO_config.h"
#include "MGPIO_priv.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : ErrorState_t MGPIO_enSetPinDirection
 * 					(MGPIO_PORT_t copy_u8port,MGPIO_PIN_t copy_u8pin,u8 copy_u8Mode)
 *
 * \Description     : This Services for configure The GPIO pin
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : MGPIO_PORT_t -> copy_u8port
 * 					 MGPIO_PIN_t  -> copy_u8pin
 * 					 Global Macro -> copy_u8Mode
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 								   -> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MGPIO_enSetPinDirection(MGPIO_PORT_t copy_u8port, MGPIO_PIN_t copy_u8pin, u8 copy_u8Mode)
{
	ErrorState_t local_state = SUCCESS;
	/*	@beief This APIs use to configure the GPIO PIN
	 * 	1. choose between High and Low Control register correspoing by the GPIO PIN
	 * 	2. Clear the 4bit configuration of the correspoinding GPIO PIN
	 * 	3. Set the 4bit Configuration with the Selected Mode
	 *
	 * 	@اhint 	use 4bit Masked pins to clear and shifting it correspoinding with
	 * 			the Gpio pin and use that offest when setting the Mode
	 * */
	switch(copy_u8port)
	{
	case PORTA:
		if (copy_u8pin < MGPIO_CRL_MAX)
		{
			GPIOA->GPIO_CRL &= ~(MGPIO_MASK << (copy_u8pin * MGPIO_OFFSET)) ;
			GPIOA->GPIO_CRL |= copy_u8Mode << (copy_u8pin * MGPIO_OFFSET) ;
		}
		else if(copy_u8pin < MGPIO_CRH_MAX)
		{
			copy_u8pin -= MGPIO_CRL_MAX  ;
			GPIOA->GPIO_CRH &= ~(MGPIO_MASK << (copy_u8pin * MGPIO_OFFSET));
			GPIOA->GPIO_CRH |= (copy_u8Mode << (copy_u8pin * MGPIO_OFFSET));
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	case PORTB:
		if (copy_u8pin < MGPIO_CRL_MAX)
		{
			GPIOB->GPIO_CRL &= ~(MGPIO_MASK << (copy_u8pin * MGPIO_OFFSET)) ;
			GPIOB->GPIO_CRL |= (copy_u8Mode << (copy_u8pin * MGPIO_OFFSET)) ;
		}
		else if(copy_u8pin < MGPIO_CRH_MAX)
		{
			copy_u8pin -= MGPIO_CRL_MAX ;
			GPIOB->GPIO_CRH &= ~(MGPIO_MASK << (copy_u8pin * MGPIO_OFFSET)) ;
			GPIOB->GPIO_CRH |= (copy_u8Mode << (copy_u8pin * MGPIO_OFFSET)) ;
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	case PORTC:
		if (copy_u8pin < MGPIO_CRL_MAX)
		{
			GPIOC->GPIO_CRL &= ~(MGPIO_MASK << (copy_u8pin * MGPIO_OFFSET)) ;
			GPIOC->GPIO_CRL |= (copy_u8Mode << (copy_u8pin * MGPIO_OFFSET)) ;
		}
		else if(copy_u8pin < MGPIO_CRH_MAX)
		{
			copy_u8pin -= MGPIO_CRL_MAX ;
			GPIOC->GPIO_CRH &= ~(MGPIO_MASK) << (copy_u8pin * MGPIO_OFFSET) ;
			GPIOC->GPIO_CRH |= (copy_u8Mode << (copy_u8pin * MGPIO_OFFSET)) ;
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	default:
		local_state = OUT_OF_RANG_ERR;
		break;
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MGPIO_enSetPinValue
 * 					(MGPIO_PORT_t copy_u8port, MGPIO_PIN_t copy_u8pin, MGPIO_VALUE_t copy_u8Value)
 *
 * \Description     : This Services for Set the Value of The GPIO pin
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : MGPIO_PORT_t -> copy_u8port
 * 					 MGPIO_PIN_t  -> copy_u8pin
 * 					 MGPIO_VALUE_t -> copy_u8Value
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 								   -> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MGPIO_enSetPinValue(MGPIO_PORT_t copy_u8port, MGPIO_PIN_t copy_u8pin, MGPIO_VALUE_t copy_u8Value)
{
	ErrorState_t local_state = SUCCESS;
	/*	@beief 		This APIs use to set the GPIO PIN
	 *  choose between High and Low Value state and set it in ODR
	 * */
	switch(copy_u8port)
	{
	case PORTA:
		if (copy_u8Value == HIGH)
		{
			SET_BIT(GPIOA->GPIO_ODR, copy_u8pin);
		}
		else if(copy_u8Value == LOW)
		{
			CLR_BIT(GPIOA->GPIO_ODR, copy_u8pin);
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	case PORTB:
		if (copy_u8Value == HIGH)
		{
			SET_BIT(GPIOB->GPIO_ODR, copy_u8pin);
		}
		else if(copy_u8Value == LOW)
		{
			CLR_BIT(GPIOB->GPIO_ODR, copy_u8pin);
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;

		}
		break;

	case PORTC:
		if (copy_u8Value == HIGH)
		{
			SET_BIT(GPIOC->GPIO_ODR, copy_u8pin);
		}
		else if(copy_u8Value == LOW)
		{
			CLR_BIT(GPIOC->GPIO_ODR, copy_u8pin);
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	default:
		local_state = OUT_OF_RANG_ERR;
		break;
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MGPIO_enTogglePin
 * 					(MGPIO_PORT_t copy_u8port, MGPIO_PIN_t copy_u8pin)
 *
 * \Description     : This Services for toggle The GPIO pin
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : MGPIO_PORT_t -> copy_u8port
 * 					 MGPIO_PIN_t  -> copy_u8pin
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 								   -> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MGPIO_enTogglePin(MGPIO_PORT_t copy_u8port, MGPIO_PIN_t copy_u8pin)
{
	ErrorState_t local_state = SUCCESS;

	/*	@beief This APIs use to toggele the GPIO PIN
	 *  based on the last GPIO PIN state, T0G_BIT will flip the ODR register
	 * */
	switch(copy_u8port)
	{
	case PORTA:
		TOG_BIT(GPIOA->GPIO_ODR, copy_u8pin);
		break;

	case PORTB:
		TOG_BIT(GPIOB->GPIO_ODR, copy_u8pin);
		break;

	case PORTC:
		TOG_BIT(GPIOC->GPIO_ODR, copy_u8pin);
		break;
	default:
		local_state =  OUT_OF_RANG_ERR;
		break;
	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MGPIO_enGetPinValue
 * 					(MGPIO_PORT_t copy_u8port, MGPIO_PIN_t copy_u8pin, MGPIO_VALUE_t *pinValue)
 *
 * \Description     : This Services for get The GPIO pin Value
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : MGPIO_PORT_t -> copy_u8port
 * 					 MGPIO_PIN_t  -> copy_u8pin
 * 					 MGPIO_VALUE_t-> *pinValue
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 								   -> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MGPIO_enGetPinValue(MGPIO_PORT_t copy_u8port, MGPIO_PIN_t copy_u8pin, MGPIO_VALUE_t *pinValue)
{
	ErrorState_t local_state = SUCCESS;

	/*	@beief This APIs use to get the GPIO PIN Value
	 *  GET_BIT will get the ODR register Pin value and returned by Reference
	 * */

	switch(copy_u8port)
	{
	case PORTA:
		*pinValue = GET_BIT(GPIOA->GPIO_IDR, copy_u8pin);
		break;

	case PORTB:
		*pinValue = GET_BIT(GPIOB->GPIO_IDR, copy_u8pin);
		break;

	case PORTC:
		*pinValue = GET_BIT(GPIOC->GPIO_IDR, copy_u8pin);
		break;
	default:
		local_state =  OUT_OF_RANG_ERR;
		break;
	}

	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MGPIO_enSetPortDirection
 * 					(MGPIO_ID_t copy_u8CRID, MGPIO_PORT_t copy_u8port, u8 copy_u8Mode)
 *
 * \Description     : This Services for Set the Confifuration of GPIO Port
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : MGPIO_ID_t  -> copy_u8CRID
 * 					 MGPIO_PORT_t-> copy_u8port
 * 					 Global Macro -> copy_u8Mode
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 								   -> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MGPIO_enSetPortDirection(MGPIO_ID_t copy_u8CRID, MGPIO_PORT_t copy_u8port, u8 copy_u8Mode)
{
	ErrorState_t local_state = SUCCESS;

	/*	@beief This APIs use to configure the GPIO PORT
	 * 	1. choose between High and Low Control register correspoing by GPIO_ID
	 * 	2. Set the all register Configuration with the Selected Mode
	 *
	 * 	@اhint 	MGPIO_PORT_OFFSET when multiply with the 4-bit mode, it makes the
	 * 			all register as selected with choosen mode
	 * */
	switch(copy_u8port)
	{
	case PORTA:
		if(copy_u8CRID == GPIO_CRL_ID)
		{
			GPIOA->GPIO_CRL = copy_u8Mode * MGPIO_PORT_OFFSET ;
		}
		else if(copy_u8CRID == GPIO_CRH_ID)
		{
			GPIOA->GPIO_CRH = copy_u8Mode * MGPIO_PORT_OFFSET ;
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;


	case PORTB:
		if(copy_u8CRID == GPIO_CRL_ID)
		{
			GPIOB->GPIO_CRL = copy_u8Mode * MGPIO_PORT_OFFSET ;
		}
		else if(copy_u8CRID == GPIO_CRH_ID)
		{
			GPIOB->GPIO_CRH = copy_u8Mode * MGPIO_PORT_OFFSET ;
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	case PORTC:
		if(copy_u8CRID == GPIO_CRL_ID)
		{
			GPIOC->GPIO_CRL = copy_u8Mode * MGPIO_PORT_OFFSET ;
		}
		else if(copy_u8CRID == GPIO_CRH_ID)
		{
			GPIOC->GPIO_CRH = copy_u8Mode * MGPIO_PORT_OFFSET ;
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	default:
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MGPIO_enSetPortValue
 * 					(MGPIO_ID_t copy_u8CRID, MGPIO_PORT_t copy_u8port, MGPIO_VALUE_t copy_u8Value)
 *
 * \Description     : This Services for Set the GPIO Port Value
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : MGPIO_ID_t    -> copy_u8CRID
 * 					 MGPIO_PORT_t  -> copy_u8port
 * 					 MGPIO_VALUE_t -> copy_u8Value
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 								   -> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MGPIO_enSetPortValue(MGPIO_ID_t copy_u8CRID, MGPIO_PORT_t copy_u8port, MGPIO_VALUE_t copy_u8Value)
{
	ErrorState_t local_state = SUCCESS;

	/*	@beief This APIs use set Half of the GPIO PORT based on the GPIO_ID
	 * 	1. choose which HALF PORT SET(low,high correspoing by the GPIO ID
	 * 	2. choose which Value state (PORT_HIGH , PORT_LOW)
	 *	3. BASED on that ODR Register will cleared first then Set by the Value State
	 *
	 * 	@اhint in High state, MGPIO_PORT_LVALUE OR MGPIO_PORT_HVALUE configured to clear first then set
	 * 		  in Low state, Mask with MGPIO_PORT_LVALUE, MGPIO_PORT_HVALUE To clear the Half of the choosen PORT
	 * 		  then Set with 0x00 will not effect the Not Choosen HALF Port
	 * */
	switch(copy_u8port)
	{
	case PORTA:
		if ((copy_u8Value == HIGH) && (copy_u8CRID == GPIO_CRL_ID))
		{
			GPIOA->GPIO_ODR |= MGPIO_PORT_LVALUE;
		}
		else if ((copy_u8Value == HIGH) && (copy_u8CRID == GPIO_CRH_ID))
		{
			GPIOA->GPIO_ODR |= MGPIO_PORT_HVALUE;
		}
		else if ((copy_u8Value == LOW) && (copy_u8CRID == GPIO_CRL_ID))
		{
			GPIOA->GPIO_ODR &= ~(MGPIO_PORT_LVALUE);
			GPIOA->GPIO_ODR |= MGPIO_PORT_RESET;
		}
		else if ((copy_u8Value == LOW) && (copy_u8CRID == GPIO_CRH_ID))
		{
			GPIOA->GPIO_ODR &= ~(MGPIO_PORT_HVALUE);
			GPIOA->GPIO_ODR |= MGPIO_PORT_RESET;
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	case PORTB:
		if ((copy_u8Value == HIGH) && (copy_u8CRID == GPIO_CRL_ID))
		{
			GPIOB->GPIO_ODR |= MGPIO_PORT_LVALUE;
		}
		else if ((copy_u8Value == HIGH) && (copy_u8CRID == GPIO_CRH_ID))
		{
			GPIOB->GPIO_ODR |= MGPIO_PORT_HVALUE;
		}
		else if ((copy_u8Value == LOW) && (copy_u8CRID == GPIO_CRL_ID))
		{
			GPIOB->GPIO_ODR &= ~(MGPIO_PORT_LVALUE);
			GPIOB->GPIO_ODR |= MGPIO_PORT_RESET;
		}
		else if ((copy_u8Value == LOW) && (copy_u8CRID == GPIO_CRH_ID))
		{
			GPIOB->GPIO_ODR &= ~(MGPIO_PORT_HVALUE);
			GPIOB->GPIO_ODR |= MGPIO_PORT_RESET;
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	case PORTC:
		if ((copy_u8Value == HIGH) && (copy_u8CRID == GPIO_CRL_ID))
		{
			GPIOC->GPIO_ODR |= MGPIO_PORT_LVALUE;
		}
		else if ((copy_u8Value == HIGH) && (copy_u8CRID == GPIO_CRH_ID))
		{
			GPIOC->GPIO_ODR |= MGPIO_PORT_HVALUE;
		}
		else if ((copy_u8Value == LOW) && (copy_u8CRID == GPIO_CRL_ID))
		{
			GPIOC->GPIO_ODR &= ~(MGPIO_PORT_LVALUE);
			GPIOC->GPIO_ODR |= MGPIO_PORT_RESET;
		}
		else if ((copy_u8Value == LOW) && (copy_u8CRID == GPIO_CRH_ID))
		{
			GPIOC->GPIO_ODR &= ~(MGPIO_PORT_HVALUE);
			GPIOC->GPIO_ODR |= MGPIO_PORT_RESET;
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	default:
		local_state = OUT_OF_RANG_ERR;
		break;

	}
	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MGPIO_enSetResetPin
 * 					(MGPIO_PORT_t copy_u8port, MGPIO_PIN_t copy_u8pin,MGPIO_MODE_t copy_u8Mode)
 *
 * \Description     : This Services for Set/Reset the GPIO Pin
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : MGPIO_PORT_t -> copy_u8port
 * 					 MGPIO_PIN_t  -> copy_u8pin
 * 					 MGPIO_MODE_t -> copy_u8Mode
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 								   -> OUT_OF_RANG_ERR
 *******************************************************************************/
ErrorState_t MGPIO_enSetResetPin(MGPIO_PORT_t copy_u8port,MGPIO_PIN_t copy_u8pin, MGPIO_MODE_t copy_u8Mode)
{
	ErrorState_t local_state = SUCCESS;

	/*	@beief This APIs use to Set/Reset of the GPIO Pin
	 *	 by setting the GPIO pin the BSRR/BRR register will set/clear the GPIO based on selected Mode
	 * 	@اhint In Arm Architures, there is An Atomic Access which the statement executes in One Asm Ins.
	 * */
	switch(copy_u8port)
	{
	case PORTA:
		if (copy_u8Mode == GPIO_PIN_SET)
		{
			GPIOA->GPIO_BSRR = (1<<copy_u8pin);
		}
		else if(copy_u8Mode == GPIO_PIN_RESET)
		{
			GPIOA->GPIO_BRR = (1<<copy_u8pin);
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	case PORTB:
		if (copy_u8Mode == GPIO_PIN_SET)
		{
			GPIOB->GPIO_BSRR = (1<<copy_u8pin);
		}
		else if(copy_u8Mode == GPIO_PIN_RESET)
		{
			GPIOB->GPIO_BRR = (1<<copy_u8pin);
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	case PORTC:
		if (copy_u8Mode == GPIO_PIN_SET)
		{
			GPIOC->GPIO_BSRR = (1<<copy_u8pin);
		}
		else if(copy_u8Mode == GPIO_PIN_RESET)
		{
			GPIOC->GPIO_BRR = (1<<copy_u8pin);
		}
		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
		break;

	default:
		local_state = OUT_OF_RANG_ERR;
		break;
	}

	return local_state;
}

/******************************************************************************
 * \Syntax          : ErrorState_t MGPIO_enLockPin
 * 					(MGPIO_PORT_t copy_u8port, MGPIO_PIN_t copy_u8pin)
 *
 * \Description     : This Services for lock  the GPIO pin Value
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : MGPIO_PORT_t -> copy_u8port
 * 					 MGPIO_PIN_t  -> copy_u8pin
 *
 * \Return value:   : ErrorState_t  -> SUCEESS
 * 								    -> OUT_OF_RANG_ERR
 * 								    -> FAILARE
 *******************************************************************************/

ErrorState_t MGPIO_enLockPin(MGPIO_PORT_t copy_u8port, MGPIO_PIN_t copy_u8pin)
{
	ErrorState_t local_state = SUCCESS;

	/*	@beief This APIs use to lock  the GPIO pin Value
	 * 	1. Write 1 -> write 0 -> write 1 on the LCKK PIN
	 * 	2. get the LCKK state, check if it (0) ?
	 * 	3. if (0), get the state again, check if it (1)?
	 * 	4. if (1), the operation is done successfully
	 *
	 * 	@اhint 1.there are a sequence to write and to enable that featuers
	 * 		  2.in Arm Achitures there is option to lock the GPIO PIN state
	 * */
	u8 pinState ;

	switch (copy_u8port)
	{
	case PORTA:
	//	SET_BIT(GPIOA->GPIO_LCKR,copy_u8pin);


		SET_BIT(GPIOA->GPIO_LCKR,LCKK);
		CLR_BIT(GPIOA->GPIO_LCKR,LCKK);
		SET_BIT(GPIOA->GPIO_LCKR,LCKK);

		pinState = GET_BIT(GPIOA->GPIO_LCKR,LCKK);
		pinState = GET_BIT(GPIOA->GPIO_LCKR,LCKK);

		if (GET_BIT(GPIOA->GPIO_LCKR,LCKK))
		{
			local_state = SUCCESS;
		}
		else
		{
			local_state = FAILARE;
		}

		break;

	case PORTB:
		SET_BIT(GPIOB->GPIO_LCKR,copy_u8pin);

		SET_BIT(GPIOB->GPIO_LCKR,LCKK);
		CLR_BIT(GPIOB->GPIO_LCKR,LCKK);
		SET_BIT(GPIOB->GPIO_LCKR,LCKK);

		pinState = GET_BIT(GPIOB->GPIO_LCKR,LCKK);
		if (pinState == 0)
		{
			pinState = GET_BIT(GPIOB->GPIO_LCKR,LCKK);
			if (pinState == 1)
			{
				local_state = SUCCESS;
			}
			else
			{
				local_state = FAILARE;
			}
		}
		else
		{
			local_state = FAILARE;
		}
		break;

	case PORTC:
		SET_BIT(GPIOC->GPIO_LCKR,copy_u8pin);

		SET_BIT(GPIOC->GPIO_LCKR,LCKK);
		CLR_BIT(GPIOC->GPIO_LCKR,LCKK);
		SET_BIT(GPIOC->GPIO_LCKR,LCKK);

		pinState = GET_BIT(GPIOC->GPIO_LCKR,LCKK);
		if (pinState == 0)
		{
			pinState = GET_BIT(GPIOC->GPIO_LCKR,LCKK);
			if (pinState == 1)
			{
				local_state = SUCCESS;
			}
			else
			{
				local_state = FAILARE;
			}
		}
		else
		{
			local_state = FAILARE;
		}
		break;

	default:
		local_state = OUT_OF_RANG_ERR;
		break;
	}

	return local_state;
}

/**********************************************************************************************************************
 *  END OF FILE: MGPIO_prog.c
 *********************************************************************************************************************/
