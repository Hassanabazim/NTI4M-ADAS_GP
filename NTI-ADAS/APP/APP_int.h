/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         @Author	:  NTI Team
 *         @File	:  APP_int.h
 *         @Module	:  APP
 *
 *  Description:  This file Provide the Module APIs and Interfacing MACROS and Data types
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  HEADER GUARD
 *********************************************************************************************************************/
#ifndef APP_INT_H_
#define APP_INT_H_

#include "STD_TYPES.h"
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void App_voidstartApp(void);


/**
 * @fn u8 ADAS_u8CollisionAvoidence(float, u8)
 * @brief
 *
 * @param Copy_fDistance
 * @param Copy_u8CallerFunctionName
 * @return Error State
 */
u8 ADAS_u8CollisionAvoidence(float Copy_fDistance , u8 Copy_u8CallerFunctionName);

/**
 * @fn 		u8 ADAS_u8FrontCollision(void)
 * @brief 	This function apply the front avoidness algorithm
 * 			and will not exit until the safe distance achieved
 *
 * @return	Error State
 */
u8 ADAS_u8FrontCollision(void);


u8 ADAS_u8SideCollision(u8 Copy_u8SideCollision);

/**
 * @fn		void ADS_voidAdaptiveCuriseControl(u8)
 * @brief 	Check the Front visibility and Make the car move!
 *
 * @param 	Copy_u8CAR_SPEED_DUTY_CYCLE
 * @return Error State
 */
u8 ADS_voidAdaptiveCuriseControl(u8 Copy_u8CAR_SPEED_DUTY_CYCLE);

/**
 * @fn void ADAS_voidEmergencyBreak(void)
 * @brief
 *
 */
void ADAS_voidEmergencyBreak(void);
#endif /* APP_INT_H_ */

/**********************************************************************************************************************
 *  END OF FILE:  APP_int.h
 *********************************************************************************************************************/

