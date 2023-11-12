#ifndef HDCMOTOR_INTERFACE_H
#define HDCMOTOR_INTERFACE_H
#include "MGPIO_int.h"
#include "ERROR_STATE.h"
#include "HDCMOTOR_cfg.h"



/**********************************************************************************************/

void HDCMOTOR_voidInit(void);

/**********************************************************************************************/

void HDCMOTOR_voidForward(void);
void HDCMOTOR_voidBackward(void);


/**********************************************************************************************/

void HDCMOTOR_voidTurnRight(void);
void HDCMOTOR_voidTurnLeft(void);

/**********************************************************************************************/

void HDCMOTOR_voidDiretionalStop(void);
void HDCMOTOR_voidForwardBackwardStop(void);

/**********************************************************************************************/




#endif
