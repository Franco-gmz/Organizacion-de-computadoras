#include<stdio.h>
#include"../../lib/Block.h"

int testWRByte(int block_size,char* data){

	Block* block = new_block(block_size);
	int result = 0;
	for(int i = 0; i<block_size; i++){
		write_byte(block,i,data[i]);
	}

	for(int i = 0; i<block_size; i++){
		char* data_read = read_byte(block,i);
		if(*data_read != data[i]) result = -1;
	}
	free_block(block);
	return result;
}

int testWRBlock(int block_size,char* data){

	Block* block = new_block(block_size);
	int result = 0;
	write_block(block,data);
	char* read_data = read_block(block);
	if(read_data == data) result = -1;
	free_block(block);
	return result;
}

int main(){


	char data[6] = {'B','l','o','q','u','e'};

	if(testWRByte(6,data) == -1) printf("\nTest Write/Read byte : Fail\n");
	else printf("\n Test Write/Read byte : OK\n");

	if(testWRBlock(6,data) == -1) printf("\nTest Write/Read block : Fail\n");
	else printf("\n Test Write/Read block : OK\n");

	return 0;
}