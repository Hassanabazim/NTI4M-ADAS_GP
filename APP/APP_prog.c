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
#include "MADC_int.h"
#include "MUSART_int.h"
#include "HLCD_int.h"
#include "HRAIN_int.h"
#include "HLM35_int.h"
#include "TIMERx_interface.h"
#include "APP_int.h"
#include "APP_config.h"
#include "APP_priv.h"



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

	/**********************************************************************************************************************/
#if (APPLICATION == ADAS_SYSTEM)
	/**********************************************************************************************************************/

	while (1)
	{

	}
	/**********************************************************************************************************************/
#elif (APPLICATION == ANALOG_SENORS_APP)
	/**********************************************************************************************************************/

	u8 Local_u8TemperatureDegree, Local_u8WaterLevel;
	MRCC_enSysClkINIT();
	MRCC_enEnablePeripheralCLK(MRCC_IOPA);
	MRCC_enEnablePeripheralCLK(MRCC_ADC1);

	/* LCD */
	lcd_vidInit();

	/* SYSTICK */
	MSYSTICK_enInit();

	/* LM35 */
	MADC_GROUP_t LM35_TEMP =  {MADC_channel0, MADC_SAMPLE_71_5CYCLE, MADC_INDEX_0};
	LM35_u8TemperatureInit(&LM35_TEMP);

	/* Rain Sensor */
	MADC_GROUP_t RAIN_SEN  =  {MADC_channel7, MADC_SAMPLE_71_5CYCLE, MADC_INDEX_1};
	RainSensor_u8Init(&RAIN_SEN);

	MADC_INIT_t Sensors = {MADC_CONTINUES_CONV, MADC_ENABLE,MADC_RIGHT_ALLIGN,MADC_channel1,MADC_SWSTART, MADC_channel0,MADC_JSWSTART};
	MADC_enInit(&Sensors);
////buffer
	u8 Analog_Sensors[2]={0};
	while (1)
	{
		LM35_u16GetTemperature(&Local_u8TemperatureDegree);
		MSYSTICK_enDelayMS(1);
		RainSensor_u8GetWaterLevel(&Local_u8WaterLevel);
//
//		// TODO TEMP Action
//		lcd_vidGotoRowColumn(0, 0);
//		lcd_vidDisplyStr("temp =");
//		lcd_vidDisplayNum(Local_u8TemperatureDegree);
//
//		//// TODO RAIN Action
//		lcd_vidGotoRowColumn(1, 0);
//		lcd_vidDisplyStr("rain =");
//		lcd_vidDisplayNum(Local_u8WaterLevel);
//		MSYSTICK_enDelayMS(500);
//		lcd_vidClrDislay();
	/////save buffer
		Analog_Sensors[0]=&Local_u8TemperatureDegree;
		Analog_Sensors[0]=&Local_u8WaterLevel;
	}
	/**********************************************************************************************************************/
#elif(APPLICATION == COLLESION_AVOIDENCE)
	/**********************************************************************************************************************/


	while (1)
	{


	}

	/**********************************************************************************************************************/
#elif(APPLICATION == LANE_KEEPING)
	/**********************************************************************************************************************/


	while (1)
	{


	}
	/**********************************************************************************************************************/
#elif(APPLICATION == LANE_CHANGE)
	/**********************************************************************************************************************/


	while (1)
	{


	}
	/**********************************************************************************************************************/
#elif(APPLICATION == EMERGENCY_BREAK)
	/**********************************************************************************************************************/


	while (1)
	{


	}
	/**********************************************************************************************************************/
#elif(APPLICATION == ADAPTIVE_CURISE_CONTROL)
	/**********************************************************************************************************************/

	MRCC_enSysClkINIT();
	MRCC_enEnablePeripheralCLK(MRCC_IOPA);
	MRCC_enEnablePeripheralCLK(MRCC_TIM3);
	MGPIO_enSetPinDirection(PORTA, PIN2, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(PORTA, PIN3, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(PORTA, PIN6, OUT_2MHZ_AF_PUSH_PULL);
	MGPIO_enSetPinDirection(PORTA, PIN7, OUT_2MHZ_AF_PUSH_PULL);
	TIM3_PWM_Init();
	TIM3_PWM_CH1_Generate(60);

	while (1)
	{


	}

	/**********************************************************************************************************************/
#elif(APPLICATION == BLIND_SPOT)
	/**********************************************************************************************************************/


// step 1
#define  Right_Angle_One	60
#define  Right_Angle_Two	120

#define	 Left_Angle_One		240
#define	 Left_Angle_Two		300

#define	 Front_Angle_One	150
#define	 Front_Angle_Two	210

#define	 Back_Angle_One		330
#define	 Back_Angle_Two		30
f32 Distance[5]={0};
//Get_Distance()
while(1)
	{
	HULTRASONIC_enGetRead(&Distance[0]);
	Distance[1]=RPLIDAR_voidScanResponse(Right_Angle_One,Right_Angle_Two);
	Distance[2]=RPLIDAR_voidScanResponse(Left_Angle_One,Left_Angle_Two);
	Distance[3]=RPLIDAR_voidScanResponse(Front_Angle_One,Front_Angle_Two);
	Distance[4]=RPLIDAR_voidScanResponse(Back_Angle_One,Back_Angle_Two);
	}

/*
	while(1)
	{
	if((RPLIDAR_voidScanResponse(45,90)>10 && RPLIDAR_voidScanResponse(45,95)<30) ||
					(RPLIDAR_voidScanResponse(95,135)>10 && RPLIDAR_voidScanResponse(95,135)<30))
	{
		Right_Flag = true;
	}
	if((RPLIDAR_voidScanResponse(270,315)>10 && RPLIDAR_voidScanResponse(270,315)<30) ||
						(RPLIDAR_voidScanResponse(225,270)>10 && RPLIDAR_voidScanResponse(225,270)<30))
		{
			Left_Flag = true;
		}

	}
*/

	/*
	while (1)
	{
		//check right
		if((RPLIDAR_voidScanResponse(50,70)>10 && RPLIDAR_voidScanResponse(50,70)<30) ||
				(RPLIDAR_voidScanResponse(70,90)>10 && RPLIDAR_voidScanResponse(70,90)<30) ||
				(RPLIDAR_voidScanResponse(90,110)>10 && RPLIDAR_voidScanResponse(90,110)<30) ||
				(RPLIDAR_voidScanResponse(110,130)>10 && RPLIDAR_voidScanResponse(110,130)<30)
				)
		{
			Right_Flag= true;
		}

		//else
		//{
			//check left
			if((RPLIDAR_voidScanResponse(290,310)>10 && RPLIDAR_voidScanResponse(290,310)<30) ||
				(RPLIDAR_voidScanResponse(270,290)>10 && RPLIDAR_voidScanResponse(270,290)<30) ||
				(RPLIDAR_voidScanResponse(250,270)>10 && RPLIDAR_voidScanResponse(250,270)<30) ||
				(RPLIDAR_voidScanResponse(230,250)>10 && RPLIDAR_voidScanResponse(230,250)<30)
				)
			{
				Left_Flag= true;
			} */

		//}
//		else
//		{
//			if(RPLIDAR_voidScanResponse(70,90)>10 && RPLIDAR_voidScanResponse(70,90)<30)
//			{
//				//turn left
//			}
//			else
//			{	if(RPLIDAR_voidScanResponse(90,110)>10 && RPLIDAR_voidScanResponse(90,110)<30)
//			{
//				//turn left
//			}
//			else
//			{
//				if(RPLIDAR_voidScanResponse(110,130)>10 && RPLIDAR_voidScanResponse(110,130)<30)
//			{
//				//turn left
//			}
//
//			}
//
//			}
//
//		}


	//}

	/**********************************************************************************************************************/
#elif (APPLICATION == SLEEP_MODE)
	/**********************************************************************************************************************/

	while (1)
	{

	}
#endif
}
/**********************************************************************************************************************
 *  END OF FILE: APP_prog.c
 *********************************************************************************************************************/
