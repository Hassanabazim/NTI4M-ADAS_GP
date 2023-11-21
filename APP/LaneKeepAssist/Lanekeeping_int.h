/*
 * Lanekeeping_int.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Amola
 */

#ifndef LANEKEEPASSIST_LANEKEEPING_INT_H_
#define LANEKEEPASSIST_LANEKEEPING_INT_H_


typedef enum {
	LANE_KEEPING,
	LANE_CHANGE_RIGHT,
	LANE_CHANGE_LEFT
} LaneState_t;


void ADAS_laneKeeping(void);
void ADAS_LaneChange(void);


#endif /* LANEKEEPASSIST_LANEKEEPING_INT_H_ */
