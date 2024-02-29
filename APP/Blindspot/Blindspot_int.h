/*
 * Blindspot_int.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Shrouk Hesham
 */

#ifndef BLINDSPOT_BLINDSPOT_INT_H_
#define BLINDSPOT_BLINDSPOT_INT_H_

#define FRONT_LED		PORTB, PIN12
#define BACK_LED		PORTB, PIN13
#define RIGHT_LED		PORTB, PIN14
#define LEFT_LED		PORTB, PIN15

#define  Right_Angle_One		60
#define  Right_Angle_Two		120

#define	 Left_Angle_One			240
#define	 Left_Angle_Two			300

#define	 Front_Angle_One		150
#define	 Front_Angle_Two		210

#define	 Back_Angle_One			330
#define	 Back_Angle_Two			30
#define  MIN_Distance			300

#define  MAX_Distance			500
#define  Second_MIN_Distance	700
#define  Second_MAX_Distance	1000
#define  Object					1
#define  NO_Object				0

void ADAS_voidBlindspot_Init(void);
void ADAS_voidBlindspot_status(void);
void ADAS_Distance_Manager(void);

#endif /* BLINDSPOT_BLINDSPOT_INT_H_ */
