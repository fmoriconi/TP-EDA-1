#ifndef GENERAL_H
#define GENERAL_H

#define PROGRAMNAME "parseprog"
#define NUM_TEST 9
#define MAX_TEST 10
#define CANTIDAD_OPCIONES 3
#define CANTIDAD_VALORES 3
#define CANTIDAD_PARAMETROS 3
#define SIZE_VALORES 15
#define MAX_TEST_PARAM 8
#define MAX_PARAM_SIZE 16 //Es el tamaño máximo de caracteres un parámetro. Es 16 para dejar un margen razonable.

#define TESTINGON //Define para el banco de pruebas

#include<string.h>

typedef int(*pCallback) (char * key, char * value, void * userdata);

int parseCallback(char *key, char *value, void *userData); 
/*  Esta funcion recibe 3 parametros, key y value corresponden a los strings a analizar,
	y userData es un pasaje por referencia de una estructura en la cual se encuentran las posibles opciones y parametros validos.
	La funcion trabaja comparando los strings recibidos con aquellos encontrados en la estructura.
	Devuelve 1 si la interpretación es correcta y 0 si no lo es.
*/

char* strlwr(char str[]); //tranforma un string a lowercase
/*  
	Tranforma un string a lowercase, recibe un arreeglo de char
*/


/**********************
*	Estructura Option
	Consiste en un arreglo de char en el cual entrara la clave.
	Luego un arreglo de punteros a char, que estos seran los posibles valores para esta clave.
	Estos valores deben asignarse antes de compilar
***********************/
typedef struct {
	char * clave;
	char * valores[CANTIDAD_VALORES]; //En caso de que haya opciones con cantidad de valores distinta, llenarla con algo invalido asi la copmaracion no se cumple
} option_t;
/*********************
*	Estructura userdata
	Contiene un arreglo de option_t dentro de donde iran todas las posibles opciones (con sus claves y valores correspondientes).
	Tambien contiene un arreglo de punteros a char, que seran los punteros a los strings para los parametros.
**********************/
typedef struct {
	option_t opciones[CANTIDAD_OPCIONES];
	
	char *parametros[CANTIDAD_PARAMETROS]; // Los creo como punteros a char, ya que asumo que los strings se van a guardar en ROM
} userdata_t;

/*********************
*	Typedef para puntero a función
**********************/
typedef int(*pCallback) (char * key, char * value, void * userdata);


#endif