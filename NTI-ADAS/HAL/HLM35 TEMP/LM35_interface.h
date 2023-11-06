/*
 * LM35_interface.h
 *
 *  Created on: Oct 25, 2023
 *      Author: Mohamed Samir
 */

#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

#include "STD_TYPES.h"
#include "MADC_int.h"

 /****************************************
  *    The sensitivity of LM35 is 10 mV/degree Celsius.
  *    As temperature increases, output voltage also increases.
  *       E.g. 250 mV means 25°C.
  *
  ********************************************/
typedef struct
{
	u8  LM35_Sensitivity;	// In milli_volt
	u8  LM35_ADC_Channel;	// From the ADC_interface.h	or you can include the LM35_AdcChannels.h
}LM35_Object_t;


/*******************************************
 * This function Gets the Temperature direct
 *
 * Return :  1- Error State
 *			 2- The Temperature
 *
 ********************************************/
ErrorState_t LM35_u16GetTemperature(LM35_Object_t *Copy_StructLM35  ,u8 *Copy_u8pLM35Temp);


/*******************************************
 * This function Initialize the LM35
 *
 ********************************************/
ErrorState_t LM35_u8TemperatureInit(MADC_INIT_t *Copy_pStructLM35);


/***********************************************************************************************
 * V_ref is in milli_volt to increase the software reading accuracy for Analog parameter
 * in Milli_Volt
 *
 * Analog = Digital 	* Step_Size
 * Analog = ADC_Reading * V_ref  / 2^resolution
 * u16 = u16		* u16 / u8 or u16 => the multiplication will cause over flow then,
 * u16 = (u16)( ( (u32)u16	* (u32)u16 ) / (u32)u8 or u16 );
 *
 ***********************************************************************************************/
u16 ADC_u16ConvertToVolt(u16 Copy_u16ADC_Reading);


#endif /* LM35_INTERFACE_H_ */
