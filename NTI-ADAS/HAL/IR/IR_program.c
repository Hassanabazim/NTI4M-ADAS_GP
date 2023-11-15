
#include "MGPIO_int.h"

#include "../../HAL/IR/IR_config.h"
#include "../../HAL/IR/IR_interface.h"

void IR_voidInit(void)
{
    MGPIO_enSetPinDirection(IR1_PORT_NUM, IR1_PIN_NUM, IR1_PIN_MODE);
    MGPIO_enSetPinDirection(IR2_PORT_NUM, IR2_PIN_NUM, IR1_PIN_MODE);
}

IR_PinValue_t IR_IR_PinValueReadLeft(void)
{
	IR_PinValue_t Copy_IRValue=IR_LOW;
	u8 Copy_u8GetPinVal=Copy_IRValue;
	if(MGPIO_enGetPinValue(IR1_PORT_NUM, IR1_PIN_NUM, &Copy_u8GetPinVal)!=SUCCESS)
	{
		Copy_IRValue=IR_ERROR;
	}
	else
	{
		if(Copy_u8GetPinVal==HIGH)
		{
			Copy_IRValue=IR_HIGH;
		}
		else if(Copy_u8GetPinVal==LOW)
		{
			Copy_IRValue=IR_LOW;
		}
	}
    return Copy_u8GetPinVal;
}

IR_PinValue_t IR_IR_PinValueReadRight(void)
{
	IR_PinValue_t Copy_IRValue=IR_LOW;
	u8 Copy_u8GetPinVal=Copy_IRValue;
	if(MGPIO_enGetPinValue(IR2_PORT_NUM, IR2_PIN_NUM, &Copy_u8GetPinVal)!=SUCCESS)
	{
		Copy_IRValue=IR_ERROR;
	}
	else
	{
		if(Copy_u8GetPinVal==HIGH)
		{
			Copy_IRValue=IR_HIGH;
		}
		else if(Copy_u8GetPinVal==LOW)
		{
			Copy_IRValue=IR_LOW;
		}
	}
    return Copy_IRValue;
}

