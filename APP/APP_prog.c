/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  Hassan Abdelazim Abdelsalam
 *         @File	:  APP_prog.c
 *         @Module	:  APP
 *
 *  Description:  This file provide Module APIs code Implementation
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "MRCC_int.h"
#include "MGPIO_int.h"
#include "MNVIC_int.h"
#include "MEXTI_int.h"
#include "MAFIO_int.h"
#include "MSYSTICK_int.h"
#include "APP_int.h"
#include "APP_config.h"
#include "APP_priv.h"
#include "HDCMOTOR_int.h"




#include "TIMERx_interface.h"


/* PWM from chat GPT */







/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : void App_voidstartApp(void)
 *
 * \Description     : This Services for start the Application
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 *
 * \Return value:   : None
 *******************************************************************************/
void App_voidstartApp(void)
{


	MRCC_enSysClkINIT();
	MRCC_enEnablePeripheralCLK(MRCC_IOPA);
	MRCC_enEnablePeripheralCLK(MRCC_TIM3);
	MGPIO_enSetPinDirection(PORTA, PIN2, OUT_2MHZ_AF_PUSH_PULL);
	MGPIO_enSetPinDirection(PORTA, PIN3, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(PORTA, PIN4, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(PORTA, PIN5, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(PORTA, PIN6, OUT_2MHZ_AF_PUSH_PULL);
	MGPIO_enSetPinDirection(PORTA, PIN7, OUT_2MHZ_AF_PUSH_PULL);
	//MTIMERx_voidInit();
	TIM3_PWM_Init();
	TIM3_PWM_CH2_Generate(30);
	TIM3_PWM_CH1_Generate(90);
	while (1)
	{
		TIM3_PWM_CH1_Generate(50);


	}
}
/**********************************************************************************************************************
 *  END OF FILE: APP_prog.c
 *********************************************************************************************************************/
