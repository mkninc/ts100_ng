/*
 * PID.c
 *
 *  Created on: 20 Sep 2016
 *      Author: ralim
 */
#include "config.h"
#include "PID.h"


pidSettingsType pidSettings;

#define MAXPIDOUTPUT 50000

static int32_t ITerm;

//This function computes the new value for the ON time of the system
//This is the return value from this function
int32_t computePID(uint16_t const currentValue, uint16_t setpoint) {
	int32_t DInput;
	int32_t output;

	static int16_t lastReading = 0;
	int32_t currentReading = currentValue; //get the current temp of the iron
	pidSettings.currentError = (setpoint - currentReading) * 1000; //calculate the error term

	output = FIXPOINT_DIVROUND(pidSettings.kp * pidSettings.currentError); //  ((pidSettings.kp * error) / FIXPOINT_FACTOR);

	if(output < FIXPOINT_FACTOR)
	{
		ITerm += FIXPOINT_DIVROUND(pidSettings.ki * pidSettings.currentError);  // ((pidSettings.ki * error) / FIXPOINT_FACTOR);
	}

	if (ITerm > (FIXPOINT_FACTOR / 2))  // TODO: check limit
		ITerm = (FIXPOINT_FACTOR / 2);
	else if (ITerm < 0)
		ITerm = 0; //cap at 0 since we cant force the iron to cool itself :)

	DInput = (currentReading - lastReading) * 1000; //compute the input to the D term
	output += (ITerm) - FIXPOINT_DIVROUND(pidSettings.kd * DInput);

	lastReading = currentReading; //storing values for next iteration of the loop
	return output;

}

/*Sets up the pid values*/
void setupPID(void) {
	pidSettings.kp = 100; // 15;
	pidSettings.ki = 10; // 2;
	pidSettings.kd = 0; //3;

	ITerm = 0;
}

int32_t PID_GetError(void) {
return pidSettings.currentError;
}
