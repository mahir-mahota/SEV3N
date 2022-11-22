bool endAllTasks(int fret_start, int strum_start, int direction)
{
	motor[motorA] = motor[motorD] = 0;

	const int CURRENT_CLICKS = nMotorEncoder[motorD];
	const int OFFSET = CURRENT_CLICKS % 360;
	const int ADJUSTMENT = 360 - OFFSET + fret_start;

	nMotorEncoder[motorD] = 0;

	motor[motorD] = FRET_SPEED;
	while(abs(nMotorEncoder[motorD]) < ADJUSTMENT)
	{}
	motor[motorD] = 0;

	motor[motorA] = -1 * direction * STRUMMING_POWER;
	while(abs(nMotorEncoder[motorA]) > strum_start)
	{}
	motor[motorA] = 0;

	return true;
}
