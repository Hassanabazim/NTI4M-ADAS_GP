/*
 * LDR_AdcChannels.h
 *
 *  Created on: Oct 26, 2023
 *      Author: Mohamed Samir
 */

#ifndef LM35_PRIV_H_
#define LM35_PRIV_H_


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

#endif /* LM35_PRIV_H_ */
