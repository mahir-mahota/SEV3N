#include "Mahir.c"
#include "Ryan.c"
#include "Iram.c"
#include "Noah.c"

task main()
{
	bool startup = startAllTasks();

	if(startup == true)
	{
		displayTextLine(5, "Startup successful");
	}

	int fret[] = {-1};
	int timing[] = {-1};

	int const NOTE_COUNT = readSheet();
	displayTextLine(5, "Song loaded");

	playNotes(fret, timing, NOTE_COUNT);

	displayTextLine(5, "Song finished!");

	bool shutdown = endAllTasks(0,0);

	if(shutdown == true)
	{
		displayTextLine(5, "Shutdown successful");
	}
}
