#include <stdio.h>
#include parsecmdl.h

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData)
{
	int vacounter = 0; // "Valid argument counter"
	bool abort = false;

	for (int i = 1; i <= argc && abort != true; i++)
	{
		if (*argv[i] == '-')
		{
			if (parseCallback(argv[i], argv[i + 1], userData) == 1)
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
