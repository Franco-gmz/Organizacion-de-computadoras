#include"Block.h"

typedef struct{
	
	int block_number;
	int block_size;
	Block* blocks;

}Set;

extern Set new_set(int blocks, int block_size);

extern void free_set(Set set);