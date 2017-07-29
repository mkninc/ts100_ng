/*
 * Heater.c
 *
 *  Created on: 27.07.2017
 *      Author: Marco
 */

#include "stm32f10x.h"

#include "S100V0_1.h"

#include "Heater.h"

void Heater_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef tTimerConfig;
	TIM_OCInitTypeDef tTimerOCConfig;

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
	tTimerOCConfig.TIM_Pulse = 0; // Initial duty cycle 0
	tTimerOCConfig.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM3, &tTimerOCConfig);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_Cmd(TIM3, ENABLE);

    TIM_CCxCmd(TIM3, TIM_Channel_1, TIM_CCx_Enable);

    TIM_CtrlPWMOutputs(TIM3, ENABLE);
}
