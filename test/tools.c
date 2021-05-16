#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../lib/proximo.h"

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

void write_pbm_file(FILE* output_file, unsigned char* cells, unsigned int n){

	fprintf(output_file, "P1\n%d %d\n", n, n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			fputc(cells[n*i + j]+48, output_file);
		}
		fputc('\n',output_file);
	}
}

void read_initial_state(FILE* input_file, unsigned char* output_cells, unsigned int n){

	for(int j=0;j<n;j++){
		unsigned char caracter = fgetc(input_file);
		if(caracter == 48) output_cells[j] = 0;
		else output_cells[j] = 1;
	}
}

void compute_states(unsigned char* output_cells, unsigned char rule, unsigned int n){

	for(int i=0;i<n-1;i++){
		for(int j=0;j<n;j++){
			output_cells[n*(i+1) + j] = proximo(output_cells,i,j,rule,n);
		}
	}
}