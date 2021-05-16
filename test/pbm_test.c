#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define EQUALS 0

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

//Precondicion: todos los archivos en el directorio deben ser .pbm
int file_select(const struct dirent* entry);

int pbm_cmp(FILE* file_1, FILE* file_2);

void run_test(struct dirent** files,int n,char* route);

int main(int argc, char* argv[]){

	struct dirent** files;
	int n;
	char* route = "../files/output/";

	n = scandir(route,&files,file_select,alphasort);
	if(n<0) perror("scandir");
	else{
		
		run_test(files,n,route);

		for(int i=0;i<n;i++){
			free(files[i]);
		}

		free(files);
	}

	return 0;
}

void run_test(struct dirent** files, int n,char* route){
	int passed = 0;
	int errors = 0;
	int not_open = 0;
	printf("\n\nRunning test...  %d files\n\n",n);
	sleep(1);
	for(int i=0;i<n;i=i+2){
		char* name_1 = malloc(strlen(route)+strlen(files[i]->d_name));
		char* name_2 = malloc(strlen(route)+strlen(files[i+1]->d_name));
		strcpy(name_1,route);
		strcat(name_1,files[i]->d_name);
		strcpy(name_2,route);
		strcat(name_2,files[i+1]->d_name);
		if(name_1 == NULL || name_2 == NULL){
			printf(RED "\nError with malloc\n"RESET);
			exit(-1);
		}
		FILE* file_1 = fopen(name_1,"r");
		FILE* file_2 = fopen(name_2,"r");
		
		if(file_1==NULL || file_2==NULL){
			printf(RED"Could not open files\n"RESET);
			not_open++;
		}
		else{
			if(pbm_cmp(file_1,file_2)== EQUALS){
				printf(GREEN "[PASS]" RESET);
				passed++;
			}
			else{
				printf(RED"[ERROR]"RESET);
				errors++;
			}
			printf(": %s - %s \n",files[i]->d_name,files[i+1]->d_name);
			sleep(1);
		
			free(name_1);
			free(name_2);
		}
			if(file_1!=NULL) fclose(file_1);
			if(file_2!=NULL) fclose(file_2);

	}
	printf(GREEN "\nPASSED:%d" RESET ,passed);
	printf(RED "\tERRORS:%d" RESET,errors);
	printf(RED "\tFILES NOT OPEN:%d\n\n"RESET,not_open);
	return;
}

int pbm_cmp(FILE* file_1, FILE* file_2){
	
	char char_1;
	char char_2;

	while(!feof(file_1) && !feof(file_2)){
		char_1 = fgetc(file_1);
		char_2 = fgetc(file_2);
		if(char_1 != char_2) return 1;
	}

	return 0;
}


int file_select(const struct dirent* entry){

	if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0){
		return 0;
	}
	else return 1;
}
