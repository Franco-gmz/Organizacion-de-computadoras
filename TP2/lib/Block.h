typedef struct{
	
	int size;
	int valid;
	char* tag;
	char* data;

}Block;

extern Block new_block(int size, char* tag);

extern void free_block(Block block);

extern void write_byte(Block block,int byte, char data);

extern char* read_byte(Block block,int byte);

extern char* read_block(Block block);