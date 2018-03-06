#include <stdio.h>
#include <stdbool.h>
#include "parseCmdLine.h"

int parseCmdLine(int argc, char *argv[], pCallback parseCallback, void *userData)
{
	int vacounter = 0; // "Valid argument counter"
	bool abort = false;

	for (int i = 1; i <= argc && abort != true; i++)
	{
		if (*argv[i] == '-')
		{
			if (parseCallback(argv[i]+1, argv[i + 1], userData) == 1)
			{
				vacounter++;
			}
			else
			{
				abort = true;
			}
		}
		else
		{
			if (parseCallback(NULL, argv[i], userData) == 1)
			{
				vacounter++;
			}
			else
			{
				abort = true;
			}
		}
	}
	
	if (abort == true) {
		vacounter = -1;
	}
return vacounter;
}
