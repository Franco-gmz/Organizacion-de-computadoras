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
	
	puts("Leyendo estado inicial...");
	if(read_initial_state(input_file, output_cells, n) != 0) {
		fprintf(stderr, "Error: el archivo %s no cumple con el formato\n", input);
		return 1;
	}

	compute_states(output_cells, rule, n);

	printf("Grabando %s\n", output);
	write_pbm_file(output_file, output_cells, n);

	free(output_cells);
	fclose(input_file);
	fclose(output_file);

	puts("Listo");
	return 0;
}
