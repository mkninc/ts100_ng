/*
 * FreeRTOSConfig.h
 *
 *  Created on: 10.08.2017
 *      Author: Marco
 */

#ifndef INC_FREERTOSCONFIG_H_
#define INC_FREERTOSCONFIG_H_

#define configTOTAL_HEAP_SIZE		(8192)
#define configMINIMAL_STACK_SIZE	(120)

#define configSYSTICK_CLOCK_HZ		(48000000)
#define configTICK_RATE_HZ			(1000)

#define configUSE_IDLE_HOOK    		(0)
#define configUSE_PREEMPTION		(1)
#define configMAX_PRIORITIES		(4)
#define configUSE_16_BIT_TICKS		(0)
#define configUSE_TICK_HOOK			(0)
#define configMAX_SYSCALL_INTERRUPT_PRIORITY	(0x7F)


#endif /* INC_FREERTOSCONFIG_H_ */
