#include  "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "MGPIO_int.h"
#include "MRCC_int.h"
#include "TIMERx_interface.h"
#include "HSERVO_inteerface.h"
#include "HSERVO_cfg.h"


/* this function initiate timer2 and setting to generate 50HZ on channel(2) PINA1 */
void SERVO_motor_init(void)
{
	//initiate timer2
//	MRCC_enSysClkINIT();
//	MRCC_enEnablePeripheralCLK(MRCC_IOPA);
//	MRCC_enEnablePeripheralCLK(MRCC_TIM2);
	// initiate PWM mode1
	TIM2_PWM_Init();
}

void SERVO_motor_setAngle(u8 angle)
{
    // Map the servo angle to CCR2 values
    u8 pulseWidth = map(angle, 0, 180, 1, 175);
    TIM2_SetPulseWidth((pulseWidth/6));
}


