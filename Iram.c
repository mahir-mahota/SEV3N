void pluck(int power, int direction)
{
	motor[motorA] = direction * power;

	nMotorEncoder[motorA] = 0;

	while(abs(nMotorEncoder[motorA]) < 90)
	{}

	motor[motorA] = 0;
}

void setAndPlayFret(int fret, int direction)
{
	int clicksForFret = FRET_CLICKS(fret - 1);
	int clicksToRotate = FULL_ROTATION - clicksBetweenFrets;

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
