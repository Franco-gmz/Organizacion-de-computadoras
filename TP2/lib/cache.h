#ifndef __CACHE__
#define __CACHE__

#include "Set.h"

extern Set* cache;

void init();
unsigned int find_set(int address);
unsigned int find_earliest(int setnum);
void read_block(int blocknum);
void write_byte_tomem(int address, char *hit);
char read_byte(int address, char *hit);
char write_byte(int address, char value, char *hit);
char get_miss_rate();

#endif