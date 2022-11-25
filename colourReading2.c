const int COLOURPORT = S1;
const int MOTORPORT = motorC;
const int USPORT = S2;
const int WAITCOLOUR = 500;
const int WAITWHITE = 200;
const int MAXNOTES = 30;
const int MOTORSPEED = -5;
const int SENSORDIST = 11;
const int REPEATTIME = 5;
const int REPEATS = 10;

int readSheet(int * Times, int * Frets);

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

int Times[MAXNOTES];
int Frets[MAXNOTES];

task main()
{
		SensorMode[COLOURPORT] = modeEV3Color_Color;

		while (!getButtonPress(buttonEnter))
		{}

		int numNotes = readSheet(Times, Frets);

		//displayString(5, "%d Notes", numNotes);
		wait1Msec(1000000000);
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
