bool startAllTasks(int ultrasonic, int colour)
{
	SensorType[ultrasonic] = sensorEV3_Ultrasonic;
	wait1Msec(50);
	SensorType[colour] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[colour] = modeEV3Color_Color;
	wait1Msec(100);

	nMotorEncoder[motorA] = nMotorEncoder[motorD] = 0;

	return true;
}

void playNotes(int fret[], int hold[], int length)
{
	int direction = 1;

	for(int note = 0; note < length; note++)
	{
		setFret(fret[note]);
		pluck(direction);

		wait1Msec[hold[note]*TIME_UNIT];

		direction *= -1;
	}
}
