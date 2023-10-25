/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  MRCC_prog.c
 *         @Module	:  RCC
 *
 *  Description:  This file provide Module APIs code Implementation
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "REGISTERS.h"
#include "ERROR_STATE.h"
#include "MRCC_int.h"
#include "MRCC_config.h"
#include "MRCC_priv.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : ErrorState_t MRCC_enSysClkINIT(void)
* \Description     : Selecting and Initialize the SysClock
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Return value:   : ErrorState_t  SUCEESS
*
*******************************************************************************/
ErrorState_t MRCC_enSysClkINIT(void)
{
	/** CLK source is HSE CRYSTAL **/
#if (MRCC_CLK_TYPE == MRCC_HSE_CRYSTAL)
	/* 1. ENABLE the HSE */
	SET_BIT(RCC->RCC_CR, HSEON);
	/* 2. Clear the HSEBYPASS PIN to choose CRYSTAL */
	CLR_BIT(RCC->RCC_CR, HSEBYP);

	/* 3. wait till HSE is READY 'settling time finished', stable */
	while (!(GET_BIT(RCC->RCC_CR, HSERDY)));

	/* 4. if CSS is ENABLED, set the CSS pin */
#if(MRCC_CSS_EN == MRCC_CSS_ON)
	{
		SET_BIT(RCC->RCC_CR,CSS);
	}
#endif

	/* 5. Enable System switch clock with HSE */
	SET_BIT(RCC->RCC_CFGR, SWC);

	/** CLK source is HSE RC BYPASS **/
#elif(MRCC_CLK_TYPE == MRCC_HSE_RC)
	/* 1. ENABLE the HSE */
	SET_BIT(RCC->RCC_CR, HSEON);
	/*2. set the HSEBYPASS PIN to choose RC */
	SET_BIT(RCC->RCC_CR, HSEBYP);

	/* 3. wait till HSE is READY 'settling time finished', stable */
	while (!(GET_BIT(RCC->RCC_CR, HSERDY)));

	/* 4. if CSS is ENABLED, set the CSS pin */
#if(MRCC_CSS_EN == MRCC_CSS_ON)
	{
		SET_BIT(RCC->RCC_CR,CSS);
	}
#endif

	/* 5. Enable System switch clock with HSE */
	SET_BIT(RCC->RCC_CFGR, SWC);


	/** CLK source is HSI **/
#elif(MRCC_CLK_TYPE == MRCC_HSI)
	/* 1. ENABLE the HSI */
	SET_BIT(RCC->RCC_CR, HSION);

	/* 2. wait till HSE is READY 'settling time finished', stable */
	while (!(GET_BIT(RCC->RCC_CR, HSIRDY)));

	/* 3. Enable System switch clock with HSI */
	CLR_BIT(RCC->RCC_CFGR, SWC);

	/** CLK source is RCC_PLL **/
#elif(MRCC_CLK_TYPE == MRCC_PLL)
	/* 1. choose PLL input CLK Source */
#if (MRCC_PLL_INPUT_MODE == MRCC_PLL_HSI_DIV_2)
	CLR_BIT(RCC->RCC_CFGR, PLLSRC);

#elif (MRCC_PLL_INPUT_MODE == MRCC_PLL_HSE)
	SET_BIT(RCC->RCC_CFGR, PLLSRC);
	CLR_BIT(RCC->RCC_CFGR, PLLXTPRE);

#elif (MRCC_PLL_INPUT_MODE == MRCC_PLL_HSE_DIV_2)
	SET_BIT(RCC->RCC_CFGR, PLLXTPRE);
#else
#error("WRONG PLL INPUT SELECTION!");
#endif

	/* 2. Mask the PLL MUL pins and Set the value of MUL factor */
	RCC->RCC_CFGR &= MRCC_PLL_CLK_MASK;
	RCC->RCC_CFGR |= MRCC_PLL_MUL_FAC ;

	/* 3. Enable the PLL  */
	SET_BIT(RCC->RCC_CR, PLLON);

	/* 4. wait till HSE is READY 'settling time finished', stable */
	while (!(GET_BIT(RCC->RCC_CR, PLLRDY)));

	/* 5. if CSS is On, set the CSS pin */
#if(MRCC_CSS_EN == RCC_CSS_ON)
	{
		SET_BIT(RCC->RCC_CR,CSS);
	}
#endif

	/* 6. Enable System switch clock with PLL*/
	SET_BIT(RCC->RCC_CFGR, SWC)<<1;

#else
#error("WRONG CLK TYPE");
#endif
	/* MASK the AHB and set the value of the chosen prescaler*/
	RCC->RCC_CFGR &= MRCC_AHB_MASK;
	RCC->RCC_CFGR |= MRCC_AHB_PRESCALER;

	/* MASK the APB1 and set the value of the chosen prescaler*/
	RCC->RCC_CFGR &= MRCC_APB1_MASK;
	RCC->RCC_CFGR |= MRCC_APB1_PRESCALER_MODE;

	/* MASK the APB2 and set the value of the chosen prescaler*/
	RCC->RCC_CFGR &= MRCC_APB2_MASK;
	RCC->RCC_CFGR |= MRCC_APB2_PRESCALER_MODE;

#if (MRCC_MCO_EN == MRCC_MCO_ON)
	{
		RCC->RCC_CFGR &= MRCC_MCO_MASK;
		RCC->RCC_CFGR |= MRCC_MCO_MODE ;
	}
#endif

	return SUCCESS;
}

/******************************************************************************
* \Syntax          : ErrorState_t MRCC_enEnablePeripheralCLK(u8 copy_u8Peripheral)
* \Description     : Enable the Peripheral clock
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : copy_u8Peripheral
* \Return value:   : ErrorState_t  -> SUCEESS
* 								   -> OUT_OF_RANG_ERR
*******************************************************************************/

ErrorState_t MRCC_enEnablePeripheralCLK(u8 copy_u8Peripheral)
{
	ErrorState_t local_state = SUCCESS;

	/* based on predefined Peripheral, switch to corresponding Register, and Enabled it*/
	if (copy_u8Peripheral < MRCC_AHB_REG)
		SET_BIT(RCC->RCC_AHBENR, copy_u8Peripheral);

	else if (copy_u8Peripheral < MRCC_APB1_REG)
	{
		copy_u8Peripheral -= MRCC_AHB_REG;
		SET_BIT(RCC->RCC_APB1ENR, copy_u8Peripheral);
	}

	else if (copy_u8Peripheral < MRCC_APB2_REG)
	{
		copy_u8Peripheral -= MRCC_APB1_REG;
		SET_BIT(RCC->RCC_APB2ENR, copy_u8Peripheral);
	}

	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state;
}


/******************************************************************************
* \Syntax          : ErrorState_t MRCC_enDisablePeripheralCLK(u8 copy_u8Peripheral)
* \Description     : Enable the Peripheral clock
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : copy_u8Peripheral
* \Return value:   : ErrorState_t  -> SUCEESS
* 								   -> OUT_OF_RANG_ERR
*******************************************************************************/

ErrorState_t MRCC_enDisablePeripheralCLK(u8 copy_u8Peripheral)
{
	ErrorState_t local_state = SUCCESS;

	/* based on predefined Peripheral, switch to corresponding Register, and Enabled it*/
	if (copy_u8Peripheral < MRCC_AHB_REG)
		CLR_BIT(RCC->RCC_AHBENR, copy_u8Peripheral);

	else if (copy_u8Peripheral < MRCC_APB1_REG)
	{
		copy_u8Peripheral -= MRCC_AHB_REG;
		CLR_BIT(RCC->RCC_APB1ENR, copy_u8Peripheral);
	}

	else if (copy_u8Peripheral < MRCC_APB2_REG)
	{
		copy_u8Peripheral -= MRCC_APB1_REG;
		CLR_BIT(RCC->RCC_APB2ENR, copy_u8Peripheral);
	}

	else
	{
		local_state = OUT_OF_RANG_ERR;
	}
	return local_state ;
}


/**********************************************************************************************************************
 *  END OF FILE: MRCC_prog.c
 *********************************************************************************************************************/
