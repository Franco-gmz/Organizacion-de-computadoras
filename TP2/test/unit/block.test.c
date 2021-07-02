#include<stdio.h>
#include<string.h>
#include"../../lib/Block.h"

int testWRByte(int block_size,char* data){
	printf("\nTEST:testWRByte");
	printf("\nCreando bloque de tamaño %dB...\n",block_size);
	Block block;
	init_block(&block, block_size); 
	int result = 0;
	for(int i = 0; i<block_size; i++){
		printf("\tEscribiendo byte#%d...\n",i+1);
		block.data[i] = data[i];
	}

	for(int i = 0; i<block_size; i++){
		char data_read = block.data[i];
		if(data_read != data[i]){
			printf("\tLectura del byte#%d incorrecta",i+1);
			result = -1;
		}
		else printf("\tLectura del byte#%d correcta\n",i+1);
	}
	printf("\nLiberando bloque...\n");
	free_block(&block);
	if(result == 0) printf("Resultado: OK\n");
	else printf("Resultado: Fallo\n");
	return result;
}

int testWRBlock(int block_size,char* data){
	printf("\nTEST:testWRBlock");
	printf("\nCreando bloque de tamaño %dB...\n",block_size);
	Block block;
	init_block(&block, block_size); 
	int result = 0;
	printf("Escribiendo bloque...\n");
	memcpy(block.data, data, block_size);
	char* read_data = block.data;
	if(memcmp(read_data, data, block_size) != 0){
		result = -1;
	}
	else printf("Lectura del bloque correcta\n");
	printf("\nLiberando bloque...\n");
	free_block(&block);
	if(result == 0) printf("Resultado: OK\n");
	else printf("Resultado: Fallo\n");
	return result;
}

int main(){


	char data[6] = {'B','l','o','q','u','e'};
	testWRByte(6,data);
	testWRBlock(6,data);
	return 0;
}