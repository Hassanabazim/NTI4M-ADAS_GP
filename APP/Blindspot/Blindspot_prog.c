/*
 * Blindspot_prog.c
 *
 *  Created on: Nov 19, 2023
 *      Author: Shrouk Hesham
 */


#include "STD_TYPES.h"
#include "MGPIO_int.h"
#include "HULTRASONIC_int.h"
#include "RPLIDAR_interface.h"
#include "Blindspot_int.h"

u8 Indication[7]=	{0};
f32 Dist_MG[5] = {0};

void ADAS_voidBlindspot_Init(void)
{
	MGPIO_enSetPinDirection(FRONT_LED, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(BACK_LED, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(RIGHT_LED, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(LEFT_LED, OUT_2MHZ_PUSH_PULL);
}

void ADAS_Distance_Manager(void)
{
	HULTRASONIC_enGetRead(&Dist_MG[0]);
	Dist_MG[1] = RPLIDAR_GetDistanceValue(Right_Angle_One,Right_Angle_Two);
	Dist_MG[2] = RPLIDAR_GetDistanceValue(Left_Angle_One,Left_Angle_Two);
	Dist_MG[3] = RPLIDAR_GetDistanceValue(Front_Angle_One,Front_Angle_Two);
	Dist_MG[4] = RPLIDAR_GetDistanceValue(Back_Angle_One,Back_Angle_Two);
}

void ADAS_voidBlindspot_status(void)
{
	//Right=Distance[1]
	if( Dist_MG[1] > MIN_Distance && Dist_MG[1] < MAX_Distance )
	{
		Indication[1] = Object;
		MGPIO_enSetPinValue(RIGHT_LED, HIGH);
	}
	else
	{
		//MGPIO_enSetPinValue(RIGHT_LED, LOW);
		Indication[1] = NO_Object;
	}
	//front
	//Left=Distance[2]
	if( Dist_MG[2] > MIN_Distance && Dist_MG[1] < MAX_Distance )
	{
		MGPIO_enSetPinValue(LEFT_LED, HIGH);
		Indication[2]=Object;
	}
	else
	{
		//MGPIO_enSetPinValue(LEFT_LED, LOW);
		Indication[2]=NO_Object;
	}
	//Front=Distance[3]
	if( Dist_MG[3] > MIN_Distance && Dist_MG[3] < MAX_Distance )
	{
		MGPIO_enSetPinValue(FRONT_LED, HIGH);
		Indication[3]=Object;
	}
	else
	{
		Indication[3]=NO_Object;
		//MGPIO_enSetPinValue(FRONT_LED, LOW);

	}
	//Back=Distance[4]
	if( Dist_MG[4] > MIN_Distance && Dist_MG[4] < MAX_Distance )
	{
		MGPIO_enSetPinValue(BACK_LED, HIGH);
		Indication[4]=Object;
	}
	else
	{
		//MGPIO_enSetPinValue(BACK_LED, LOW);
		Indication[4]=NO_Object;
	}
	//MAX_Right=Distance[5]
	if( Dist_MG[1] > Second_MIN_Distance && Dist_MG[1] < Second_MAX_Distance )
	{
		Indication[5] = Object;
	}
	else
	{
		Indication[5]=NO_Object;
	}
	//MAX_Left=Distance[6]
	if( Dist_MG[2]  > Second_MIN_Distance && Dist_MG[2] < Second_MAX_Distance )
	{
		Indication[6] = Object;
	}
	else
	{
		Indication[6]=NO_Object;
	}
}


