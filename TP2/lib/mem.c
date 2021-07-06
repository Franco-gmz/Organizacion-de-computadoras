#include"mem.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

char mem[MEMSIZE];

void init_mem(){
	memset(mem, 0, MEMSIZE);
}

void write_block_to_mem(int blocknum,char* data){
	memcpy((mem+blocknum*blocksize), data, blocksize);
}

void write_byte_to_mem(int address, char data){
	mem[address] = data;
}

char* read_block_from_mem(int blocknum){
	return (mem+blocknum*blocksize);
}

char read_byte_from_mem(int address){
	return mem[address];
}