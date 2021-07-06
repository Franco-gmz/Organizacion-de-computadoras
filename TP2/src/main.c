#include "../lib/cache.h"
#include "../lib/mem.h"
#include "../lib/command.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

#define LINE_MAX 15

int ways;
int blocksize;
int cachesize;
int sets;
int blocks;
int memsize; 
Block* cache;
char* mem;
unsigned long long time;
int accesses;
int misses;

void parse_options(int argc, char **argv, char** input_file_name, char** output_file_name);

int main(int argc, char **argv){
	
	char* output_file_name;
	char* input_file_name;

	parse_options(argc, argv, &input_file_name, &output_file_name);

	FILE* input_file = fopen(input_file_name,"r");
	if(input_file == NULL) {
		fprintf(stderr, "Error al abrir el archivo %s\n", input_file_name);
		return 1;
	}
	
	FILE* output_file;
	if(output_file_name != NULL) {
		output_file = fopen(output_file_name,"w");
		if(output_file == NULL) {
			fprintf(stderr, "Error al abrir el archivo %s\n", output_file_name);
			fclose(input_file);
			return 1;
		}	
	}
	else output_file = stdout;

	sets = cachesize/(blocksize*ways);
	blocks = cachesize/blocksize;
	memsize = 64*1024;

	init();
	init_mem();

	char buf[LINE_MAX];
	while(fgets(buf, LINE_MAX, input_file)) {
		if(execute_command(buf, output_file) == 1){
			fprintf(stderr, "Error al leer comando: %s\n", buf);
			break;
		}
	}
	
	free_cache();
	free_mem();

	fclose(input_file);
	if(output_file != stdin) {
		fclose(output_file);
	}

	return 0;
}

void parse_options(int argc, char **argv, char** input_file_name, char** output_file_name) {
	static struct option long_options[] = {
			{"version",no_argument, 0, 'v' },
			{"help",no_argument, 0,'h' },
			{"ways",required_argument,0,'w'},
			{"cs",required_argument,0,'c' },
			{"bs",required_argument,0,'b' },
			{"blocksize",required_argument,0,'b' },
			{"cachesize",required_argument,0,'c' },
			{0,0,0,0}
		};
		char mensaje[] = 
		"\tUsage:\n\
		\tp2 -h\n\
		\tp2 -V\n\
		\ttp2 options archivo\n\
		Options:\n\
		\t-h,--help\t\tImprime ayuda.\n\
		\t-v,--version\t\tVersion del programa.\n\
		\t-o --output\t\tArchivo de salida.\n\
		\t-w, --ways\t\tCantidad de vı́as.\n\
		\t-cs, --cachesize \t\tTamaño del caché en kilobytes..\n\
		\t-bs --blocksize \t\tTamaño de bloque en bytes.\n\
		Examples:\n\
		\ttp2 -w 4 -cs 8 -bs 16 prueba1.mem\n";
		char version[] = "tp2 V1.0\n";
		char* output = NULL;
		char opciones[] = "vho:w:c:b:";
		int opcion;
		int long_index =0;

		while((opcion = getopt_long_only(argc,argv,opciones,long_options, &long_index)) != -1){
			switch(opcion){
				case 'v':
					printf("%s",version);
					exit(EXIT_SUCCESS);
					break;
				case 'h':
					printf("%s",mensaje);
					exit(EXIT_SUCCESS);
					break;
				case 'o':
					if(optarg == NULL || strcmp(optarg,"\0")==0){
						printf("No se ingreso ningun nombre de archivo \n");
						output = "default";
					}else if(strcmp(optarg,"-")==0){
						printf("No se ingreso ningun nombre de archivo \n");
						output = "default";
					}else{
						output= optarg;
					}
					break;
				case 'b':
					blocksize=(unsigned int) atoi(optarg);
					break;
				case 'c':
					cachesize= 1024*(unsigned int) atoi(optarg);
					break;
				case 'w':
					ways=(unsigned int) atoi(optarg);
					break;
				default:
					printf("default\n");
					printf("%s",argv[long_index]);
					break;
			}

		}

		*input_file_name=argv[optind];

		if (*input_file_name == NULL || strcmp(*input_file_name, "") == 0){
			printf("Debe suministrar un archivo de entrada\n");
			printf("%s",mensaje);
			exit(EXIT_FAILURE);
		}
		if(optind <= 6){
			printf("ERROR:Debe especificar cantidad de vías, tamaño de la cache, tamaño del bloque y archivo de entrada\n");
			printf("%s",mensaje);
			exit(EXIT_FAILURE);
		}

		*output_file_name=output;
}