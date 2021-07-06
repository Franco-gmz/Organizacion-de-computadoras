#include "cache.h"
#include "mem.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int accesses;
int misses;
Block* cache;
unsigned long long time;


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

void count_access(){
	accesses++;
	return;
}

void count_miss(){
	misses++;
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

int find_tag(int address){
	unsigned int offset_bits = ceil(log2(blocksize));
	unsigned int index_bits = ceil(log2(sets));
	int tag = (int)( (unsigned int)address >> (offset_bits+index_bits) );
	return tag;
}

void read_block(int blocknum) {
	char* block_data = read_block_from_mem(blocknum);
	unsigned int block_address = blocknum*blocksize;
	unsigned int setnum = find_set(block_address);
	unsigned int earliest = find_earliest(setnum);
	unsigned int cache_blocknum = setnum*ways+earliest;

	memcpy(cache[cache_blocknum].data, block_data, blocksize);
	cache[cache_blocknum].valid = 1;
	cache[cache_blocknum].time = ++time;
	cache[cache_blocknum].tag = find_tag(block_address);
	return;
}

void write_byte_tomem(int address, char value) {

	write_byte_to_mem(address, value);
}

/////////////////////////////////////////////////////////////////

int find_offset(int address){
	int offset_bits = ceil(log2(blocksize));
	int offset_mask = pow(2, offset_bits)-1;
	return (address & offset_mask);
}


char* find_by_tag(int setnum, int tag){
	Block* set = cache + setnum*ways;
	char* data = NULL;
	for(int i=0;i<ways;i++){
		if( (set+i)->valid == 1 && (set+i)->tag == tag ) data = (set+i)->data;
	}
	return data;
}

int address_to_blocknum(int address){
	unsigned int offset_bits = ceil(log2(blocksize));
	int blocknum = (int) ( (unsigned int)address >> offset_bits);
	return blocknum;
}

/*
Debe retornar el valor correspondiente a la posición de memoria address, 
buscándolo primero en el caché, y escribir 1 en *hit si es un hit y 0 si es un miss.
*/
char read_byte(int address, char *hit){
	count_access();
	int setnum = (int) find_set(address);
	int offset = find_offset(address);
	int tag = find_tag(address);
	char* data = find_by_tag(setnum,tag);
	//miss
	if(data == NULL){
		count_miss();
		*hit = 0;
		int blocknum = address_to_blocknum(address);
		read_block(blocknum);//lo guarda en cache
		data = find_by_tag(setnum,tag);
	}
	else *hit = 1;
	//No deberia nunca ser data NULL
	return data[offset];
}

char write_byte(int address, char value){
	count_access();
	char hit = 0;
	int tag = find_tag(address);
	int setnum = find_set(address);
	int offset = find_offset(address);

	Block* set = (cache + setnum*ways);
	for(int i=0; i<ways; i++){
		if( (set+i)->valid == 1 && (set+i)->tag == tag ){
			(set+i)->data[offset] = value;
			hit = 1;
		}
	}
	if(hit == 0) count_miss();
	write_byte_tomem(address,value);
	return hit;
}

char get_miss_rate(){
	if(accesses == 0)
		return 0;
	return (char)(misses*100/accesses); //me lo redondea a 0
}