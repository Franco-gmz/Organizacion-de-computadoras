#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include "../lib/tools.h"


int main(int argc, char **argv){

	char help_message[] = "Uso:\n\
\tautcel -h\n\
\tautcel -V\n\
\tautcel R N inputfile [-o outputprefix]\n\
Opciones\n\
\t-h,--help\t\tImprime este mensaje.\n\
\t-V,--version\t\tDa la version del programa\n\
\t-o\t\tPrefijo de los archivos de salida.\n\
Ejemplos:\n\
\tautcel 30 80 inicial -o evolucion\n\
\tCalcula la evolucion del automata \"Regla 30\",\n\
\ten un mundo unidimensional de 80 celdas, por 80 iteraciones. \n\
\tEl archivo de salida se llamara evolucion.pbm.\n\
\tSi no se da un prefijo para los archivos de salida,\n\
\tEl prefijo sera el nombre del archivo de entrada.\n";
	char version_message[] = "autcel V1.0\n";
	char* output;
	char available_options[] = "Vho";
	int option;
	int no_output_prefix = 1;

	while((option = getopt(argc,argv,available_options)) != -1){
		switch(option){
			case 'V':
				printf("%s",version_message);
				exit(EXIT_SUCCESS);
				break;
			case 'h':
				printf("%s",help_message);
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
			default:
				printf("default\n");
				printf("%s",argv[optind]);
				break;
		}

	}
	if (argv[optind] == NULL || argv[optind + 1] == NULL || argv[optind + 2] == NULL){
		printf("Debe especificar R, N y el archivo de estado inicial\n");
		printf("%s",help_message);
		exit(EXIT_FAILURE);
	}

	unsigned char rule = (unsigned char) atoi(argv[optind]);
	unsigned int n = (unsigned int) atoi(argv[optind + 1]);
	if(n == 0) {
		fprintf(stderr, "El numero de celdas no puede ser 0\n");
		return 1;
	}	
    char* input_file_name = argv[optind +2];

    char output_file_name[strlen(no_output_prefix ? input_file_name : output) + 5];
    if(no_output_prefix == 1) {
    	strcpy(output_file_name, input_file_name);
    }
   	else strcpy(output_file_name, output);
	strcat(output_file_name, ".pbm");

	

	FILE* input_file = fopen(input_file_name,"r");
	if(input_file == NULL) {
		fprintf(stderr, "Error al abrir el archivo %s\n", input_file_name);
		return 1;
	}

	FILE* output_file = fopen(output_file_name,"w");
	if(output_file == NULL) {
		fprintf(stderr, "Error al abrir el archivo %s\n", output_file_name);
		fclose(input_file);
		return 1;
	}

	unsigned char* output_cells = create_cells(n);
	if(output_cells == NULL) {
		fprintf(stderr, "Error al pedir memoria\n");
		fclose(input_file);
		fclose(output_file);
		return 1;
	}

	puts("Leyendo estado inicial...");
	if(read_initial_state(input_file, output_cells, n) != 0) {
		fprintf(stderr, "Error: el archivo %s no cumple con el formato\n", input_file_name);
		fclose(input_file);
		fclose(output_file);
		free(output_cells);
		return 1;
	}

	compute_states(output_cells, rule, n);

	printf("Grabando %s\n", output_file_name);
	write_pbm_file(output_file, output_cells, n);

	free(output_cells);
	fclose(input_file);
	fclose(output_file);

	puts("Listo");	
	return 0;
}
