#ifndef __BLOCK__
#define __BLOCK__

typedef struct block Block;
struct block{
	
	int size;
	int tag;
	int valid;
	char* data;
	Block* next;

};

extern Block* new_block(int size);

extern void free_block(Block* block);

#endif