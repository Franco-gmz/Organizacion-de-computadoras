#include<stdio.h>
#include<stdlib.h>
#include"./tools.h"

int main(int argc,char* argv[]){

	char* input = argv[3];
	char* output = argv[4];
	unsigned char rule = (unsigned char) atoi(argv[1]);
	unsigned int n = atoi(argv[2]);

	FILE* input_file = fopen(input,"r");
	FILE* output_file = fopen(output,"w");

	unsigned char* output_cells = create_cells(n);
	
	read_initial_state(input_file, output_cells, n);

	compute_states(output_cells, rule, n);

	write_pbm_file(output_file, output_cells, n);

	free(output_cells);
	fclose(input_file);
	fclose(output_file);
	return 0;
}
