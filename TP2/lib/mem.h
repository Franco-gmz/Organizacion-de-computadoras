#ifndef __MEM__
#define __MEM__

#include "Block.h"

extern char* mem;
extern int blocksize;
extern int memsize;

void init_mem();
void free_mem();
char* read_block_from_mem(int blocknum);
void write_block_to_mem(int blocknum,char* data);
void write_byte_to_mem(int blocknum,int offset, char* data);


#endif