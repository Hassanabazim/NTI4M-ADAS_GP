 /**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MRCC_config.h
 *         @Module	:  RCC
 *
 *  Description:  This file provide the pre Configuration of the Module
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  HEADER GUARD
 *********************************************************************************************************************/
#ifndef MRCC_CONFIG_H_
#define MRCC_CONFIG_H_

/**********************************************************************************************************************
*  LOCAL MACROS CONFIGURATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
* PLEASE CHOOSE RCC CLOCK TYPE FROM THE FOLLOWING:
		*
		*   MRCC_HSE_CRYSTAL
		*   MRCC_HSE_RC
		*   MRCC_HSI
		*   MRCC_PLL
		*
**********************************************************************************************************************/
#define MRCC_CLK_TYPE	 MRCC_HSI


/**********************************************************************************************************************
* PLEASE CHOOSE CSS MODE FROM THE FOLLOWING:
		*
		*	MRCC_CSS_ON
		* 	MRCC_CSS_OFF
		*	MCO_ON
		* 	MCO_OFF
**********************************************************************************************************************/
#define MRCC_CSS_EN		MRCC_CSS_OFF
#define MRCC_MCO_EN		MRCC_MCO_OFF


/**********************************************************************************************************************
* PLEASE CHOOSE FROM THE FOLLOWING AHB PRESCALER :

		* MRCC_SYSCLK_NOT_DIV
		* MRCC_SYSCLK_DIV_2
		* MRCC_SYSCLK_DIV_4
		* MRCC_SYSCLK_DIV_8
		* MRCC_SYSCLK_DIV_16
		* MRCC_SYSCLK_DIV_64
		* MRCC_SYSCLK_DIV_128
		* MRCC_SYSCLK_DIV_256
		* MRCC_SYSCLK_DIV_512
**********************************************************************************************************************/
#define MRCC_AHB_PRESCALER	(MRCC_SYSCLK_NOT_DIV << 4)

/**********************************************************************************************************************
* PLEASE CHOOSE FROM THE FOLLOWING APB1, APB2 PRESCALER

		* MRCC_HCLK_NOT_DIV
		* MRCC_HCLK_DIV_2
		* MRCC_HCLK_DIV_4
		* MRCC_HCLK_DIV_8
		* MRCC_HCLK_DIV_16
**********************************************************************************************************************/
#define MRCC_APB1_PRESCALER_MODE	(MRCC_HCLK_NOT_DIV << 8)
#define MRCC_APB2_PRESCALER_MODE	(MRCC_HCLK_NOT_DIV << 11)

/**********************************************************************************************************************
* PLEASE CHOOSE FROM THE FOLLOWING MCO MODES:

		*  MRCC_MCO_NO_CLK
		*  MRCC_MCO_SYS_CLK
		*  MRCC_MCO_HSI_CLK
		*  MRCC_MCO_HSE_CLK
		*  MRCC_MCO_PLL_DIV_2
**********************************************************************************************************************/
#define MRCC_MCO_MODE		(MRCC_MCO_NO_CLK << 24)

/**********************************************************************************************************************
*PLEASE CHOOSE FROM THE FOLLOWING PLL MUL FACTORS:

		*	MRCC_PLL_CLK_MUL_2
		*	MRCC_PLL_CLK_MUL_3
		*	MRCC_PLL_CLK_MUL_4
		*	MRCC_PLL_CLK_MUL_5
		*	MRCC_PLL_CLK_MUL_6
		*	MRCC_PLL_CLK_MUL_7
		*	MRCC_PLL_CLK_MUL_8
		*	MRCC_PLL_CLK_MUL_9
		*	MRCC_PLL_CLK_MUL_10
		*	MRCC_PLL_CLK_MUL_11
		*	MRCC_PLL_CLK_MUL_12
		*	MRCC_PLL_CLK_MUL_13
		*	MRCC_PLL_CLK_MUL_14
		*	MRCC_PLL_CLK_MUL_15
		*	MRCC_PLL_CLK_MUL_16
**********************************************************************************************************************/
#if (MRCC_CLK_TYPE == MRCC_PLL)
#define MRCC_PLL_MUL_FAC		(MRCC_PLL_CLK_MUL_2<< 18)


/**********************************************************************************************************************
* PLEASE CHOOSE FROM THE FOLLOWING PLL INPUT SELECTION MODES:

		*  MRCC_PLL_HSI_DIV_2
		*  MRCC_PLL_HSE
		*  MRCC_PLL_HSE_DIV_2
**********************************************************************************************************************/
#define MRCC_PLL_INPUT_MODE 	(MRCC_PLL_HSI_DIV_2)

#endif

#endif  /* MRCC_CONFIG_H_ */

/**********************************************************************************************************************
 *  END OF FILE: MRCC_config.h
 *********************************************************************************************************************/

