/*
 * RainSensor_prog.c
 *
 *  Created on: Oct 30, 2023
 *      Author: Mohamed Samir
 */



#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATE.h"
#include "MGPIO_int.h"
#include "MADC_int.h"
#include "HRAIN_int.h"
#include "HRAIN_config.h"
#include "HRAIN_priv.h"

/*******************************************
 * This function Initialize the Rain Sensor
 *
 ********************************************/
ErrorState_t RainSensor_u8Init(MADC_GROUP_t *Copy_pStructRainSensor)
{
	ErrorState_t Local_u8ErrorState = SUCCESS;
	if(NULL != Copy_pStructRainSensor)	/* check the validation of the address */
	{
		/*GPIO for RainSensor */
		MGPIO_enSetPinDirection(HRAIN_PORT, HRAIN_PIN, IN_ANALOG);
		MADC_enRegGroupChannel_Init(Copy_pStructRainSensor);
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
ErrorState_t RainSensor_u8GetWaterLevel(u8 *Copy_u8pStoreVariable)
{
	ErrorState_t Local_u8ErrorState = SUCCESS;
	if(NULL != Copy_u8pStoreVariable)
	{
		//u16 Local_u16AverageWaterLevel;
		/* 1- Read The Analog Value */
		u16 Local_u16AdcChannelReading ;

		/* 2- Read The voltage from ADC */
		MADC_enRegChannel_Conv(&Local_u16AdcChannelReading);

		/* 3- Get the Precentage water level */
		Local_u16AdcChannelReading = ((Local_u16AdcChannelReading * HRAIN_SENSOR_PERCENTAGE)/ HRAIN_SENSOR_RESOULTION);

		*Copy_u8pStoreVariable = Local_u16AdcChannelReading;
		if(Local_u16AdcChannelReading == RAIN_SENSOR_NO_RAIN )
		{
		 *Copy_u8pStoreVariable = WATER_NO_LEVEL;
		}
		else if((Local_u16AdcChannelReading > RAIN_SENSOR_NO_RAIN) && (Local_u16AdcChannelReading <= RAIN_SENSOR_LOW_LEVEL))
		{
		 *Copy_u8pStoreVariable = WATER_LEVEL_LOW;
		}
		else if((Local_u16AdcChannelReading > RAIN_SENSOR_LOW_LEVEL) && (Local_u16AdcChannelReading <= RAIN_SENSOR_MIDDLE_LEVEL))
		{
		 *Copy_u8pStoreVariable = WATER_LEVEL_MIDDEL;
		}
		else if ((Local_u16AdcChannelReading > RAIN_SENSOR_MIDDLE_LEVEL) && (Local_u16AdcChannelReading <= RAIN_SENSOR_HIGH_LEVEL))
		{
		 *Copy_u8pStoreVariable = WATER_LEVEL_HIGH;
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













