/*
 * Heater.h
 *
 *  Created on: 27.07.2017
 *      Author: Marco
 */

#ifndef INC_HEATER_H_
#define INC_HEATER_H_

#include <stdint.h>
#include "PID.h"

class Heater {
public:
	enum HEATER_STATUS {
		eHeaterStatusMaintain,
		eHeaterStatusHeating,
		eHeaterStatusCooling,
	};

	void Init(void);

	void SetTemperature(float const targetTemperature);

	Heater::HEATER_STATUS GetStatus(void);

	void Execute(void);

	void DisablePWM(void);

	void EnablePWM(void);

	void SetDutyCycle(float const dutyCycle);

	float GetDutyCycle(void);

	float GetCurrentTemperature(void);

	void SetCalibrationValue(uint32_t const calibrationValue);

	float ConvertCalibrateTemperature(uint32_t const rawTemperature);

private:
	float dutyCycle_;
	int32_t cycleTimeMS_;
	uint32_t rawTemperature_;
	float currentTemperature_;
	float setTemperature_;
	int32_t temperatureCalibrationValue_;

};


#endif /* INC_HEATER_H_ */
