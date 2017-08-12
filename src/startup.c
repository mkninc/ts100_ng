#include "config.h"
#include "FreeRTOS.h"
#include "main.h"
#include "Interrupt.h"

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void ResetISR(void);
static void NmiSR(void);
static void FaultISR(void);
static void IntDefaultHandler(void);
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);
extern void vPortSVCHandler(void);

//*****************************************************************************
//
// Reserve space for the system stack.
//
//*****************************************************************************
#ifndef STACK_SIZE
#define STACK_SIZE                              512
#endif
static unsigned long pulStack[STACK_SIZE];

//*****************************************************************************
//
// The minimal vector table for a Cortex M3.  Note that the proper constructs
// must be placed on this to ensure that it ends up at physical address
// 0x0000.0000.
//
//*****************************************************************************
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
	(void (*)(void))((unsigned long)pulStack + sizeof(pulStack)),
	// The initial stack pointer
		ResetISR,// The reset handler
		NmiSR,// The NMI handler
		FaultISR,// The hard fault handler
		MemManage_Handler,
		BusFault_Handler,
		UsageFault_Handler,
		0,
		0,
		0,
		0,
		vPortSVCHandler,
		DebugMon_Handler,
		0,
		xPortPendSVHandler,
		xPortSysTickHandler,
		WWDG_IRQHandler,
		PVD_IRQHandler,
		TAMPER_IRQHandler,
		RTC_IRQHandler,
		FLASH_IRQHandler,
		RCC_IRQHandler,
		EXTI0_IRQHandler,
		EXTI1_IRQHandler,
		EXTI2_IRQHandler,
		EXTI3_IRQHandler,
		EXTI4_IRQHandler,
		DMA1_Channel1_IRQHandler,
		DMA1_Channel2_IRQHandler,
		DMA1_Channel3_IRQHandler,
		DMA1_Channel4_IRQHandler,
		DMA1_Channel5_IRQHandler,
		DMA1_Channel6_IRQHandler,
		DMA1_Channel7_IRQHandler,
		ADC1_2_IRQHandler,
		USB_HP_CAN1_TX_IRQHandler,
		USB_LP_CAN1_RX0_IRQHandler,
		CAN1_RX1_IRQHandler,
		CAN1_SCE_IRQHandler,
		EXTI9_5_IRQHandler,
		TIM1_BRK_IRQHandler,
		TIM1_UP_IRQHandler,
		TIM1_TRG_COM_IRQHandler,
		TIM1_CC_IRQHandler,
		TIM2_IRQHandler,
		TIM3_IRQHandler,
		TIM4_IRQHandler,
		I2C1_EV_IRQHandler,
		I2C1_ER_IRQHandler,
		I2C2_EV_IRQHandler,
		I2C2_ER_IRQHandler,
		SPI1_IRQHandler,
		SPI2_IRQHandler,
		USART1_IRQHandler,
		USART2_IRQHandler,
		USART3_IRQHandler,
		EXTI15_10_IRQHandler,
		RTCAlarm_IRQHandler,
		USBWakeUp_IRQHandler,
		TIM8_BRK_IRQHandler,
		TIM8_UP_IRQHandler,
		TIM8_TRG_COM_IRQHandler,
		TIM8_CC_IRQHandler,
		ADC3_IRQHandler,
		FSMC_IRQHandler,
		SDIO_IRQHandler,
		TIM5_IRQHandler,
		SPI3_IRQHandler,
		UART4_IRQHandler,
		UART5_IRQHandler,
		TIM6_IRQHandler,
		TIM7_IRQHandler,
		DMA2_Channel1_IRQHandler,
		DMA2_Channel2_IRQHandler,
		DMA2_Channel3_IRQHandler,
		DMA2_Channel4_5_IRQHandler,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,

};

//*****************************************************************************
//
// The following are constructs created by the linker, indicating where the
// the "data" and "bss" segments reside in memory.  The initializers for the
// for the "data" segment resides immediately following the "text" segment.
//
//*****************************************************************************
extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
//extern unsigned long _bss;
//extern unsigned long _ebss;
//extern U32 __SRAM_START; ///< Startaddresse des Programmspeichers, muss vom Linker bereitgestellt.
//extern U32 __SRAM_SIZE; ///< Größe des Programmspeichers, muss vom Linker bereitgestellt.

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied main() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void ResetISR(void) {
	unsigned long *pulSrc, *pulDest;

	// Copy the data segment initializers from flash to SRAM.
	pulSrc = &_etext;
	for (pulDest = &_data; pulDest < &_edata;) {
		*pulDest++ = *pulSrc++;
	}

	// Zero fill the bss segment.  This is done with inline assembly since this
	// will clear the value of pulDest if it is not kept in a register.
	__asm("    ldr     r0, =_bss\n"
			"    ldr     r1, =_ebss\n"
			"    mov     r2, #0\n"
			"    .thumb_func\n"
			"zero_loop:\n"
			"        cmp     r0, r1\n"
			"        it      lt\n"
			"        strlt   r2, [r0], #4\n"
			"        blt     zero_loop");

	// Call the application's entry point.
	main();
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void NmiSR(void) {
	//
	// Enter an infinite loop.
	//
	while (1) {
	}
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
#ifndef ISR_FAULT_DEBUG
static void FaultISR(void) {
	//
	// Enter an infinite loop.
	//
	while (1) {
	}
}
#else
__attribute__((naked))
void FaultISR(void) {
	/*
	 * Get the appropriate stack pointer, depending on our mode,
	 * and use it as the parameter to the C handler. This function
	 * will never return
	 */

	__asm(
			"MOVS   R0, #4  \n"
			"MOV    R1, LR  \n"
			"TST    R0, R1  \n"
			"BEQ    _MSP    \n"
			"MRS    R0, PSP \n"
			"B      HardFault_HandlerC      \n"
			"_MSP:  \n"
			"MRS    R0, MSP \n"
			"B      HardFault_HandlerC      \n"
	);
}
void HardFault_HandlerC(unsigned long *hardfault_args);
void HardFault_HandlerC(unsigned long *hardfault_args) {
	volatile unsigned long stacked_r0;
	volatile unsigned long stacked_r1;
	volatile unsigned long stacked_r2;
	volatile unsigned long stacked_r3;
	volatile unsigned long stacked_r12;
	volatile unsigned long stacked_lr;
	volatile unsigned long stacked_pc;
	volatile unsigned long stacked_psr;
	volatile unsigned long _CFSR;
	volatile unsigned long _HFSR;
	volatile unsigned long _DFSR;
	volatile unsigned long _AFSR;
	volatile unsigned long _BFAR;
	volatile unsigned long _MMAR;

	stacked_r0 = ((unsigned long)hardfault_args[0]);
	stacked_r1 = ((unsigned long)hardfault_args[1]);
	stacked_r2 = ((unsigned long)hardfault_args[2]);
	stacked_r3 = ((unsigned long)hardfault_args[3]);
	stacked_r12 = ((unsigned long)hardfault_args[4]);
	stacked_lr = ((unsigned long)hardfault_args[5]);
	stacked_pc = ((unsigned long)hardfault_args[6]);
	stacked_psr = ((unsigned long)hardfault_args[7]);

	// Configurable Fault Status Register
	// Consists of MMSR, BFSR and UFSR
	_CFSR = (*((volatile unsigned long *)(0xE000ED28)));

	// Hard Fault Status Register
	_HFSR = (*((volatile unsigned long *)(0xE000ED2C)));

	// Debug Fault Status Register
	_DFSR = (*((volatile unsigned long *)(0xE000ED30)));

	// Auxiliary Fault Status Register
	_AFSR = (*((volatile unsigned long *)(0xE000ED3C)));

	// Read the Fault Address Registers. These may not contain valid values.
	// Check BFARVALID/MMARVALID to see if they are valid values
	// MemManage Fault Address Register
	_MMAR = (*((volatile unsigned long *)(0xE000ED34)));
	// Bus Fault Address Register
	_BFAR = (*((volatile unsigned long *)(0xE000ED38)));

	__asm("BKPT #0\n");// Break into the debugger

}
#endif

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void IntDefaultHandler(void) {
	//
	// Go into an infinite loop.
	//
	while (1) {
	}
}
