#ifndef _TOOLS_
#define _TOOLS_

void print_cells(unsigned char* cells,unsigned int n);

unsigned char* create_cells(unsigned int n);

void write_pbm_file(FILE* output_file, unsigned char* cells, unsigned int n);
void read_initial_state(FILE* input_file, unsigned char* output_cells, unsigned int n);
void compute_states(unsigned char* output_cells, unsigned char rule, unsigned int n);

#endif
