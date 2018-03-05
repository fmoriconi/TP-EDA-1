#include <stdio.h>

#define PROGRAMNAME "parseprog"
#define NUM_TESTS 9
#define MAX_TEST 10
#define CANTIDAD_OPCIONES 3
#define CANTIDAD_VALORES 3
#define CANTIDAD_PARAMETROS 3
#define TAMAÑO_VALORES 15

int parseCallback(char *key, char *value, void *userData); //Devuelve 1 si la interpretación es correcta y 0 si no lo es.
char* strlwr(char str[]); //tranforma un string a lowercase



//Parametros takehome, forhere, napkin
//Opciones food: pizza, burger, pasta // beverage: coke, water,sprite // size: small, medium, big

/**********************
*	Estructura Option
	Consiste en un arreglo de char en el cual entrara la clave.
	Luego un arreglo de punteros a char, que estos seran los posibles valores para esta clave.
	Estos valores deben asignarse antes de compilar
***********************/
typedef struct {
	char clave[10];
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

int main (void)
{
	// Testing Bench
	// 
	userdata_t valEstablecidos = { {"food"} {"pizza"} {"burguer"} {"pasta"} {"beverage"} {"coke"} {"water"} {"sprite"} {"size"} {"small"} {"medium"} {"big"} {"takehome"} {"forhere"} {"napkin"} }
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
	int quantity;
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
/***********************************
	Funcion parseCallback
************************************/
/*  Esta funcion recibe 3 parametros, key y value corrsponden a los strings a analizar,
	y userData es un pasaje por referencia de una estructura en la cual se encuentran las posibles opciones y parametros validos.
	La funcion trabaja comparando los strings recibidos con aquellos encontrados en la estructura.
*/
int parseCallback(char *key, char *value, void *userData) {

	userdata_t * data = (userdata_t*)userData; //Esto es medio redundante, lo sé, pero visual studio no me dejaba desreferenciarlo bien si no lo hacía. (creo que esta bien por que hay que castear el puntero ese que es void, hay que decirle que es la estructura que creamos)
	int validez; //Respuesta del callback
	if (key == NULL) // Analizo parametros
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
		for (i = 0; (i < CANTIDAD_OPCIONES) && (cerrarBucle == 0); i++) //ciclo el arreglo de opciones hasta hayar la clave igual
		{
			if (!(strcmp(strlwr(key), data->opciones[i].clave)))
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
