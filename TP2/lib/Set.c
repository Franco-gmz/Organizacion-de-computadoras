#include"Block.h"
#include"Set.h"
#include<stdlib.h>

int init_set(Set* set, int ways, int block_size){

	set->first = NULL;
	set->last = NULL;
	for(int i=0; i<ways; i++) {
		Block* block = new_block(block_size);
		if(block == NULL) {
			free_set(set);
			return 1;
		}
		if (i == 0) 
			set->last = block;
		block->next = set->first;
		set->first = block;
	}
	
	return 0;
}

void move_first_to_last(Set* set) {

	if(set == NULL || set->first_next == NULL)
		return;

	Block* block = Set->first;

	Set->first = block->next;
	block->next = NULL;
	Set->last->next = block;
	Set->last = block;
}

Block* find_block(Set* set, int tag) {

	if(set == NULL)
		return NULL;

	Block* current = Set->first;
	while(current != NULL) {
		if(current->valid != 0 && current->tag == tag)
			return current; //hit
	}

	return NULL; //miss
}



void free_set(Set* set){

	while(set->first != NULL) {
		Block* next = set->first->next;
		free_block(set->first);
		set->first = next;
	}
}
