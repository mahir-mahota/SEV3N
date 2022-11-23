void pluck(int direction)
{
	motor[motorA] = direction * STRUMMING_POWER;

	nMotorEncoder[motorA] = 0;

	while(abs(nMotorEncoder[motorA]) < STRUM_ANGLE)
	{}

	motor[motorA] = 0;
}

void setAndPlayFret(int fret, int time, int direction)
{
	int previous_clicks = nMotorEncoder[D];
	int offset = previous_clicks % 360;
	int rotation = FULL_ROTATION - offset;
	int clicksForFret = FRET_CLICKS * (fret - 1);
	int clicksToRotate = rotation - clicksForFret;

	time1[T1] = 0;

	motor[motorD] = FRET_SPEED;
	while(abs(nMotorEncoder[motorD]) < clicksToRotate)
	{}
	motor[motorD] = 0;

	while(time1[T1] < time * TIME_UNIT - FRET_TIMING)
	{}

	pluck(direction);

	wait1Msec(FRET_TIMING);
}
