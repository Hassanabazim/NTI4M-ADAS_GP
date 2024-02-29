#ifndef _HSERVO_interface__H
#define _HSERVO_interface__H

#include "MGPIO_int.h"
#include "ERROR_STATE.h"
#include "HSERVO_cfg.h"


/*** private ***/

void SERVO_motor_init(void);
void SERVO_motor_setAngle(u8 angle); //0 to 90

#endif    //_HSERVO_interface__H
