/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  NTI Team
 *         @File	:  APP_prog.c
 *         @Module	:  ADAS APP
 *         @Features : 1-  Lane Keeping
 *         			   2-  Lane Changing
 *         			   3-  Blind-Spot Detection
 *         			   5-  Emergency Break
 *         			   6-  Adaptive Cruise Control
 *         			   7-  Front Collision Avoidance
 *         			   8-  Rear Collision Avoidance
 *         			   9-  Right Side Collision Avoidance
 *         			   10- Left Side Collision Avoidance
 *         			   11- Surrounding Temperature Detection
 *         			   12- Rain Detection with Auto Wipers Movement
 *         			   13- Thief detection when car is Parking
 *         			   14- Street Water Level Detection for Cars Engine and Chassis Protection
 *
 *         	@Features Welling to have :
 *         			   1- Auto Lighting HeadLights System
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
#include "RPLIDAR_interface.h"
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
	MRCC_enSysClkINIT();
	MRCC_enEnablePeripheralCLK(MRCC_IOPA);
	MRCC_enEnablePeripheralCLK(MRCC_TIM3);
	MRCC_enEnablePeripheralCLK(MRCC_ADC1);
	MGPIO_enSetPinDirection(PORTA, PIN2, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(PORTA, PIN3, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(PORTA, PIN6, OUT_2MHZ_AF_PUSH_PULL);
	MGPIO_enSetPinDirection(PORTA, PIN7, OUT_2MHZ_AF_PUSH_PULL);
	TIM3_PWM_Init();
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

	while (1)
	{
		LM35_u16GetTemperature(&Local_u8TemperatureDegree);
		MSYSTICK_enDelayMS(1);
		RainSensor_u8GetWaterLevel(&Local_u8WaterLevel);

		// TODO TEMP Action
		lcd_vidGotoRowColumn(0, 0);
		lcd_vidDisplyStr("temp =");
		lcd_vidDisplayNum(Local_u8TemperatureDegree);

		//// TODO RAIN Action
		lcd_vidGotoRowColumn(1, 0);
		lcd_vidDisplyStr("rain =");
		lcd_vidDisplayNum(Local_u8WaterLevel);
		MSYSTICK_enDelayMS(500);
		lcd_vidClrDislay();
	}
	/**********************************************************************************************************************/
#elif(APPLICATION == COLLISION_AVOIDENCE)
	/**********************************************************************************************************************/
	/*This function will exit only when safe distance achieved */
	/* for Copy_u8CallerFunctionName in RTOS we can make it in a Que! */
	u8 ADAS_u8CollisionAvoidence(float Copy_fDistance , u8 Copy_u8CallerFunctionName)
	{
		u8 Local_u8CAR_SPEED_DUTY_CYCLE , Local_u8ErrorState = SUCCESS;

		/*First check who is calling the Collision Function */
		if(ADAPTIVE_CRUISE_CONTROL == Copy_u8CallerFunctionName) /* for Front near accident detection */
		{
			Local_u8ErrorState = ADAS_u8FrontCollision();
		}
		else if(BLIND_SPOT_REAR_NEAR_ACCIDENT_DETECTION == Copy_u8CallerFunctionName ) /* for Rear near accident detection */
		{
			/* This is detected by BlindSpot from the Indication Buffer or Que in RTOS!  */
			Local_u8ErrorState = ADAS_u8RearCollision();
		}
		else if(BLIND_SPOT_LEFT_NEAR_ACCIDENT_DETECTION == Copy_u8CallerFunctionName)	/* for Left side collision near accident detection */
		{
			/* This is detected by BlindSpot from the Indication Buffer or Que in RTOS!  */
			Local_u8ErrorState = ADAS_u8SideCollision(LEFT_COLLISION);
		}
		else if(BLIND_SPOT_RIGHT_NEAR_ACCIDENT_DETECTION == Copy_u8CallerFunctionName)	/* for Right side collision near accident detection */
		{
			/* This is detected by BlindSpot from the Indication Buffer or Que in RTOS!  */
			Local_u8ErrorState = ADAS_u8SideCollision(RIGHT_COLLISION);
		}
		else
		{
			/* DO no thing */
		}


		return Local_u8ErrorState;
	}
	/**********************************************************************************************************************/
	//#elif(APPLICATION == FRONT_COLLISION)

	u8 ADAS_u8FrontCollision(void)
	{
		extern Copy_floatDistance;	/* Get the lidar distance from Lidar file*/
		u8 Local_u8CAR_SPEED_DUTY_CYCLE , Local_u8BlindSpotIndication , Local_u8ErrorState = SUCCESS;
		float Local_fFrontReadingLidarDistance, Local_fLidarReading;

		/* 1- Get the car speed first */
		Local_u8CAR_SPEED_DUTY_CYCLE = CAR_SPEED_DUTY_CYCLE; //we can make in a Que!

		/* Then Run Front Collision Avoidance!*/
		do{
			/* 3- check the front visibility distance again  */
			RPLIDAR_voidScanResponse(CAR_FRONT_START_ANGLE , CAR_FRONT_END_ANGLE);
			Local_fFrontReadingLidarDistance = Copy_floatDistance;

			if((float)CAR_SAFE_DISTANCE <= Local_fFrontReadingLidarDistance)	/* Safe distance */
			{
				/* 4- Car is doing will then exit the Front collision function*/
				break;
			}
			else if((float)CAR_SAFE_DISTANCE > Local_fFrontReadingLidarDistance)	/* Critical distance */
			{
				/* Then the car is still in critical situation so, decrease the speed and check the distance again*/

				/**** 4- Check which distance Level is the car in!****/
				/*Check from Highest critical situation to lowest critical situation */
				/* check if the car below the Quarter safe distance so apply Emergency break immediately */
				if((float)CAR_QUARTER_SAFE_DISTANCE <= Local_fFrontReadingLidarDistance )
				{
					/* 5- Call Emergency break */
					ADAS_voidEmergencyBreak();
				}
				/* check if the car above the Quarter safe distance and below the half safe distance */
				else if( ((float)CAR_QUARTER_SAFE_DISTANCE <= Local_fFrontReadingLidarDistance ) &&((float)CAR_HALF_SAFE_DISTANCE > Local_fFrontReadingLidarDistance ) )
				{
					/* Then car can will choose if it will ( changes the lane or Continue to decrease its speed ) */
					/* 5- Take the information from the BlindSpot function This function will return the available side*/
					Local_u8BlindSpotIndication = ADAS_u8BlindSpot(COLLESION_AVOIDENCE);

					/* Make the Decision in switch case to be faster response*/
					switch(Local_u8BlindSpotIndication)
					{
					case BLIND_SPOT_LEFT_LANE_AVAILABLE: /* Car finds That the Left lane is available to go in! */
						/*6- Call the Lane change function to go in!*/
						ADAS_voidLaneChange(BLIND_SPOT_LEFT_LANE_AVAILABLE);
						break;
					case BLIND_SPOT_RIGHT_LANE_AVAILABLE: /* Car finds That the Right lane is available to go in! */
						/*6- Call the Lane change function to go in!*/
						ADAS_voidLaneChange(BLIND_SPOT_RIGHT_LANE_AVAILABLE);
						break;
					case BLIND_SPOT_NO_LANE_AVAILABLE: /* Car couldn't finds any available lane to go in! */
						/*6- So it will continue decreasing its speed*/
						Local_u8CAR_SPEED_DUTY_CYCLE--;
						TIM3_PWM_CH1_Generate(Local_u8CAR_SPEED_DUTY_CYCLE);
						break;
					default: break ;
					}
				}
				/* check if the car above the half safe distance and below the safe distance */
				else if( ((float)CAR_HALF_SAFE_DISTANCE <= Local_fFrontReadingLidarDistance ) &&((float)CAR_SAFE_DISTANCE > Local_fFrontReadingLidarDistance ) )
				{
					/* 5- Then the car will decrease its speed only */
					Local_u8CAR_SPEED_DUTY_CYCLE--;
					TIM3_PWM_CH1_Generate(Local_u8CAR_SPEED_DUTY_CYCLE);
				}
				/* check if the car above the safe distance */
				else if((float)CAR_SAFE_DISTANCE < Local_fFrontReadingLidarDistance )
				{
					/* Car is doing will then Do no thing*/
				}
				else
				{
					/* There is an error in some thing then return an error state */
					Local_u8ErrorState = FAILARE;
				}

			}
			else
			{
				/* There is an error in some thing then return an error state */
				Local_u8ErrorState = FAILARE;
			}
		}while((float)CAR_SAFE_DISTANCE > Local_fFrontReadingLidarDistance); /* Repeat all these steps again */

		return Local_u8ErrorState ;
	}
	/**********************************************************************************************************************/
	//#elif(APPLICATION == LEFT_COLLISION)

	u8 ADAS_u8SideCollision(u8 Copy_u8SideCollision)
	{
		extern Copy_floatDistance;	/* Get the lidar distance from Lidar file*/
		u8 Local_u8CAR_SPEED_DUTY_CYCLE , Local_u8BlindSpotIndication , Local_u8ErrorState = SUCCESS;
		u8 Local_u8Flag = FAILARE;
		float Local_fFrontReadingLidarDistance, Local_fLidarReading;

		/* 1- Get the car speed first */
		Local_u8CAR_SPEED_DUTY_CYCLE = CAR_SPEED_DUTY_CYCLE; //we can make in a Que!

		/* Then Run Front Collision Avoidance!*/

		/* 2- Check the Availability to change the lane from BlindSpotFunction */
		Local_u8BlindSpotIndication = ADAS_u8BlindSpot(COLLESION_AVOIDENCE);

		/* Make the Decision in switch case to be faster response*/
		if(LEFT_COLLISION == Copy_u8SideCollision)
		{
			switch(Local_u8BlindSpotIndication)
			{
			case BLIND_SPOT_RIGHT_LANE_AVAILABLE: /* Car finds That the Right lane is available to go in! */
				/*6- Call the Lane change function to go in!*/
				ADAS_voidLaneChange(BLIND_SPOT_RIGHT_LANE_AVAILABLE);
				Local_u8Flag = SUCCESS;	/* to indicates that lane change is achieved */
				break;
			default: break ;
			}
		}
		else if(RIGHT_COLLISION == Copy_u8SideCollision)
		{
			switch(Local_u8BlindSpotIndication)
			{
			case BLIND_SPOT_LEFT_LANE_AVAILABLE: /* Car finds That the Left lane is available to go in! */
				/*6- Call the Lane change function to go in!*/
				ADAS_voidLaneChange(BLIND_SPOT_LEFT_LANE_AVAILABLE);
				Local_u8Flag = SUCCESS;	/* to indicates that lane change is achieved */
				break;
			default: break ;
			}
		}
		else
		{
			/* Do no thing */
		}

		/*if no action token! so car will Try to decrease or critically increase the speed */
		if(FAILARE == Local_u8Flag)
		{
			/* check the Rear Visibility first */
			Local_u8ErrorState = ADAS_u8RearCollision();

			if(SUCCESS == Local_u8ErrorState)	/* No thing behind the car */
			{
				do{
					/* 4- Then decrease the speed */
					CAR_SPEED_DUTY_CYCLE--;		/* change in global to make Rear function see it! */
					TIM3_PWM_CH1_Generate(CAR_SPEED_DUTY_CYCLE);

					/* check the Rear Visibility again */
					Local_u8ErrorState = ADAS_u8RearCollision();

					/* 5- check if the obstacle still will hit me on the side or not  */
					Local_u8BlindSpotIndication = ADAS_u8BlindSpot(COLLESION_AVOIDENCE);

					/* check if the obstacle still will hit me on the side or not  */
				}while( (Copy_u8SideCollision == Local_u8BlindSpotIndication) && (SUCCESS == Local_u8ErrorState)) ;

				/* 6- when exit the while loop then return back car to its speed*/
				CAR_SPEED_DUTY_CYCLE = Local_u8CAR_SPEED_DUTY_CYCLE;
				TIM3_PWM_CH1_Generate(CAR_SPEED_DUTY_CYCLE);
			}
			else if(FAILARE == Local_u8ErrorState)	/* No action token */
			{
				/* Then try to increase the speed cause it is critical situation; the passenger will die! */

				/* check the Front Visibility first */
				Local_u8ErrorState = ADAS_u8FrontCollision();

				if(SUCCESS == Local_u8ErrorState)	/* No thing on front of the car */
				{
					do{
						/* 4- Then increase the speed */
						CAR_SPEED_DUTY_CYCLE++;		/* change in global to make Rear function see it! */
						TIM3_PWM_CH1_Generate(CAR_SPEED_DUTY_CYCLE);

						/* check the Front Visibility first */
						Local_u8ErrorState = ADAS_u8FrontCollision();

						/* 5- check if the obstacle still will hit me on the side or not  */
						Local_u8BlindSpotIndication = ADAS_u8BlindSpot(COLLESION_AVOIDENCE);

						/* check if the obstacle still will hit me on the side or not  */
					}while( (Copy_u8SideCollision == Local_u8BlindSpotIndication) && (SUCCESS == Local_u8ErrorState) );

					/* 6- when exit the while loop then return back car to its speed*/
					CAR_SPEED_DUTY_CYCLE = Local_u8CAR_SPEED_DUTY_CYCLE;
					TIM3_PWM_CH1_Generate(CAR_SPEED_DUTY_CYCLE);

				}
				else
				{
					/* no response*/
					Local_u8ErrorState = NO_RESPONSE;
				}
			}
			else
			{
				/*DO no thing */
			}


			return Local_u8ErrorState ;
		}
		/**********************************************************************************************************************/
		//#elif(APPLICATION == REAR_COLLISION)

		u8 ADAS_u8RearCollision(void)
		{
			extern Copy_floatDistance;	/* Get the lidar distance from Lidar file*/
			u8 Local_u8CAR_SPEED_DUTY_CYCLE,Local_u8CAR_TempSpeed_DutyCycle , Local_u8BlindSpotIndication , Local_u8ErrorState = SUCCESS;
			float Local_fFrontReadingLidarDistance, Local_fLidarReading;

			/* 1- Get the car speed first */
			Local_u8CAR_SPEED_DUTY_CYCLE = CAR_SPEED_DUTY_CYCLE; 	//we can make in a Que!

			/* Then Run Rear Collision Avoidance!*/
			do{
				/* 2- check the Rear visibility distance again  */
				RPLIDAR_voidScanResponse(CAR_REAER_START_ANGLE , CAR_REAR_END_ANGLE);
				Local_fFrontReadingLidarDistance = Copy_floatDistance;

				if((float)CAR_SAFE_DISTANCE <= Local_fFrontReadingLidarDistance)	/* Safe distance */
				{
					/* 3- Car is doing will then exit the Front collision function*/
					break;
				}
				else if((float)CAR_SAFE_DISTANCE > Local_fFrontReadingLidarDistance)	/* Critical distance */
				{
					/* Then the car is still in critical situation so, decrease the speed and check the distance again*/

					/**** 3- Check which distance Level is the car in!****/
					/*Check from Highest critical situation to lowest critical situation */

					/* check if the car below the Quarter safe distance then
					 * Increase the speed if possible! cause it is very critical condition ( Passenger may be DIE)*/
					if((float)CAR_QUARTER_SAFE_DISTANCE <= Local_fFrontReadingLidarDistance )
					{
						do{
							/* 4- Check the Front Visibility to increase the speed */
							Local_u8ErrorState = ADAS_u8FrontCollision();	/* Call the function and receive its error state!  */

							if(SUCCESS == Local_u8ErrorState)
							{
								/* The Front Safe distance is achievable */
								/* 5- Increase the speed if possible! cause it is very critical condition ( Passenger may be DIE) */
								CAR_SPEED_DUTY_CYCLE++; /* I change in the Global one to make change visible for the front function */
								TIM3_PWM_CH1_Generate(CAR_SPEED_DUTY_CYCLE);

								/*6- check the Rear visibility distance again  */
								RPLIDAR_voidScanResponse(CAR_REAER_START_ANGLE , CAR_REAR_END_ANGLE);
								Local_fFrontReadingLidarDistance = Copy_floatDistance;
							}
							else if(FAILARE == Local_u8ErrorState)
							{
								/* Then the there is something fault happens and get no response */

								/* 6- Change The Lane if possible */
								/* Take the information from the BlindSpot function This function will return the available side*/
								Local_u8BlindSpotIndication = ADAS_u8BlindSpot(COLLESION_AVOIDENCE);

								/* Make the Decision in switch case to be faster response*/
								switch(Local_u8BlindSpotIndication)
								{
								case BLIND_SPOT_LEFT_LANE_AVAILABLE: /* Car finds That the Left lane is available to go in! */
									/*7- Call the Lane change function to go in!*/
									ADAS_voidLaneChange(BLIND_SPOT_LEFT_LANE_AVAILABLE);
									break;
								case BLIND_SPOT_RIGHT_LANE_AVAILABLE: /* Car finds That the Right lane is available to go in! */
									/*7- Call the Lane change function to go in!*/
									ADAS_voidLaneChange(BLIND_SPOT_RIGHT_LANE_AVAILABLE);
									break;
								case BLIND_SPOT_NO_LANE_AVAILABLE: /* Car couldn't finds any available lane to go in! */
									/*7- So Car will do no thing because it didn't get any response from the front visibility*/
									break;
								default: break ;
								}
							}
							else
							{
								/*No response; Accident Happened -_- */
							}
						}while((float)CAR_QUARTER_SAFE_DISTANCE <= Local_fFrontReadingLidarDistance);
						/* If Do while Exit then it means that the car avoid the critical Quarter rear safe distance or has been crashed */

						/* 8- Then return Car speed to what it was anyway! -_- */
						CAR_SPEED_DUTY_CYCLE = Local_u8CAR_SPEED_DUTY_CYCLE; /* Return the speed value as it was! */
						TIM3_PWM_CH1_Generate(CAR_SPEED_DUTY_CYCLE);
					}
					/* check if the car above the Quarter safe distance and below the half safe distance */
					else if( ((float)CAR_QUARTER_SAFE_DISTANCE <= Local_fFrontReadingLidarDistance ) &&((float)CAR_HALF_SAFE_DISTANCE > Local_fFrontReadingLidarDistance ) )
					{
						/* Then car can will choose if it will ( changes the lane ) */
						/* 4- Take the information from the BlindSpot function This function will return the available side*/
						Local_u8BlindSpotIndication = ADAS_u8BlindSpot(COLLESION_AVOIDENCE);

						/* Make the Decision in switch case to be faster response*/
						switch(Local_u8BlindSpotIndication)
						{
						case BLIND_SPOT_LEFT_LANE_AVAILABLE: /* Car finds That the Left lane is available to go in! */
							/*5- Call the Lane change function to go in!*/
							ADAS_voidLaneChange(BLIND_SPOT_LEFT_LANE_AVAILABLE);
							break;
						case BLIND_SPOT_RIGHT_LANE_AVAILABLE: /* Car finds That the Right lane is available to go in! */
							/*5- Call the Lane change function to go in!*/
							ADAS_voidLaneChange(BLIND_SPOT_RIGHT_LANE_AVAILABLE);
							break;
						case BLIND_SPOT_NO_LANE_AVAILABLE: /* Car couldn't finds any available lane to go in! */
							/*5- So do nothing cause I am restricted with fixed speed that change in very critical ranges only!*/
							break;
						default: break ;
						}
					}
					/* check if the car above the half safe distance and below the safe distance */
					else if( ((float)CAR_HALF_SAFE_DISTANCE <= Local_fFrontReadingLidarDistance ) &&((float)CAR_SAFE_DISTANCE > Local_fFrontReadingLidarDistance ) )
					{
						/* 5- Then the car will make nothing , we can add a Led indicator to the driver */
					}
					else
					{
						/* There is an error in some thing then return an error state */
						Local_u8ErrorState = FAILARE;
					}

				}
				else
				{
					/* There is an error in some thing then return an error state */
					Local_u8ErrorState = FAILARE;
				}
			}while((float)CAR_SAFE_DISTANCE > Local_fFrontReadingLidarDistance); /* Repeat all these steps again */
			return Local_u8ErrorState;
		}
		/**********************************************************************************************************************/
		//#elif(APPLICATION == EMERGENCY_BREAK)
		/**********************************************************************************************************************/
		void ADAS_voidEmergencyBreak(void)
		{
			/* Make an emergency break and make the car stops */
			HDCMOTOR_u8Stop(PORTA, Diriction_Motor_CW, Diriction_Motor_ANTI_CW);
		}
		/**********************************************************************************************************************/

		//#elif(APPLICATION == ADAPTIVE_CRUISE_CONTROL)
		/**********************************************************************************************************************/
		/**
		 * @fn		void ADS_voidAdaptiveCuriseControl(u8)
		 * @brief 	Check the Front visibility and Make the car move!
		 *
		 * @param 	Copy_u8CAR_SPEED_DUTY_CYCLE
		 * @return Error State
		 */
		u8 ADS_voidAdaptiveCuriseControl(u8 Copy_u8CAR_SPEED_DUTY_CYCLE)
		{
			extern Copy_floatDistance;
			u8 Local_u8ErrorState = SUCCESS;
			float Local_fFrontReadingLidarDistance, Local_fLidarReading;
			/*Start moving the car! */
			TIM3_PWM_CH1_Generate(Copy_u8CAR_SPEED_DUTY_CYCLE);
			while (1)
			{
				/* 1- check the front visibility distance */
				RPLIDAR_voidScanResponse(CAR_FRONT_START_ANGLE , CAR_FRONT_END_ANGLE);
				Local_fFrontReadingLidarDistance = Copy_floatDistance;
				/* 2- Check for collision! */
				if((float)CAR_SAFE_DISTANCE <= Local_fFrontReadingLidarDistance)
				{
					/* Do nothing*/
				}
				else if((float)CAR_SAFE_DISTANCE > Local_fFrontReadingLidarDistance)
				{
					/* Then the car is in critical situation so, Call the collision function */
					Local_u8ErrorState = ADAS_u8CollisionAvoidence(Local_fFrontReadingLidarDistance, ADAPTIVE_CRUISE_CONTROL);

				}

			}
			return Local_u8ErrorState;
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
		/**
		 * @fn 	void ADAS_voidLaneChange(u8)
		 * @brief This function Takes the available lane to move the car in!
		 *
		 * @param Copy_u8AvailableLaneDirection
		 */
		void ADAS_voidLaneChange(u8 Copy_u8AvailableLaneDirection)
		{

			while (1)
			{


			}
		}

		/**********************************************************************************************************************/
#elif(APPLICATION == BLIND_SPOT)
		/**********************************************************************************************************************/
		// step 1

		while (1)
		{


		}

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
