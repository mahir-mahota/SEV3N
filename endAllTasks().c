bool endAllTasks(int fret_start, int strum_start)
{
	motor[motorA] = motor[motorD] = 0;
	
	motor[motorD] = -20;
	while(abs(nMotorEncoder[motorD]) > fret_start)
	{}
	motor[motorD] = 0;

	motor[motorA] = -20;
	while(abs(nMotorEncoder[motorA]) > strum_start)
	{}
	motor[motorA] = 0;

	return true;
}