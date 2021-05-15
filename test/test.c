#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../lib/proximo.h"
#include"tools.h"

int main(int argc, char* argv[]){
	
	unsigned char rule = (unsigned char) atoi(argv[1]);
	unsigned int n = atoi(argv[2]);
	
	FILE* input = fopen(argv[3],"r");
	FILE* output = fopen(argv[4],"w");

	if(!input || !output) exit(-1);
	
	unsigned char** cells = create_cells(n);
	
	for(int i=0;i<n;i++){
	        unsigned char caracter = fgetc(input);
		if(caracter == 48) cells[0][i]=0;
	       	else cells[0][i]=1;
	}

	for(int i=0;i<n-1;i++){
		for(int j=0;j<n;j++){
			cells[i+1][j] = proximo(&cells[0][0],i,j,rule,n);
		}
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			fputc(cells[i][j]+48,output);
		}
		fputc('\n',output);
	}

	free_cells(cells,n);
	fclose(input);
	fclose(output);
	return 0 ;
}
