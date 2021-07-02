#include "cache.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void init(){
	
	cache = malloc(blocks*sizeof(Block));

	for(int i = 0; i<sets; i++){
		init_block(cache+i,blocksize);
	}
	return;
}

void free_cache(){
	for(int i = 0; i<sets; i++){
		free_block(cache+i);
	}
	free(cache);
	return;
}

unsigned int find_set(int address) {

	unsigned int offset_bits = ceil(log2(blocksize));
	unsigned int index_bits = ceil(log2(sets));
	unsigned int index_mask = (unsigned int)pow(2, index_bits)-1;

	return ((unsigned int)address >> offset_bits) & index_mask;
}

unsigned int find_earliest(int setnum) {

	Block* set = cache + setnum*ways;
	int min = 0;
	int i = 0;
	for(; i<ways; i++) {			// Encontramos el primer valido
		if(set[i].valid == 1) {
			min = i;
			break;
		}
	}
	for(; i<ways; i++) {			// Vemos si hay uno con menor tiempo
		if(set[i].valid == 1 && set[i].time < set[min].time) {
			min = i;
		}
	}
	return min;	
}

