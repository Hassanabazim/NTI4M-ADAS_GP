/********************************************************************************
 * 	@file        		:  							 							*
 *	@Author 	 		:  HASSAN ABDELAZIM ABDELSALAM							*
 *	@Version 			:  1.0.0							 					*
 *	@Date				:  														*
 *********************************************************************************
 *  HEADER GAURD
 ********************************************************************************/
#ifndef MADC_MADC_PRIV_H_
#define MADC_MADC_PRIV_H_


/********************************************************************************
 * MOST USED REGISTER PINS
 ********************************************************************************/
// ADC_CR1 Register
#define SCAN	8

// ADC_CR2 Register

#define SWSTART		22 		//Start conversion of regular channels
#define JSWSTART	21		//Start conversion of injected channels
#define EXTTRIG		20 		//External trigger conversion mode for regular channels
#define JEXTTRIG	15		//External trigger conversion mode for injected channels
#define ALIGN		11  	//Data alignment
#define CAL			2 		//A/D Calibration
#define CONT		1		//Continuous conversion
#define ADON		0		//A/D converter ON / OFF

// ADC_SR Register
#define	AWD			0 		//Analog watchdog flag
#define	EOC			1		//End of conversion
#define	JEOC		2		//Injected channel end of conversion
#define JSTRT		3		//Injected channel Start flag
#define STRT		4		//Regular channel Start flag



/********************************************************************************
 * PRIVATE MACROS CONFIGURATION
 ********************************************************************************/
#define MADC_CHANNEL_OFFSET			5
#define MADC_SAMPLE_OFFSET			3


/********************************************************************************
 *  PRIVATE MACROS MASKS
 ********************************************************************************/
#define MADC_REG_CHANNELS_MASK		0xFF0FFFFF
#define MADC_INJ_CHANNELS_MASK		0xFFFCFFFF

#define MADC_GROUP_CHANNELS_MASK	0xFFFFFFE0

#define MADC_GREG_SOURCE_MASK		0xFFF1FFFF
#define MADC_GINJ_SOURCE_MASK		0xFFFF8FFF

#define MADC_SAMPLE_CHANNEL_MASK	0x7



static void MADC_RegEnable(void);


#endif /* MADC_MADC_PRIV_H_ */
