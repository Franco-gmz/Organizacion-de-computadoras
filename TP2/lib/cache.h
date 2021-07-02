#ifndef __CACHE__
#define __CACHE__

#include "Block.h"

extern Block* cache;
extern int cachesize;
extern int blocksize;
extern int ways;
extern int sets; //cachesize/(blocksize*ways)
extern int blocks;
extern unsigned long long time;

void init();
unsigned int find_set(int address);
unsigned int find_earliest(int setnum);
void read_block(int blocknum);
void write_byte_tomem(int address, char value);
char read_byte(int address, char *hit);
char write_byte(int address, char value, char *hit);
char get_miss_rate();
void free_cache();

#endif