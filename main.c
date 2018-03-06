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
#include "parseCmdLine.h"
#include "general.h"


int main (int argc, char * argv[])
{
    userdata_t valEstablecidos;
    
    //Parametros takehome, forhere, napkin
    //Opciones food: pizza, burger, pasta // beverage: coke, water,sprite // size: small, medium, big
    
    
    valEstablecidos.opciones[0].clave = "food";
    valEstablecidos.opciones[0].valores[0] = "pizza";
    valEstablecidos.opciones[0].valores[1] = "burger";
    valEstablecidos.opciones[0].valores[2] = "pasta";
    valEstablecidos.opciones[1].clave = "beverage";
    valEstablecidos.opciones[1].valores[0] = "coke";
    valEstablecidos.opciones[1].valores[1] = "water";
    valEstablecidos.opciones[1].valores[2] = "sprite";
    valEstablecidos.opciones[2].clave = "size";
    valEstablecidos.opciones[2].valores[0] = "small";
    valEstablecidos.opciones[2].valores[1] = "medium";
    valEstablecidos.opciones[2].valores[2] = "big";
    valEstablecidos.parametros[0] = "takehome";
    valEstablecidos.parametros[1] = "forhere";
    valEstablecidos.parametros[2] = "napkin";
    
    
    int quantity;        
    
#ifdef TESTINGON
    // Testing Bench
    // 	
    
    char * attempts[NUM_TEST][MAX_TEST]= {
    {PROGRAMNAME, "-phone", "salad" , NULL }, // Inexistent option + value
    {PROGRAMNAME, "shop", NULL }, // Inexistent parameter
    {PROGRAMNAME, "-food", NULL }, // No value for an option
    {PROGRAMNAME, "-", "pizza"}, //Keyless option
    {PROGRAMNAME, "-", NULL}, //Keyless option without value.
    {PROGRAMNAME, "-food", "salad" , NULL }, // Unknown value
    {PROGRAMNAME, "-food", "salad", "shop" , NULL }, // Option is OK but the parameter does not exist
    {PROGRAMNAME, "-food", "pasta", "-beverage", "water", "forhere", "napkin", "-size", NULL }, //non-value for size option
    {PROGRAMNAME, "-food", "pasta", "-beverage", "water", "forhere", "napkin", "-size", "big" , NULL }, // Valid input
    {PROGRAMNAME, "-FOOD", "burger", "-beverage", "coke", "takehome", "napkin", "-size", "small" , NULL }, // Valid input with uppercase
    {PROGRAMNAME, "-food", "pizza", "-beverage", "water", "forhere", NULL } // Valid input
    };
    
    int i;
    int j;
    int parameters;
    
    for (i = 0; i < NUM_TEST; i++)
    {
        parameters = 0;
        
        for(j = 0; attempts[i][j] !=  NULL; j++){
            parameters++; //Esta variable nos permite enviar el número correcto que tendría ARGC.
        }
        
        quantity = parseCmdLine(parameters, attempts[i] ,&parseCallback, &valEstablecidos);
        
        if(quantity > -1)
        {
            printf("Test: %d ; Result: %d ;All data is correct \n", i+1, quantity);
        }
        else
        {
            printf("Test: %d; One or more inputs are invalid.\n", i+1);
        }
    }
#endif
    
#ifndef TESTINGON
    quantity = parseCmdLine(argc, argv,&parseCallback, &valEstablecidos);
    
    if(quantity > -1)
    {
        printf("All options/parameters are valid. Number of valid options/parameters: %d \n", quantity);
    }
    else
    {
        printf("One or more inputs are invalid.\n");
    }
    
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
        for (i = 0; (i < CANTIDAD_PARAMETROS)&&(cerrarBucle == 0); i++) //Ciclo el arreglo de parametros para buscar cual coincide
        {
            strcpy(casehandler,value);
            if(!(strcmp(strlwr(casehandler), data->parametros[i]))) // analizo si el string en el arreglo de parametros es igual al enviado por el parser
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
        
        if(strlen(&(key[1])) <= MAX_PARAM_SIZE){
            strcpy(casehandler,&(key[1])); // para no tomar con el strcmp el OPTION_IDENTIFIER
        }
        
        for (i = 0; (i < CANTIDAD_OPCIONES) && (cerrarBucle == 0); i++) //ciclo el arreglo de opciones hasta hallar la clave igual
        {
            if (!(strcmp(strlwr(casehandler), data->opciones[i].clave)))
            {
                for (j = 0; (j < CANTIDAD_VALORES) && (cerrarBucle == 0);j++)// cuando la encuentro analizo posibles valores dentro de esa opcion, en el arreglo de valores
                {
                    strcpy(casehandler, value);
                    if (!strcmp(strlwr(casehandler), data->opciones[i].valores[j])) //si se encuentra un valor valido entonces se cierra el loop y se responde un 1
                    {
                        validez = 1;
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
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + ('a' - 'A');
        }
        i++; 
    }
    return str;
} 
