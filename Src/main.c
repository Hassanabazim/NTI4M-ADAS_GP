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
#include "HSERVO_inteerface.h"
#include "HRAIN_int.h"
#include "HLM35_int.h"
#include "TIMERx_interface.h"
#include "HDCMOTOR_int.h"
#include "HULTRASONIC_int.h"
#include "RPLIDAR_interface.h"
#include "IR_interface.h"
#include "ACC_int.h"
#include "Lanekeeping_int.h"
#include "Analog_int.h"
#include "Blindspot_int.h"
#include "collesion_int.h"
#include "Emergency_int.h"
#include "Mobileapp_int.h"
#include "sleep_int.h"
#include "SCM.h"


void ADAS_Init(void);

int main(void)
{
	ADAS_Init();

	while(1)
	{

		AnalogSensor_voidAction();
		//ADAS_laneKeeping();
		Check_error_t Copy_CheckValue =  RPLIDAR_DescriptorCheck();
		float Copy_f32Distnace;

		while (1)
		{
			if(Copy_CheckValue==OK)
			{
				Copy_f32Distnace=RPLIDAR_GetDistanceValue(170,190);
				if(Copy_f32Distnace < 700)
				{
					HDCMOTOR_voidForwardBackwardStop();
					MGPIO_enSetPinValue(PORTB, PIN10, LOW);
				}
				else if(Copy_f32Distnace > 900)
				{
					HDCMOTOR_voidForward();
					MGPIO_enSetPinValue(PORTB, PIN10, HIGH);
				}
			}
		}


	}
}



void ADAS_Init(void)
{
	MRCC_enSysClkINIT();
	MRCC_enEnablePeripheralCLK(MRCC_IOPA);
	MRCC_enEnablePeripheralCLK(MRCC_IOPB);
	MRCC_enEnablePeripheralCLK(MRCC_TIM2);
	MRCC_enEnablePeripheralCLK(MRCC_TIM3);
	MRCC_enEnablePeripheralCLK(MRCC_AFIO);

	IR_voidInit();
	SERVO_motor_init();
	AnalogSensor_voidInit();
	HDCMOTOR_voidInit();
	HULTRASONIC_enInit();
	MSYSTICK_enInit();
	TIM3_PWM_Init();
	TIM3_PWM_CH1_Generate(90);
	RPLIDAR_voidINT();
	MGPIO_enSetPinValue(PORTB, PIN10, HIGH);
}

