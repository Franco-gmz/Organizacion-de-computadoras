#include"Block.h"
#include<stdlib.h>

void init_block(Block* block, int size){
	
	block->tag = 0;
	block->valid = 0;
	block->time = 0;
	block->data = (char*) malloc(size);
}

void free_block(Block* block){

	free(block->data);
}
