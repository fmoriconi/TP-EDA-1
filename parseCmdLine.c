#include <stdio.h>
#include <stdbool.h>
#include "parseCmdLine.h"

int parseCmdLine(int argc, char *argv[], pCallback parseCallback, void *userData)
{
    int vacounter = 0; // "Valid argument counter"
    bool abort = false;
    
    
    for (int i = 1; i < argc && abort != true; i++)
    {
        if (*argv[i] == '-')
        {
            if ((i != argc-1) && (parseCallback(argv[i], argv[i+1], userData) == 1))
            {
                vacounter++;
            }
            else
            {
                if(i == argc-1) //Si el ultimo argumento es una opción, no tiene clave.
                {
                    printf("Error type 1: Option without value\n");
                    if(strlen(argv[i]) == 1) //Si la opción tiene un solo caracter, no tiene clave.
                    {
                        printf("Error type 2: Option without key\n");
                    }
                }
                else if(strlen(argv[i]) == 1) //Si la opción tiene un solo caracter, no tiene clave.
                {
                    printf("Error type 2: Option without key\n");
                }
                else //Si no es uno de esos errores, la clave y/o el valor son incorrectos.
                {
                    printf("Invalid option\n");
                }
                abort = true;
            }
            i++; //Incremento i pues el siguiente elemento obligatoriamente es un valor y debo saltearlo.
        }
        else
        {
            //    printf("Llego hasta aca, %s \n", argv[i]);
            if (parseCallback(NULL, argv[i], userData) == 1)
            {
                vacounter++;
            }
            else
            {
                printf("Error: Invalid parameter.\n");
                abort = true;
            }
        }
        
        
    }
    
    if (abort == true) {
        vacounter = -1;
    }
    
    return vacounter;
}