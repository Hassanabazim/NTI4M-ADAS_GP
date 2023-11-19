

//#include "../../MCAL/MGPIO/MGPIO_int.h"

#ifndef IR_INTERFACE_H_
#define IR_INTERFACE_H_

typedef enum{
	IR_HIGH,
	IR_LOW,
	IR_ERROR
}IR_PinValue_t;

void IR_voidInit(void);
IR_PinValue_t IR_IR_PinValueReadLeft(void);
IR_PinValue_t IR_IR_PinValueReadRIGH(void);

#endif


