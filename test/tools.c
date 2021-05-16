#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print_cells(unsigned char* cells, unsigned int n){

	printf("\n\n");
	for(int i=0;i<n;i++){
		for(int j=i*n;j<i*n+n;j++){
			printf("%u",cells[j]);
		}
		printf("\n");
	}
	printf("\n\n");
	return;
}

unsigned char* create_cells(unsigned int n){

	unsigned char *cells = malloc(sizeof(unsigned char)*n*n);

	return cells;
}

