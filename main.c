#include <stdio.h>

#define PROGRAMNAME "parseprog"
#define NUM_TESTS 9
#define MAX_TEST 10

int parseCallback(char *key, char *value, void *userData); //Devuelve 1 si la interpretación es correcta y 0 si no lo es.


//Parametros takehome, forhere, napkin
//Opciones food: pizza, burger, pasta // beverage: coke, water // size: small, medium, big

int main (void)
{
	// Testing Bench
	// 
	char *attempts[NUM_TESTS][]= {{PROGRAMNAME, "-clothes", "trouser" , NULL } // unexist option and value
						 {PROGRAMNAME, "shop", NULL } // unexist parameter
						 {PROGRAMNAME, "-food", NULL } // non-value for the option
						 {PROGRAMNAME, "-food", "salad" , NULL } // unknown value
						 {PROGRAMNAME, "-food", "salad", "shop" , NULL } // option is well but the parameter does not exist
						 {PROGRAMNAME, "-food", "pasta", "-beverage", "water", "forhere", "napkin", "-size", NULL } //non-value for size option
						 {PROGRAMNAME, "-food", "pasta", "-beverage", "water", "forhere", "napkin", "-size", "big" , NULL } // good try
						 {PROGRAMNAME, "-food", "burger", "-beverage", "coke", "takehome", "napkin", "-size", "small" , NULL } // good try
						 {PROGRAMNAME, "-food", "pizza", "-beverage", "water", "forhere", NULL } // good try
						};
	int i;
    for (i = 0; i < NUM_TESTS; i++)
	{
		quantity = parseCmdLine(,,,);
		
		if(quantity > -1)
		{
			printf("Test: %d \n Result: %d\n All data is correct \n", i+1, quantity);
		}
		else
		{
			printf("One or more inputs are invalid.\n");
		}
	}
	
	getchar();
	return 0;
}

int parseCallback(char *key, char *value, void *userData) {

	bool validargument;
	userdata * data = (userdata*)userData; //Esto es medio redundante, lo sé, pero visual studio no me dejaba desreferenciarlo bien si no lo hacía.

	if(key != NULL){

	}

	else {

	}

	return validargument;
}