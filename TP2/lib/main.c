#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

#define BLOCKSIZE 8
#define CACHESIZE 64
#define WAYS 2
#define MEMSIZE 64*1024


char memory[MEMSIZE];
Set* cache;

int main() {

	int number_of_sets = CACHESIZE/BLOCKSIZE/WAYS;

	cache = malloc(number_of_sets* sizeof(Set));
	if (cache == NULL)
		return 1;

	for(int i=0; i<number_of_sets; i++) {
		init_set(&cache[i], WAYS, BLOCKSIZE);
	}

}
