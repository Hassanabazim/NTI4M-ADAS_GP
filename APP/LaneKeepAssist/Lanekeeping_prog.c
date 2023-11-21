/*
 * Lanekeeping_prog.c
 *
 *  Created on: Nov 19, 2023
 *      Author: Amola
 */

#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "MGPIO_int.h"
#include "MSYSTICK_int.h"
#include "TIMERx_interface.h"
#include "IR_interface.h"
#include "HULTRASONIC_int.h"
#include "RPLIDAR_interface.h"
#include "HDCMOTOR_int.h"
#include "Blindspot_int.h"
#include "Lanekeeping_int.h"




LaneState_t LaneState = LANE_KEEPING;

extern u8 Indication[7];
extern u16 Dist_MG [5];

void ADAS_laneKeeping(void)
{
	IR_PinValue_t leftIRValue = IR_IR_PinValueReadLeft();
	IR_PinValue_t rightIRValue = IR_IR_PinValueReadRight();

	if(leftIRValue== IR_HIGH && rightIRValue==IR_HIGH)
	{
		HDCMOTOR_voidDiretionalStop(); //forward wheel   no left no right
		HDCMOTOR_voidForward(); //back wheel
		TIM3_PWM_CH1_Generate(90); //speed
	}
	else if (leftIRValue == IR_LOW && rightIRValue==IR_HIGH)
	{
		HDCMOTOR_voidForwardBackwardStop();
		HDCMOTOR_voidTurnRight();
		HDCMOTOR_voidForward();
		TIM3_PWM_CH1_Generate(70);

		if(leftIRValue== IR_HIGH && rightIRValue==IR_HIGH)
		{
			HDCMOTOR_voidForward();
			TIM3_PWM_CH1_Generate(90);
		}

	}
	else if (rightIRValue == IR_LOW && leftIRValue== IR_HIGH)
	{
		HDCMOTOR_voidForwardBackwardStop();
		HDCMOTOR_voidTurnLeft();
		HDCMOTOR_voidForward();
		TIM3_PWM_CH1_Generate(70);
		if(leftIRValue== IR_HIGH && rightIRValue==IR_HIGH)
		{
			HDCMOTOR_voidForward();
			TIM3_PWM_CH1_Generate(90);
		}
	}
	else
	{
		HDCMOTOR_voidForwardBackwardStop();
	}


}

void ADAS_LaneChange(void)
{
	IR_PinValue_t leftIRValue2 = IR_IR_PinValueReadLeft();
	IR_PinValue_t rightIRValue2 = IR_IR_PinValueReadRight();
	u16 average =  ((Dist_MG[0] + Dist_MG[3]) / 2);
	if (average < 30 && LaneState == LANE_KEEPING)
	{
		if(Indication[1] == NO_Object)
		{
			LaneState = LANE_CHANGE_RIGHT;
			HDCMOTOR_voidTurnRight();
			HDCMOTOR_voidForward();
			TIM3_PWM_CH1_Generate(80);
			if (leftIRValue2 == IR_LOW && rightIRValue2==IR_LOW)
			{
				HDCMOTOR_voidTurnLeft();
				HDCMOTOR_voidForward();
				TIM3_PWM_CH1_Generate(60);
				LaneState = LANE_KEEPING;
			}
		}
		else
		{
			HDCMOTOR_voidForwardBackwardStop();

		}
	}
	else if (average < 30 && LaneState == LANE_KEEPING)
	{

		if(Indication[2] == NO_Object)
		{
			LaneState = LANE_CHANGE_LEFT;
			HDCMOTOR_voidTurnLeft();
			HDCMOTOR_voidForward();
			TIM3_PWM_CH1_Generate(80);
			if (rightIRValue2 == IR_LOW && leftIRValue2 == IR_LOW)
			{
				HDCMOTOR_voidTurnRight();
				HDCMOTOR_voidForward();
				TIM3_PWM_CH1_Generate(60);
				LaneState = LANE_KEEPING;
			}
		}
		else
		{
			HDCMOTOR_voidForwardBackwardStop();
		}
	}
	else
	{
		LaneState = LANE_KEEPING;
	}
}
