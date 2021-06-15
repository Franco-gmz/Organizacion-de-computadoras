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

extern void write_byte(Block* block,int byte, char data);

extern char read_byte(Block* block,int byte);

extern char* read_block(Block* block);

extern  void write_block(Block* block,char* data);

#endif