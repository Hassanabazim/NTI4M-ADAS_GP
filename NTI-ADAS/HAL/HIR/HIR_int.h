/*
 * ir.h
 *
 *  Created on: Oct 28, 2023
 *      Author: amale
 */
#include "MGPIO_int.h"

#ifndef IR_H_
#define IR_H_


void IR_Sensor_Init(void);
u16 IR_Sensor_ReadLeft(void);
u16 IR_Sensor_ReadRight(void);

#endif


