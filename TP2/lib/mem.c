#include"mem.h"
#include"Block.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

void init_mem(){

	mem = calloc(memsize, 1);
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

void write_byte_to_mem(int address, char* data){
	memcpy(mem+address, data, 1);
	return;
}

char* read_block_from_mem(int blocknum){
	return (mem+blocknum*blocksize);
}

char read_byte_from_mem(int address){
	return mem[address];
}