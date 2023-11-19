/*
 * Analog_prog.c
 *
 *  Created on: Nov 19, 2023
 *      Author: Hassa
 */

#include "STD_TYPES.h"
#include "MRCC_int.h"
#include "MGPIO_int.h"
#include "MSYSTICK_int.h"
#include "MADC_int.h"
#include "HLCD_int.h"
#include "HRAIN_int.h"
#include "HLM35_int.h"
#include "Analog_int.h"


void AnalogSensor_voidInit(void)
{
	MRCC_enEnablePeripheralCLK(MRCC_ADC1);

#if(APP_MODE == DEBUG_MODE)
	/* LCD */
	lcd_vidInit();
#endif

	/* LM35 */
	MADC_GROUP_t LM35_TEMP =  {MADC_channel0, MADC_SAMPLE_71_5CYCLE, MADC_INDEX_0};
	LM35_u8TemperatureInit(&LM35_TEMP);

	/* Rain Sensor */
	MADC_GROUP_t RAIN_SEN  =  {MADC_channel7, MADC_SAMPLE_71_5CYCLE, MADC_INDEX_1};
	RainSensor_u8Init(&RAIN_SEN);

	MADC_INIT_t Sensors = {MADC_CONTINUES_CONV, MADC_ENABLE,MADC_RIGHT_ALLIGN,MADC_channel1,MADC_SWSTART, MADC_channel0,MADC_JSWSTART};
	MADC_enInit(&Sensors);
}


void AnalogSensor_voidAction(void)
{
	u8 Local_u8TemperatureDegree, Local_u8WaterLevel;

	while (1)
	{
		LM35_u16GetTemperature(&Local_u8TemperatureDegree);

		if (Local_u8TemperatureDegree > HIGH_TEMP)
		{
			// do Action
		}
		else if (Local_u8TemperatureDegree > AVG_TEMP)
		{
			// do Action
		}

		RainSensor_u8GetWaterLevel(&Local_u8WaterLevel);

		if (Local_u8WaterLevel == WATER_NO_LEVEL)
		{
			// do servo Action
		}
		else if (Local_u8WaterLevel == WATER_LEVEL_LOW)
		{
			// do servo Action
		}
		else if (Local_u8WaterLevel == WATER_LEVEL_MIDDEL)
		{
			// do servo Action
		}
		else if (Local_u8WaterLevel == WATER_LEVEL_HIGH)
		{
			// do servo Action
		}

#if(APP_MODE == DEBUG_MODE)
		lcd_vidGotoRowColumn(0, 0);
		lcd_vidDisplyStr("temp =");
		lcd_vidDisplayNum(Local_u8TemperatureDegree);

		lcd_vidGotoRowColumn(1, 0);
		lcd_vidDisplyStr("rain =");
		lcd_vidDisplayNum(Local_u8WaterLevel);
		MSYSTICK_enDelayMS(500);
		lcd_vidClrDislay();
#endif

	}
}


