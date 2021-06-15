#ifndef __SET__
#define __SET__

#include"Block.h"

typedef struct{
	
	Block* first;
	Block* last;
}Set;

extern int init_set(Set* set, int ways, int block_size);

extern void free_set(Set* set);

#endif