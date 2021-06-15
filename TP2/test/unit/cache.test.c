#include "../../lib/cache.h"
#include <string.h>

int ways;
int blocksize;
int cachesize;
int sets;
Set* cache;


int main(int argc, char* argv[]){

	ways = 4;//atoi(argv[1]);
	cachesize = 4096; //4KB //atoi(argv[2]);
	blocksize = 256; //atoi(argv[3]);
	sets = cachesize/(blocksize*ways);
	init();

	free_cache();

	return 0;
}