// TPEDA01.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <ctype.h>

/*  EDA_TPn1
Grupo n°4

Integrantes:
FRANCO LEON MORICONI
FRANCISCO MUSICH
GUIDO MARTIN PANAGGIO VENERANDI
FRANCISCO MARTIN TOLABA

En este programa se solicitó hacer un parseo de datos ingresados con un banco de pruebas
se prueba la función parsecmdl simulando mediante una matriz los datos que se ingresarían
por linea de comandos.
Dicha función utiliza un callback para la validación de los datos mediante la comparación
y búsqueda en una estructura donde se encuentran preestablecidos.
*/

#include "parseCmdLine.h"
#include "general.h"


int main(int argc, char * argv[])
{
	userdata_t valEstablecidos;

	//Parametros takehome, forhere, napkin
	//Opciones food: pizza, burger, pasta // beverage: coke, water,sprite // size: small, medium, big


	valEstablecidos.opciones[0].clave = (char *) "food";
	valEstablecidos.opciones[0].valores[0] = (char *)"pizza";
	valEstablecidos.opciones[0].valores[1] = (char *)"burger";
	valEstablecidos.opciones[0].valores[2] = (char *)"pasta";
	valEstablecidos.opciones[1].clave = (char *)"beverage";
	valEstablecidos.opciones[1].valores[0] = (char *)"coke";
	valEstablecidos.opciones[1].valores[1] = (char *)"water";
	valEstablecidos.opciones[1].valores[2] = (char *)"sprite";
	valEstablecidos.opciones[2].clave = (char *)"size";
	valEstablecidos.opciones[2].valores[0] = (char *)"small";
	valEstablecidos.opciones[2].valores[1] = (char *)"medium";
	valEstablecidos.opciones[2].valores[2] = (char *)"big";
	valEstablecidos.parametros[0] = (char *)"takehome";
	valEstablecidos.parametros[1] = (char *)"forhere";
	valEstablecidos.parametros[2] = (char *)"napkin";


	int quantity;

#ifdef TESTINGON
	// Testing Bench
	// 	

	char * attempts[NUM_TEST][MAX_TEST] = {
		{ (char *)PROGRAMNAME, (char *)"-phone", (char *)"salad" , NULL }, // Inexistent option + value
	{ (char *)PROGRAMNAME, (char *)"shop", NULL }, // Inexistent parameter
	{ (char *)PROGRAMNAME, (char *)"-food", NULL }, // No value for an option
	{ (char *)PROGRAMNAME, (char *)"-", (char *)"pizza" }, //Keyless option
	{ (char *)PROGRAMNAME, (char *)"-", NULL }, //Keyless option without value.
	{ (char *)PROGRAMNAME, (char *)"-food", (char *)"salad" , NULL }, // Unknown value
	{ (char *)PROGRAMNAME, (char *)"-food", (char *)"salad",(char *) "shop" , NULL }, // Option is OK but the parameter does not exist
	{ (char *)PROGRAMNAME,(char *) "-food", (char *)"pasta",(char *) "-beverage", (char *)"water", (char *)"forhere", (char *)"napkin",(char *) "-size", NULL }, //non-value for size option
	{ (char *)PROGRAMNAME, (char *)"-food", (char *)"pasta", (char *)"-beverage", (char *)"water", (char *)"forhere", (char *)"napkin", (char *)"-size",(char *) "big" , NULL }, // Valid input
	{ (char *)PROGRAMNAME, (char *)"-FOOD", (char *)"burger", (char *)"-beverage", (char *)"coke", (char *)"takehome", (char *)"napkin", (char *)"-size", (char *)"small" , NULL }, // Valid input with uppercase
	{ (char *)PROGRAMNAME, (char *)"-food", (char *)"pizza", (char *)"-beverage", (char *)"water", (char *)"forhere", NULL } // Valid input
	};

	int i;
	int j;
	int parameters;

	for (i = 0; i < NUM_TEST; i++)
	{
		parameters = 0;

		for (j = 0; attempts[i][j] != NULL; j++) {
			parameters++; //Esta variable nos permite enviar el número correcto que tendría ARGC.
		}

		quantity = parseCmdLine(parameters, attempts[i], &parseCallback, &valEstablecidos);

		if (quantity > -1)
		{
			printf("Test: %d ; Result: %d ;All data is correct \n", i + 1, quantity);
		}
		else
		{
			printf("Test: %d; One or more inputs are invalid.\n", i + 1);
		}
	}

	getchar();
#endif

#ifndef TESTINGON
	quantity = parseCmdLine(argc, argv, &parseCallback, &valEstablecidos);

	if (quantity > -1)
	{
		printf("All options/parameters are valid. Number of valid options/parameters: %d \n", quantity);
	}
	else
	{
		printf("One or more inputs are invalid.\n");
	}
	getchar();
#endif
	return 0;
}

/***********************************
Función parseCallback
************************************/

int parseCallback(char *key, char *value, void *userData)
{

	userdata_t * data = (userdata_t*)userData; //Esto es redundante, pero visual studio no me dejaba desreferenciarlo bien si no lo hacía.


	int validez = 1; //Respuesta del callback
	char casehandler[MAX_PARAM_SIZE]; //String para trabajar con las mayusculas/minusculas.


	if (key == NULL) // Analizo parámetros
	{

		int i;
		int cerrarBucle = 0;
		for (i = 0; (i < CANTIDAD_PARAMETROS) && (cerrarBucle == 0); i++) //Ciclo el arreglo de parametros para buscar cual coincide
		{
			strcpy_s(casehandler, value);
			if (!(strcmp(strlower(casehandler), data->parametros[i]))) // analizo si el string en el arreglo de parametros es igual al enviado por el parser
			{
				cerrarBucle = 1;  // Paro el ciclado
				validez = 1; //responde que los parametros son validos
			}
			else  //ocurre en el caso que se mande mal un parametro y no se encuentre en aquellos especificados por el usuario
			{
				validez = 0;
			}
		}
	}
	else
	{
		int i, j;
		int cerrarBucle = 0;

		if (strlen(&(key[1])) <= MAX_PARAM_SIZE) {
			strcpy_s(casehandler, &(key[1])); // para no tomar con el strcmp el OPTION_IDENTIFIER
		}

		for (i = 0; (i < CANTIDAD_OPCIONES) && (cerrarBucle == 0); i++) //ciclo el arreglo de opciones hasta hallar la clave igual
		{
			if (!(strcmp(strlower(casehandler), data->opciones[i].clave)))
			{
				for (j = 0; (j < CANTIDAD_VALORES) && (cerrarBucle == 0); j++)// cuando la encuentro analizo posibles valores dentro de esa opcion, en el arreglo de valores
				{
					strcpy_s(casehandler, value);
					if (!strcmp(strlower(casehandler), data->opciones[i].valores[j])) //si se encuentra un valor valido entonces se cierra el loop y se responde un 1
					{
						validez = 1;
						cerrarBucle = 1;
					}
				}
			}
			else  //ocurre en el caso en el que la clave no es valida, o si la clave es valida, pero no su valor
			{
				validez = 0;
			}
		}

	}
	return validez;
}

/***********************************
Función strlwr
************************************/

char* strlower(char str[])
{
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		str[i] = tolower(str[i]);
	}
	return str;
}