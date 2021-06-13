typedef struct{
	
	int size;
	int valid;
	char* tag;
	char* data;

}Block;

extern Block new_block(int size, char* tag);

extern void free_block(Block block);