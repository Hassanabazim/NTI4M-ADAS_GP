/*
 * SCM.h
 *
 *
 *
 */

#ifndef SERVICE_SCM_INC_SCM_H_
#define SERVICE_SCM_INC_SCM_H_

#include "STD_TYPES.h"


#define MAX_NO_TASK		(3)

typedef struct
{
	u8 priority;
	u32 periodicity;
	void (*taskPtr)(void);
}SCM_TaskHandler;


void SCM_Init(void);
void SCM_Start(void);
void SCM_Handller(void);
void SCM_CreatTask(SCM_TaskHandler *taskInfo);


#endif /* SERVICE_SCM_INC_SCM_H_ */
