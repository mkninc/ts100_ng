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
		int32_t const deltaTime) {
	pFactor_ = pFactor;
	iFactor_ = iFactor;
	dFactor_ = dFactor;
	deltaTime_ = deltaTime;
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

	error = setPoint - currentValue;

	pOut = FIXPOINT_DIVROUND(pFactor_ * error);

//	if(pOut < FIXPOINT_FACTOR)
		integral_ += FIXPOINT_DIVROUND(deltaTime_ * error);
	iOut = FIXPOINT_DIVROUND(iFactor_ * integral_);
//	if(iOut > (FIXPOINT_FACTOR / 2))
//			iOut = (FIXPOINT_FACTOR / 2);
//	if(iOut < 0)
//		iOut = 0;

	//derivative = ((error - previousError_) / deltaTime_)
	dOut = 0;

	output = pOut + iOut + dOut;

	previousError_ = error;

	return output;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int32_t PID::GetError(void) {
	return previousError_;
}
//-----------------------------------------------------------------------------
