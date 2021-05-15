#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print_cells(unsigned char** cells, unsigned int n){

	printf("\n\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("\t%u",cells[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	return;
}

unsigned char** create_cells(unsigned int n){

	unsigned char** cells = malloc(sizeof(char*)*n);
	for(int i=0;i<n;i++){
		cells[i] = malloc(sizeof(char*)*n);
	}
	return cells;
}

void free_cells(unsigned char** cells, unsigned int n){
	for(int i=0;i<n;i++){
		free(cells[i]);
	}
	free(cells);
	return;
}
