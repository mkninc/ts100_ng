/*
 * Heater.c
 *
 *  Created on: 27.07.2017
 *      Author: Marco
 */

#include "stm32f10x.h"

#include "S100V0_1.h"
#include "Interrupt.h"
#include "Analog.h"

#include "Heater.h"

void Heater_Init(HEATER_INST * const inst)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef tTimerConfig;
	TIM_OCInitTypeDef tTimerOCConfig;

	inst->cycleTimeMS = 100;
	inst->dutyCycle = 0.0f;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseStructInit(&tTimerConfig);
	tTimerConfig.TIM_Prescaler = 0;
	tTimerConfig.TIM_CounterMode = TIM_CounterMode_Up;
	tTimerConfig.TIM_Period = 2399;
	tTimerConfig.TIM_ClockDivision = TIM_CKD_DIV1;
	tTimerConfig.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &tTimerConfig);

	GPIO_InitStructure.GPIO_Pin = HEAT_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

	TIM_OCStructInit(&tTimerOCConfig);
	tTimerOCConfig.TIM_OCMode = TIM_OCMode_PWM1;  // Clear on compare match
	tTimerOCConfig.TIM_OutputState = TIM_OutputState_Disable;
	tTimerOCConfig.TIM_Pulse = 1200; // Initial duty cycle 50%
	tTimerOCConfig.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM3, &tTimerOCConfig);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_Cmd(TIM3, ENABLE);

    TIM_CCxCmd(TIM3, TIM_Channel_1, TIM_CCx_Enable);

    TIM_CtrlPWMOutputs(TIM3, ENABLE);
}

void Heater_Execute(HEATER_INST * const inst)
{
	uint32_t timeOn;
	uint32_t timeOff;
	uint32_t measureDelay;
	uint32_t avgSum;

	if(inst->dutyCycle < 0.0f)
		inst->dutyCycle = 0.0f;
	if(inst->dutyCycle > 1.0f)
		inst->dutyCycle = 1.0f;

	timeOn = inst->cycleTimeMS * inst->dutyCycle + 0.5f;
	timeOff = inst->cycleTimeMS - timeOn;

	Heater_Resume(inst);
	delayMs(timeOn);
	Heater_Suspend(inst);
	delayMs(timeOff);

	if(timeOff < 5)
	{
		measureDelay = 5 - timeOff;
		delayMs(measureDelay);
	}

	avgSum = 0;
	for(uint32_t i = 0; i < 8; i++)
	{
		avgSum += Get_ADC1Value(0);
	}
	avgSum /= 8;
	inst->rawTemperature = avgSum;

	inst->currentTemperature = Heater_ConvertCalibrateTemperature(inst, inst->rawTemperature);

}


void Heater_Suspend(HEATER_INST * const inst)
{
	TIM_CCxCmd(TIM3, TIM_Channel_1, TIM_CCx_Disable);
}

void Heater_Resume(HEATER_INST * const inst)
{
	TIM_CCxCmd(TIM3, TIM_Channel_1, TIM_CCx_Enable);
}

void Heater_SetDutyCycle(HEATER_INST * const inst, float const dutyCycle)
{
inst->dutyCycle = dutyCycle;
}

uint16_t Heater_GetCurrentTemperature(HEATER_INST * const inst)
{

	return inst->currentTemperature;
}

void Heater_SetCalibrationValue(HEATER_INST * const inst, uint16_t const calibrationValue)
{
	inst->temperatureCalibrationValue = calibrationValue;
}

uint16_t Heater_ConvertCalibrateTemperature(HEATER_INST * const inst,
		uint16_t const rawTemperature) {
	uint16_t calibratedTemperature;

	int16_t ColdJTemp = readSensorTemp();
	if (ColdJTemp > 400)
		ColdJTemp = 400;

	calibratedTemperature = (rawTemperature * 1000 + 807 * ColdJTemp
			- inst->temperatureCalibrationValue * 1000) / 807;

	return calibratedTemperature;
}
