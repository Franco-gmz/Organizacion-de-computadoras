#include "../../lib/cache.h"
#include "../../lib/mem.h"

#include <string.h>
#include <stdio.h>

int ways;
int blocksize;
int cachesize;
int sets;
int blocks;
int memsize; 
Block* cache;
char* mem;
unsigned long long time;

void test_find_set();
void test_find_earliest();
void test_read_block();

int main(int argc, char* argv[]){

	ways = 4;//atoi(argv[1]);
	cachesize = 4096; //4KB //atoi(argv[2]);
	blocksize = 256; //atoi(argv[3]);
	sets = cachesize/(blocksize*ways);
	blocks = cachesize/blocksize;
	memsize = 1024;
	time = 0;
	init();
	init_mem();

	test_find_set();
	test_find_earliest();
	test_read_block();

	free_cache();
	free_mem();

	return 0;
}

void test_find_set(){
	int error = 0;
	for(int i = 0; i<8; i++) {
		if(find_set(0xFF0FF + 0x100*i) != i%4){
			error = 1;
		}
	}
	if(error == 1)
		printf("error en find_set\n");
	else
		printf("find_set OK\n");
}

void test_find_earliest() {
	int error = 0;

	cache[0].time = 8;
	cache[0].valid = 1;

	cache[1].time = 34;
	cache[1].valid = 1;

	cache[2].time = 7;
	cache[2].valid = 1;
	
	cache[3].time = 16;
	cache[3].valid = 1;

	unsigned int earliest = find_earliest(0);
	if(earliest != 2)
		error = 1;
	
	cache[1].valid = 0;
	earliest = find_earliest(0);
	if(earliest != 1)
		error = 1;

	if(error == 0)
		printf("find_earliest OK\n");
	else
		printf("error en find_earliest %d\n", error);
}

void test_read_block() {

	int error = 0;

	/* Escribimos valores en los primeros 4 bloques de memoria*/
	for(int i=0; i<1024; i++) {
		write_byte_tomem(i, (char)(i%256));
	}


	/* Copiamos los 4 bloques a cache y verificamos que
	los datos son los mismos */


	unsigned int setnum = find_set(0*blocksize);
	unsigned int earliest = find_earliest(setnum);
	unsigned int cache_blocknum = setnum*ways+earliest;
	read_block(0);
	for(int i=0; i<256; i++) {
		if(cache[cache_blocknum].data[i] != (char)i)
			error = 1;
	}

	setnum = find_set(1*blocksize);
	earliest = find_earliest(setnum);
	cache_blocknum = setnum*ways+earliest;
	read_block(1);
	for(int i=0; i<256; i++) {
		if(cache[cache_blocknum].data[i] != (char)i)
			error = 1;
	}

	setnum = find_set(2*blocksize);
	earliest = find_earliest(setnum);
	cache_blocknum = setnum*ways+earliest;
	read_block(2);
	for(int i=0; i<256; i++) {
		if(cache[cache_blocknum].data[i] != (char)i)
			error = 1;
	}

	setnum = find_set(3*blocksize);
	earliest = find_earliest(setnum);
	cache_blocknum = setnum*ways+earliest;
	read_block(3);
	for(int i=0; i<256; i++) {
		if(cache[cache_blocknum].data[i] != (char)i)
			error = 1;
	}

	if(error == 0)
		printf("read_block OK\n");

	else
		printf("error en read_block\n");
}