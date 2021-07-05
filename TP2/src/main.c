#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>



int main(int argc, char **argv){
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
	char* output;
	char opciones[] = "vho:w:c:b:";
	int opcion;
	int no_output_prefix = 1;
	int long_index =0;

	unsigned int cant_vias=0;
	unsigned int tam_cache=0;
	unsigned int tam_bloque=0;

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
				no_output_prefix = 0;
				if((*argv)[optind]=='\0' || argv[optind] == NULL){
					printf("No se ingreso ningun nombre de archivo \n");
					output = "default";
				}else if(strcmp(argv[optind],"-")==0){
					printf("No se ingreso ningun nombre de archivo \n");
					output = "default";
				}else{
					output= argv[optind];
				}
				break;
			case 'b':
				tam_bloque=(unsigned int) atoi(optarg);
				break;
			case 'c':
				tam_cache=(unsigned int) atoi(optarg);
				break;
			case 'w':
				cant_vias=(unsigned int) atoi(optarg);
				break;
			default:
				printf("default\n");
				printf("%s",argv[long_index]);
				break;
		}

	}
	char* archivo_entrada=argv[optind];
	if (archivo_entrada == NULL || archivo_entrada == ""){
		printf("Debe suministrar un archivo de entrada\n");
		printf("%s",mensaje);
		exit(EXIT_FAILURE);
	}
	if(optind <= 6){
		printf("ERROR:Debe especificar cantidad de vías, tamaño de la cache, tamaño del bloque y archivo de entrada\n");
		printf("%s",mensaje);
		exit(EXIT_FAILURE);
	}
	return 0;
}