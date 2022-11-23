#include "Mahir.c"
#include "Ryan.c"
#include "Iram.c"
#include "Noah.c"

const int STRUMMING_POWER = 20;
const int FRET_SPEED = -20;
const int STRUMMING_POWER = 20;
const int FRET_SPEED = -20;
const int TIME_UNIT = 500;
const int COLOUR_PORT = S1;
const int ULTRASONIC_PORT = S2;
const int ARR_LENGTH = 100;
const int FULL_ROTATION = 360;
const int FRET_CLICKS = 30;
const int COLOURPORT = S1;
const int MOTORPORT = motorC;
const int WAITCOLOUR = 1000;
const int WAITWHITE = 50;
const int MAXNOTES = 10;
const int MOTORSPEED = -5;
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

task main()
{
	bool startup = startAllTasks(ULTRASONIC_PORT, COLOUR_PORT);

	if(startup)
	{
		displayTextLine(5, "Startup successful");
	}

	int fret[ARR_LENGTH];
	int timing[ARR_LENGTH];

	int const NOTE_COUNT = readSheet(timing, fret);
	displayTextLine(5, "Song loaded");

	int direction = playNotes(fret, timing, NOTE_COUNT);

	displayTextLine(5, "Song finished!");

	bool shutdown = endAllTasks(0,0, direction);

	if(shutdown)
	{
		displayTextLine(5, "Shutdown successful");
	}
}
