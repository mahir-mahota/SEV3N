#include "Mahir.c"
#include "Ryan.c"
#include "Iram.c"
#include "Noah.c"

const int STRUMMING_POWER = 20;
const int FRET_SPEED = -20;
const int TIME_UNIT = 500;
const int COLOUR_PORT = S1;
const int ULTRASONIC_PORT = S2;
const int ARR_LENGTH = 100;
const int FULL_ROTATION = 360;
const int FRET_CLICKS = 30;

task main()
{
	bool startup = startAllTasks(ULTRASONIC_PORT, COLOUR_PORT);

	if(startup)
	{
		displayTextLine(5, "Startup successful");
	}

	int fret[ARR_LENGTH] = {-1};
	int timing[ARR_LENGTH] = {-1};

	int const NOTE_COUNT = readSheet();
	displayTextLine(5, "Song loaded");

	int direction = playNotes(fret, timing, NOTE_COUNT);

	displayTextLine(5, "Song finished!");

	bool shutdown = endAllTasks(0,0, direction);

	if(shutdown)
	{
		displayTextLine(5, "Shutdown successful");
	}
}
