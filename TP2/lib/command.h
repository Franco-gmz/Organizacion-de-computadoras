#ifndef __COMMAND__
#define __COMMAND__

#include <stdio.h>

/* Recibe un comando cmd y lo ejecuta, escribiendo
en output_file la salida del comando si es necesario */
int execute_command(char* cmd, FILE* output_file);


#endif