const int STRUMMING_POWER = 100;
const int FRET_SPEED = -80;
const int TIME_UNIT = 500;
const int FULL_ROTATION = 360;
const int FRET_CLICKS = 30;
const int FRET_TIMING = 500;

void pluck(int direction)
{
	motor[motorA] = direction * STRUMMING_POWER;

	nMotorEncoder[motorA] = 0;

	while(abs(nMotorEncoder[motorA]) < 90)
	{}

	motor[motorA] = 0;
}

void setAndPlayFret(int fret, int time, int direction)
{
	int clicksForFret = FRET_CLICKS * (fret - 1);
	int clicksToRotate = FULL_ROTATION - clicksForFret;

	time1[T1] = 0;

	motor[motorD] = FRET_SPEED;
	while(abs(nMotorEncoder[motorD]) % 360 < clicksToRotate)
	{}
	motor[motorD] = 0;

	while(time1[T1] < time * TIME_UNIT - FRET_TIMING)
	{}

	pluck(direction);

	wait1Msec(FRET_TIMING);

	motor[motorD] = FRET_SPEED;
	while(abs(nMotorEncoder[motorD]) % 360 != 0)
	{}
	motor[motorD] = 0;
}

int playNotes(int *fret, int *hold, int length)
{
	int direction = 1;

	for(int note = 0; note < length; note++)
	{
		setAndPlayFret(fret[note], hold[note], direction);

		direction *= -1;
	}

	return direction;
}

task main()
{
	int fret[16] = {7, 7, 10, 7, 5, 3, 2, 7, 7, 10, 7, 5, 3, 5, 3, 2};
	int hold[16] = {0, 6, 2,  3, 3, 2, 8, 8, 6, 2,  3, 3, 2, 3, 3, 2};

	playNotes(fret, hold, 16);
}
