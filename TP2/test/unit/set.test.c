#include"../../lib/Set.h"
#include<stdio.h>


int compare_data(char* a, char* b, int size){
	for(int i=0; i<size; i++){
		if(a[i] != b[i]) return -1;
	}
	return 0;
}

//blocks: cantidad de bloques en data (solo sirve para el test)
void testWRBlocks(int ways, int block_size, char* data,int blocks){
	int result = 0;
	Set* set;
	printf("\nCreando Conjunto de tamaño %dB\n",ways*block_size);
	init_set(set, ways, block_size);

	for(int i=0; i<blocks;i++){
		//uso el valor de i como tag
		printf("Escribiendo bloque#%d...\n",i+1);
		write_block(set,i,block_size,data+i*block_size);
	}
	int misses_expected = blocks-ways;
	if(ways >= blocks) misses_expected = 0;

	for(int j=0; j<blocks;j++){
		printf("Leyendo bloque#%d...\t",j+1);
		char* cached_data =  read_block(set,j);
		if(j<misses_expected && cached_data == NULL){
			printf("Miss de lectura esperado - OK\n");
		}
		else if(j>=misses_expected && compare_data(cached_data,data+j*block_size,block_size) == 0){
			printf("Hit - OK\n");
		}
		else{
			printf("Error en la lectura del bloque#%d\n",j+1);
			result = -1;
		}
	}
	if(result == -1) printf("Resultado: Fallo\n\n");
	else printf("Resultado: OK\n\n");
	return;

}

int main(){

	char* data = "ABCDEFGHIJKMNLOP";
	//Caso: 2 misses / 2 hits
	testWRBlocks(2,4,data,4);

	//Caso: ways > bloques cacheados -> deberian ser todos hits
	testWRBlocks(6,4,data,4);

	//Caso: 1 miss / 3 hits (unica via -> direct mapped)
	testWRBlocks(1,4,data,4);
	return 0;
}