#ifndef __SET__
#define __SET__

#include"Block.h"

typedef struct{
	
	int block_number;
	int block_size;
	Block** blocks;
	int tag;

}Set;

extern Set* new_set(int blocks, int block_size);

extern void free_set(Set* set);

#endif