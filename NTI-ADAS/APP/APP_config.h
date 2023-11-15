/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  NTI Team
 *         @File	:  APP_config.h
 *         @Module	:  APP
 *
 *  Description:  This file provide the pre Configuration of the Module
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  HEADER GUARD
 *********************************************************************************************************************/
#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_


#define APPLICATION		COLLISION_AVOIDENCE


#define CAR_SAFE_DISTANCE				100 /* Distance in cm (safe distance + error ) */
#define CAR_HALF_SAFE_DISTANCE			50 	/* (CAR_SAFE_DISTANCE / 2 ) Take a decision for (changing lane or Stop) */
#define CAR_QUARTER_SAFE_DISTANCE		25	/* (CAR_SAFE_DISTANCE / 4 ) Take critical decision for (Emergency Stop) */

/*Front Range */
#define CAR_FRONT_START_ANGLE		160
#define CAR_FRONT_END_ANGLE			200
/*Right Side */
#define CAR_Right_SIDE_START_ANGLE	200
#define CAR_Right_SIDE_END_ANGLE	340
/*Rear Range */
#define CAR_REAER_START_ANGLE		340
#define CAR_REAR_END_ANGLE			20
/*Left Side*/
#define CAR_LEFT_SIDE_START_ANGLE	0
#define CAR_LEFT_SIDE_END_ANGLE		30

#define CAR_SPEED_DUTY_CYCLE		60		/* Make a 60% initial speed */

#endif /* APP_CONFIG_H_ */

 /**********************************************************************************************************************
  *  END OF FILE:	APP_config.h
  *********************************************************************************************************************/
