/*
 * PID.c
 *
 *  Created on: 20 Sep 2016
 *      Author: ralim
 */
#include "config.h"
#include "PID.h"

//-----------------------------------------------------------------------------
PID::PID(float const pFactor, float const iFactor, float const dFactor,
		float const bFactor, float const deltaTime, float const outMin,
		float const outMax) {
	pFactor_ = pFactor;
	iFactor_ = iFactor;
	dFactor_ = dFactor;
	bFactor_ = bFactor;
	deltaTime_ = deltaTime;
	outMin_ = outMin;
	outMax_ = outMax;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
float PID::Update(float const currentValue, float const setPoint) {
	float error;
	float pOut;
	float iOut;
	float dOut;
	float output;
	float derivative;
	float saturation;
	float error_i;

	error = setPoint - currentValue;

	pOut = pFactor_ * error;

	derivative = (error - previousError_) / deltaTime_;
	dOut = derivative * dFactor_;

	error_i = deltaTime_ * error;
	iOut = iFactor_ * (integral_ + error_i);

	output = pOut + iOut + dOut;

	if(output > outMax_) {
		saturation = output - outMax_;
	}
	else if(output < outMin_) {
		saturation = output - outMin_;
	}
	else {
		saturation = 0;
	}

	integral_ += error_i - (saturation * bFactor_);
	iOut = iFactor_ * integral_;

	output = pOut + iOut + dOut;

	if(output > outMax_) {
		output = outMax_;
	}
	else if(output < outMin_) {
		output = outMin_;
	}

	previousError_ = error;

	return output;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
float PID::GetError(void) {
	return previousError_;
}
//-----------------------------------------------------------------------------
