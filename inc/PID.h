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

#include <stdint.h>

class PID {
public:
	PID(float const pFactor, float const iFactor, float const dFactor, float const bFactor, float const deltaTime, float const outMin, float const outMax);
	float Update(float const currentValue, float const setPoint);
	float GetError(void);

private:
	float pFactor_;
	float iFactor_;
	float dFactor_;
	float bFactor_;
	float deltaTime_;
	float outMin_;
	float outMax_;
	float integral_ = 0.0f;
	float previousError_ = 0.0f;
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


#endif /* PID_H_ */
