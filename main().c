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
		wait1Msec(5000);
		eraseDisplay();
	}

	//Initialize arrays
	//readSheet();
	//playNote();

	displayTextLine(4, "Song finished!");

	bool shutdown = endAllTasks(0,0);

	if(shutdown == true)
	{
		displayTextLine(5, "Shutdown successful");
	}
}
