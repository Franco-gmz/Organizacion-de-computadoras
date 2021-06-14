#include"Block.h"
#include<stdlib.h>

Block* new_block(int size){
	
	Block* ptr;
	Block block;

	block.size = size;
	block.valid = 0;
	block.data = (char*) malloc(size);
	ptr = &block;
	return ptr;
}

void free_block(Block* block){

	free(block->data);
	return;
}

void write_byte(Block* block,int byte, char data){

	(block->data)[byte] = data;
	block->valid = 1;

	return;
}

char* read_byte(Block* block,int byte){

	return &((block->data)[byte]);
}

char* read_block(Block* block){
	return (block->data);
}

void write_block(Block* block,char* data){

	*(block->data) = *data;
	return;
}