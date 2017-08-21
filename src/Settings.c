/*
 * Settings.c
 *
 *  Created on: 29 Sep 2016
 *      Author: Ralim
 *
 *      This file holds the users settings and saves / restores them to the devices flash
 */
#include "Interrupt.h"
#include "Oled.h"
#include "graphbuffer.h"

#include "FreeRTOS.h"
#include "task.h"

#include "Settings.h"


systemSettingsType systemSettings;

#define FLASH_ADDR 		(0x8000000|0xBC00)/*Flash start OR'ed with the maximum amount of flash - 1024 bytes*/
#define FLASH_LOGOADDR 	(0x8000000|0xB800) /*second last page of flash set aside for logo image*/

//-----------------------------------------------------------------------------
void saveSettings(void) {
	uint16_t *data = (uint16_t*) &systemSettings;

	//First we erase the flash
	FLASH_Unlock(); //unlock flash writing
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	while (FLASH_ErasePage(FLASH_ADDR) != FLASH_COMPLETE)
		; //wait for it
	//erased the chunk
	//now we program it

	for (uint8_t i = 0; i < (sizeof(systemSettings) / 2); i++) {
		FLASH_ProgramHalfWord(FLASH_ADDR + (i * 2), data[i]);
	}
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void restoreSettings(void) {
	//We read the flash
	uint16_t *data = (uint16_t*) &systemSettings;
	for (uint8_t i = 0; i < (sizeof(systemSettings) / 2); i++) {
		data[i] = *(uint16_t *) (FLASH_ADDR + (i * 2));
	}
	//if the version is correct were done
	//if not we reset and save
	if (systemSettings.version != SETTINGSVERSION) {
		//probably not setup
		resetSettings();
		saveSettings();
	}
}
//-----------------------------------------------------------------------------

//Lookup function for cutoff setting -> X10 voltage
/*
 * 0=DC
 * 1=3S
 * 2=4S
 * 3=5S
 * 4=6S
 */
//-----------------------------------------------------------------------------
uint32_t lookupVoltageLevel(uint32_t const level) {
	if (level == 0)
		return 100;	//10V since iron does not function below this
	else
		return (level * 33) + (33 * 2);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void resetSettings(void) {

	systemSettings.SleepTemp = 150;//Temperature the iron sleeps at - default 150.0 C
	systemSettings.SleepTime = 1;//How many minutes we wait until going to sleep - default 1 min
	systemSettings.SolderingTemp = 320;	//Default soldering temp is 320.0 C
	systemSettings.cutoutSetting = 0;			//default to no cut-off voltage
	systemSettings.version = SETTINGSVERSION;//Store the version number to allow for easier upgrades
	systemSettings.displayTempInF = 0;			//default to C
	systemSettings.flipDisplay = 0;				//Default to right handed mode
	systemSettings.sensitivity = 6;				//Default high sensitivity
	systemSettings.tempCalibration = 239;	//Default to their calibration value
	systemSettings.voltageDiv = 144;			//Default divider from schematic
	systemSettings.ShutdownTime = 30;//How many minutes until the unit turns itself off
	systemSettings.temperatureRounding = 0;	//How the temperature is rounded off
	systemSettings.boostModeEnabled = 0;//Default to safe, with no boost mode
	systemSettings.BoostTemp = 400;				//default to 400C
}
//-----------------------------------------------------------------------------
