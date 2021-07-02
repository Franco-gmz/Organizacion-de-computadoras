#include "cache.h"
#include "mem.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init(){
	
	cache = malloc(blocks*sizeof(Block));

	for(int i = 0; i<blocks; i++){
		init_block(cache+i,blocksize);
	}
	return;
}

void free_cache(){
	for(int i = 0; i<blocks; i++){
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

	for(; i<ways; i++) {	
		if(set[i].valid == 0) {		// Si hay uno no valido devolvemos ese
			return i;				

		}	
		if(set[i].valid == 1) {		// Encontramos el primer valido
			min = i;
			break;
		}
				
	}	
	for(; i<ways; i++) {
		if(set[i].valid == 0) {		// Si hay uno no valido devolvemos ese
			return i;				
		}									
		if(set[i].valid == 1 && set[i].time < set[min].time) {
			min = i;				// Vemos si hay uno con menor tiempo
		}
		
	}
	return min;	
}

void read_block(int blocknum) {
	char* block_data = read_block_from_mem(blocknum);
	unsigned int block_address = blocknum*blocksize;
	unsigned int setnum = find_set(block_address);
	unsigned int earliest = find_earliest(setnum);
	unsigned int cache_blocknum = setnum*ways+earliest;

	memcpy(cache[cache_blocknum].data, block_data, blocksize);
	cache[cache_blocknum].valid = 1;
	cache[cache_blocknum].time = time;
	// FALTA ACTUALIZAR TAG
}

void write_byte_tomem(int address, char value) {

	write_byte_to_mem(address, &value);
}

