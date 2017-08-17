/*
 * Setup functions for the basic hardware present in the system
 */
#ifndef __BIOS_H
#define __BIOS_H

#include "stm32f10x.h"
#include "S100V0_1.h"/*For pin definitions*/
#include "Analog.h"/*So that we can attach the DMA to the output array*/
#include "stm32f10x_flash.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_iwdg.h"
#include "misc.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Init_Gtime(void);
extern void USB_Port(u8 state);
extern void NVIC_Config(u16 tab_offset);
extern void RCC_Config(void);
extern void GPIO_Config(void);
extern void Adc_Init(void);
extern void Init_Timer3(void);
/*Interrupts*/
extern void TIM3_ISR(void);
extern void Init_EXTI(void);
/*Watchdog*/
extern void Start_Watchdog(uint32_t ms);
extern void Clear_Watchdog(void);

#ifdef __cplusplus
}
#endif

#endif

