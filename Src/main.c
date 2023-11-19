#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "MRCC_int.h"
#include "MGPIO_int.h"
#include "MNVIC_int.h"
#include "MEXTI_int.h"
#include "MAFIO_int.h"
#include "MSYSTICK_int.h"
#include "MADC_int.h"
#include "MUSART_int.h"
#include "HLCD_int.h"
#include "HRAIN_int.h"
#include "HLM35_int.h"
#include "TIMERx_interface.h"
#include "HDCMOTOR_int.h"
#include "RPLIDAR_interface.h"
#include "IR_interface.h"
#include "ACC_int.h"
#include "Analog_int.h"
#include "Blindspot_int.h"
#include "collesion_int.h"
#include "Emergency_int.h"
#include "Lanekeeping_int.h"
#include "laneDept_int.h"
#include "Mobileapp_int.h"
#include "sleep_int.h"
#include "SCM.h"


int main(void)
{

	MRCC_enSysClkINIT();
	MRCC_enEnablePeripheralCLK(MRCC_IOPA);
	MRCC_enEnablePeripheralCLK(MRCC_TIM3);
	MRCC_enEnablePeripheralCLK(MRCC_AFIO);
	MGPIO_enSetPinDirection(PORTA, PIN6, OUT_2MHZ_AF_PUSH_PULL);
	//	MGPIO_enSetPinDirection(PORTA, PIN7, OUT_2MHZ_AF_PUSH_PULL);
	TIM3_PWM_Init();
	HDCMOTOR_voidInit();
	TIM3_PWM_CH1_Generate(70);
	//	TIM3_PWM_CH2_Generate(90);
	MSYSTICK_enInit();
	while (1)
	{


		//		HDCMOTOR_voidForward();
		//		HDCMOTOR_voidTurnLeft();
		//		MSYSTICK_enDelayMS(1000);
		//		HDCMOTOR_voidForwardBackwardStop();
		//		HDCMOTOR_voidDiretionalStop();
		//		MSYSTICK_enDelayMS(1000);
		//		/**********************/
		//		HDCMOTOR_voidForwardBackwardStop();
		//		HDCMOTOR_voidTurnRight();
		//		MSYSTICK_enDelayMS(1000);
		//		HDCMOTOR_voidForwardBackwardStop();
		//		HDCMOTOR_voidDiretionalStop();
		//		MSYSTICK_enDelayMS(1000);
		HDCMOTOR_voidBackward();
		HDCMOTOR_voidTurnRight();
		MSYSTICK_enDelayMS(2000);
		HDCMOTOR_voidDiretionalStop();
		HDCMOTOR_voidForwardBackwardStop();
		MSYSTICK_enDelayMS(2000);
		HDCMOTOR_voidForward();
		HDCMOTOR_voidTurnLeft();
		MSYSTICK_enDelayMS(2000);
		HDCMOTOR_voidDiretionalStop();
		HDCMOTOR_voidForwardBackwardStop();
		MSYSTICK_enDelayMS(2000);


		//	/*Enable pripherals  */
		//	MRCC_enSysClkINIT();
		//	MRCC_enEnablePeripheralCLK(MRCC_IOPB);
		//	MRCC_enEnablePeripheralCLK(MRCC_IOPA);
		//	MRCC_enEnablePeripheralCLK(MRCC_TIM3);
		//	MRCC_enEnablePeripheralCLK(MRCC_AFIO);
		//	/*********************************************************************************************************************/
		//	MSYSTICK_enInit();
		//	HDCMOTOR_voidInit();
		//	RPLIDAR_voidINT();
		//
		//	TIM3_PWM_Init();
		//	TIM3_PWM_CH1_Generate(65);
		//	Check_error_t Copy_CheckValue =  RPLIDAR_DescriptorCheck();
		//	float Copy_f32Distnace;
		//	while (1)
		//	{
		//		if(Copy_CheckValue==OK)
		//		{
		//			Copy_f32Distnace=RPLIDAR_GetDistanceValue(170,190);
		//			if(Copy_f32Distnace<900)
		//			{
		//				HDCMOTOR_voidForward();
		//				MGPIO_enSetPinValue(PORTB, PIN10, LOW);
		//			}
		//			else if(Copy_f32Distnace>=1000)
		//			{
		//				HDCMOTOR_voidForwardBackwardStop();
		//				MGPIO_enSetPinValue(PORTB, PIN10, HIGH);
		//			}
		//
		//
		//
		//		}
		//	}
		//
		//	/********* Initialization functions ***************/
		//
		//
		//

	}
}
