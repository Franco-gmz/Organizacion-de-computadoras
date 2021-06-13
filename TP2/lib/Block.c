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
