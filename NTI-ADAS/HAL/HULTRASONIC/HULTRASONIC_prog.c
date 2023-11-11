#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "REGISTERS.h"
#include "ERROR_STATE.h"
#include "MGPIO_int.h"
#include "MSYSTICK_int.h"
#include "MTIM1_int.h"
#include "HULTRASONIC_config.h"
#include "HULTRASONIC_int.h"
#include "HULTRASONIC_priv.h"


ErrorState_t HULTRASONIC_enInit(void)
{
	ErrorState_t local_state = SUCCESS;

	MGPIO_enSetPinDirection(HULTRASONIC_TRIG_PORT, HULTRASONIC_TRIG_PIN, OUT_2MHZ_PUSH_PULL);
	MGPIO_enSetPinDirection(HULTRASONIC_ECHO_PORT, HULTRASONIC_ECHO_PIN, IN_PULL_UP_PULL_DOWN);
	AFIO->AFIO_MAPR |= 1<<6;
	MTIMER1_enInit();
	MTIMER1_setPrescaler(MTIM1_PRESCALER);

	return local_state;
}


ErrorState_t HULTRASONIC_enGetRead(u16* copy_u16distance)
{
	ErrorState_t local_state = SUCCESS;
	if (copy_u16distance != NULL)
	{
		u16 Reading_1 = 0, Reading_2 = 0;
		u32 TimeTicks;

		MGPIO_enSetPinValue(HULTRASONIC_TRIG_PORT, HULTRASONIC_TRIG_PIN, HIGH);
		MSYSTICK_enSetBusyWait(10);
		MGPIO_enSetPinValue(HULTRASONIC_TRIG_PORT, HULTRASONIC_TRIG_PIN, LOW);

		while(MTIM1_ICU_BSY);
		MTIMER1_ICU_enRead(&Reading_1);
		MTIMER1_enStart();
		MTIMER1_ICU_enSetTrigger(MTIM1_FAILING_TRIG);

		while(MTIM1_ICU_BSY);
		MTIMER1_ICU_enRead(&Reading_2);
		MTIMER1_ICU_enSetTrigger(MTIM1_RISING_TRIG);
		MTIMER1_enStop();
		MTIMER1_enReset();

		TimeTicks = (u32)Reading_2 - (u32)Reading_1;


		f32 TickTime = MTIM1_PRESCALER / F_CPU;
		f32 time  = (TimeTicks *TickTime)/1000000.0;
		*copy_u16distance = (SPEED_OF_SOUND * (time/2));

	}
	else
	{
		local_state = NULL_PTR_ERR;
	}
	return local_state;
}









