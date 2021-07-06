#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"
#include "mem.h"
#include "command.h"


int execute_command(char* cmd, FILE* output_file) {
	if(strcmp(cmd, "init\n") == 0) {
		execute_init_command();
		return 0;
	}

	if(strcmp(cmd, "MR\n") == 0) {
		execute_mr_command(output_file);
		return 0;
	}
	switch(cmd[0]) {
		case 'R':
			return execute_read_command(cmd, output_file);
		case 'W':
			return execute_write_command(cmd, output_file);
	}

	return 1;
}

void execute_init_command() {
	free_cache();
	init();
	init_mem();
}

void execute_mr_command(FILE* output_file) {
	fprintf(output_file, "%d\n", get_miss_rate());
}

int execute_read_command(char* cmd, FILE* output_file) {
	if(cmd[1] != ' ' || !isdigit(cmd[2]))
		return 1;
	int address = atoi(cmd+2);
	if(address >= MEMSIZE)
		return 1;
	char hit = 0;
	char byte = read_byte(address, &hit);
	fprintf(output_file, "%d\n", byte);
	fprintf(output_file, "%s\n", hit == 0 ? "MISS" : "HIT");
	return 0;
}

int execute_write_command(char* cmd, FILE* output_file) {
	if(cmd[1] != ' ' || !isdigit(cmd[2]))
		return 1;

	size_t i = 3;
	for(; cmd[i] != ','; i++)
		if(cmd[i] == '\0')
			return 1;

	if(!isdigit(cmd[i+2]))
		return 1;

	int address = atoi(cmd+2);
	if(address >= MEMSIZE)
		return 1;

	int value = atoi(cmd+i+2);
	if(value > 255)
		return 1;

	char hit = write_byte(address, (char)value);
	fprintf(output_file, "%s\n", hit == 0 ? "MISS" : "HIT");
	return 0;
}