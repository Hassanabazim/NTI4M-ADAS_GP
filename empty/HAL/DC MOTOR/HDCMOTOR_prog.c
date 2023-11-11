#include  "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "MGPIO_int.h"
#include "HDCMOTOR_cfg.h"

ErrorState_t HDCMotor_u8RotatCW(MGPIO_PORT_t copy_u8PortNumber,MGPIO_PIN_t copy_u8CWPin,MGPIO_PIN_t copy_u8CCWPin )
{
	ErrorState_t Local_ErrType=SUCCESS;

	if ((copy_u8CWPin>=PIN0)&&(copy_u8CWPin<=PIN15)&&(copy_u8CCWPin>=PIN0)&&(copy_u8CCWPin<=PIN15))
	{
		switch(copy_u8PortNumber)
		{
		case PORTA :
			MGPIO_enSetPinValue(PORTA,copy_u8CCWPin,LOW);
			MGPIO_enSetPinValue(PORTA,copy_u8CWPin,HIGH);break;
		case PORTB :
			MGPIO_enSetPinValue(PORTB,copy_u8CCWPin,LOW);
			MGPIO_enSetPinValue(PORTB,copy_u8CWPin,HIGH);break;
		case PORTC :
			MGPIO_enSetPinValue(PORTC,copy_u8CCWPin,LOW);
			MGPIO_enSetPinValue(PORTC,copy_u8CWPin,HIGH);break;

		default:Local_ErrType=OUT_OF_RANG_ERR; break;

		}
	}
	else
	{
		Local_ErrType=OUT_OF_RANG_ERR;
	}
	return Local_ErrType;
}
ErrorState_t HDCMOTOR_u8RotatCCW(MGPIO_PORT_t copy_PortNum,MGPIO_PIN_t copy_u8CWPin,MGPIO_PIN_t copy_u8CCWPin)
{
	ErrorState_t Local_ErrType = SUCCESS;

	if ((copy_u8CWPin>=PIN0)&&(copy_u8CWPin<=PIN15)&&(copy_u8CCWPin>=PIN0)&&(copy_u8CCWPin<=PIN15))
	{
		switch(copy_PortNum)
		{
		case PORTA :
			MGPIO_enSetPinValue(PORTA,copy_u8CWPin,LOW);
			MGPIO_enSetPinValue(PORTA,copy_u8CCWPin,HIGH);break;
		case PORTB :
			MGPIO_enSetPinValue(PORTB,copy_u8CWPin,LOW);
			MGPIO_enSetPinValue(PORTB,copy_u8CCWPin,HIGH);break;
		case PORTC :
			MGPIO_enSetPinValue(PORTC,copy_u8CWPin,LOW);
			MGPIO_enSetPinValue(PORTC,copy_u8CCWPin,HIGH);break;

		default:Local_ErrType=OUT_OF_RANG_ERR; break;

		}
	}
	else
	{
		Local_ErrType = OUT_OF_RANG_ERR;
	}
	return Local_ErrType;
}
ErrorState_t HDCMOTOR_u8Stop(MGPIO_PORT_t copy_PortNum,MGPIO_PIN_t copy_u8CWPin,MGPIO_PIN_t copy_u8CCWPin)
{
	ErrorState_t Local_ErrType = SUCCESS;

	if ((copy_u8CWPin >= PIN0) && (copy_u8CWPin <= PIN15)&&(copy_u8CCWPin >= PIN0) && (copy_u8CCWPin<=PIN15))
	{
		switch(copy_PortNum)
		{
		case PORTA :
			MGPIO_enSetPinValue(PORTA,copy_u8CWPin,LOW);
			MGPIO_enSetPinValue(PORTA,copy_u8CCWPin,LOW);break;
		case PORTB :
			MGPIO_enSetPinValue(PORTB,copy_u8CWPin,LOW);
			MGPIO_enSetPinValue(PORTB,copy_u8CCWPin,LOW);break;
		case PORTC :
			MGPIO_enSetPinValue(PORTC,copy_u8CWPin,LOW);
			MGPIO_enSetPinValue(PORTC,copy_u8CCWPin,LOW);break;

		default:Local_ErrType = OUT_OF_RANG_ERR ; break;

		}
	}
	else
	{
		Local_ErrType= OUT_OF_RANG_ERR;
	}
	return Local_ErrType;
}




