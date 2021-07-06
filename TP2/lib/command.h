#ifndef __COMMAND__
#define __COMMAND__

#include <stdio.h>

int execute_command(char* cmd, FILE* output_file);
void execute_init_command();
void execute_mr_command(FILE* output_file);
int execute_read_command(char* cmd, FILE* output_file);
int execute_write_command(char* cmd, FILE* output_file);

#endif