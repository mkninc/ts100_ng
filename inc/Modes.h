/*
 * Modes.h
 *
 *  Created on: 17 Sep 2016
 *      Author: Ralim
 *
 *      Modes.h -> Main function for driving the application
 *      This processes the buttons then does the gui
 */

#ifndef MODES_H_
#define MODES_H_

#include "Interrupt.h"
#include "S100V0_1.h"
#include "Oled.h"
#include "Settings.h"
#include "Analog.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	STARTUP, 		//we are sitting on the prompt to push a button
	SOLDERING, 		//Normal operating mode
	TEMP_ADJ,		//Adjust the set temperature
	SETTINGS,		//Settings menu
	SLEEP,			//Iron is snoozing due to lack of use
	COOLING,		//Iron is cooling down -> Warning screen
	UVLOWARN,		//Unit tripped low voltage
	THERMOMETER,	//Read the tip temp
	DCINDISP,		//Disp the input voltage && Cal the DCin voltage divider
	TEMPCAL,		//Cal tip temp offset
} operatingModeEnum;

#define SETTINGSOPTIONSCOUNT 10 /*Number of settings in the settings menu*/

typedef enum {
	UVCO = 0,
	SLEEP_TEMP,
	SLEEP_TIME,
	SHUTDOWN_TIME,
	MOTIONSENSITIVITY,
	TEMPDISPLAY,
	TEMPROUNDING,
	LEFTY,
	BOOSTMODE,
	BOOSTTEMP,
} settingsPageEnum;

extern void ProcessUI(void);
extern void DrawUI(void);
extern void drawTemp(uint16_t temp, uint8_t x, uint8_t roundingMode);

#ifdef __cplusplus
}
#endif

#endif /* MODES_H_ */
