/*
 * LM35_prog.c
 *
 *  Created on: Oct 25, 2023
 *      Author: Mohamed Samir
 */

#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "MADC_int.h"
#include "LM35_interface.h"
#include "LM35_cfg.h"
#include "LM35_interface.h"
#include "LM35_priv.h"




/*******************************************
 * This function Initialize the LM35
 *
 ********************************************/
ErrorState_t LM35_u8TemperatureInit(MADC_INIT_t *Copy_pStructLM35)
{
	u8 Local_u8ErrorState = SUCCESS;
	if(NULL != Copy_pStructLM35)	/* check the validation of the address */
	{
		MADC_enInit(Copy_pStructLM35);
	}
	else
	{
		/*Address not valid */

		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
/*******************************************
 * This function Gets the Temperature direct
 *
 * Return :  1- Error State
 *			 2- The Temperature
 *
 ********************************************/
ErrorState_t LM35_u16GetTemperature(LM35_Object_t *Copy_StructLM35  ,u8 *Copy_u8pLM35Temp)
{
	ErrorState_t Local_u8ErrorState = SUCCESS;
	u16 Local_u16AdcChannelReading, Local_u16AdcVoltageReading ;


	/* 1- check the validation of the pointer to struct */
	if(NULL != Copy_StructLM35)
	{
		/* 2- Read The voltage from ADC */
		MADC_enSampleChannel(Copy_StructLM35 -> LM35_ADC_Channel ,MADC_SAMPLE_239_5CYCLE );
		MADC_enRegSingleChannel(Copy_StructLM35 -> LM35_ADC_Channel ,&Local_u16AdcChannelReading );
		/*3- Converts the reading to Volt */
		Local_u16AdcVoltageReading = ADC_u16ConvertToVolt(Local_u16AdcChannelReading);

		/*4- Return the Temperature , but first check the Copy_u8pLM35Temp validation  */
		if (NULL != Copy_u8pLM35Temp) //check the validation of the address
		{
			*Copy_u8pLM35Temp = Local_u16AdcVoltageReading / (u16)( Copy_StructLM35 ->LM35_Sensitivity );
		}
		else //the address is not valid
		{
			Local_u8ErrorState  = NULL_PTR_ERR;
		}
	}
	else //the address is not valid
	{
		Local_u8ErrorState  = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


u16 ADC_u16ConvertToVolt(u16 Copy_u16ADC_Reading)
{
	u16 Local_u16AdcVolt;

	Local_u16AdcVolt = (u16)( ( (u32)Copy_u16ADC_Reading * (u32)3300 ) / (u32)(1<<12) );
	return Local_u16AdcVolt;

}







