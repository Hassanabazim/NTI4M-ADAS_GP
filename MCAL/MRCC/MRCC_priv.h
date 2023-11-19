/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MRCC_priv.h
 *         @Module	:  RCC
 *
 *  Description:  This file provide a local MACROS/Functions
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  HEADER GUARD
 *********************************************************************************************************************/
#ifndef MRCC_PRIV_H_
#define	MRCC_PRIV_H_

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
// REGISTERS PINS
#define	HSION					0
#define HSIRDY					1
#define	HSEON					16
#define HSERDY					17
#define HSEBYP					18
#define CSS						19
#define	PLLON					24
#define PLLRDY					25

#define SWC						0
#define PLLXTPRE				16
#define PLLSRC					17



/**********************************************************************************************************************
*  LOCAL MACROS CFG CONSTANT
*********************************************************************************************************************/
//PINS PRE BULID
#define MRCC_CSS_ON				1
#define MRCC_CSS_OFF			0
#define MRCC_MCO_ON				2
#define MRCC_MCO_OFF			3


//MRCC CLOCK TYPE
#define MRCC_HSE_CRYSTAL		1
#define MRCC_HSE_RC				2
#define MRCC_HSI				3
#define MRCC_PLL				4


//APB1,APB2 PRESCALER
#define MRCC_HCLK_NOT_DIV 		0
#define MRCC_HCLK_DIV_2 		4
#define MRCC_HCLK_DIV_4			5
#define MRCC_HCLK_DIV_8			6
#define MRCC_HCLK_DIV_16		7


//AHB PRESCALER
#define MRCC_SYSCLK_NOT_DIV		0
#define MRCC_SYSCLK_DIV_2		8
#define MRCC_SYSCLK_DIV_4		9
#define MRCC_SYSCLK_DIV_8		10
#define MRCC_SYSCLK_DIV_16		11
#define MRCC_SYSCLK_DIV_64		12
#define MRCC_SYSCLK_DIV_128		13
#define MRCC_SYSCLK_DIV_256		14
#define MRCC_SYSCLK_DIV_512		15


//MCO MODES
#define MRCC_MCO_NO_CLK			0
#define MRCC_MCO_SYS_CLK		4
#define MRCC_MCO_HSI_CLK		5
#define MRCC_MCO_HSE_CLK		6
#define MRCC_MCO_PLL_DIV_2		7


//PLL MUL FACTORS
#define MRCC_PLL_CLK_MUL_2		0x0
#define MRCC_PLL_CLK_MUL_3		0x1
#define MRCC_PLL_CLK_MUL_4		0x2
#define MRCC_PLL_CLK_MUL_5		0x3
#define MRCC_PLL_CLK_MUL_6		0x4
#define MRCC_PLL_CLK_MUL_7		0x5
#define MRCC_PLL_CLK_MUL_8		0x6
#define MRCC_PLL_CLK_MUL_9		0x7
#define MRCC_PLL_CLK_MUL_10		0x8
#define MRCC_PLL_CLK_MUL_11		0x9
#define MRCC_PLL_CLK_MUL_12		0xA
#define MRCC_PLL_CLK_MUL_13		0xB
#define MRCC_PLL_CLK_MUL_14		0xC
#define MRCC_PLL_CLK_MUL_15		0xD
#define MRCC_PLL_CLK_MUL_16		0xE


//PLL SYSTEM SELECTION
#define MRCC_PLL_HSI_DIV_2			0
#define MRCC_PLL_HSE				1
#define MRCC_PLL_HSE_DIV_2			2


//SYSTEM REGISTERS MASKING
#define MRCC_SCW_MASK			0xFFFFFFFC
#define MRCC_AHB_MASK			0xFFFFFF0F
#define MRCC_APB1_MASK			0xFFFFF8FF
#define MRCC_APB2_MASK			0xFFFFC7FF
#define MRCC_PLL_CLK_MASK		0xFFC3FFFF
#define MRCC_MCO_MASK			0xF8FFFFFF
#define MRCC_ADC_MASK			0xFFFF3FFF

//ADC Prescaler
#define MRCC_PCLK2_DIV_2		0
#define MRCC_PCLK2_DIV_4		1
#define MRCC_PCLK2_DIV_6		2
#define MRCC_PCLK2_DIV_8		3

//PERIPHERIAL BUS MACROS
#define MRCC_AHB_REG			32
#define MRCC_APB1_REG			64
#define MRCC_APB2_REG			96



#endif /* MRCC_PRIV_H_ */

/**********************************************************************************************************************
 *  END OF FILE: MRCC_priv.h
 *********************************************************************************************************************/
