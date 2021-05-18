#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include "./tools.h"


int test(unsigned char rule, unsigned int n, char* input, char* output){

	FILE* input_file = fopen(input,"r");
	if(input_file == NULL) {
		fprintf(stderr, "Error al abrir el archivo %s\n", input);
		return 1;
	}
	FILE* output_file = fopen(output,"w");
	if(output_file == NULL) {
		fprintf(stderr, "Error al abrir el archivo %s\n", output);
		fclose(input_file);
		return 1;
	}

	unsigned char* output_cells = create_cells(n);
	
	puts("Leyendo estado inicial...");
	if(read_initial_state(input_file, output_cells, n) != 0) {
		fprintf(stderr, "Error: el archivo %s no cumple con el formato\n", input);
		return 1;
	}

	compute_states(output_cells, rule, n);

	printf("Grabando %s\n", output);
	write_pbm_file(output_file, output_cells, n);

	free(output_cells);
	fclose(input_file);
	fclose(output_file);

	puts("Listo");
	return 0;
}


int main(int argc, char **argv){

	char helpMessage[] = "Uso:\n\
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
	char versionMessage[] = "autcel V1.0\n";
	char* outputFile;
	char availableOptions[] = "Vho";
	int option;
	int no_output_prefix = 1;

	while((option = getopt(argc,argv,availableOptions)) != -1){
		switch(option){
			case 'V':
				printf("%s",versionMessage);
				exit(EXIT_SUCCESS);
				break;
			case 'h':
				printf("%s",helpMessage);
				exit(EXIT_SUCCESS);
				break;
			case 'o':
				no_output_prefix = 0;
				if((*argv)[optind]=='\0' || argv[optind] == NULL){
					printf("No se ingreso ningun nombre de archivo, uso default: \n");
					outputFile = "default";
				}else if(strcmp(argv[optind],"-")==0){
					printf("No se ingreso ningun nombre de archivo \n");
					outputFile = "default";
				}else{
					outputFile= argv[optind];
					printf("opcion archivo ingresada: %s \n", outputFile );
				}
				break;
			default:
				printf("default\n");
				printf("%s",argv[optind]);
				break;
		}

	}
	if (argv[optind] == NULL || argv[optind + 1] == NULL) {
		printf("Debe especificar R, N y el archivo de estado inicial\n");
		exit(EXIT_FAILURE);
	}else{

		unsigned char rule = (unsigned char) atoi(argv[optind]);
		unsigned int n = (unsigned int) atoi(argv[optind + 1]);	
	    char* input = argv[optind +2];

	    char output[strlen(no_output_prefix ? input : outputFile) + 5];
	    if(no_output_prefix == 1) {
	    	strcpy(output, input);
	    }
	   	else strcpy(output, outputFile);
		strcat(output, ".pbm");

		test(rule, n, input, output);
	} 
	return 0;
}
