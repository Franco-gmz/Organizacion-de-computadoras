#ifndef _TOOLS_
#define _TOOLS_

/*
(DEBUG) Imprime el contenido de cells en forma de matriz n*n
*/
void print_cells(unsigned char* cells,unsigned int n);

/*
Reserva en memoria dinamica un arreglo de n*n y devuelve un puntero
a la primera posicion del arreglo.
*/
unsigned char* create_cells(unsigned int n);

/*
Lee el estado inicial de las celdas del archivo input_file, y las guarda
en la primera fila de output_cells.
Devuelve 0 en caso de exito, y 1 en caso de error.
*/
int read_initial_state(FILE* input_file, unsigned char* output_cells, unsigned int n);

/*
Calcula todos los estados siguientes a partir de las celdas de la primera fila
de output_cells, siguiendo la regla rule.
*/
void compute_states(unsigned char* output_cells, unsigned char rule, unsigned int n);

/*
Escribe el contenido de la matriz cells en el archivo output_file,
en formato PBM.
*/
void write_pbm_file(FILE* output_file, unsigned char* cells, unsigned int n);


#endif
