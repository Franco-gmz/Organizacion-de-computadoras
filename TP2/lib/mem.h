#ifndef __MEM__
#define __MEM__

#define MEMSIZE 64*1024

extern int blocksize;

/* Inicializa la memoria principal con ceros */
void init_mem();

/* Devuelve un puntero al bloque de memoria blocknum */
char* read_block_from_mem(int blocknum);

/* Carga data en el bloque de memoria blocknum */
void write_block_to_mem(int blocknum,char* data);

/* Escribe el byte data en la direccion de memoria address */
void write_byte_to_mem(int address, char data);

/* Devuelve el byte presente en la direccion de memoria address */
char read_byte_from_mem(int address);

#endif