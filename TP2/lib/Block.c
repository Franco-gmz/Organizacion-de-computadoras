#include"Block.h"
#include<stdlib.h>

Block* new_block(int size){
	
	Block* block = malloc(sizeof(Block));
	if(block == NULL)
		return NULL;
	block->size = size;
	block->tag = 0;
	block->valid = 0;
	block->data = (char*) malloc(size);
	block->next = NULL;

	return block;
}

void free_block(Block* block){

	free(block);
	return;
}
