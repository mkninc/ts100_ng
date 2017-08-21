/*
 * PID.c
 *
 *  Created on: 20 Sep 2016
 *      Author: ralim
 */
#include "config.h"
#include "PID.h"

//-----------------------------------------------------------------------------
PID::PID(int32_t const pFactor, int32_t const iFactor, int32_t const dFactor,
		int32_t const bFactor, int32_t const deltaTime, int32_t const outMin,
		int32_t const outMax) {
	pFactor_ = pFactor;
	iFactor_ = iFactor;
	dFactor_ = dFactor;
	bFactor_ = bFactor;
	deltaTime_ = deltaTime;
	outMin_ = outMin;
	outMax_ = outMax;
	integral_ = 0;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int32_t PID::Update(int32_t const currentValue, int32_t const setPoint) {
	int32_t error;
	int32_t pOut;
	int32_t iOut;
	int32_t dOut;
	int32_t output;
	int32_t derivative;
	int32_t saturation;
	int32_t error_i;

	error = setPoint - currentValue;

	pOut = FIXPOINT_MULTIPLY(pFactor_, error);

	derivative = FIXPOINT_DIVIDE((error - previousError_),  deltaTime_);
	dOut = FIXPOINT_MULTIPLY(derivative, dFactor_);

	error_i = FIXPOINT_MULTIPLY(deltaTime_, error);
	iOut = FIXPOINT_MULTIPLY(iFactor_, integral_ + error_i);

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

	integral_ += error_i - FIXPOINT_MULTIPLY(saturation, bFactor_);
	iOut = FIXPOINT_MULTIPLY(iFactor_, integral_);

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
int32_t PID::GetError(void) {
	return previousError_;
}
//-----------------------------------------------------------------------------
