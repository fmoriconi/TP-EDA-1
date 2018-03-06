#define OPTION_IDENTIFIER '-'
#define ERRORPARSE -1

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData); 
/*  Esta funcion recibe 4 parametros, la cantidad de datos ingresados, argc,
	el puntero correspondiente a esos datos, argv,
	un puntero a funcion para la validacion de datos, p,
	y userData es un pasaje por referencia de una estructura en la cual se encuentran las posibles opciones y parametros validos.
	Devuelve el numero de argumentos si todos son validos o -1 si alguno no lo es.
*/