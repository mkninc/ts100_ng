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


class Heater {
public:
	enum HEATER_STATUS {
		eHeaterStatusMaintain,
		eHeaterStatusHeating,
		eHeaterStatusCooling,
	};

	void Init(void);

	void SetTemperature(int32_t const targetTemperature);

	Heater::HEATER_STATUS GetStatus(void);

	void Execute(void);

	void DisablePWM(void);

	void EnablePWM(void);

	void SetDutyCycle(int32_t const dutyCycle);

	int32_t GetDutyCycle(void);

	uint32_t GetCurrentTemperature(void);

	void SetCalibrationValue(uint32_t const calibrationValue);

	uint32_t ConvertCalibrateTemperature(uint32_t const rawTemperature);

private:
	int32_t dutyCycle_;
	int32_t cycleTimeMS_;
	uint32_t rawTemperature_;
	int32_t currentTemperature_;
	int32_t setTemperature_;
	int32_t temperatureCalibrationValue_;
};

#ifdef __cplusplus
}
#endif

#endif /* INC_HEATER_H_ */
