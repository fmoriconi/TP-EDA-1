#ifndef PARSECMDLINE_H
#define PARSECMDLINE_H
#include "general.h"

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData); //Devuelve el numero de argumentos si todos son validos o -1 si alguno no lo es.

#endif
