#ifndef __BLOCK__
#define __BLOCK__

typedef struct{
	
	int size;
	int valid;
	char* data;

}Block;

extern Block new_block(int size);

extern void free_block(Block block);

extern void write_byte(Block block,int byte, char data);

extern char* read_byte(Block block,int byte);

extern char* read_block(Block block);

#endif