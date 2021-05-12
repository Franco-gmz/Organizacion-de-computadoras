#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

unsigned char proximo(unsigned char*,unsigned int,unsigned int,unsigned char,unsigned int);

unsigned char proximo(unsigned char* a,unsigned int i,unsigned int j,unsigned char regla,unsigned int N) {

    unsigned char center = *(a + N*i + j); //input[i][j]

    unsigned char left;
    if(j == 0)
        left = *(a + N*i + N-1);    //input[i][N-1]
    else 
        left = *(a + N*i + j-1);   //input[i][j-1]

    unsigned char right;
    if(j == N-1)
        right = *(a + N*i + 0);     //input[i][0]
    else 
        right = *(a + N*i + j+1);  //input[i][j+1]

    unsigned char indice = (left<<2)|(center<<1)|right; // 0 0 0 0 0 L C R
    
    return (regla>>indice)&1;   //regla[indice]

}


int main(int argc, char **argv){

	char helpMessage[] = "Uso:\n\tautcel -h\n\tautcel -V\n\tautcel R N inputfile [-o outputprefix]\nOpciones\n\t-V,--version\t\tVer version de programa\n\t-h,--help\t\tImprime este mensaje.\n\t-o,--output\t\tPrefijo del archivo de salida.\n";
	char versionMessage[] = "autcel V1.0\n";
	FILE *outputFile;
	char availableOptions[] = "Vho";
	int oFlag = 0;
	int option;
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
				oFlag = 1;
				if(*argv[optind]=='\0'){
					fprintf(stderr, "%s\n", "Nombre archivo salida vacio -o.");
				}
				if(strcmp(argv[optind],"-")==0){
					outputFile = stdout;
				}
				else{
					outputFile = fopen(argv[optind],"wb");
					if (outputFile == NULL){
						fprintf(stderr, "Error al abrir el archivo -o: %s\n", strerror(errno));
						exit(EXIT_FAILURE);
					}
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
		unsigned char input[5][5] = {

		    {0, 0, 0, 1, 0},
		    {0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0},
		    {0, 0, 0, 0, 0}

		};

		unsigned char expected_output[5][5] = {

		    {0, 0, 0, 1, 0},
		    {0, 0, 1, 1, 1},
		    {1, 1, 1, 0, 0},
		    {1, 0, 0, 1, 1},
		    {0, 1, 1, 1, 0}

		};

		int errors = 0;
		unsigned int n = 5;
		unsigned char rule = 30;
		unsigned char* ptr = &input[0][0];


		printf("\n\n");
		for(unsigned int i=0;i<4;i++){
		    for(unsigned int j=0;j<5;j++){
		        
		        input[i+1][j] = proximo(ptr,i,j,rule,n);
		        if(input[i+1][j] == expected_output[i+1][j]){
		            printf("(%d,%d) EXITO\n",i,j);
		        }
		        else{
		            printf("(%d,%d) FALLO\n",i,j);
		            errors+=1;
		        }
		        printf("\tEstado esperado: %d\n",expected_output[i+1][j]);
		        printf("\tEstado calculado: %d\n\n",input[i+1][j]);
		    }
		}
		printf("Errores totales:%d\n\n",errors);
		return 0;

	
	
	} 
	if(!oFlag) outputFile = stdout;
	return 0;
}
