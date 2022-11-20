#include "Mahir.c"
#include "Ryan.c"
#include "Iram.c"
#include "Noah.c"

task main()
{


	bool end = endAllTasks(0,0);

	if(end == true)
	{
		displayTextLine(5, "Shutdown successful");
	}
}
