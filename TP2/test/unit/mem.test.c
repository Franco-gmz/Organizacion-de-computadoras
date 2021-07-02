#include"../../lib/mem.h"
#include"../../lib/Block.h"
#include<string.h>
#include<stdio.h>

char* mem;
int memsize; 
int blocksize;

int datacmp(char* a, char* b,int len){
	int cmp = 0;
	for(int i=0; i<len; i++){
		if( *(a+i) != *(b+i)) cmp = 1;
	}
	return cmp;
}

void test_WR_blocks(int blocks){
	int errors = 0;
	printf("\nTEST: Escritura/Lectura de bloques de la memoria principal\n");
	char* data = "ABCD";
	printf("Escribiendo memoria...\n");
	for(int i=0; i<blocks; i++){
		write_block_to_mem(i,data);
	}

	printf("Leyendo memoria...\n");
	for(int i=0; i<blocks; i++){
		if(datacmp(read_block_from_mem(i),data,blocksize) != 0) errors = errors + 1;
	}
	printf("Se encontraron %d errores\n\n",errors);

	return;

}

void test_WR_byte(int blocks){

	printf("\nTEST: Escritura/Lectura de bytes de la memoria principal\n");
	char* data = "Z";
	int errors = 0;
	printf("Escribiendo memoria...\n");
	for(int i=0; i<blocks; i++){
		write_byte_to_mem(i,0,data);
	}
	printf("Leyendo memoria...\n");
	for(int i=0; i<blocks; i++){

		if(datacmp(read_block_from_mem(i),data,1) != 0) errors = errors + 1;
	}
	printf("Se encontraron %d errores\n\n",errors);

	return;
}

int main(){

	memsize = 65536; //64KB
	blocksize = 4; //4B
	int blocks = (memsize/blocksize);
	init_mem();
	test_WR_blocks(blocks);
	test_WR_byte(blocks);
	free_mem();
	return 0;

}