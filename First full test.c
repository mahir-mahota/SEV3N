const int STRUMMING_POWER = 100;
const int FRET_SPEED = -100;
const int TIME_UNIT = 300;
const int COLOUR_PORT = S1;
const int ULTRASONIC_PORT = S2;
const int ARR_LENGTH = 100;
const int FULL_ROTATION = 360;
const int FRET_CLICKS = 30;
const int FRET_TIMING = 100;
const int PLUCK_ANGLE = 45;
const int SHUTDOWN_WAIT = 2000;
const int COLOURPORT = S1;
const int MOTORPORT = motorC;
const int USPORT = S2;
const int WAITCOLOUR = 500;
const int WAITWHITE = 200;
const int MOTORSPEED = -5;
const int SENSORDIST = 11;
const int REPEATTIME = 5;
const int REPEATS = 10;
const int colourValues[8] =
	{
		0,////empty 0
		0,//black 1
		2,//blue 2
		3,//green 3
		5,//yellow 4
		7,//red 5
		0,//white 6
		10//brown 7
	};
const int Remap[11] = {0,1,2,3,4,6,6,8,8,9,10}; //reverse of c++ code

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

void pluck(int direction)
{
	motor[motorA] = direction * STRUMMING_POWER;

	nMotorEncoder[motorA] = 0;

	while(abs(nMotorEncoder[motorA]) < PLUCK_ANGLE)
	{}

	motor[motorA] = 0;
}

void setAndPlayFret(int fret, int time, int direction, int count)
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
	while(abs(nMotorEncoder[motorD]) < 360*count)
	{}
	motor[motorD] = 0;
}

int playNotes(int *fret, int *hold, int length)
{
	int direction = 1;
	int count = 1;

	for(int note = 0; note < length; note++)
	{
		setAndPlayFret(fret[note], hold[note], direction, count);

		direction *= -1;
		count++;
	}

	return direction;
}

bool paperPresent()
{
	return SensorValue[USPORT] < SENSORDIST || SensorValue[USPORT] == 255;
}

int getRepeatRead()
{
	int values[REPEATS];
	for (int i = 0; i < REPEATS; i++)
	{
		values[i] = -1;
	}

	bool Loop = true;
	while (Loop)
	{
		Loop = false;
		for (int i = 0; i < REPEATS; i++)
		{
			if (i!=-1 && i > 0 && values[i] != values[i-1])
			{
				Loop = true;
			}
	  }

	  for (int i = 0; i < REPEATS; i++)
	  {
	  	if(i < REPEATS - 1)
	  	{
	  		values[i] = values[i+1];
			}
			else
			{
				values[i] = SensorValue[COLOURPORT];
			}
		}

		if (values[0] == -1)
		{
			Loop = true;
		}

		wait1Msec(REPEATTIME);
	}

	return values[0];
}

int readSheet(int * Times, int * Frets)
{
	// start to read in.

		int Notes = 0;
		bool timeRead = false;

		motor[MOTORPORT] = MOTORSPEED;

		while(paperPresent())
		{
			while (getRepeatRead() == (int)colorWhite && paperPresent())
			{}

			displayString(5, "Not White");

			wait1Msec(WAITCOLOUR);

			int value = getRepeatRead();

			displayString(5, "%d         ", value);

			if(!timeRead)
			{
				Times[Notes] = Remap[colourValues[value]];
				timeRead = true;
			}
			else
			{
				Frets[Notes] = colourValues[value];
				timeRead = false;
				Notes++;
			}

			while (getRepeatRead() != (int)colorWhite && paperPresent())
			{}

			displayString(5, "White     ");

			wait1Msec(WAITWHITE);
	}

	motor[MOTORPORT] = 0;

	return Notes;
}

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
	while(abs(nMotorEncoder[motorA]) < strum_start)
	{}
	motor[motorA] = 0;

	return true;
}

task main()
{
	bool startup = startAllTasks(ULTRASONIC_PORT, COLOUR_PORT);

	if(startup)
	{
		displayBigTextLine(5, "Startup successful");
	}

	int fret[ARR_LENGTH];
	int timing[ARR_LENGTH];

	while (!getButtonPress(buttonEnter))
	{}

	int const NOTE_COUNT = readSheet(timing, fret);
	displayBigTextLine(5, "Song loaded");

	int direction = playNotes(fret, timing, NOTE_COUNT);

	displayBigTextLine(5, "Song finished!");

	wait1Msec(SHUTDOWN_WAIT);

	bool shutdown = endAllTasks(0,0, direction);

	if(shutdown)
	{
		displayBigTextLine(5, "Shutdown successful");
	}
}
