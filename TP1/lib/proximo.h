#ifndef _PROXIMO_
#define _PROXIMO_

/*
Recibe un puntero a la primera posicion de la matriz, la fila y la columna del elemento (i, j)
cuyos vecinos queremos calcular, la regla y la cantidad de filas y columnas de la matriz.
Devuelve el estado del elemento (i+1, j).
*/
unsigned char proximo(unsigned char*,unsigned int,unsigned int,unsigned char,unsigned int);

#endif
