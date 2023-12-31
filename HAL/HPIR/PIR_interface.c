

#include "MGPIO_int.h"
#include "PIR_interface.h"
#include "PIR_config.h"
#include "PIR_private.h"

void PIR_voidInit()
{
	MGPIO_enSetPinDirection(PIR_PORT_NUM, PIR_PIN_NUM, PIR_PIN_MODE);
}

u8 PIR_u8GetPinVal()
{
	u8 Copy_u8PIRVal=PIR_LOW;
	if(MGPIO_enGetPinValue(PIR_PORT_NUM, PIR_PIN_NUM,&Copy_u8PIRVal)!=SUCCESS)
	{
		Copy_u8PIRVal=PIR_ERROR;
	}
	return Copy_u8PIRVal;
}
