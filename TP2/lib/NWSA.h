typedef struct{

	Set** sets;
	int set_number;
	int blocks_by_set;
	int block_size;

}NWSA;

extern NWSA new_NWSA(int sets, int blocks_by_set, int block_size);

extern void free_NWSA(NWSA nwsa);