/*
 * Created by Ben V. Brown
 */

#include <stdbool.h>
#include "Modes.h"
#include "Bios.h"
#include "MMA8652FC.h"
#include "PID.h"
#include "Oled.h"
#include "Settings.h"
#include "I2C.h"
#include "Heater.h"
#include "graphbuffer.h"

#include "FreeRTOS.h"
#include "task.h"

void setup(void);

HEATER_INST heater;
volatile uint32_t systemReady;

//-----------------------------------------------------------------------------
static void MainTask(void * pvParameters) {

	setup();/*Setup the system*/

	systemReady = true;

	while (1) {
#ifndef SIMULATION_BOARD
		Clear_Watchdog(); //reset the Watch dog timer
#endif
#ifdef SIMULATION_BOARD
//		Heater_SetDutyCycle(&heater, dummy);
//		dummy += 0.001f;
//		if(dummy > 1.0f)
//			dummy = 0.0f;
#endif
		Heater_Execute(&heater);
	}
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void UITask(void * pvParameters) {
	TickType_t previousWakeTime;

	while(!systemReady);

	previousWakeTime = xTaskGetTickCount();

	while (1) {

		ProcessUI();
		Graph_Clear();
		DrawUI();
		Graph_Update();

		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == Bit_RESET) {
			lastMovement = millis();
			//This is a workaround for the line staying low as the user is still moving. (ie sensitivity is too high for their amount of movement)
		}

		vTaskDelayUntil(&previousWakeTime, pdMS_TO_TICKS(50));
	}
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
static void setupSystem(void) {
	RCC_Config(); 										//setup system clock
	NVIC_Config(0x4000); //this shifts the NVIC table to be offset, for the usb bootloader's size

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int main(void) {
	systemReady = false;

	setupSystem();

	xTaskCreate(MainTask, "HeaterControl", configMINIMAL_STACK_SIZE, NULL,
			tskIDLE_PRIORITY + 2, NULL);

	xTaskCreate(UITask, "UI", configMINIMAL_STACK_SIZE, NULL,
				tskIDLE_PRIORITY + 1, NULL);

	vTaskStartScheduler();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void setup(void) {

	GPIO_Config(); 									//setup all the GPIO pins
	Init_EXTI(); 										//Init the EXTI inputs
	//Init_Timer3(); 							//Used for the soldering iron tip
	Adc_Init(); 										//Init adc and DMA
	I2C_Configuration();								//Start the I2C hardware
	GPIO_Init_OLED();						//Init the GPIO ports for the OLED

	Heater_Init(&heater);

	restoreSettings();									//Load settings
#ifndef SIMULATION_BOARD
	StartUp_Accelerometer(systemSettings.sensitivity); //Start the accelerometer
#endif
	setupPID(); 										//Init the PID values
	Heater_SetCalibrationValue(&heater, systemSettings.tempCalibration); //  readIronTemp(systemSettings.tempCalibration, 0, 0); //load the default calibration value
	Init_Oled(systemSettings.flipDisplay); 				//Init the OLED display

	Graphic_Init();

#ifndef SIMULATION_BOARD
	OLED_DrawString("VER 0.XX", 8); 					//Version Number
#endif
	delayMs(300);								//Pause to show version number
	showBootLogoIfavailable();
#ifndef SIMULATION_BOARD
	Start_Watchdog(1000); 		//start the system watch dog as 1 second timeout
#endif
}
//-----------------------------------------------------------------------------
