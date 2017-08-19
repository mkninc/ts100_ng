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
	PID(int32_t const pFactor, int32_t const iFactor, int32_t const dFactor, int32_t const deltaTime);
	int32_t Update(int32_t const currentValue, int32_t const setPoint);
	int32_t GetError(void);

private:
	int32_t pFactor_;
	int32_t iFactor_;
	int32_t dFactor_;
	int32_t deltaTime_;
	int32_t integral_ = 0;
	int32_t previousError_ = 0;
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


#endif /* PID_H_ */
