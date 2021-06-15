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

	free(block->data);
	free(block);
	return;
}

void write_byte(Block* block, int offset, char data){

	(block->data)[offset] = data;
	block->valid = 1;

	return;
}

char read_byte(Block* block, int offset){

	return (block->data)[offset];
}

char* read_block(Block* block){
	return (block->data);
}

void write_block(Block* block, char* data){

	*(block->data) = *data;
	return;
}