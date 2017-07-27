/*
 * Analog.h
 *
 *  Created on: 20 Sep 2016
 *      Author: ralim
 *
 *      Interface to the ADC's basically
 */

#ifndef ANALOG_H_
#define ANALOG_H_
#include "stm32f10x.h"
#include "Bios.h"
#include "Interrupt.h"
extern volatile uint16_t ADC1ConvertedValue[2];

extern uint16_t Get_ADC1Value(uint8_t i);
extern uint16_t readIronTemp(uint16_t calibration_temp, uint8_t read,
		uint16_t setPointTemp); //read the iron temp in C X10
extern uint16_t readDCVoltage(uint16_t divFactor);/*Get the system voltage X10*/
extern int16_t readTipTemp(void);
int readSensorTemp(void);
#endif /* ANALOG_H_ */
