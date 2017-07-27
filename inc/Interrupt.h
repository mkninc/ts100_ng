/*
 * Interrupt Service Routines
 * This file manages all the IRQ events that can be generated
 */
#ifndef __INTERRUPT_H
#define __INTERRUPT_H

#include <stdint.h>

/* Functions for access to data */
extern volatile uint32_t system_Ticks;
void delayMs(uint32_t ticks);
volatile extern uint32_t lastKeyPress;
volatile extern uint32_t lastMovement;

volatile extern uint8_t keyState;
volatile extern uint8_t rawKeys;

extern uint32_t millis(void);

extern uint32_t getLastButtonPress(void);

extern void resetLastButtonPress(void);

extern void resetButtons(void);

extern uint32_t getLastMovement(void);

extern uint16_t getButtons(void);

extern uint16_t getRawButtons(void);

extern void restoreButtons(void);

/*IRQ prototypes*/
extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void MemManage_Handler(void);
extern void BusFault_Handler(void);
extern void UsageFault_Handler(void);
extern void SVC_Handler(void);
extern void DebugMon_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);

extern void WWDG_IRQHandler(void);
extern void PVD_IRQHandler(void);
extern void TAMPER_STAMP_IRQHandler(void);
extern void RTC_WKUP_IRQHandler(void);
extern void FLASH_IRQHandler(void);

extern void USB_LP_CAN1_RX0_IRQHandler(void);
extern void I2C1_EV_IRQHandler(void);
extern void I2C1_ER_IRQHandler(void);
extern void TIM2_IRQHandler(void);
extern void TIM3_IRQHandler(void);

extern void WWDG_IRQHandler(void);
extern void PVD_IRQHandler(void);

extern void TAMPER_IRQHandler(void);
extern void RTC_IRQHandler(void);
extern void FLASH_IRQHandler(void);
extern void RCC_IRQHandler(void);
extern void EXTI0_IRQHandler(void);
extern void EXTI1_IRQHandler(void);
extern void EXTI2_IRQHandler(void);
extern void EXTI3_IRQHandler(void);
extern void EXTI4_IRQHandler(void);
extern void DMA1_Channel1_IRQHandler(void);
extern void DMA1_Channel2_IRQHandler(void);
extern void DMA1_Channel3_IRQHandler(void);
extern void DMA1_Channel4_IRQHandler(void);
extern void DMA1_Channel5_IRQHandler(void);
extern void DMA1_Channel6_IRQHandler(void);
extern void DMA1_Channel7_IRQHandler(void);
extern void ADC1_2_IRQHandler(void);
extern void USB_HP_CAN1_TX_IRQHandler(void);
extern void CAN1_RX1_IRQHandler(void);
extern void CAN1_SCE_IRQHandler(void);
extern void EXTI9_5_IRQHandler(void);
extern void TIM1_BRK_IRQHandler(void);
extern void TIM1_UP_IRQHandler(void);
extern void TIM1_TRG_COM_IRQHandler(void);
extern void TIM1_CC_IRQHandler(void);
extern void TIM4_IRQHandler(void);
extern void I2C1_EV_IRQHandler(void);
extern void I2C1_ER_IRQHandler(void);
extern void I2C2_EV_IRQHandler(void);
extern void I2C2_ER_IRQHandler(void);
extern void SPI1_IRQHandler(void);
extern void SPI2_IRQHandler(void);
extern void USART1_IRQHandler(void);
extern void USART2_IRQHandler(void);
extern void USART3_IRQHandler(void);
extern void EXTI15_10_IRQHandler(void);
extern void RTCAlarm_IRQHandler(void);
extern void USBWakeUp_IRQHandler(void);
extern void TIM8_BRK_IRQHandler(void);
extern void TIM8_UP_IRQHandler(void);
extern void TIM8_TRG_COM_IRQHandler(void);
extern void TIM8_CC_IRQHandler(void);
extern void ADC3_IRQHandler(void);
extern void FSMC_IRQHandler(void);
extern void SDIO_IRQHandler(void);
extern void TIM5_IRQHandler(void);
extern void SPI3_IRQHandler(void);
extern void UART4_IRQHandler(void);
extern void UART5_IRQHandler(void);
extern void TIM6_IRQHandler(void);
extern void TIM7_IRQHandler(void);
extern void DMA2_Channel1_IRQHandler(void);
extern void DMA2_Channel2_IRQHandler(void);
extern void DMA2_Channel3_IRQHandler(void);
extern void DMA2_Channel4_5_IRQHandler(void);

#endif /* __INTERRUPT_H */

/*********************************  END OF FILE  ******************************/
