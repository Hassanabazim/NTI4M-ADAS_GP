

#ifndef HULTRASONI_HULTRASONIC_INT_H_
#define HULTRASONI_HULTRASONIC_INT_H_


#include "ERROR_STATE.h"

ErrorState_t HULTRASONIC_enInit(void);

ErrorState_t HULTRASONIC_enGetRead(u16* copy_u16Value);


#endif /* HULTRASONI_HULTRASONIC_INT_H_ */
