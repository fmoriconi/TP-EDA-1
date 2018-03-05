#include <stdio.h>
#include <stdbool.h>

typedef int(*pCallback) (char *, char*, void *);

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData); //Devuelve el numero de argumentos si todos son validos o -1 si alguno no lo es.

int parseCallback(char *key, char *value, void *userData); //Devuelve 1 si la interpretación es correcta y 0 si no lo es.

//hola

typedef struct {
	char key[10];
	char value[10];
} option;

typedef struct {
	option option1;
	option option2;
	option option3;
	char param1[10];
	char param2[10];
	char param3[10];

} userdata;


typedef int(*pCallBack) (char *key, char *value, void *userData);

int main(int argc, char *argv[])
	{
		userdata MyData = { { "food", "pizza" },{ "food", "pasta" },{ "beverage", "coke" },"glass", "dish", "napkin" };
	
		int numargums = parseCmdLine(argc,argv, &parseCallback,&MyData);
		if( numargums >= 0){
			printf("There are %d valid inputs and no invalid inputs", numargums);
		}
		else{
			printf("One or more inputs are invalid.");
		}
		
		getchar();
		return 0;
	}

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData) {

	int vacounter = 0; // "Valid argument counter"
	bool abort = false;

	for (int i = 1; i <= argc && abort != true; i++) {
		if (*argv[i] == '-') {
			if (parseCallback(argv[i], argv[i + 1], userData) == 1) {
				vacounter++;
			}
			else {
				abort = true;
			}
		}
		else{
			if (parseCallback(NULL, argv[i], userData) == 1) {
				vacounter++;
			}
			else {
				abort = true;
			}
		}
	}
	
	if (abort == true) {
		vacounter = -1;
	}

	return vacounter;
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
