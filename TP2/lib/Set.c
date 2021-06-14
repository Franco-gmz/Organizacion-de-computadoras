#include"Block.h"
#include"Set.h"
#include<stdlib.h>

Set* new_set(int blocks, int block_size){

	Set* ptr;
	Set set;

	set.block_number = blocks;
	set.block_size = block_size;
	set.blocks = malloc(blocks);
	for(int i = 0; i<blocks; i++){
		Block* block = new_block(block_size);
		set.blocks[i] = block;
	}
	ptr = &set;
	return ptr;
}

void free_set(Set* set){

	for(int i = 0; i<set->block_number;i++){
		Block* block = (set->blocks)[i];
		free_block(block);
	}

	return;
}

int tag_cmp(Set set, int tag){

	int match = 1;
	if(set.tag == tag) match = 0;
	return match;
}