#ifndef __BLOCK__
#define __BLOCK__

typedef struct block Block;
struct block{
	
	int tag;
	int valid;
	unsigned long long time;
	char* data;
};

extern void init_block(Block* block, int size);

extern void free_block(Block* block);

#endif