/*
 * config.h
 *
 *  Created on: 07.08.2017
 *      Author: Marco
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_


#define FIXPOINT_FACTOR		(10000)

#define FIXPOINT_DIVROUND(x)     ((x >= 0)?((x + (FIXPOINT_FACTOR / 2)) / FIXPOINT_FACTOR):((x - (FIXPOINT_FACTOR / 2)) / FIXPOINT_FACTOR))

#endif /* INC_CONFIG_H_ */
