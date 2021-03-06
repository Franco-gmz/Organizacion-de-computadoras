#include "../../lib/cache.h"
#include "../../lib/mem.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int ways;
int blocksize;
int cachesize;
int sets;
int blocks;
int memsize; 
Block* cache;
char* mem;
unsigned long long time;
int accesses;
int misses;

void test_find_set();
void test_find_earliest();
void test_read_block();
void test_read_byte();
void test_write_cache_empty();
void test_read_cache_empty();
void test_write_byte();
void load_mem();
void load_cache();
void reset_mr();

int main(int argc, char* argv[]){


	accesses = 0;
	misses = 0;
	ways = 4;
	cachesize = 1024;
	blocksize = 32;
	sets = cachesize/(blocksize*ways);
	blocks = cachesize/blocksize;
	memsize = 4096;
	time = 0;
	printf("\n__________________________________________\n\n");
	printf("Mem. principal:%dB\nMemoria cache %dWSA - %dB - Bloque:%dB\n",memsize,ways,cachesize,blocksize);
	printf("__________________________________________\n\n");
	
	init();
	init_mem();

	test_write_cache_empty();
	test_read_cache_empty();
	test_read_byte();
	test_write_byte();
	test_find_set();
	test_find_earliest();
	test_read_block();

	free_cache();

	return 0;
}

void test_find_set(){
	int error = 0;
	for(int i = 1; i<sets; i++) {
		if(find_set(0xFF00F + 0x10*i) == i){
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
	for(int i=0; i<4*blocksize; i++) {
		write_byte_tomem(i, (char)(i%blocksize));
	}


	/* Copiamos los 4 bloques a cache y verificamos que
	los datos son los mismos */


	unsigned int setnum = find_set(0*blocksize);
	unsigned int earliest = find_earliest(setnum);
	unsigned int cache_blocknum = setnum*ways+earliest;
	read_block(0);
	for(int i=0; i<blocksize; i++) {
		if(cache[cache_blocknum].data[i] != (char)i)
			error = 1;
	}

	setnum = find_set(1*blocksize);
	earliest = find_earliest(setnum);
	cache_blocknum = setnum*ways+earliest;
	read_block(1);
	for(int i=0; i<blocksize; i++) {
		if(cache[cache_blocknum].data[i] != (char)i)
			error = 1;
	}

	setnum = find_set(2*blocksize);
	earliest = find_earliest(setnum);
	cache_blocknum = setnum*ways+earliest;
	read_block(2);
	for(int i=0; i<blocksize; i++) {
		if(cache[cache_blocknum].data[i] != (char)i)
			error = 1;
	}

	setnum = find_set(3*blocksize);
	earliest = find_earliest(setnum);
	cache_blocknum = setnum*ways+earliest;
	read_block(3);
	for(int i=0; i<blocksize; i++) {
		if(cache[cache_blocknum].data[i] != (char)i)
			error = 1;
	}

	if(error == 0)
		printf("read_block OK\n");

	else
		printf("error en read_block\n");
}

void test_read_byte(){
	printf("Test read byte\n");
	load_mem();
	load_cache();
	reset_mr();

	int err = 0;
	char hit = 0;

	int misses_expected = (memsize/blocksize) - sets*ways;
	int accesses_expected = memsize;
	char mr_expected = (char)(misses_expected*100/accesses_expected);

	for(int i=memsize; i>0; i--){
		
		char data = read_byte(i-1,&hit);
		char data_expected = read_byte_from_mem(i-1);
		if(data != data_expected) err++;		
	}

	char mr = get_miss_rate();
	printf("\tAccesos a memoria: %d/%d\n\tMisses: %d/%d\n\tMiss rate: %d/%d\n\t",accesses,accesses_expected,misses,misses_expected,mr, mr_expected);
	printf("Errores lectura/escritura: %d\n\n",err);
}

void load_mem(){
	char value;
	for(int i=0; i<memsize; i++){
		write_byte_tomem(i,(char)i%256);
	}
}

void load_cache(){
	char* hit;
	for(int i=0; i<(memsize/blocksize);i++){
		read_block(i);
	}
}

void reset_mr(){
	accesses = 0;
	misses = 0;
}

void test_write_byte(){
	printf("Test write byte\n");
	load_mem();
	load_cache();
	reset_mr();

	int err = 0;
	char hit = 0;
	char value = 'Z';

	//No Allocate
	int misses_expected = memsize - sets*ways*blocksize;
	int accesses_expected = memsize;
	char mr_expected = (char)(misses_expected*100/accesses_expected);


	for(int i=memsize; i>0; i--){
		write_byte(i-1,value);
	}

	char mr = get_miss_rate();

	printf("\tAccesos a memoria: %d/%d\n\tMisses: %d/%d\n\tMiss rate: %d/%d\n\t",accesses,accesses_expected,misses,misses_expected,mr, mr_expected);
	printf("Errores lectura/escritura: %d\n\n",err);
}

//Ejecutar con la cache recien inicializada
void test_write_cache_empty(){

	printf("Test write byte in empty cache\n");
	reset_mr(); //Aseguro el correcto conteo

	int misses_expected = memsize;
	int accesses_expected = memsize;
	char mr_expected = (char)(misses_expected*100/accesses_expected);
	for(int i=memsize; i>0; i--){
		write_byte(i-1,(char)i%256);
	}
	char mr = get_miss_rate();
	printf("\tAccesos a memoria: %d/%d\n\tMisses: %d/%d\n\tMiss rate: %d/%d\n\n",accesses,accesses_expected,misses,misses_expected,mr, mr_expected);
	return;
}

/*Ejecutar con la cache recien inicializada y con la memoria principal
inicializada*/
void test_read_cache_empty(){

	printf("Test read byte in empty cache\n");
	reset_mr(); //Aseguro el correcto conteo

	int accesses_expected = memsize;
	int misses_expected = (memsize/blocksize);
	char mr_expected = (char)(misses_expected*100/accesses_expected);
	char hit = 0;

	for(int i=0; i<memsize; i++){
		char data = read_byte(i,&hit);	
	}
	char mr = get_miss_rate();
	printf("\tAccesos a memoria: %d/%d\n\tMisses: %d/%d\n\tMiss rate: %d/%d\n\n",accesses,accesses_expected,misses,misses_expected,mr, mr_expected);
	return;

}