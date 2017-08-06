/*
 * Heater.h
 *
 *  Created on: 27.07.2017
 *      Author: Marco
 */

#ifndef INC_HEATER_H_
#define INC_HEATER_H_

#include <stdint.h>


typedef struct
{
	float dutyCycle;
	uint32_t cycleTimeMS;
	uint32_t rawTemperature;
	uint32_t currentTemperature;
	uint16_t temperatureCalibrationValue;

}HEATER_INST;

extern void Heater_Init(HEATER_INST * const inst);

extern void Heater_Execute(HEATER_INST * const inst);

extern void Heater_Suspend(HEATER_INST * const inst);

extern void Heater_Resume(HEATER_INST * const inst);

extern void Heater_SetDutyCycle(HEATER_INST * const inst, float const dutyCycle);

extern float Heater_GetDutyCycle(HEATER_INST * const inst);

extern uint16_t Heater_GetCurrentTemperature(HEATER_INST * const inst);

extern void Heater_SetCalibrationValue(HEATER_INST * const inst, uint16_t const calibrationValue);

extern uint16_t Heater_ConvertCalibrateTemperature(HEATER_INST * const inst, uint16_t const rawTemperature);

#endif /* INC_HEATER_H_ */
