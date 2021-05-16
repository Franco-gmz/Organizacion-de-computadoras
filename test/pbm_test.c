#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Precondicion: todos los archivos en el directorio deben ser .pbm
int file_select(const struct dirent* entry);

int main(int argc, char* argv[]){

	struct dirent** files;
	int n;

	n = scandir("../files/output",&files,file_select,alphasort);
	if(n<0) perror("scandir");
	else{
		int i = n;
		for(int i=0;i<n;i++){
			printf("\n%s\n",files[i]->d_name);
		
		}
		for(int i=0;i<n;i++){
			free(files[i]);
		}

		free(files);
	}

	return 0;
}


int file_select(const struct dirent* entry){

	if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0){
		return 0;
	}
	else return 1;
}
