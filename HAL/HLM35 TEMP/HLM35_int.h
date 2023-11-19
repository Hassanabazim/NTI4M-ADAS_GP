/*
 * LM35_interface.h
 *
 *  Created on: Oct 25, 2023
 *      Author: Mohamed Samir
 */

#ifndef HLM35_INT_H_
#define HLM35_INT_H_


/*******************************************
 * This function Gets the Temperature direct
 *
 * Return :  1- Error State
 *			 2- The Temperature
 *
 ********************************************/
ErrorState_t LM35_u16GetTemperature(u8 *Copy_u8pLM35Temp);


/*******************************************
 * This function Initialize the LM35
 *
 ********************************************/
ErrorState_t LM35_u8TemperatureInit(MADC_GROUP_t *Copy_pStructLM35);


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


#endif /* HLM35_INT_H_ */
