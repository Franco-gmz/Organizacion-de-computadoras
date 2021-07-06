#ifndef __BLOCK__
#define __BLOCK__

typedef struct block Block;
struct block{
	
	int tag;
	int valid;
	unsigned long long time;
	char* data;
};

/* Inicializa un bloque de cache de tamaño size, reservando
memoria para los datos y configurando la metadata*/
extern void init_block(Block* block, int size);

/* Libera la memoria reservada para los datos del bloque */
extern void free_block(Block* block);

#endif