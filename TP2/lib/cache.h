#ifndef __CACHE__
#define __CACHE__

extern int cachesize;
extern int blocksize;
extern int ways;
extern int sets; //cachesize/(blocksize*ways)
extern int blocks;

/* Reserva memoria para la cache e inicializa los bloques 
de cache como invalidos */
void init();

/* Devuelve el conjunto de cache al que mapea la direccion address */
unsigned int find_set(int address);

/* Devuelve el bloque mas antiguo dentro de un conjunto */
unsigned int find_earliest(int setnum);

/* Lee el bloque blocknum de memoria y lo guarda en la memoria cache */
void read_block(int blocknum);

/* Escribe el valor value en la memoria principal */
void write_byte_tomem(int address, char value);

/* Retorna el valor correspondiente a la posicion de memoria address,
buscandolo primero en el cache. Escribe 1 en *hit en caso de hit, y 0
en caso de miss */
char read_byte(int address, char *hit);

/* Escribe el valor value en la posicion correcta del bloque que corresponde
a address, si esta en el cache, y en la memoria en todos los casos,
y devuelve 1 si es un hit y 0 si es un miss */
char write_byte(int address, char value);

/* Devuelve el porcentaje de misses desde que se inicializo el cache */
char get_miss_rate();

/* Libera la memoria asociada al cache */
void free_cache();

#endif