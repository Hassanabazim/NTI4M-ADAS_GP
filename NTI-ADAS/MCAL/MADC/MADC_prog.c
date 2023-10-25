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
		ADC->ADC_SQR[0] &= MADC_REG_CHANNELS_MASK;
		ADC->ADC_SQR[0] |=	ptr_u8config->Reg_ChNum << 20;

		ADC->ADC_JSQR &= MADC_INJ_CHANNELS_MASK;
		ADC->ADC_JSQR |= ptr_u8config->Inj_ChNum << 20;

		ADC->ADC_CR2 &= MADC_GREG_SOURCE_MASK;
		ADC->ADC_CR2 |= ptr_u8config->RegGP_trig << 17;
		if (ptr_u8config->RegGP_trig != MADC_SWSTART)
		{
			SET_BIT(ADC->ADC_CR2, EXTTRIG);
		}

		ADC->ADC_CR2 &= MADC_GINJ_SOURCE_MASK;
		ADC->ADC_CR2 |= ptr_u8config->InjGP_trig << 12;
		if (ptr_u8config->InjGP_trig != MADC_JSWSTART)
		{
			SET_BIT(ADC->ADC_CR2, JEXTTRIG);
		}



		switch(ptr_u8config->Conv_Mood)
		{
		case MADC_DISABLE:
			CLR_BIT(ADC->ADC_CR2, CONT);
			break;
		case MADC_ENABLE:
			CLR_BIT(ADC->ADC_CR2, CONT);
			break;
		default:
			local_state = OUT_OF_RANG_ERR;
		}

		switch (ptr_u8config->Scan_Mood)
		{
		case MADC_DISABLE:
			CLR_BIT(ADC->ADC_CR1, SCAN);
			break;
		case MADC_ENABLE:
			CLR_BIT(ADC->ADC_CR1, SCAN);
			break;
		default:
			local_state = OUT_OF_RANG_ERR;
		}


		switch (ptr_u8config->Data_Alignment)
		{
		case MADC_DISABLE:
			CLR_BIT(ADC->ADC_CR2, ALIGN);
			break;
		case MADC_ENABLE:
			SET_BIT(ADC->ADC_CR2, ALIGN);
			break;
		default:
			local_state = OUT_OF_RANG_ERR;
		}

		/* Enable the ADC Peripherial */
		SET_BIT(ADC->ADC_CR2, ADON);

		/* Enable the ADC Calibration */
		SET_BIT(ADC->ADC_CR2, CAL);
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

ErrorState_t MADC_enSampleChannel(MADC_CHANNELS_t copy_u8channel, MADC_SAMPLE_t copy_u8sample)
{
	ErrorState_t local_state = SUCCESS;
	u8 local_u8RegIndex = copy_u8channel / 10;

	if (copy_u8channel < MADC_channel17)
	{
		ADC->ADC_SMPR[local_u8RegIndex] &= MADC_SAMPLE_CHANNEL_MASK ;
		ADC->ADC_SMPR[local_u8RegIndex] |= copy_u8sample << (copy_u8channel * MADC_SAMPLE_OFFSET);
	}
	else
	{
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}

ErrorState_t MADC_enRegSingleChannel(MADC_CHANNELS_t copy_u8channel, u16 *ptr_u16data)
{
	ErrorState_t local_state = SUCCESS;

	if(ptr_u16data != NULL)
	{
		if (copy_u8channel <= MADC_channel17)
		{
			ADC->ADC_SQR[2] = 0;
			ADC->ADC_SQR[2] = copy_u8channel;

			/*2. start conversion */
			SET_BIT(ADC->ADC_CR2, SWSTART);

			/*3. wait till the conversion is finished */
			while (!(GET_BIT(ADC->ADC_SR, EOC)));

			/* 4. get the data from Data register and assign it to ptr_data */
			ptr_u16data = (u16*)ADC->ADC_DR;
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

ErrorState_t MADC_enInjSingleChannel(MADC_CHANNELS_t copy_u8channel, u16 *ptr_u16data)
{
	ErrorState_t local_state = SUCCESS;

	if(ptr_u16data != NULL)
	{
		if (copy_u8channel < MADC_channel17)
		{
			ADC->ADC_JSQR |= copy_u8channel;

			/*2. start conversion */
			SET_BIT(ADC->ADC_CR2, JSWSTART);

			/*3. wait till the conversion is finished */
			while (!(GET_BIT(ADC->ADC_SR, JEOC)));

			/* 4. get the data from Data register and assign it to ptr_data */
			ptr_u16data = (u16*)ADC->ADC_JDR[0];
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

ErrorState_t MADC_enInjGroupChannel(MADC_CHANNELS_t copy_u8channel, u8 copy_u8index, u16 *ptr_u16data)
{
	ErrorState_t local_state = SUCCESS;

	if ((copy_u8channel <= MADC_channel17) && (copy_u8index<=3))
	{
		ADC->ADC_JSQR &= MADC_GROUP_CHANNELS_MASK<< (copy_u8index * MADC_CHANNEL_OFFSET);
		ADC->ADC_JSQR = copy_u8channel<< (copy_u8index * MADC_CHANNEL_OFFSET);

		/*2. wait till the conversion is finished */
		while (!(GET_BIT(ADC->ADC_SR, EOC)));

		/* 3. get the data from Data register and assign it to ptr_data */
		ptr_u16data = (u16*)ADC->ADC_JDR[copy_u8index];
	}

	else
	{
		local_state = OUT_OF_RANG_ERR;
	}

	return local_state;
}

ErrorState_t MADC_enRegGroupChannel(MADC_CHANNELS_t copy_u8channel, u8 copy_u8index, u16 *ptr_u16data)
{
	ErrorState_t local_state = SUCCESS;

	if (copy_u8channel <= MADC_channel17)
	{
		if (copy_u8index < 6)
		{
			ADC->ADC_SQR[2] &= MADC_GROUP_CHANNELS_MASK<< (copy_u8index * MADC_CHANNEL_OFFSET);
			ADC->ADC_SQR[2] = copy_u8channel<< (copy_u8index * MADC_CHANNEL_OFFSET);
		}

		else if (copy_u8index < 12)
		{
			copy_u8index -= 6;
			ADC->ADC_SQR[1] &= MADC_GROUP_CHANNELS_MASK<< (copy_u8index * MADC_CHANNEL_OFFSET);
			ADC->ADC_SQR[1] = copy_u8channel<< (copy_u8index * MADC_CHANNEL_OFFSET);
		}

		else if (copy_u8index < 16)
		{
			copy_u8index -= 12;
			ADC->ADC_SQR[0] &= MADC_GROUP_CHANNELS_MASK<< (copy_u8index * MADC_CHANNEL_OFFSET);
			ADC->ADC_SQR[0] = copy_u8channel<< (copy_u8index * MADC_CHANNEL_OFFSET);
		}
		else
		{

		}

		/*2. wait till the conversion is finished */
		while (!(GET_BIT(ADC->ADC_SR, EOC)));

		/* 3. get the data from Data register and assign it to ptr_data */
		ptr_u16data = (u16*)ADC->ADC_DR;
	}

	else
	{
		local_state = OUT_OF_RANG_ERR;
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


