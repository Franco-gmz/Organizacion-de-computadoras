#include<stdio.h>
#include"../../lib/Block.h"

int main(){


	int size = 6;
	char data[6] = {'B','l','o','q','u','e'};
	Block block = new_block(size);

	for(int i = 0; i<size; i++){
		write_byte(block,i,data[i]);
	}
	
	printf("\n\nLectura byte a byte\n");
	for(int i = 0; i<size; i++){
		char* data_read = read_byte(block,i);
		printf("\t%c",*data_read);
	}
	printf("\n\n");
	free_block(block);
	return 0;
}