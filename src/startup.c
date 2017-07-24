//#include "config.h"
//#include "FreeRTOS.h"
#include "main.h"

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
		IntDefaultHandler,// The MPU fault handler
		IntDefaultHandler,// The bus fault handler
		IntDefaultHandler,// The usage fault handler
		0,// Reserved
		0,// Reserved
		0,// Reserved
		0,// Reserved
		IntDefaultHandler,//vPortSVCHandler, 						// SVCall handler
		IntDefaultHandler,// Debug monitor handler
		0,// Reserved
		IntDefaultHandler,//xPortPendSVHandler, 					// The PendSV handler
		IntDefaultHandler,//xPortSysTickHandler, 					// The SysTick handler
		IntDefaultHandler,// GPIO Port A
		IntDefaultHandler,// GPIO Port B
		IntDefaultHandler,// GPIO Port C
		IntDefaultHandler,// GPIO Port D
		IntDefaultHandler,// GPIO Port E
		IntDefaultHandler,// UART0 Rx and Tx
		IntDefaultHandler,// UART1 Rx and Tx
		IntDefaultHandler,// SSI Rx and Tx
		IntDefaultHandler,// I2C Master and Slave
		IntDefaultHandler,// PWM Fault
		IntDefaultHandler,// PWM Generator 0
		IntDefaultHandler,// PWM Generator 1
		IntDefaultHandler,// PWM Generator 2
		IntDefaultHandler,// Quadrature Encoder
		IntDefaultHandler,// ADC Sequence 0
		IntDefaultHandler,// ADC Sequence 1
		IntDefaultHandler,// ADC Sequence 2
		IntDefaultHandler,// ADC Sequence 3
		IntDefaultHandler,// Watchdog timer
		IntDefaultHandler,// Timer 0 subtimer A
		IntDefaultHandler,// Timer 0 subtimer B
		IntDefaultHandler,// Timer 1 subtimer A
		IntDefaultHandler,// Timer 1 subtimer B
		IntDefaultHandler,// Timer 2 subtimer A
		IntDefaultHandler,// Timer 2 subtimer B
		IntDefaultHandler,// Analog Comparator 0
		IntDefaultHandler,// Analog Comparator 1
		IntDefaultHandler,// Analog Comparator 2
		IntDefaultHandler,// System Control (PLL, OSC, BO)
		IntDefaultHandler,// FLASH Control
		IntDefaultHandler,// GPIO Port F
		IntDefaultHandler,// GPIO Port G
		IntDefaultHandler,// GPIO Port H
		IntDefaultHandler,// UART2 Rx and Tx
		IntDefaultHandler,// SSI1 Rx and Tx
		IntDefaultHandler,// Timer 3 subtimer A
		IntDefaultHandler,// Timer 3 subtimer B
		IntDefaultHandler,// I2C1 Master and Slave
		IntDefaultHandler,// Quadrature Encoder 1
		IntDefaultHandler,// CAN0
		IntDefaultHandler,// CAN1
		IntDefaultHandler,// CAN2
		IntDefaultHandler,// Ethernet
		IntDefaultHandler,// Hibernate
		IntDefaultHandler,// USB0
		IntDefaultHandler,// PWM Generator 3
		IntDefaultHandler,// uDMA Software Transfer
		IntDefaultHandler
		// uDMA Error
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
