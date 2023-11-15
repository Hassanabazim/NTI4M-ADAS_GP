/********************************************************************************
 * @file        		:  MADC_prog.c					 						*
 * @Author 	 			:  HASSAN ABDELAZIM ABDELSALAM							*
 * @Version 			:  1.0.0							 					*
 * @Date				:  08/08/2023											*
 ********************************************************************************
 * @attention   Driver Implementation for STM32F103C8
 *
 *
 *
 *
 *********************************************************************************
 * INCLUDES
 ********************************************************************************/
#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "REGISTERS.h"
#include "BIT_MATH.h"
#include "MSYSTICK_int.h"
#include "MADC_int.h"
#include "MADC_config.h"
#include "MADC_priv.h"


/********************************************************************************
 * GLOBAL STATIC VARIABLES
 ********************************************************************************/
static void (*ADC_CallBack)(void) = 0;



/********************************************************************************
 * APIs IMPLEMENTATION
 ********************************************************************************/
/*
 *	@brief
 *
 *	@para
 *	@retval
 */
ErrorState_t MADC_enInit(MADC_INIT_t *ptr_u8config)
{
	ErrorState_t local_state = SUCCESS;

	if (ptr_u8config != NULL)
	{
		/*	use to select the no.of channels in ADC Regular Group */
		ADC->ADC_SQR[0] &= MADC_REG_CHANNELS_MASK;
		ADC->ADC_SQR[0] |=	ptr_u8config->Reg_ChNum << 20;
		/**********************************************************************/

		/*	use to select the no.of channels in ADC Injected Group*/
		ADC->ADC_JSQR &= MADC_INJ_CHANNELS_MASK;
		ADC->ADC_JSQR |= ptr_u8config->Inj_ChNum << 20;

		/**********************************************************************/

		/* use to select the trig of the regular group conversion */
		ADC->ADC_CR2 &= MADC_GREG_SOURCE_MASK;
		ADC->ADC_CR2 |= ptr_u8config->RegGP_trig << 17;
		if (ptr_u8config->RegGP_trig != MADC_SWSTART)
		{
			SET_BIT(ADC->ADC_CR2, EXTTRIG);
		}

		/**********************************************************************/

		/*	use to select the trig of the Injected group conversion*/
		ADC->ADC_CR2 &= MADC_GINJ_SOURCE_MASK;
		ADC->ADC_CR2 |= ptr_u8config->InjGP_trig << 12;
		if(ptr_u8config->InjGP_trig != MADC_JSWSTART)
		{
			SET_BIT(ADC->ADC_CR2, JEXTTRIG);
		}

		/**********************************************************************/

		/* use to select conversion mood and scan mode and data Align mood and */
		switch(ptr_u8config->Conv_Mood)
		{
		case MADC_SINGLE_CONV:
			CLR_BIT(ADC->ADC_CR2, CONT);
			break;
		case MADC_CONTINUES_CONV:
			SET_BIT(ADC->ADC_CR2, CONT);
			break;
		default:
			local_state = OUT_OF_RANG_ERR;
		}
		/**********************************************************************/

		switch (ptr_u8config->Scan_Mood)
		{
		case MADC_DISABLE:
			CLR_BIT(ADC->ADC_CR1, SCAN);
			break;
		case MADC_ENABLE:
			SET_BIT(ADC->ADC_CR1, SCAN);
			break;
		default:
			local_state = OUT_OF_RANG_ERR;
		}
		/**********************************************************************/
		switch (ptr_u8config->Data_Alignment)
		{
		case MADC_RIGHT_ALLIGN:
			CLR_BIT(ADC->ADC_CR2, ALIGN);
			break;
		case MADC_LEFT_ALLIGN:
			SET_BIT(ADC->ADC_CR2, ALIGN);
			break;
		default:
			local_state = OUT_OF_RANG_ERR;
		}

		/**********************************************************************/
		/* Enable the ADC Calibration */

		SET_BIT(ADC->ADC_CR2, ADON);

		SET_BIT(ADC->ADC_CR2, CAL);

		while (GET_BIT(ADC->ADC_CR2, CAL));



	}
	else
	{
		local_state = NULL_PTR_ERR;
	}

	return local_state;
}


/*
 *	@brief
 *
 *	@para
 *	@retval
 */

ErrorState_t MADC_enRegGroupChannel_Init(MADC_GROUP_t *ptr_u8GroupConfig)
{
	ErrorState_t local_u8state = SUCCESS;

	if (ptr_u8GroupConfig != NULL)
	{
		if ((ptr_u8GroupConfig->channel <= MADC_channel17) && (ptr_u8GroupConfig->Index <= MADC_INDEX_16))
		{
			/*	use to set the Regular channel and their index in Sequence register*/
			if (ptr_u8GroupConfig->Index < 6)
			{
				ADC->ADC_SQR[2] &= (MADC_GROUP_CHANNELS_MASK<< (ptr_u8GroupConfig->Index * MADC_CHANNEL_OFFSET));
				ADC->ADC_SQR[2] |= (ptr_u8GroupConfig->channel<< (ptr_u8GroupConfig->Index * MADC_CHANNEL_OFFSET));
			}

			else if (ptr_u8GroupConfig->Index< 12)
			{
				ptr_u8GroupConfig->Index-= 6;
				ADC->ADC_SQR[1] &= (MADC_GROUP_CHANNELS_MASK << (ptr_u8GroupConfig->Index * MADC_CHANNEL_OFFSET));
				ADC->ADC_SQR[1] |= (ptr_u8GroupConfig->channel << (ptr_u8GroupConfig->Index * MADC_CHANNEL_OFFSET));
			}

			else if (ptr_u8GroupConfig->Index< 16)
			{
				ptr_u8GroupConfig->Index-= 12;
				ADC->ADC_SQR[0] &=(MADC_GROUP_CHANNELS_MASK<< (ptr_u8GroupConfig->Index * MADC_CHANNEL_OFFSET));
				ADC->ADC_SQR[0] |= (ptr_u8GroupConfig->channel<< (ptr_u8GroupConfig->Index * MADC_CHANNEL_OFFSET));
			}

			/**********************************************************************/
			/*	use to select the Sample of each Adc Channel */
			if (ptr_u8GroupConfig->channel < MADC_channel10)
			{
				ADC->ADC_SMPR[1] &= ~(MADC_SAMPLE_CHANNEL_MASK << (ptr_u8GroupConfig->channel * MADC_SAMPLE_OFFSET)) ;
				ADC->ADC_SMPR[1] |= ptr_u8GroupConfig->Sample << (ptr_u8GroupConfig->channel * MADC_SAMPLE_OFFSET);
			}
			else if (ptr_u8GroupConfig->channel <= MADC_channel17)
			{
				ptr_u8GroupConfig->channel -= MADC_channel10;
				ADC->ADC_SMPR[0] &= ~(MADC_SAMPLE_CHANNEL_MASK << (ptr_u8GroupConfig->channel * MADC_SAMPLE_OFFSET)) ;
				ADC->ADC_SMPR[0] |= ptr_u8GroupConfig->Sample << (ptr_u8GroupConfig->channel * MADC_SAMPLE_OFFSET);
			}
		}
		else
		{
			local_u8state = OUT_OF_RANG_ERR;
		}
	}
	else
	{
		local_u8state = NULL_PTR_ERR;
	}
	return local_u8state;
}

ErrorState_t MADC_enInjGroupChannel_Init(MADC_GROUP_t *ptr_u8Injconnfig)
{
	ErrorState_t local_u8state = SUCCESS;

	if (ptr_u8Injconnfig != NULL)
	{
		if ((ptr_u8Injconnfig->channel <= MADC_channel17) && (ptr_u8Injconnfig->Index <= 3))
		{
			ADC->ADC_JSQR &= (MADC_GROUP_CHANNELS_MASK<< (ptr_u8Injconnfig->Index * MADC_CHANNEL_OFFSET));
			ADC->ADC_JSQR = (ptr_u8Injconnfig->channel << (ptr_u8Injconnfig->Index  * MADC_CHANNEL_OFFSET));

			/**********************************************************************/
			/*	use to select the Sample of each Adc Channel */
			if (ptr_u8Injconnfig->channel < MADC_channel10)
			{
				ADC->ADC_SMPR[1] &= ~(MADC_SAMPLE_CHANNEL_MASK << (ptr_u8Injconnfig->channel * MADC_SAMPLE_OFFSET)) ;
				ADC->ADC_SMPR[1] |= (ptr_u8Injconnfig->Sample << (ptr_u8Injconnfig->channel * MADC_SAMPLE_OFFSET));
			}
			else if (ptr_u8Injconnfig->channel <= MADC_channel17)
			{
				ptr_u8Injconnfig->channel -= MADC_channel10;
				ADC->ADC_SMPR[0] &= ~(MADC_SAMPLE_CHANNEL_MASK << (ptr_u8Injconnfig->channel * MADC_SAMPLE_OFFSET)) ;
				ADC->ADC_SMPR[0] |= (ptr_u8Injconnfig->Sample << (ptr_u8Injconnfig->channel * MADC_SAMPLE_OFFSET));
			}
		}
		else
		{
			local_u8state = OUT_OF_RANG_ERR;
		}
	}
	else
	{
		local_u8state = NULL_PTR_ERR;
	}
	return local_u8state;
}

ErrorState_t MADC_enRegChannel_Conv(u16 *ptr_u16data)
{
	ErrorState_t local_state = SUCCESS ;

	if(ptr_u16data != NULL)
	{
		SET_BIT(ADC->ADC_CR2, ADON);

		/* Enable the ADC Peripherial */
		SET_BIT(ADC->ADC_CR2, SWSTART);

		/*3. wait till the conversion is finished */
		while (!(GET_BIT(ADC->ADC_SR, EOC)));

		ADC->ADC_SR = 0;

		/* 4. get the data from Data register and assign it to ptr_data */
		*ptr_u16data = ADC->ADC_DR;

		ADC->ADC_DR = 0;

	}

	else
	{
		local_state = NULL_PTR_ERR;
	}

	return local_state;
}

ErrorState_t MADC_enInjChannel_Conv(MADC_INDEX_t copy_u8Index, u16 *ptr_u16data)
{
	ErrorState_t local_state = SUCCESS;

	if(ptr_u16data != NULL)
	{
		if (copy_u8Index <= MADC_INDEX_3)
		{
			/*2. start conversion */
			SET_BIT(ADC->ADC_CR2, ADON);

			SET_BIT(ADC->ADC_CR2, JSWSTART);

			/*3. wait till the conversion is finished */
			while (!(GET_BIT(ADC->ADC_SR, JEOC)));

			/* 4. get the data from Data register and assign it to ptr_data */
			*ptr_u16data = ADC->ADC_JDR[copy_u8Index];
		}

		else
		{
			local_state = OUT_OF_RANG_ERR;
		}
	}

	else
	{
		local_state = NULL_PTR_ERR;
	}

	return local_state;
}

ErrorState_t MADC_enEnableInt(MADC_INT_t copy_u8Interrupt)
{
	ErrorState_t local_state = SUCCESS;
	if ((copy_u8Interrupt <= MADC_JEOC_INT) && (copy_u8Interrupt >= MADC_EOC_INT))
	{
		SET_BIT(ADC->ADC_CR1, copy_u8Interrupt);
	}

	else
	{
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}

ErrorState_t MADC_enDisableInt(MADC_INT_t copy_u8Interrupt)
{
	ErrorState_t local_state = SUCCESS;
	if ((copy_u8Interrupt <= MADC_JEOC_INT) && (copy_u8Interrupt >= MADC_EOC_INT))
	{
		CLR_BIT(ADC->ADC_CR1, copy_u8Interrupt);
	}

	else
	{
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}

ErrorState_t MADC_enIntCallBack(void(*CallBack_ptr)(void))
{
	ErrorState_t local_state = SUCCESS;
	if (CallBack_ptr != NULL)
	{
		ADC_CallBack = CallBack_ptr;
	}

	else
	{
		local_state = NULL_PTR_ERR;
	}
	return local_state;
}


/********************************************************************************
 * HANDLEAR IMPLEMENTATION
 ********************************************************************************/

void ADC1_2_IRQHandler(void)
{
	if (ADC_CallBack != NULL)
	{
		if (GET_BIT(ADC->ADC_SR, EOC))
		{

		}
		else if (GET_BIT(ADC->ADC_SR, JEOC))
		{

		}
		ADC_CallBack();
	}
}


