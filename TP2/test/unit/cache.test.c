#include "../../lib/cache.h"
#include <string.h>
#include <stdio.h>

int ways;
int blocksize;
int cachesize;
int sets;
int blocks;
Block* cache;

void test_find_set();
void test_find_earliest();

int main(int argc, char* argv[]){

	ways = 4;//atoi(argv[1]);
	cachesize = 4096; //4KB //atoi(argv[2]);
	blocksize = 256; //atoi(argv[3]);
	sets = cachesize/(blocksize*ways);
	blocks = cachesize/blocksize;
	init();

	test_find_set();
	test_find_earliest();

	free_cache();

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
	cache[0].time = 8;
	cache[1].valid = 0;

	cache[1].time = 34;
	cache[1].valid = 1;

	cache[2].time = 9;
	cache[2].valid = 1;
	
	cache[3].time = 16;
	cache[3].valid = 1;

	unsigned int earliest = find_earliest(0);
	if(earliest == 2)
		printf("find_earliest OK\n");
	else
		printf("error en find_earliest\n");
}

