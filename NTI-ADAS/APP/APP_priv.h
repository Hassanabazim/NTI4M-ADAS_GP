/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  NTI Team
 *         @File	:  APP_priv.h
 *         @Module	:  APP
 *
 *  Description:  This file provide a local MACROS/Functions
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  HEADER GUARD
 *********************************************************************************************************************/
#ifndef APP_PRIV_H_
#define APP_PRIV_H_

/* I prefer to be an enum for ease */
#define ANALOG_SENORS_APP							1
#define COLLISION_AVOIDENCE							2
#define FRONT_COLLISION								3
#define REAR_COLLISION								4
#define LEFT_COLLISION								5
#define RIGHT_COLLISION								6
#define LANE_KEEPING 								7
#define LANE_CHANGE									8
#define EMERGENCY_BREAK								9
#define ADAPTIVE_CRUISE_CONTROL						10
#define BLIND_SPOT									11
#define SLEEP_MODE									12
#define ADAS_SYSTEM									13

/* Defines for Blind Spot  */
#define BLIND_SPOT_LEFT_LANE_AVAILABLE				14
#define BLIND_SPOT_RIGHT_LANE_AVAILABLE				15
#define BLIND_SPOT_NO_LANE_AVAILABLE				16
#define BLIND_SPOT_REAR_NEAR_ACCIDENT_DETECTION		17
#define BLIND_SPOT_RIGHT_NEAR_ACCIDENT_DETECTION	18
#define BLIND_SPOT_LEFT_NEAR_ACCIDENT_DETECTION		19



#endif /* APP_PRIV_H_ */

/**********************************************************************************************************************
 *  END OF FILE: 	APP_priv.h
 *********************************************************************************************************************/
