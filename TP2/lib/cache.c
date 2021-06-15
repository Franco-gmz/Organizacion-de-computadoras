#include "cache.h"
#include <stdlib.h>

//implementar primitivas

void init(){
	
	cache = malloc(sets*sizeof(Set));

	for(int i = 0; i<sets; i++){
		init_set(cache+i*sizeof(Set),ways,blocksize);
	}
	return;
}

void free_cache(){
	for(int i = 0; i<sets; i++){
		free_set(cache+i*sizeof(Set));
	}
	return;
}