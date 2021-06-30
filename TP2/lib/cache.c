#include "cache.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void init(){
	
	cache = malloc(sets*sizeof(Set));

	for(int i = 0; i<sets; i++){
		init_set(cache+i,ways,blocksize);
	}
	return;
}

void free_cache(){
	for(int i = 0; i<sets; i++){
		free_set(cache+i);
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