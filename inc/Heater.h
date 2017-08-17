/*
 * Heater.h
 *
 *  Created on: 27.07.2017
 *      Author: Marco
 */

#ifndef INC_HEATER_H_
#define INC_HEATER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


//class Heater {
//
//private:
//	int32_t dutyCycle;
//	uint32_t cycleTimeMS;
//	uint32_t rawTemperature;
//	int32_t currentTemperature;
//	int32_t setTemperature;
//	int32_t temperatureCalibrationValue;
//};

typedef struct
{
	int32_t dutyCycle;
	uint32_t cycleTimeMS;
	uint32_t rawTemperature;
	int32_t currentTemperature;
	int32_t setTemperature;
	int32_t temperatureCalibrationValue;
}HEATER_INST;

typedef enum {
	eHeaterStatusMaintain,
	eHeaterStatusHeating,
	eHeaterStatusCooling,
}HEATER_STATUS;

extern void Heater_Init(HEATER_INST * const inst);

extern void Heater_SetTemperature(HEATER_INST * const inst, int32_t const targetTemperature);

extern HEATER_STATUS Heater_GetStatus(HEATER_INST * const inst);

extern void Heater_Execute(HEATER_INST * const inst);

extern void Heater_DisablePWM(HEATER_INST * const inst);

extern void Heater_EnablePWM(HEATER_INST * const inst);

extern void Heater_SetDutyCycle(HEATER_INST * const inst, int32_t const dutyCycle);

extern int32_t Heater_GetDutyCycle(HEATER_INST * const inst);

extern uint32_t Heater_GetCurrentTemperature(HEATER_INST * const inst);

extern void Heater_SetCalibrationValue(HEATER_INST * const inst, uint32_t const calibrationValue);

extern uint32_t Heater_ConvertCalibrateTemperature(HEATER_INST * const inst, uint32_t const rawTemperature);

#ifdef __cplusplus
}
#endif

#endif /* INC_HEATER_H_ */
