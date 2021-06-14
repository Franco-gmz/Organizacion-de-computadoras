#include"NWSA.h"
#include"Set.h"
#include<stdlib.h>

NWSA* new_NWSA(int sets, int blocks_by_set, int block_size){

	NWSA* ptr;
	NWSA cache;

	cache.set_number = sets;
	cache.blocks_by_set = blocks_by_set;
	cache.block_size = block_size;
	cache.sets = malloc(sets);

	for(int i = 0; i<sets; i++){
		Set* set = new_set(blocks_by_set,block_size);
		cache.sets[i] = set;
	}
	ptr = &cache;
	return ptr;
}

void free_NWSA(NWSA nwsa){

	for(int = 0; i< nwsa.set_number; i++){

		free_set(nwsa->sets[i]);
	}
	return;
}