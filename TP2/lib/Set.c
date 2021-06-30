#include"Block.h"
#include"Set.h"
#include<stdlib.h>
#include<stdio.h>

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

	if(set == NULL || set->first->next == NULL)
		return;

	Block* block = set->first;

	set->first = block->next;
	block->next = NULL;
	set->last->next = block;
	set->last = block;
	return;
}

Block* find_block(Set* set, int tag) {

	if(set == NULL)
		return NULL;

	Block* current = set->first;
	while(current != NULL) {
		if(current->valid != 0 && current->tag == tag)
			return current; //hit
		current = current->next;
	}

	return NULL; //miss
}

void write_block(Set* set, int tag, int block_size, char* data){
	
	Block* block = find_block(set, tag);
	/* Si hay un hit: */
	if(block != NULL) {
		block->data = data;
		return;
	}

	/* Si hay un miss: */
	Block* first = set->first;
	first->tag = tag;
	first->data = data;
	first->valid = 1;
	move_first_to_last(set);
	return;
}

char* read_block(Set* set, int tag){
	Block* block = find_block(set,tag);
	if(block == NULL) {
		return NULL;
	} //miss
	return block->data; //hit
}

void free_set(Set* set){
	
	while(set->first != NULL) {
		Block* next = set->first->next;
		free_block(set->first);
		set->first = next;
	}
}
