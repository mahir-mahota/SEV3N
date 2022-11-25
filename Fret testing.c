const int STRUMMING_POWER = 80;
const int FRET_SPEED = -10;
const int TIME_UNIT = 2000;
const int FULL_ROTATION = 360;
const int FRET_CLICKS = 30;
const int FRET_TIMING = 2000;
const int STRUM_ANGLE = 45;

void pluck(int direction)
{
	motor[motorA] = direction * STRUMMING_POWER;

	nMotorEncoder[motorA] = 0;

	while(abs(nMotorEncoder[motorA]) < STRUM_ANGLE)
	{}

	motor[motorA] = 0;
}

int cycleEncoderValue()
{
	int encoderValue = abs(nMotorEncoder[motorD]);
	return encoderValue - encoderValue/FULL_ROTATION * FULL_ROTATION;
}

void setAndPlayFret(int fret, int time, int direction, int previous_fret)
{
	//int encoder = nMotorEncoder[D];
	//int offset = previous_clicks % 360;
	//int rotation = FULL_ROTATION - offset;
	int clicksForFret = FRET_CLICKS * (fret - 1);
	//int clicksToRotate = encoder - encoder/FULL_ROTATION * FULL_ROTATION;

	time1[T1] = 0;
	motor[motorD] = FRET_SPEED;
	while(cycleEncoderValue() > clicksForFret)
	{}
	while(cycleEncoderValue() < clicksForFret)
	{}

	//while(abs(nMotorEncoder[motorD]) < abs(clicksToRotate))
	//{}
	motor[motorD] = 0;

	displayString("%d",cycleEncoderValue());

	while(time1[T1] < time * TIME_UNIT - FRET_TIMING)
	{}

	pluck(direction);

	wait1Msec(FRET_TIMING);

	//motor[motorD] = FRET_SPEED;
	//while(abs(nMotorEncoder[motorD]) < FULL_ROTATION)
	//{}
	//motor[motorD] = 0;

	//nMotorEncoder[motorD] = 0;
}

int playNotes(int *fret, int *hold, int length)
{
	int direction = 1;
	int previous_fret = 1;

	for(int note = 0; note < length; note++)
	{
		setAndPlayFret(fret[note], hold[note], direction, previous_fret);

		previous_fret = fret[note];

		direction *= -1;
	}
	return direction;
}

task main()
{
	int fret[10] = {10, 7, 5, 3, 2, 2, 3, 5, 7, 10};
	int hold[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	playNotes(fret, hold, 10);
}
