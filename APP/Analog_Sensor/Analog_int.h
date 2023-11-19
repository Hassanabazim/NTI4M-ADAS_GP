/*
 * Analog_int.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Hassa
 */

#ifndef ANALOG_SENSOR_ANALOG_INT_H_
#define ANALOG_SENSOR_ANALOG_INT_H_


#define DDBUG_MODE		 0
#define NORMAL_MODE		 1

#define HIGH_TEMP		42
#define AVG_TEMP		20

#define APP_MODE		NORMAL_MODE


void AnalogSensor_voidInit(void);
void AnalogSensor_voidAction(void);


#endif /* ANALOG_SENSOR_ANALOG_INT_H_ */
