#include"Block.h"
#include<stdlib.h>

Block new_block(int size, char* tag){
	
	Block block;

	block.size = size;
	block.tag = tag;
	block.valid = 0;
	block.data = (char*) malloc(size);

	return block;
}

void free_block(Block block){

	free(block.data);
}

void write_byte(Block block,int byte, char data){

	block.data[byte] = data;
}

char* read_byte(Block block,int byte){

	return &(block.data[byte]);
}