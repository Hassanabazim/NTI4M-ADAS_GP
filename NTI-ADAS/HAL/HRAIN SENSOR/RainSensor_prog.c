/*
 * RainSensor_prog.c
 *
 *  Created on: Oct 30, 2023
 *      Author: Mohamed Samir
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATE.h"
#include "MADC_int.h"
#include "RainSensor_interface.h"
#include "RainSensor_cfg.h"
#include "RainSensor_prv.h"



/*******************************************
 * This function Initialize the Rain Sensor
 *
 ********************************************/
ErrorState_t RainSensor_u8Init(MADC_INIT_t *Copy_pStructRainSensor)
{
	ErrorState_t Local_u8ErrorState = SUCCESS;
	if(NULL != Copy_pStructRainSensor)	/* check the validation of the address */
	{
		MADC_enInit(Copy_pStructRainSensor);
	}
	else
	{
		/*Address not valid */

		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}


/*********************************
 * USES: Get the Water Level
 * Return:  1- Water Level
 * 			2- Error State
 *********************************/
ErrorState_t RainSensor_u8GetWaterLevel(u8 Copy_u8ADCChannel,u8 *Copy_u8pStoreVariable)
{
	ErrorState_t Local_u8ErrorState = SUCCESS;
	if(NULL != Copy_u8pStoreVariable)
	{
		//u16 Local_u16AverageWaterLevel;
		/* 1- Read The Analog Value */
		u16 Local_u16AdcChannelReading, Local_u16AdcVoltageReading ;

		/* 2- Read The voltage from ADC */
		MADC_enSampleChannel(Copy_u8ADCChannel ,MADC_SAMPLE_239_5CYCLE );
		MADC_enRegSingleChannel(Copy_u8ADCChannel ,&Local_u16AdcChannelReading );

		/* 3- Get the Precentage water level */
		Local_u16AdcChannelReading = ((Local_u16AdcChannelReading / HRAIN_SENSOR_RESOULTION) * HRAIN_SENSOR_PERCENTAGE);

		/* 4- Converts it to Water Level*/
		//Local_u16AverageWaterLevel = (RAIN_SENSOR_HIGH_LEVEL_VOLT  + RAIN_SENSOR_LOW_LEVEL_VOLT) / (u16)2;

		if(Local_u16AdcChannelReading == RAIN_SENSOR_NO_RAIN )
		{
			*Copy_u8pStoreVariable = WATER_NO_LEVEL;
		}
		else if((Local_u16AdcChannelReading > RAIN_SENSOR_NO_RAIN)&&(Local_u16AdcChannelReading <= RAIN_SENSOR_LOW_LEVEL_VOLT))
		{
			*Copy_u8pStoreVariable = WATER_LEVEL_LOW;
		}
		else if((Local_u16AdcChannelReading > RAIN_SENSOR_LOW_LEVEL_VOLT) && (Local_u16AdcVoltageReading <= RAIN_SENSOR_MIDDLE_LEVEL_VOLT))
		{
			*Copy_u8pStoreVariable = WATER_LEVEL_MIDDEL;
		}
		else if(Local_u16AdcChannelReading > RAIN_SENSOR_MIDDLE_LEVEL_VOLT && (Local_u16AdcVoltageReading <= RAIN_SENSOR_HIGH_LEVEL_VOLT))
		{
			*Copy_u8pStoreVariable = WATER_LEVEL_HIGH;
		}
		else if(Local_u16AdcChannelReading > RAIN_SENSOR_HIGH_LEVEL_VOLT && (Local_u16AdcVoltageReading <= RAIN_SENSOR_MAX_LEVEL_VOLT))
		{
			*Copy_u8pStoreVariable = WATER_LEVEL_MAX;
		}
		else
		{
			Local_u8ErrorState  = FAILARE;
		}
	}
	else
	{
		/*This is Non Valid address*/
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}













