/*
 * PID.h
 *
 *  Created on: 20 Sep 2016
 *      Author: ralim
 *
 *      Functions for computing the PID for the iron temp
 */

#ifndef PID_H_
#define PID_H_
#include "Analog.h"
#include "Interrupt.h"

typedef struct {
	int32_t kp;
	int32_t ki;
	int32_t kd; //PID values
	int32_t currentError;
} pidSettingsType;

extern int32_t computePID(uint16_t const currentValue, uint16_t setpoint);
extern void setupPID(void);

extern int32_t PID_GetError(void);

#endif /* PID_H_ */
