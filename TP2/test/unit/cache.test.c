#include "../../lib/cache.h"
#include <string.h>
#include <stdio.h>

int ways;
int blocksize;
int cachesize;
int sets;
Set* cache;

void test_find_set();

int main(int argc, char* argv[]){

	ways = 4;//atoi(argv[1]);
	cachesize = 4096; //4KB //atoi(argv[2]);
	blocksize = 256; //atoi(argv[3]);
	sets = cachesize/(blocksize*ways);
	init();

	test_find_set();

	free_cache();

	return 0;
}

void test_find_set(){
	int error = 0;
	for(int i = 0; i<8; i++) {
		if(find_set(0xFF0FF + 0x100*i) != i%4){
			printf("error = %d, %d\n", i, i%4);
			error = 1;
		}
	}
	if(error == 1)
		printf("error en find_set\n");
	else
		printf("find_set OK\n");
}