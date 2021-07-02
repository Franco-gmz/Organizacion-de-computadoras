#include"mem.h"
#include"Block.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

void init_mem(){

	mem = malloc(memsize);
	return;
}

void free_mem(){
	free(mem);
	return;
}

void write_block_to_mem(int blocknum,char* data){
	memcpy((mem+blocknum*blocksize), data, blocksize);
	return;
}

void write_byte_to_mem(int blocknum,int offset, char* data){
	memcpy((mem+blocknum*blocksize)+offset, data, 1);
	return;
}

char* read_block_from_mem(int blocknum){
	return (mem+blocknum*blocksize);
}
