#ifndef __SET__
#define __SET__

#include"Block.h"

typedef struct{
	
	Block* first;
	Block* last;
}Set;

extern int init_set(Set* set, int ways, int block_size);

extern void free_set(Set* set);

extern void write_block(Set* set,int tag, int block_size,char* data);

extern char* read_block(Set* set, int tag);

#endif