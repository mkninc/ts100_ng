/*
 * PID.c
 *
 *  Created on: 20 Sep 2016
 *      Author: ralim
 */

#include "PID.h"


pidSettingsType pidSettings;

#define MAXPIDOUTPUT 50000

static float ITerm;

//This function computes the new value for the ON time of the system
//This is the return value from this function
float computePID(uint16_t const currentValue, uint16_t setpoint) {
	int16_t DInput;
	float output;

	static int16_t lastReading = 0;
	uint16_t currentReading = currentValue; //get the current temp of the iron
	float error = ((float)setpoint - (float)currentReading) / 10.0f; //calculate the error term

	output = (pidSettings.kp * error);

	if(output < 1.0f)
	{
		ITerm += (pidSettings.ki * error);
	}

	if (ITerm > 0.5f)
		ITerm = 0.5f;
	else if (ITerm < 0.0f)
		ITerm = 0.0f; //cap at 0 since we cant force the iron to cool itself :)

	DInput = (currentReading - lastReading); //compute the input to the D term
	output += (ITerm) - (pidSettings.kd * DInput);

	lastReading = currentReading; //storing values for next iteration of the loop
	return output;

}

/*Sets up the pid values*/
void setupPID(void) {
	pidSettings.kp = 0.04f; // 15;
	pidSettings.ki = 0.002f; // 2;
	pidSettings.kd = 0.0f; //3;

	ITerm = 0.0f;
}
