const int COLOURPORT = S1;
const int MOTORPORT = motorC;
const int WAITCOLOUR = 1000;
const int WAITWHITE = 50;
const int MAXNOTES = 10;
const int MOTORSPEED = -5;

int readSheet(int * Times, int * Frets);

const int colourValues[8] =
	{
		0,////empty
		0,//black
		2,//blue
		3,//green
		5,//yellow
		7,//red
		0,//white
		10//brown
	};

const int Remap[11] = {0,1,2,3,4,6,6,8,8,9,10}; //reverse of c++ code

int Times[MAXNOTES];
int Frets[MAXNOTES];

task main()
{
		SensorMode[COLOURPORT] = modeEV3Color_Color;

		int numNotes = readSheet(Times, Frets);

		displayString(5, "%d Notes", numNotes);
}

int readSheet(int * Times, int * Frets)
{
	// start to read in.
		while (!getButtonPress(buttonEnter))
		{}

		int Notes = 0;
		bool timeRead = false;

		motor[MOTORPORT] = MOTORSPEED;

		for (int count = 0; count < MAXNOTES; count ++)//while(true)
		{
			while (SensorValue[COLOURPORT] == (int)colorWhite)
			{}

			displayString(5, "Not White");

			wait1Msec(WAITCOLOUR);

			if(!timeRead)
			{
				Times[Notes] = Remap[colourValues[SensorValue[COLOURPORT]]];
				timeRead = true;
			}
			else
			{
				Frets[Notes] = colourValues[SensorValue[COLOURPORT]];
				timeRead = false;
				Notes++;
			}

			while (SensorValue[COLOURPORT] != (int)colorWhite)
			{}

			displayString(5, "White     ");

			wait1Msec(WAITWHITE);
	}

	return Notes;
}
