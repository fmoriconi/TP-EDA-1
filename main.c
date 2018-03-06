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

#include <stdio.h>
#include <string.h>
#include "parseCmdLine.h"
#include "general.h"

int main (int argc, char * argv[])
{
	userdata_t valEstablecidos;

	//Parametros takehome, forhere, napkin
	//Opciones food: pizza, burger, pasta // beverage: coke, water,sprite // size: small, medium, big
	
	strcpy(valEstablecidos.opciones[0].clave, "food");
	strcpy(valEstablecidos.opciones[0].valores[0], "pizza");
	strcpy(valEstablecidos.opciones[0].valores[1], "burguer");
	strcpy(valEstablecidos.opciones[0].valores[2], "pasta");
	strcpy(valEstablecidos.opciones[1].clave, "beverage");
	strcpy(valEstablecidos.opciones[1].valores[0], "coke");
	strcpy(valEstablecidos.opciones[1].valores[1], "water");
	strcpy(valEstablecidos.opciones[1].valores[2], "sprite");
	strcpy(valEstablecidos.opciones[2].clave, "size");
	strcpy(valEstablecidos.opciones[2].valores[0], "small");
	strcpy(valEstablecidos.opciones[2].valores[1], "medium");
	strcpy(valEstablecidos.opciones[2].valores[2], "big");
	strcpy(valEstablecidos.parametros[0], "takehome");
	strcpy(valEstablecidos.parametros[1], "forhere");
	strcpy(valEstablecidos.parametros[2], "napkin");

	// Testing Bench
	// 	
	
	char * attempts[NUM_TESTS][MAX_TEST]= {{PROGRAMNAME, "-clothes", "trouser" , NULL }, // unexist option and value
						 {PROGRAMNAME, "shop", NULL }, // unexist parameter
						 {PROGRAMNAME, "-food", NULL }, // non-value for the option
						 {PROGRAMNAME, "-food", "salad" , NULL }, // unknown value
						 {PROGRAMNAME, "-food", "salad", "shop" , NULL }, // option is well but the parameter does not exist
						 {PROGRAMNAME, "-food", "pasta", "-beverage", "water", "forhere", "napkin", "-size", NULL }, //non-value for size option
						 {PROGRAMNAME, "-food", "pasta", "-beverage", "water", "forhere", "napkin", "-size", "big" , NULL }, // good try
						 {PROGRAMNAME, "-Food", "Burger", "-beverage", "coke", "takehome", "napkin", "-size", "small" , NULL }, // good try with uppercase
						 {PROGRAMNAME, "-food", "pizza", "-beverage", "water", "forhere", NULL } // good try
						};
	int i;
	int quantity;
    for (i = 0; i < NUM_TESTS; i++)
	{
		quantity = parseCmdLine(NUM_TEST, attempts ,&parseCallback, &valEstablecidos);
		
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

/***********************************
	Función parseCallback
************************************/

int parseCallback(char *key, char *value, void *userData)
{

	userdata_t * data = (userdata_t*)userData; //Esto es medio redundante, pero visual studio no me dejaba desreferenciarlo bien si no lo hacía. (creo que esta bien por que hay que castear el puntero ese que es void, hay que decirle que es la estructura que creamos)
	int validez; //Respuesta del callback
	if (key == NULL) // Analizo parámetros
	{
		int i;
		int cerrarBucle = 0;
		for (i = 0; (i < CANTIDAD_PARAMETROS)&&(cerrarBucle == 0); i++) //Ciclo el arreglo de parametros para buscar cual coincide
		{
			if(!(strcmp(strlwr(value), data->parametros[i]))) // analizo si el string en el arreglo de parametros es igual al enviado por el parser
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
		int cerrarBucle;
		char * optionkey = &(key[1]); // para no tomar con el strcmp el OPTION_IDENTIFIER
		for (i = 0; (i < CANTIDAD_OPCIONES) && (cerrarBucle == 0); i++) //ciclo el arreglo de opciones hasta hayar la clave igual
		{
			if (!(strcmp(strlwr(optionkey), data->opciones[i].clave)))
			{
				for (j = 0; (j < CANTIDAD_VALORES) && (cerrarBucle == 0);j++)// cuando la encuentro analizo posibles valores dentro de esa opcion, en el arreglo de valores
				{
					if (!strcmp(strlwr(value), data->opciones[i].valores[j])) //si se encuentra un valor valido entonces se cierra el loop y se responde un 1
					{
						    validez =1;
							cerrarBucle =1;
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

char* strlwr(char str[])
{ 
      int i = 0; 

      while(str[i] != '\0') 
      { 
                   if(str[i] >= 'A' && str[i] <= 'Z') 
                   str[i] = str[i] + ('a' - 'A'); 
                   i++; 
      }
      return str;
} 
