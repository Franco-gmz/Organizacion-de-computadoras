#include"Block.h"
#include"Set.h"
#include<stdlib.h>

Set new_set(int blocks, int block_size){

	int size = (2*sizeof(int)+block_size);

	Set set;
	set.blocks = malloc(size*blocks);
	for(int i = 0; i<blocks; i++){
		Block block = new_block(block_size);
		set.blocks[i] = block;
	}

	return set;
}

void free_set(Set set){

	for(int i = 0; i<set.block_number;i++){
		Block block = set.blocks[i];
		free_block(block);
	}

	return;
}