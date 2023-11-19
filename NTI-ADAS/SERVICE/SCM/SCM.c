/*
 * SCM.c
 *
 *
 *
 */


#include "STD_TYPES.h"
#include "REGISTERS.h"
#include "BIT_MATH.h"
#include "SCM.h"
#include "MSYSTICK_int.h"

volatile u32 Scheduler_Ticks = 0;
SCM_TaskHandler SCM_Tasks[MAX_NO_TASK];


void SCM_Init(void)
{
	MSYSTICK_enInit();
}

void SCM_Start(void)
{
	MSYSTICK_enSetIntervalPeriodic(1000, &SCM_Handller);
}

void SCM_Handller(void)
{
	u8 cnt = 0;
	Scheduler_Ticks++;

	for(cnt=0; cnt < MAX_NO_TASK; cnt++)
	{
		if (Scheduler_Ticks % SCM_Tasks[cnt].periodicity == 0)
		{
			SCM_Tasks[cnt].taskPtr();
		}
	}
}

void SCM_CreatTask(SCM_TaskHandler *taskInfo)
{
	SCM_Tasks[taskInfo->priority].periodicity = taskInfo->periodicity;

	SCM_Tasks[taskInfo->priority].taskPtr = taskInfo->taskPtr;
}

