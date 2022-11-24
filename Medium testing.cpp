const int STRUMMING_POWER = 20;
const int FRET_SPEED = -20;
const int TIME_UNIT = 2000;
const int FULL_ROTATION = 360;
const int FRET_CLICKS = 30;
const int FRET_TIMING = 1000;

void pluck(int direction)
{
	motor[motorA] = direction * STRUMMING_POWER;

	nMotorEncoder[motorA] = 0;

	while(abs(nMotorEncoder[motorA]) < 90)
	{}

	motor[motorA] = 0;
}

void setAndPlayFret(int fret, int direction)
{
	int clicksForFret = FRET_CLICKS * (fret - 1);
	int clicksToRotate = FULL_ROTATION - clicksForFret;

	motor[motorD] = FRET_SPEED;
	while(abs(nMotorEncoder[motorD]) < clicksToRotate)
	{}
	motor[motorD] = 0;

	pluck(direction);

	motor[motorD] = FRET_SPEED;
	while(abs(nMotorEncoder[motorD]) < FULL_ROTATION)
	{}
	motor[motorD] = 0;

	nMotorEncoder[motorD] = 0;
}

int playNotes(int *fret, int *hold, int length)
{
	int direction = 1;

	for(int note = 0; note < length; note++)
	{
		setAndPlayFret(fret[note], direction);

		wait1Msec(hold[note]*TIME_UNIT);

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
