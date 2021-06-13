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
	block.valid = 1;
}

char* read_byte(Block block,int byte){

	return &(block.data[byte]);
}

char* read_block(Block block){
	return (block.data);
}