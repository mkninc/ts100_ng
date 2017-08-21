/*
 * config.h
 *
 *  Created on: 07.08.2017
 *      Author: Marco
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif


//#define ISR_FAULT_DEBUG

#define FIXPOINT_FACTOR		(10000)

//#define FIXPOINT_DIVROUND(x)     ((x >= 0)?((x + (FIXPOINT_FACTOR / 2)) / FIXPOINT_FACTOR):((x - (FIXPOINT_FACTOR / 2)) / FIXPOINT_FACTOR))
#define FIXPOINT_MULTIPLY(x1, x2)	(((x1) * (x2)) / FIXPOINT_FACTOR)
#define FIXPOINT_DIVIDE(x1, x2)		(((x1) * FIXPOINT_FACTOR) / (x2))

#ifdef __cplusplus
}
#endif

#endif /* INC_CONFIG_H_ */
