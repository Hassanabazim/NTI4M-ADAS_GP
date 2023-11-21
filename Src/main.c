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
	ADAS_Distance_Manager();
	ADAS_laneKeeping();
	ADAS_LaneChange();
}


void ADAS_Init(void)
{
	MRCC_enSysClkINIT();
	MRCC_enEnablePeripheralCLK(MRCC_IOPA);
	MRCC_enEnablePeripheralCLK(MRCC_IOPB);
	MRCC_enEnablePeripheralCLK(MRCC_TIM3);
	MRCC_enEnablePeripheralCLK(MRCC_AFIO);

	IR_voidInit();
	HDCMOTOR_voidInit();
	MSYSTICK_enInit();
	TIM3_PWM_Init();
	TIM3_PWM_CH1_Generate(70);
	RPLIDAR_voidINT();
	ADAS_voidBlindspot_Init();
}

