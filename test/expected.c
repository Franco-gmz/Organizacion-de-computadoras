#include<stdio.h>
#include<stdlib.h>
#include"../lib/proximo.h"
#include"./tools.h"

int main(int argc,char* argv[]){

	char* input = argv[3];
	char* output = argv[4];
	unsigned char rule = (unsigned char) atoi(argv[1]);
	unsigned int n = atoi(argv[2]);

	FILE* input_file = fopen(input,"r");
	FILE* output_file = fopen(output,"w");

	unsigned char** output_cells = create_cells(n);
	
	for(int i=0;i<n;i++){
		unsigned char caracter = fgetc(input_file);
		if(caracter == 48) output_cells[0][i] = 0;
		else output_cells[0][i] = 1;
	}

	unsigned char* ptr = &output_cells[0][0];

	for(int i=0;i<n-1;i++){
		for(int j=0;j<n;j++){
			output_cells[i+1][j] = proximo(ptr,i,j,rule,n);
		}
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			fputc(output_cells[i][j]+48,output_file);
		}
		fputc('\n',output_file);
	}

	free_cells(output_cells,n);
	fclose(input_file);
	fclose(output_file);
	return 0;
}
